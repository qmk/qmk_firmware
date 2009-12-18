using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace TestWinForms
{
    public partial class MailNotifier : Form
    {
        private MessengerAPI.Messenger Messenger;
        private RegistryKey AppRegKey;

        private const int LIGHT_MAX = 0x1F;

        public MailNotifier()
        {
            InitializeComponent();

            Messenger = new MessengerAPI.Messenger();
            AppRegKey = Registry.CurrentUser.CreateSubKey("Software\\MailNotifier");

            for (int i = 1; i < 99; i++)
                cmbComPort.Items.Add("COM" + i.ToString());

            cmbComPort.SelectedIndex = System.Convert.ToInt32(AppRegKey.GetValue("Port", "1")) - 1;
            serSerialPort.PortName = cmbComPort.Text;

            nicoNotifyIcon.Icon = this.Icon;
            nicoNotifyIcon.MouseClick += new MouseEventHandler(TrayIconClick);
        }

        private void MailNotifier_Load(object sender, EventArgs e)
        {
            Messenger.OnUnreadEmailChange += new MessengerAPI.DMessengerEvents_OnUnreadEmailChangeEventHandler(NewEmail);

            bool UnreadMail = (Messenger.get_UnreadEmailCount(MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX) > 0);
            NotifyLight((!UnreadMail ? LIGHT_MAX : 0), (UnreadMail ? LIGHT_MAX : 0), 0);

            Hide();
        }

        private void TrayIconClick(object sender, MouseEventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
        }

        private void NewEmail(MessengerAPI.MUAFOLDER folder, int amount, ref bool enableDefault)
        {
            if (folder == MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX)
            {
                bool UnreadMail = (Messenger.get_UnreadEmailCount(MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX) > 0);
                NotifyLight((!UnreadMail ? LIGHT_MAX : 0), (UnreadMail ? LIGHT_MAX : 0), 0);
            }
        }

        private void NotifyLight(int Red, int Green, int Blue)
        {
            byte[] buffer = new byte[3];
            buffer[0] = (byte)(0x80 | (Red & LIGHT_MAX));
            buffer[1] = (byte)(0x40 | (Green & LIGHT_MAX));
            buffer[2] = (byte)(0x20 | (Blue & LIGHT_MAX));

            try
            {
                serSerialPort.Open();
                serSerialPort.Write(buffer, 0, buffer.Length);
                serSerialPort.Close();
            }
            catch (Exception e)
            {

            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void cmbComPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            AppRegKey.SetValue("Port", cmbComPort.SelectedIndex + 1);
            serSerialPort.PortName = cmbComPort.Text;

            for (int i = 1; i < 10; i++)
            {
                NotifyLight((LIGHT_MAX / i), (LIGHT_MAX / (i * 10)), 0);
                System.Threading.Thread.Sleep(10);
            }

            for (int i = 10; i > 0; i--)
            {
                NotifyLight((LIGHT_MAX / i), (LIGHT_MAX / (i * 10)), 0);
                System.Threading.Thread.Sleep(10);
            }

            bool UnreadMail = (Messenger.get_UnreadEmailCount(MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX) > 0);
            NotifyLight((!UnreadMail ? LIGHT_MAX : 0), (UnreadMail ? LIGHT_MAX : 0), 0);
        }

        private void btnMinimize_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}
