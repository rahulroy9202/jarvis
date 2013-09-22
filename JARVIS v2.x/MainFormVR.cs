/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/

using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace Jarvis
{
    public partial class MainFormVR : Form
    {
        private PXCMSession session;
        private MainScreen mainScreen;

        public MainFormVR(PXCMSession session, MainScreen mainScreen)
        {
            InitializeComponent();
            this.mainScreen = mainScreen;
            this.session = session;

            try
            {
                PopulateSource();
                PopulateModule();
                PopulateLanguage();
                dictationToolStripMenuItem_Click(null, null);
            }
            catch (Exception e)
            {
                //MessageBox.Show("VR INIT NOT SUCCESSFUL");
            }

            Console2.AfterLabelEdit += new NodeLabelEditEventHandler(Console2_AfterLabelEdit);
            Console2.KeyDown += new KeyEventHandler(Console2_KeyDown);
            FormClosing += new FormClosingEventHandler(MainForm_FormClosing);
        }

        private void PopulateSource()
        {
            PXCMSession.ImplDesc desc = new PXCMSession.ImplDesc();
            desc.group = PXCMSession.ImplGroup.IMPL_GROUP_SENSOR;
            desc.subgroup = PXCMSession.ImplSubgroup.IMPL_SUBGROUP_AUDIO_CAPTURE;
            ToolStripMenuItem sm = new ToolStripMenuItem("Source");
            for (uint i = 0; ; i++)
            {
                PXCMSession.ImplDesc desc1;
                if (session.QueryImpl(ref desc, i, out desc1) < pxcmStatus.PXCM_STATUS_NO_ERROR) break;
                PXCMCapture capture;
                if (session.CreateImpl<PXCMCapture>(ref desc1, PXCMCapture.CUID, out capture) < pxcmStatus.PXCM_STATUS_NO_ERROR) continue;
                for (uint j = 0; ; j++)
                {
                    PXCMCapture.DeviceInfo dinfo;
                    if (capture.QueryDevice(j, out dinfo) < pxcmStatus.PXCM_STATUS_NO_ERROR) break;
                    ToolStripMenuItem sm1 = new ToolStripMenuItem(dinfo.name.get(), null, new EventHandler(Source_Item_Click));
                    sm.DropDownItems.Add(sm1);
                }
                capture.Dispose();
            }
            if (sm.DropDownItems.Count > 0)
                (sm.DropDownItems[0] as ToolStripMenuItem).Checked = true;
            MainMenu.Items.RemoveAt(0);
            MainMenu.Items.Insert(0, sm);
        }

        private void PopulateModule()
        {
            PXCMSession.ImplDesc desc = new PXCMSession.ImplDesc();
            desc.cuids[0] = PXCMVoiceRecognition.CUID;
            ToolStripMenuItem mm = new ToolStripMenuItem("Module");
            for (uint i = 0; ; i++)
            {
                PXCMSession.ImplDesc desc1;
                if (session.QueryImpl(ref desc, i, out desc1) < pxcmStatus.PXCM_STATUS_NO_ERROR) break;
                ToolStripMenuItem mm1 = new ToolStripMenuItem(desc1.friendlyName.get(), null, new EventHandler(Module_Item_Click));
                mm.DropDownItems.Add(mm1);
            }
            if (mm.DropDownItems.Count > 0)
                (mm.DropDownItems[0] as ToolStripMenuItem).Checked = true;
            MainMenu.Items.RemoveAt(1);
            MainMenu.Items.Insert(1, mm);
        }

        private void PopulateLanguage()
        {
            PXCMSession.ImplDesc desc = new PXCMSession.ImplDesc();
            desc.cuids[0] = PXCMVoiceRecognition.CUID;
            desc.friendlyName.set(GetCheckedModule());

            PXCMVoiceRecognition vrec;
            if (session.CreateImpl<PXCMVoiceRecognition>(ref desc, PXCMVoiceRecognition.CUID, out vrec) < pxcmStatus.PXCM_STATUS_NO_ERROR) return;

            ToolStripMenuItem lm = new ToolStripMenuItem("Language");
            for (uint i = 0; ; i++)
            {
                PXCMVoiceRecognition.ProfileInfo pinfo;
                if (vrec.QueryProfile(i, out pinfo) < pxcmStatus.PXCM_STATUS_NO_ERROR) break;
                ToolStripMenuItem lm1 = new ToolStripMenuItem(LanguageToString(pinfo.language), null, new EventHandler(Language_Item_Click));
                lm.DropDownItems.Add(lm1);
            }
            vrec.Dispose();

            if (lm.DropDownItems.Count > 0)
                (lm.DropDownItems[0] as ToolStripMenuItem).Checked = true;
            MainMenu.Items.RemoveAt(2);
            MainMenu.Items.Insert(2, lm);
        }

        public string GetCheckedSource()
        {
            foreach (ToolStripMenuItem m in MainMenu.Items)
            {
                if (!m.Text.Equals("Source")) continue;
                foreach (ToolStripMenuItem e in m.DropDownItems)
                {
                    if (e.Checked) return e.Text;
                }
            }
            return null;
        }

        public string GetCheckedModule()
        {
            foreach (ToolStripMenuItem m in MainMenu.Items)
            {
                if (!m.Text.Equals("Module")) continue;
                foreach (ToolStripMenuItem e in m.DropDownItems)
                {
                    if (e.Checked) return e.Text;
                }
            }
            return null;
        }

        public uint GetCheckedLanguage()
        {
            foreach (ToolStripMenuItem m in MainMenu.Items)
            {
                if (!m.Text.Equals("Language")) continue;
                for (int i = 0; i < m.DropDownItems.Count; i++)
                {
                    if ((m.DropDownItems[i] as ToolStripMenuItem).Checked)
                        return (uint)i;
                }
            }
            return 0;
        }

        public bool IsCommandControl()
        {
            return commandControlToolStripMenuItem.Checked;
        }

        private void RadioCheck(object sender, string name)
        {
            foreach (ToolStripMenuItem m in MainMenu.Items)
            {
                if (!m.Text.Equals(name)) continue;
                foreach (ToolStripMenuItem e1 in m.DropDownItems)
                {
                    e1.Checked = (sender == e1);
                }
            }
        }

        private void Source_Item_Click(object sender, EventArgs e)
        {
            RadioCheck(sender, "Source");
        }

        private void Module_Item_Click(object sender, EventArgs e)
        {
            RadioCheck(sender, "Module");
            PopulateLanguage();
        }

        private void Language_Item_Click(object sender, EventArgs e)
        {
            RadioCheck(sender, "Language");
        }

        private void commandControlToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Status2.Nodes.Clear();
            ConsoleMode.Text = "Command Control:";
            commandControlToolStripMenuItem.Checked = true;
            dictationToolStripMenuItem.Checked = false;
            Console2.Nodes.Clear();
            Console2.LabelEdit = true;
            AlwaysAddNewCommand();
        }

        private void dictationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Status2.Nodes.Clear();
            ConsoleMode.Text = "Dictation:";
            commandControlToolStripMenuItem.Checked = false;
            dictationToolStripMenuItem.Checked = true;
            Console2.LabelEdit = false;
            Console2.Nodes.Clear();
        }

        public void Start_Click(object sender, EventArgs e)
        {
            try
            {
                Start.Enabled = false;
                Stop.Enabled = true;
                MainMenu.Enabled = false;

                stop = false;
                System.Threading.Thread thread = new System.Threading.Thread(DoVoiceRecognition);
                thread.Start();
                System.Threading.Thread.Sleep(5);
            }
            catch (Exception x)
            {
                //todo
            }
        }

        private delegate void VoiceRecognitionCompleted();

        private void DoVoiceRecognition()
        {
            VoiceRecognition.DoIt(this);
            try
            {
                this.Invoke(new VoiceRecognitionCompleted(
                    delegate
                    {
                        Start.Enabled = true;
                        Stop.Enabled = false;
                        MainMenu.Enabled = true;
                        if (closing) Close();
                    }
                ));
            }
            catch (Exception i)
            {
                Start.Enabled = true;
                Stop.Enabled = false;
                MainMenu.Enabled = true;
                if (closing) Close();
            }
        }

        private void Stop_Click(object sender, EventArgs e)
        {
            stop = true;
        }

        private void Console2_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (e.Label == null) return;
            if (e.Label.Length == 0) return;
            e.Node.EndEdit(false);
            if (e.Node.Text.Equals("[Enter New Command]"))
                Console2.Nodes.Add("[Enter New Command]");
        }

        public static string TrimScore(string s)
        {
            s = s.Trim();
            int x = s.IndexOf('[');
            if (x < 0) return s;
            return s.Substring(0, x);
        }

        private string LanguageToString(PXCMVoiceRecognition.ProfileInfo.Language language)
        {
            switch (language)
            {
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_US_ENGLISH: return "US English";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_GB_ENGLISH: return "British English";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_DE_GERMAN: return "Deutsch";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_IT_ITALIAN: return "italiano";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_BR_PORTUGUESE: return "PORTUGUÊS";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_CN_CHINESE: return "中文";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_FR_FRENCH: return "Français";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_JP_JAPANESE: return "日本語";
                case PXCMVoiceRecognition.ProfileInfo.Language.LANGUAGE_US_SPANISH: return "español";
            }
            return null;
        }

        private delegate void TreeViewUpdateDelegate(string line);

        public void PrintConsole(string line)
        {
            CommandHandler.parseCommand(line);
            if (this.Visible == true)
                Console2.Invoke(new TreeViewUpdateDelegate(delegate(string line1) { Console2.Nodes.Add(line1).EnsureVisible(); }), new object[] { line });

            if (mainScreen.Visible == true)
                mainScreen.Invoke(new Action(delegate() { mainScreen.label4.Text = line; mainScreen.label7.Text = "-- OK --"; }));
        }

        public void PrintStatus(string line)
        {
            if (mainScreen.Visible == true)
                mainScreen.Invoke(new Action(delegate() { mainScreen.label7.Text = line; mainScreen.label4.Text = "----"; }));
            //mainScreen.label4.Text = line;

            if (this.Visible == true)
                Status2.Invoke(new TreeViewUpdateDelegate(delegate(string line1) { Status2.Nodes.Add(line1).EnsureVisible(); }), new object[] { line });
        }

        private delegate void ConsoleReplaceTextDelegate(TreeNode tn1, string text);

        public void ClearScores()
        {
            foreach (TreeNode n in Console2.Nodes)
            {
                string s = TrimScore(n.Text);
                if (s.Length > 0)
                    Console2.Invoke(new ConsoleReplaceTextDelegate(delegate(TreeNode tn1, string text) { tn1.Text = text; }), new object[] { n, s });
            }
        }

        public void SetScore(int label, uint confidence)
        {
            for (int i = 0; i < Console2.Nodes.Count; i++)
            {
                string s = TrimScore(Console2.Nodes[i].Text);
                if (s.Length == 0) continue;
                if ((label--) != 0) continue;
                Console2.Invoke(new ConsoleReplaceTextDelegate(delegate(TreeNode tn1, string text) { tn1.Text = text; }), new object[] { Console2.Nodes[i], Console2.Nodes[i].Text + " [" + confidence + "%]" });
                break;
            }
        }

        public string[] GetCommands()
        {
            int ncmds = 0;
            foreach (TreeNode tn in Console2.Nodes)
                if (TrimScore(tn.Text).Length > 0) ncmds++;
            if (ncmds == 0) return null;
            string[] cmds = new string[ncmds];
            for (int i = 0, k = 0; i < Console2.Nodes.Count; i++)
            {
                string cmd = TrimScore(Console2.Nodes[i].Text);
                if (cmd.Length <= 0) continue;
                cmds[k++] = cmd;
            }
            return cmds;
        }

        public string AlertToString(PXCMVoiceRecognition.Alert.Label label)
        {
            switch (label)
            {
                case PXCMVoiceRecognition.Alert.Label.LABEL_SNR_LOW: return "SNR_LOW";
                case PXCMVoiceRecognition.Alert.Label.LABEL_SPEECH_UNRECOGNIZABLE: return "SPEECH_UNRECOGNIZABLE";
                case PXCMVoiceRecognition.Alert.Label.LABEL_VOLUME_HIGH: return "VOLUME_HIGH";
                case PXCMVoiceRecognition.Alert.Label.LABEL_VOLUME_LOW: return "VOLUME_LOW";
            }
            return "UNKNOWN";
        }

        public volatile bool stop = false;
        private bool closing = false;

        public bool IsStop()
        {
            return stop;
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            /*
            stop = true;
            e.Cancel = Stop.Enabled;
            closing = true;
             * */
        }

        private void AlwaysAddNewCommand()
        {
            foreach (TreeNode tn in Console2.Nodes)
                if (tn.Text.Equals("[Enter New Command]")) return;
            Console2.Nodes.Add("[Enter New Command]").EnsureVisible();
        }

        private void Console2_KeyDown(Object sender, KeyEventArgs e)
        {
            if (!IsCommandControl()) return;
            if (e.KeyCode != Keys.Delete) return;
            if (Console2.SelectedNode != null)
                Console2.Nodes.Remove(Console2.SelectedNode);
            AlwaysAddNewCommand();
        }

        private void MainFormVR_FormClosing(object sender, FormClosingEventArgs e)
        {
            //MessageBox.Show("closing VR 2");
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            //MessageBox.Show("closing VR");
            mainScreen.Show();
            this.Hide();
            e.Cancel = true;
            //base.OnClosing(e);
        }
    }
}