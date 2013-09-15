using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace Jarvis
{
    internal class ExtProgramHandle
    {
        //WINDOW
        [DllImport("USER32.DLL", CharSet = CharSet.Unicode)]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        [DllImport("USER32.DLL")]
        public static extern bool SetForegroundWindow(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        [DllImport("user32.dll")]
        private static extern bool ShowWindowAsync(IntPtr hWnd, int nCmdShow);

        //MOUSE
        [DllImport("user32.dll")]
        private static extern bool SetCursorPos(int X, int Y);
        [DllImport("user32.dll")]
        public static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

        
        public string prog_path,win_class, win_name;
        public IntPtr win_handle;
        private Process p;
        private int processID,prog_number=0;
        static int total_programs = 0;

        //pass null if unknown; path is must;
        public ExtProgramHandle(string p_Path, string w_class, string w_name)
        {
            this.prog_path = p_Path;
            this.win_class = w_class;
            this.win_name = w_name;          
            start_Program();
        }

        public bool start_Program()
        {
            p = new System.Diagnostics.Process();
            this.prog_number = ++total_programs;
            p.StartInfo.FileName = prog_path;
            p.StartInfo.Domain = "RR";
            if (!p.Start())
                MessageBox.Show("Program not Started - " + prog_path.Substring(prog_path.LastIndexOf('/')));
            processID = p.Id;
            if (find_win_handle_F())
                return true;

            return false;
        }


        public bool find_win_handle_F()
        {
            int count = 0;
            do
            {
                win_handle = FindWindow(win_class, win_name);
                Thread.Sleep(50);
                count++;
                if (count > 150)
                {
                    MessageBox.Show("TimwOut - Handle not found for -" + prog_path.Substring(prog_path.LastIndexOf('/')));
                    return false;
                }
            }
            while (win_handle == IntPtr.Zero);

            return true;
        }


        public void exitApplication()
        {
            p.Kill();
        }


//WORKING FINE
        //bring to front
        public void bring_to_ForeGround()
        {
            SetForegroundWindow(win_handle);
        }

        //maximize,minimize,hide etc
        public bool set_show_state(ShowState s_state)
        {
            ShowWindow(win_handle, (int)s_state);
            return false;
        }

        //set cursor position
        public static void set_cursor_pos(int x, int y)
        {
            SetCursorPos(x, y);
        }

        //simulate mouse event
        public static void Mouse_Event(Mouse_Event e, int x, int y)
        {
            mouse_event((int)e, x, y, 0, 0);
        }
    }
}

    public enum Mouse_Event : int
    {
        Left_button_Down = 2,
        Left_button_Up = 4,
        Right_button_Down = 8,
        Right_button_Up = 16
    }

    public enum ShowState : int
    {
        SW_HIDE = 0,
        SW_SHOWNORMAL = 1,
        SW_NORMAL = 1,
        SW_SHOWMINIMIZED = 2,
        SW_SHOWMAXIMIZED = 3,
        SW_MAXIMIZE = 3,
        SW_SHOWNOACTIVATE = 4,
        SW_SHOW = 5,
        SW_MINIMIZE = 6,
        SW_SHOWMINNOACTIVE = 7,
        SW_SHOWNA = 8,
        SW_RESTORE = 9,
        SW_SHOWDEFAULT = 10,
        SW_FORCEMINIMIZE = 11,
        SW_MAX = 11
    }
