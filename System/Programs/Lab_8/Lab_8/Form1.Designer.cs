
namespace Lab_8
{
    partial class Form1
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
            this.buttonMainInfo = new System.Windows.Forms.Button();
            this.buttonPictures = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonMainInfo
            // 
            this.buttonMainInfo.Location = new System.Drawing.Point(31, 668);
            this.buttonMainInfo.Name = "buttonMainInfo";
            this.buttonMainInfo.Size = new System.Drawing.Size(241, 48);
            this.buttonMainInfo.TabIndex = 0;
            this.buttonMainInfo.Text = "Get Main Information";
            this.buttonMainInfo.UseVisualStyleBackColor = true;
            this.buttonMainInfo.Click += new System.EventHandler(this.buttonMainInfo_Click);
            // 
            // buttonPictures
            // 
            this.buttonPictures.Location = new System.Drawing.Point(31, 589);
            this.buttonPictures.Name = "buttonPictures";
            this.buttonPictures.Size = new System.Drawing.Size(241, 48);
            this.buttonPictures.TabIndex = 1;
            this.buttonPictures.Text = "Assemble Pictures";
            this.buttonPictures.UseVisualStyleBackColor = true;
            this.buttonPictures.Click += new System.EventHandler(this.buttonPictures_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1290, 742);
            this.Controls.Add(this.buttonPictures);
            this.Controls.Add(this.buttonMainInfo);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonMainInfo;
        private System.Windows.Forms.Button buttonPictures;
    }
}

