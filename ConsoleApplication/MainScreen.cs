using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Jarvis
{
    public partial class MainScreen : Form
    {
        private PXCMSession session;

        public MainScreen(PXCMSession session)
        {
            this.session = session;
            InitializeComponent();
            //MouseClick += new MouseEventHandler(MainScreen_MouseClick);
            //MouseHover += new MouseEventHandler(MainScreen_MouseClick);
            //MouseMove += new MouseEventHandler(MainScreen_MouseMove);
            //this.WindowState = FormWindowState.Maximized;
        }

        void MainScreen_MouseMove(object sender, MouseEventArgs e)
        {
            this.label2.Text = "Mouse X : " + Control.MousePosition.X.ToString();
            this.label3.Text = "Mouse Y : " + Control.MousePosition.Y.ToString();
        }

        void MainScreen_MouseClick(object sender, MouseEventArgs e)
        {
            this.label2.Text = "Mouse X : " + Control.MousePosition.X.ToString();
            this.label3.Text = "Mouse Y : " + Control.MousePosition.Y.ToString();
        }

        private string new_prog_path;

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            openFileDialog1.CheckFileExists = true;

            //textBox1.Text=  openFileDialog1.FileName;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        }

        private void textBox1_MouseDown(object sender, MouseEventArgs e)
        {
            openFileDialog1.DereferenceLinks = true;
            DialogResult res = openFileDialog1.ShowDialog();
            if (res == DialogResult.OK)
                new_prog_path = openFileDialog1.FileName;
            textBox1.ForeColor = Color.Black;
            textBox1.Text = new_prog_path;
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }
    }
}