namespace CPUMonitor
{
    partial class frmCPU
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serSerialPort = new System.IO.Ports.SerialPort(this.components);
            this.tmrCPUTimer = new System.Windows.Forms.Timer(this.components);
            this.cmbComPort = new System.Windows.Forms.ComboBox();
            this.pcCPUUsage = new System.Diagnostics.PerformanceCounter();
            this.lblCPU = new System.Windows.Forms.Label();
            this.nicoNotifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.btnMinimizeToTray = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pcCPUUsage)).BeginInit();
            this.SuspendLayout();
            // 
            // tmrCPUTimer
            // 
            this.tmrCPUTimer.Enabled = true;
            this.tmrCPUTimer.Interval = 1000;
            this.tmrCPUTimer.Tick += new System.EventHandler(this.tmrCPUTimer_Tick);
            // 
            // cmbComPort
            // 
            this.cmbComPort.FormattingEnabled = true;
            this.cmbComPort.Location = new System.Drawing.Point(48, 12);
            this.cmbComPort.Name = "cmbComPort";
            this.cmbComPort.Size = new System.Drawing.Size(156, 21);
            this.cmbComPort.TabIndex = 0;
            this.cmbComPort.SelectedIndexChanged += new System.EventHandler(this.cbPort_SelectedIndexChanged);
            // 
            // pcCPUUsage
            // 
            this.pcCPUUsage.CategoryName = "Processor";
            this.pcCPUUsage.CounterName = "% Processor Time";
            this.pcCPUUsage.InstanceName = "_Total";
            // 
            // lblCPU
            // 
            this.lblCPU.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCPU.Location = new System.Drawing.Point(44, 36);
            this.lblCPU.Name = "lblCPU";
            this.lblCPU.Size = new System.Drawing.Size(160, 28);
            this.lblCPU.TabIndex = 1;
            this.lblCPU.Text = "0%";
            this.lblCPU.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // nicoNotifyIcon
            // 
            this.nicoNotifyIcon.Text = "CPU Usage Monitor";
            this.nicoNotifyIcon.Visible = true;
            // 
            // btnMinimizeToTray
            // 
            this.btnMinimizeToTray.Location = new System.Drawing.Point(12, 67);
            this.btnMinimizeToTray.Name = "btnMinimizeToTray";
            this.btnMinimizeToTray.Size = new System.Drawing.Size(111, 28);
            this.btnMinimizeToTray.TabIndex = 2;
            this.btnMinimizeToTray.Text = "Minimize to Tray";
            this.btnMinimizeToTray.UseVisualStyleBackColor = true;
            this.btnMinimizeToTray.Click += new System.EventHandler(this.btnMinimizeToTray_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(126, 67);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(111, 28);
            this.btnExit.TabIndex = 3;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // frmCPU
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(249, 106);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnMinimizeToTray);
            this.Controls.Add(this.lblCPU);
            this.Controls.Add(this.cmbComPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "frmCPU";
            this.Text = "CPU Usage Monitor";
            this.WindowState = System.Windows.Forms.FormWindowState.Minimized;
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pcCPUUsage)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort serSerialPort;
        private System.Windows.Forms.Timer tmrCPUTimer;
        private System.Windows.Forms.ComboBox cmbComPort;
        private System.Diagnostics.PerformanceCounter pcCPUUsage;
        private System.Windows.Forms.Label lblCPU;
        private System.Windows.Forms.NotifyIcon nicoNotifyIcon;
        private System.Windows.Forms.Button btnMinimizeToTray;
        private System.Windows.Forms.Button btnExit;
    }
}

