using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace Jarvis
{
    class settingsmanager
    {
        string settings_path;
        FileStream settings;
        ExtProgramHandle[] program_handles;
        StreamReader settings_reader;

        public settingsmanager()
        {
            settings_path="settings.ini";
            try
            {
                settings = new FileStream(settings_path, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                settings_reader = new StreamReader(settings);
            }
            catch (Exception e)
            {
                MessageBox.Show("Settings Problems Detected - "+e.Message);
            }

        }

        public ExtProgramHandle[] read_programs()
        {
            


            return program_handles;
        }



    }
}
