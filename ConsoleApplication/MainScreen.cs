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
    }
}