using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace CPUMonitor
{
    public partial class frmCPU : Form
    {
        private RegistryKey AppRegKey;

        private const int LIGHT_MAX = 0x1F;

        public frmCPU()
        {
            InitializeComponent();

            nicoNotifyIcon.Icon = this.Icon;
            nicoNotifyIcon.MouseClick += new MouseEventHandler(TrayIconClick);        
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            AppRegKey = Registry.CurrentUser.CreateSubKey("Software\\CPUMonitor");

            for (int i = 1; i <= 99; i++)
                cmbComPort.Items.Add("COM" + i.ToString());

            cmbComPort.SelectedIndex = System.Convert.ToInt32(AppRegKey.GetValue("Port", "1")) - 1;
            serSerialPort.PortName = cmbComPort.Text;

            Hide();
        }

        private void NotifyLight(int Red, int Green, int Blue)
        {
            byte[] buffer = new byte[3];
            buffer[0] = (byte)(0x80 | (Red & LIGHT_MAX));
            buffer[1] = (byte)(0x40 | (Green & LIGHT_MAX));
            buffer[2] = (byte)(0x20 | (Blue & LIGHT_MAX));

            try
            {
                serSerialPort.PortName = cmbComPort.Text;
                serSerialPort.Open();
                serSerialPort.Write(buffer, 0, buffer.Length);
                serSerialPort.Close();
            }
            catch (Exception e)
            {

            }
        }

        private void tmrCPUTimer_Tick(object sender, EventArgs e)
        {
            float CPUUsage = pcCPUUsage.NextValue();

            int Red = 0;
            int Green = 0;
            int Blue = 0;

            if (CPUUsage < 25)
            {
                Green = (int)((LIGHT_MAX / 25) * CPUUsage);
            }
            else if (CPUUsage < 50)
            {
                Blue = (int)((LIGHT_MAX / 25) * (CPUUsage - 25));
                Green = LIGHT_MAX - Blue;
            }
            else if (CPUUsage < 75)
            {
                Red = (int)((LIGHT_MAX / 25) * (CPUUsage - 50));
                Blue = LIGHT_MAX - Red;
            }
            else
            {
                Red = LIGHT_MAX;
            }

            NotifyLight(Red, Green, Blue);
            lblCPU.Text = ((int)CPUUsage).ToString() + "%";
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnMinimizeToTray_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void TrayIconClick(object sender, MouseEventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
        }

        private void cbPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            AppRegKey.SetValue("Port", cmbComPort.SelectedIndex + 1);
            serSerialPort.PortName = cmbComPort.Text;
        }
    }
}
