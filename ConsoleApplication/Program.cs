using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace Jarvis
{
    internal class ProgramHandle
    {
        [DllImport("USER32.DLL")]
        public static extern bool SetForegroundWindow(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        [DllImport("USER32.DLL", CharSet = CharSet.Unicode)]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        private static IntPtr win_handle;

        [STAThread]
        private static void Main()
        {/*
            string ie_path = @"C:\Program Files\Internet Explorer\iexplore.exe";
            string ie_win_class = "IEFrame";
            string ie_win_nm = "New Tab - Windows Internet Explorer";
            ExtProgramHandle ie_handle = new ExtProgramHandle(ie_path, ie_win_class, ie_win_nm);
            ie_handle.bring_to_ForeGround();
            ie_handle.set_show_state(ShowState.SW_FORCEMINIMIZE);
            Thread.Sleep(2000);
            ie_handle.exitApplication();
            Thread.Sleep(2000);
           
            string chrom_path = @"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe";
            ExtProgramHandle chrome = new ExtProgramHandle(chrom_path, "Chrome_WidgetWin_1", "New Tab - Google Chrome");
            //MessageBox.Show(chrome.win_class + "   " + chrome.win_name + "   " + chrome.prog_path);
            //chrome.set_show_state(ShowState.SW_MINIMIZE);
            //chrome.bring_to_ForeGround();
            chrome.p.Exited += new EventHandler(p_Exited);

            chrome.exitApplication();
            */

            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            PXCMSession session = null;
            pxcmStatus sts = PXCMSession.CreateInstance(out session);

            if (sts >= pxcmStatus.PXCM_STATUS_NO_ERROR)
            {
                Application.Run(new MainScreen(session));
                session.Dispose();
            }
        }

        static void p_Exited(object sender, EventArgs e)
        {
            MessageBox.Show("EXITED "+ DateTime.Now.ToShortTimeString());
        }

        private static void get_this_window()
        {
            string win_class = null;
            string win_name = "Main Screen";
            int count = 0;
            do
            {
                win_handle = FindWindow(win_class, win_name);
                Thread.Sleep(50);
                count++;
                if (count > 100)
                    break;
            }
            while (win_handle == IntPtr.Zero);
        }

        private static void x()
        {
            Process p;
            IntPtr win_handle;
            p = new System.Diagnostics.Process();
            p = Process.GetCurrentProcess();
            win_handle = p.MainWindowHandle;
            System.AppDomain newDomain = System.AppDomain.CreateDomain("RR");

            if (win_handle != IntPtr.Zero)
            {
                ShowWindow(win_handle, (int)ShowState.SW_HIDE);
            }

            
            
            /*
            Process nw = new System.Diagnostics.Process();
            nw.StartInfo.FileName=@"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe";
            nw.StartInfo.Domain = "RR";
            nw.Start();
            */

            /*
            string ie_path = @"C:\Program Files\Internet Explorer\iexplore.exe";
            string ie_win_class = "IEFrame";
            string ie_win_nm = "New Tab - Windows Internet Explorer";
            ExtProgramHandle ie_handle = new ExtProgramHandle(ie_path, ie_win_class, ie_win_nm);
            ie_handle.bring_to_ForeGround();
            //ExtProgramHandle.set_cursor_pos(120,40);
            ExtProgramHandle.set_cursor_pos(55,40);
            ExtProgramHandle.Mouse_Event(Mouse_Event.Left_button_Down,55,40);

            //MessageBox.Show("will be waiting");
            ie_handle.bring_to_ForeGround();
            Thread.Sleep(500);

            SendKeys.SendWait("Life, the universe and everything");
            SendKeys.SendWait("{ENTER}");
            //MessageBox.Show(ie_handle.win_handle.ToString());
            ie_handle.set_show_state(ShowState.SW_MINIMIZE);
            Thread.Sleep(1000);
            //ie_handle.set_show_state(ShowState.SW_MAXIMIZE);

            */
            /*
            string chrom_path=@"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe";
            ExtProgramHandle chrome = new ExtProgramHandle(chrom_path, "Chrome_WidgetWin_1", "New Tab - Google Chrome");
            MessageBox.Show(chrome.win_class+"   "+chrome.win_name+"   "+chrome.prog_path);
            chrome.set_show_state(ShowState.SW_MINIMIZE);
            chrome.bring_to_ForeGround();
            MessageBox.Show("DONW- NOW EXITING");
           // chrome.exitApplication();

            for (int x = 0; x < 500; x++)
            {
                for (int y = 0; y < 500; y++)
                {
                    chrome.set_cursor_pos(x, y);
                }
            }

            */
            return;
        }
    }
}

/*
            //Process chrome = new System.Diagnostics.Process();
            Process.Start(@"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe");

            IntPtr chromeHandle = FindWindow("Chrome_WidgetWin_1", "New Tab - Google Chrome");

            if (chromeHandle == IntPtr.Zero)
            {
                MessageBox.Show("Chrome not found.");
                return;
            }

            SetForegroundWindow(chromeHandle);

            SendKeys.SendWait("%{F4}");
            //SendKeys.SendWait("{ENTER}");
            //SendKeys.SendWait("11");
            //SendKeys.SendWait("=");

            */

/* CALCULATOR
            IntPtr calculatorHandle = FindWindow("CalcFrame", "Calculator");

            if (calculatorHandle == IntPtr.Zero)
            {
                MessageBox.Show("Calculator is not running.");
                return ;
            }

            SetForegroundWindow(calculatorHandle);
            SendKeys.SendWait("111");
            SendKeys.SendWait("*");
            SendKeys.SendWait("11");
            SendKeys.SendWait("=");
            */

/*
             * chrome-class     Chrome_WidgetWin_1
             *        nm        New Tab - Google Chrome
             *
             *
             *
             *
             */

/*

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

 [System.Runtime.InteropServices.DllImport("user32.dll")]
public static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

public const int MOUSEEVENTF_LEFTDOWN = 0x02;
public const int MOUSEEVENTF_LEFTUP = 0x04;
public const int MOUSEEVENTF_RIGHTDOWN = 0x08;
public const int MOUSEEVENTF_RIGHTUP = 0x10;

public void MouseClick()
{
int x = 100;
int y = 100;
mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
*/