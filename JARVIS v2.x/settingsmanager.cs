using System;
using System.IO;
using System.Windows.Forms;

namespace Jarvis
{
    internal class settingsmanager
    {
        private string settings_path;
        private FileStream settings;
        private ExtProgramHandle[] program_handles;
        private StreamReader settings_reader;

        public settingsmanager()
        {
            settings_path = "settings.ini";
            try
            {
                settings = new FileStream(settings_path, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                settings_reader = new StreamReader(settings);
            }
            catch (Exception e)
            {
                MessageBox.Show("Settings Problems Detected - " + e.Message);
            }
        }

        public ExtProgramHandle[] read_programs()
        {
            return program_handles;
        }
    }
}