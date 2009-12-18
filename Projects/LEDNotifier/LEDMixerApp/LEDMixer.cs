using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LEDMixer
{
    public partial class LEDMixer : Form
    {
        private const int LIGHT_MAX = 0x1F;
        
        public LEDMixer()
        {
            InitializeComponent();
        }

        private void LEDMixer_Load(object sender, EventArgs e)
        {
            for (int i = 1; i <= 99; i++)
                cbPort.Items.Add("COM" + i.ToString());

            cbPort.SelectedIndex = 0;

            tbRed.Maximum = LIGHT_MAX;
            tbGreen.Maximum = LIGHT_MAX;
            tbBlue.Maximum = LIGHT_MAX;
        }

        private void tbRed_Scroll(object sender, EventArgs e)
        {
            NotifyLight(tbRed.Value, tbGreen.Value, tbBlue.Value);
        }

        private void tbGreen_Scroll(object sender, EventArgs e)
        {
            NotifyLight(tbRed.Value, tbGreen.Value, tbBlue.Value);
        }

        private void tbBlue_Scroll(object sender, EventArgs e)
        {
            NotifyLight(tbRed.Value, tbGreen.Value, tbBlue.Value);
        }
        
        private void NotifyLight(int Red, int Green, int Blue)
        {
            byte[] buffer = new byte[3];
            buffer[0] = (byte)(0x80 | (Red & LIGHT_MAX));
            buffer[1] = (byte)(0x40 | (Green & LIGHT_MAX));
            buffer[2] = (byte)(0x20 | (Blue & LIGHT_MAX));

            try
            {
                serSerialPort.PortName = cbPort.Text;
                serSerialPort.Open();
                serSerialPort.Write(buffer, 0, buffer.Length);
                serSerialPort.Close();
            }
            catch (Exception e)
            {

            }
        }

        private void cbPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            NotifyLight(tbRed.Value, tbGreen.Value, tbBlue.Value);
        }
    }
}
