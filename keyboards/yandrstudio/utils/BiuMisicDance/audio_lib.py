#!/usr/bin/env python3
"""
/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
"""
# import argparse
import queue
import sys
from scipy.fftpack import fft,ifft
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np
import math
import sounddevice as sd


def get_frq_sp_frq(num, startFrq=25, endFrq=19000):
    rate = (endFrq/startFrq)**(1/num)
    sample_index = np.linspace(0, num, num+1) # 0, 1, 2, 3, ..., n
    sample_frq = startFrq*(rate**sample_index)
    sample_frq_mean = (sample_frq[:-1] + sample_frq[1:]) / 2
    return sample_frq_mean.astype(np.int)

def get_frq_sp_point(num, samplerate=44100, length=2048, startFrq=25, endFrq=19000):
    sp_frq = get_frq_sp_frq(num, startFrq, endFrq)
    sp_index = np.around((sp_frq*(length-1)/samplerate))
    return [np.clip(sp_index-2, 0, length/2-1).astype(np.int), \
            np.clip(sp_index-1, 0, length/2-1).astype(np.int), \
            sp_index.astype(np.int), \
            np.clip(sp_index+1, 0, length/2-1).astype(np.int), \
            np.clip(sp_index+2, 0, length/2-1).astype(np.int)]


def int_or_str(text):
    """Helper function for argument parsing."""
    try:
        return int(text)
    except ValueError:
        return text

print(sd.query_devices())



class audioCfg:
    def __init__(self, samplerate=44100, window=1000, downsample=10, channels=[1], device=1):
        self.samplerate = samplerate
        self.window = window
        self.downsample = downsample
        # self.length = int(self.window * self.samplerate / (1000 * self.downsample))
        self.length = 2048 # directly
        self.blocksize = self.length

        self.channels = channels
        self.device = device


class kbRgbCfg:
    def __init__(self, row=5, col=10, col_vis=True):
        self.rgb_matrix_row = row
        self.rgb_matrix_col = col
        self.is_col_visual = col_vis



class pltCfg:
    def __init__(self, interval=3):
        self.interval = interval

power_dict = {0: 0.001,\
              1: 0.01,\
              2: 0.02,\
              3: 0.03,\
              4: 0.05,\
              5: 0.2,\
              6: 0.6,\
              7: 0.7,\
              8: 1,\
              9: 2,\
              10: 1e8}



def sigmoid(x):
    return 2 / (1 + np.exp(-x))-1


def soft_max(z, tau=1.0):
    return np.exp(z/tau) / np.sum(np.exp(z/tau), axis=0)

def genPower2(data, rgb_power_list, fft_samp_indexs):
    power_list_show = 0.1*data[fft_samp_indexs[0]] + 0.2*data[fft_samp_indexs[1]] + 0.4*data[fft_samp_indexs[2]] + 0.2*data[fft_samp_indexs[3]] + 0.1*data[fft_samp_indexs[4]]
    print('to max: ', power_list_show/(1e-8+power_list_show.max())*10)
    print('log sum:', np.log1p(power_list_show.sum()))
    print('log:', np.log1p(power_list_show))
    power_list_kb = []
    for i in power_list_show:
        for k in power_dict.keys():
            if (i < power_dict[k]):
                power_list_kb.append(k)
                break
    power_list_kb = np.roll(np.array(power_list_kb), int(len(fft_samp_indexs)/4))
    print('power dict:', power_list_kb)

def get_power(num, rgb_power_list, fft_samp_indexs):
    while True:
        try:
            data = q.get_nowait()
        except queue.Empty:
            continue
            # return np.zeros(num).astype(np.int)
        shift = len(data)
        data = np.array(data).reshape(shift)
        # print('data mean:', data.mean())
        data[(data>-2.5e-4)&(data<2.5e-4)] = 0
        # print('data mean after:', data.mean())
        data = np.abs(fft(data, shift))[:int(shift/2)]
        # line.set_ydata(data/(math.sqrt(shift/2)))
        power_list_show = 0.1*data[fft_samp_indexs[0]] + 0.2*data[fft_samp_indexs[1]] + 0.4*data[fft_samp_indexs[2]] + 0.2*data[fft_samp_indexs[3]] + 0.1*data[fft_samp_indexs[4]]
        # print('to max: ', power_list_show/(1e-8+power_list_show.max())*10)
        # print('log sum:', np.log1p(power_list_show.sum()))
        # print('log:', np.log1p(power_list_show))
        power_list_kb = []
        for i in power_list_show:
            for k in power_dict.keys():
                if (i < power_dict[k]):
                    power_list_kb.append(k)
                    break
        power_list_kb = np.roll(np.array(power_list_kb), int(len(fft_samp_indexs)/4))
        print('power dict:', power_list_kb)
        print(q.qsize())
        return power_list_kb


## run data init
q = queue.Queue()
def audio_callback(indata, frames, time, status):
    """This is called (from a separate thread) for each audio block."""
    if status:
        print(status, file=sys.stderr)
    # Fancy indexing with mapping creates a (necessary!) copy:
    # print('audio input shape:', indata.shape)
    q.put(indata.reshape(-1))


def update_plot(frame, rgb_power_list, fft_samp_indexs, line):
    """This is called by matplotlib for each plot update.

    Typically, audio callbacks happen more frequently than plot updates,
    therefore the queue tends to contain multiple blocks of audio data.

    """
    # while True:
    try:
        data = q.get()
    except queue.Empty:
        return
    shift = len(data)
    # plotdata = np.roll(plotdata, -shift, axis=0)
    data = np.array(data)
    data = data.reshape(shift)
    # print('data shape:', data.shape)
    print('data mean:', data.mean())
    data[(data>-2.5e-4)&(data<2.5e-4)] = 0
    print('data mean after:', data.mean())
    data = np.abs(fft(data, shift))[:int(shift/2)]
    line.set_ydata(data/(math.sqrt(shift/2)))
    genPower2(data, rgb_power_list, fft_samp_indexs)
    return [line]





def start_audio_dance(row=5, col=10, is_col_visual=True, dev_idx=None):

    ## some pre init cfg
    audio_cfg = audioCfg()
    kb_rgb_cfg = kbRgbCfg(row, col, is_col_visual)
    plt_cfg = pltCfg()

    ## post init
    if (kb_rgb_cfg.is_col_visual):
        rgb_frq_num = kb_rgb_cfg.rgb_matrix_col
        rgb_power_list = np.zeros(kb_rgb_cfg.rgb_matrix_col)
    else:
        rgb_frq_num = kb_rgb_cfg.rgb_matrix_row
        rgb_power_list = np.zeros(kb_rgb_cfg.rgb_matrix_row)


    try:
        if audio_cfg.samplerate is None:
            device_info = sd.query_devices(1, 'input')
            audio_cfg.samplerate = device_info['default_samplerate']

        fftlx = np.linspace(0, audio_cfg.samplerate, audio_cfg.length)[:int(audio_cfg.length/2)]
        fft_samp_indexs = get_frq_sp_point(rgb_frq_num, samplerate=audio_cfg.samplerate, length=audio_cfg.length, startFrq=25, endFrq=19000)
        # plotdata = np.zeros((length, len(args.channels)))[:int(length/2)]
        print("window:", audio_cfg.window)
        print("samplerate:", audio_cfg.samplerate)
        print("downsample", audio_cfg.downsample)
        print("channels:", audio_cfg.channels)
        print("length:", audio_cfg.length)
        # print("plotdataShape:", plotdata.shape)
        print('fft_x shape:', fftlx.shape)

        # fig, ax = plt.subplots()
        # line = ax.semilogx(fftlx, np.zeros(len(fftlx)))[0]
        # if len(audio_cfg.channels) > 1:
        #     ax.legend(['channel {}'.format(c) for c in audio_cfg.channels],
        #             loc='lower left', ncol=len(audio_cfg.channels))
        # ax.axis((1e0, audio_cfg.samplerate, 0, 1))
        # ax.set_yticks([0])
        # ax.yaxis.grid(True)
        # ax.tick_params(bottom=False, top=False, labelbottom=False,
        #                right=False, left=False, labelleft=False)
        # fig.tight_layout(pad=0)
        if (dev_idx is not None):
            stream = sd.InputStream(device=dev_idx,
                channels=max(audio_cfg.channels),blocksize=audio_cfg.length,
                samplerate=audio_cfg.samplerate, callback=audio_callback)
        else:
            stream = sd.InputStream(
                channels=max(audio_cfg.channels),blocksize=audio_cfg.length,
                samplerate=audio_cfg.samplerate, callback=audio_callback)
        # ani = FuncAnimation(fig, update_plot, interval=plt_cfg.interval, blit=True, fargs=(rgb_power_list, fft_samp_indexs, line))
        # with stream:
            # plt.show()
    except Exception as e:
        print(type(e).__name__ + ': ' + str(e))

    return stream, rgb_power_list, fft_samp_indexs

start_audio_dance()
