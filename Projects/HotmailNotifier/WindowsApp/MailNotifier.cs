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
            NotifyLight(Messenger.get_UnreadEmailCount(MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX) > 0);

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
                NotifyLight(amount > 0);
        }

        private void NotifyLight(bool ShowGreen)
        {
            char[] buffer = new char[1];
            buffer[0] = ShowGreen ? '0' : '1';

            try
            {
                serSerialPort.Open();
                serSerialPort.Write(buffer, 0, 1);
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

            for (int i = 0; i < 5; i++)
            {
                NotifyLight(true);
                System.Threading.Thread.Sleep(20);
                NotifyLight(false);
                System.Threading.Thread.Sleep(20);
            }

            NotifyLight(Messenger.get_UnreadEmailCount(MessengerAPI.MUAFOLDER.MUAFOLDER_INBOX) > 0);
        }

        private void btnMinimize_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}
