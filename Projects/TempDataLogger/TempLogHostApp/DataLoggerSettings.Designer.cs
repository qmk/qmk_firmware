namespace Project1HostApp
{
    partial class frmDataloggerSettings
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
            this.btnSetValues = new System.Windows.Forms.Button();
            this.dtpTime = new System.Windows.Forms.DateTimePicker();
            this.lblTime = new System.Windows.Forms.Label();
            this.lblLoggingInterval = new System.Windows.Forms.Label();
            this.nudLogInterval = new System.Windows.Forms.NumericUpDown();
            this.lblSeconds = new System.Windows.Forms.Label();
            this.btnGetValues = new System.Windows.Forms.Button();
            this.lblDate = new System.Windows.Forms.Label();
            this.dtpDate = new System.Windows.Forms.DateTimePicker();
            ((System.ComponentModel.ISupportInitialize)(this.nudLogInterval)).BeginInit();
            this.SuspendLayout();
            // 
            // btnSetValues
            // 
            this.btnSetValues.Location = new System.Drawing.Point(168, 136);
            this.btnSetValues.Name = "btnSetValues";
            this.btnSetValues.Size = new System.Drawing.Size(90, 35);
            this.btnSetValues.TabIndex = 0;
            this.btnSetValues.Text = "Set Values";
            this.btnSetValues.UseVisualStyleBackColor = true;
            this.btnSetValues.Click += new System.EventHandler(this.btnSetValues_Click);
            // 
            // dtpTime
            // 
            this.dtpTime.CustomFormat = "";
            this.dtpTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.dtpTime.Location = new System.Drawing.Point(148, 61);
            this.dtpTime.Name = "dtpTime";
            this.dtpTime.ShowUpDown = true;
            this.dtpTime.Size = new System.Drawing.Size(110, 20);
            this.dtpTime.TabIndex = 1;
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTime.Location = new System.Drawing.Point(51, 67);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(82, 13);
            this.lblTime.TabIndex = 2;
            this.lblTime.Text = "Device Time:";
            // 
            // lblLoggingInterval
            // 
            this.lblLoggingInterval.AutoSize = true;
            this.lblLoggingInterval.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLoggingInterval.Location = new System.Drawing.Point(30, 101);
            this.lblLoggingInterval.Name = "lblLoggingInterval";
            this.lblLoggingInterval.Size = new System.Drawing.Size(103, 13);
            this.lblLoggingInterval.TabIndex = 3;
            this.lblLoggingInterval.Text = "Logging Interval:";
            // 
            // nudLogInterval
            // 
            this.nudLogInterval.Location = new System.Drawing.Point(148, 94);
            this.nudLogInterval.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudLogInterval.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudLogInterval.Name = "nudLogInterval";
            this.nudLogInterval.Size = new System.Drawing.Size(51, 20);
            this.nudLogInterval.TabIndex = 5;
            this.nudLogInterval.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // lblSeconds
            // 
            this.lblSeconds.AutoSize = true;
            this.lblSeconds.Location = new System.Drawing.Point(209, 101);
            this.lblSeconds.Name = "lblSeconds";
            this.lblSeconds.Size = new System.Drawing.Size(49, 13);
            this.lblSeconds.TabIndex = 6;
            this.lblSeconds.Text = "Seconds";
            // 
            // btnGetValues
            // 
            this.btnGetValues.Location = new System.Drawing.Point(30, 136);
            this.btnGetValues.Name = "btnGetValues";
            this.btnGetValues.Size = new System.Drawing.Size(90, 35);
            this.btnGetValues.TabIndex = 7;
            this.btnGetValues.Text = "Get Values";
            this.btnGetValues.UseVisualStyleBackColor = true;
            this.btnGetValues.Click += new System.EventHandler(this.btnGetValues_Click);
            // 
            // lblDate
            // 
            this.lblDate.AutoSize = true;
            this.lblDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblDate.Location = new System.Drawing.Point(51, 33);
            this.lblDate.Name = "lblDate";
            this.lblDate.Size = new System.Drawing.Size(82, 13);
            this.lblDate.TabIndex = 8;
            this.lblDate.Text = "Device Date:";
            // 
            // dtpDate
            // 
            this.dtpDate.CustomFormat = "dd/MM/yyyy";
            this.dtpDate.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpDate.Location = new System.Drawing.Point(148, 27);
            this.dtpDate.Name = "dtpDate";
            this.dtpDate.Size = new System.Drawing.Size(110, 20);
            this.dtpDate.TabIndex = 9;
            // 
            // frmDataloggerSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(300, 197);
            this.Controls.Add(this.dtpDate);
            this.Controls.Add(this.lblDate);
            this.Controls.Add(this.btnGetValues);
            this.Controls.Add(this.lblSeconds);
            this.Controls.Add(this.nudLogInterval);
            this.Controls.Add(this.lblLoggingInterval);
            this.Controls.Add(this.lblTime);
            this.Controls.Add(this.dtpTime);
            this.Controls.Add(this.btnSetValues);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmDataloggerSettings";
            this.Text = "DataLogger";
            this.Load += new System.EventHandler(this.frmDataloggerSettings_Load);
            ((System.ComponentModel.ISupportInitialize)(this.nudLogInterval)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnSetValues;
        private System.Windows.Forms.DateTimePicker dtpTime;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Label lblLoggingInterval;
        private System.Windows.Forms.NumericUpDown nudLogInterval;
        private System.Windows.Forms.Label lblSeconds;
        private System.Windows.Forms.Button btnGetValues;
        private System.Windows.Forms.Label lblDate;
        private System.Windows.Forms.DateTimePicker dtpDate;
    }
}

