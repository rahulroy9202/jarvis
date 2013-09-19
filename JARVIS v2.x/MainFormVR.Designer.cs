namespace Jarvis
{
    partial class MainFormVR
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
            this.MainMenu = new System.Windows.Forms.MenuStrip();
            this.moduleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.languageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.languageToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.modeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.commandControlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dictationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ConsoleMode = new System.Windows.Forms.GroupBox();
            this.Console2 = new System.Windows.Forms.TreeView();
            this.Status2 = new System.Windows.Forms.TreeView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Start = new System.Windows.Forms.Button();
            this.Stop = new System.Windows.Forms.Button();
            this.MainMenu.SuspendLayout();
            this.ConsoleMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // MainMenu
            // 
            this.MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.moduleToolStripMenuItem,
            this.languageToolStripMenuItem,
            this.languageToolStripMenuItem1,
            this.modeToolStripMenuItem});
            this.MainMenu.Location = new System.Drawing.Point(0, 0);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(350, 24);
            this.MainMenu.TabIndex = 0;
            this.MainMenu.Text = "MainMenu";
            // 
            // moduleToolStripMenuItem
            // 
            this.moduleToolStripMenuItem.Name = "moduleToolStripMenuItem";
            this.moduleToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.moduleToolStripMenuItem.Text = "Source";
            // 
            // languageToolStripMenuItem
            // 
            this.languageToolStripMenuItem.Name = "languageToolStripMenuItem";
            this.languageToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.languageToolStripMenuItem.Text = "Module";
            // 
            // languageToolStripMenuItem1
            // 
            this.languageToolStripMenuItem1.Name = "languageToolStripMenuItem1";
            this.languageToolStripMenuItem1.Size = new System.Drawing.Size(70, 20);
            this.languageToolStripMenuItem1.Text = "Language";
            // 
            // modeToolStripMenuItem
            // 
            this.modeToolStripMenuItem.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.modeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.commandControlToolStripMenuItem,
            this.dictationToolStripMenuItem});
            this.modeToolStripMenuItem.Name = "modeToolStripMenuItem";
            this.modeToolStripMenuItem.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.modeToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.modeToolStripMenuItem.Text = "Mode";
            // 
            // commandControlToolStripMenuItem
            // 
            this.commandControlToolStripMenuItem.Name = "commandControlToolStripMenuItem";
            this.commandControlToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.commandControlToolStripMenuItem.Text = "Command Control";
            this.commandControlToolStripMenuItem.Click += new System.EventHandler(this.commandControlToolStripMenuItem_Click);
            // 
            // dictationToolStripMenuItem
            // 
            this.dictationToolStripMenuItem.Name = "dictationToolStripMenuItem";
            this.dictationToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.dictationToolStripMenuItem.Text = "Dictation";
            this.dictationToolStripMenuItem.Click += new System.EventHandler(this.dictationToolStripMenuItem_Click);
            // 
            // ConsoleMode
            // 
            this.ConsoleMode.Controls.Add(this.Console2);
            this.ConsoleMode.Location = new System.Drawing.Point(2, 25);
            this.ConsoleMode.Name = "ConsoleMode";
            this.ConsoleMode.Size = new System.Drawing.Size(348, 216);
            this.ConsoleMode.TabIndex = 1;
            this.ConsoleMode.TabStop = false;
            this.ConsoleMode.Text = "Dictation:";
            // 
            // Console2
            // 
            this.Console2.FullRowSelect = true;
            this.Console2.Indent = 5;
            this.Console2.LabelEdit = true;
            this.Console2.Location = new System.Drawing.Point(6, 20);
            this.Console2.Name = "Console2";
            this.Console2.ShowLines = false;
            this.Console2.Size = new System.Drawing.Size(336, 190);
            this.Console2.TabIndex = 0;
            // 
            // Status2
            // 
            this.Status2.Indent = 5;
            this.Status2.Location = new System.Drawing.Point(9, 268);
            this.Status2.Name = "Status2";
            this.Status2.ShowLines = false;
            this.Status2.Size = new System.Drawing.Size(335, 114);
            this.Status2.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(3, 249);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(347, 139);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Status:";
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(46, 394);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(75, 23);
            this.Start.TabIndex = 4;
            this.Start.Text = "Start";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // Stop
            // 
            this.Stop.Enabled = false;
            this.Stop.Location = new System.Drawing.Point(207, 394);
            this.Stop.Name = "Stop";
            this.Stop.Size = new System.Drawing.Size(75, 23);
            this.Stop.TabIndex = 5;
            this.Stop.Text = "Stop";
            this.Stop.UseVisualStyleBackColor = true;
            this.Stop.Click += new System.EventHandler(this.Stop_Click);
            // 
            // MainFormVR
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(350, 426);
            this.Controls.Add(this.Stop);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.Status2);
            this.Controls.Add(this.ConsoleMode);
            this.Controls.Add(this.MainMenu);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.MainMenu;
            this.Name = "MainFormVR";
            this.Text = "Voice Recognition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainFormVR_FormClosing);
            this.MainMenu.ResumeLayout(false);
            this.MainMenu.PerformLayout();
            this.ConsoleMode.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip MainMenu;
        private System.Windows.Forms.ToolStripMenuItem moduleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem languageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem languageToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem modeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem commandControlToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dictationToolStripMenuItem;
        private System.Windows.Forms.GroupBox ConsoleMode;
        private System.Windows.Forms.TreeView Console2;
        private System.Windows.Forms.TreeView Status2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Button Stop;
    }
}