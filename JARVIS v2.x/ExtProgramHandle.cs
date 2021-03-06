﻿using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using System.Text;
using System.Collections;
using System.Collections.Generic;

namespace Jarvis
{
    internal class ExtProgramHandle
    {
        #region ASSEMBLY IMPORTS

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

        [DllImport("user32.dll")]
        private static extern IntPtr GetForegroundWindow();

        [DllImport("user32.dll")]
        private static extern int GetWindowText(IntPtr hWnd, StringBuilder text, int count);



        #endregion ASSEMBLY IMPORTS

        public string prog_path, win_class, win_name;
        public IntPtr win_handle;
        public static IntPtr active_win_handle,prev_win_handle;
        public Process p;
        private int processID, prog_number = 0;
        private static int total_programs = 0;
        static Stack<IntPtr> winHandles=new Stack<IntPtr>();



        //pass null if unknown; path is must;
        public ExtProgramHandle(string p_Path, string w_class, string w_name)
        {
            this.prog_path = p_Path;
            this.win_class = w_class;
            this.win_name = w_name;
            //start_Program();
        }

        public bool start_Program()
        {
            p = new System.Diagnostics.Process();
            this.prog_number = ++total_programs;
            p.StartInfo.FileName = prog_path;
            p.StartInfo.Domain = "RR";
            if (!p.Start())
                MessageBox.Show("Program not Started - " + prog_path.Substring(prog_path.LastIndexOf('\\') + 1));
            processID = p.Id;
            MessageBox.Show(p.Id.ToString());
            Thread.Sleep(500);
            if(win_name==null)
                win_name = GetActiveWindowTitle();
            if (find_win_handle_F())
            {
                return true;
            }

            return false;
        }

        public static bool pass_string(string x)
        {
            try
            {
                SendKeys.SendWait(x);
            }
            catch (Exception e)
            {

            }
            return true;
        }

        private static IntPtr GetActiveWindowHandle()
        {
            IntPtr handle = IntPtr.Zero;
            handle = GetForegroundWindow();
            return handle;
        }

        private static string GetActiveWindowTitle()
        {
            IntPtr handle = GetActiveWindowHandle();
            const int nChars = 256;            
            StringBuilder Buff = new StringBuilder(nChars);
            if (GetWindowText(handle, Buff, nChars) > 0)
            {
                return Buff.ToString();
            }
            return null;
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
                    MessageBox.Show("TimwOut - Handle not found for -" + prog_path.Substring(prog_path.LastIndexOf('\\') + 1));
                    return false;
                }
            }
            while (win_handle == IntPtr.Zero);

            return true;
        }

        public void exitApplication()
        {
            try
            {
                p.CloseMainWindow();
                p.Kill();
            }
            catch (Exception e)
            {
                MessageBox.Show("FAILED TO KILL - " + prog_path.Substring(prog_path.LastIndexOf('\\') + 1) + e.Message);
            }
        }

        //bring to front
        public void bring_to_ForeGround()
        {
            SetForegroundWindow(win_handle);
        }

        //maximize,minimize,hide etc
        public static bool set_show_state(ShowState s_state)
        {
            active_win_handle = GetActiveWindowHandle();           
            ShowWindow(active_win_handle, (int)s_state);
            if (s_state == ShowState.SW_HIDE || s_state == ShowState.SW_MINIMIZE)
            {
                //prev_win_handle = active_win_handle;
                winHandles.Push(active_win_handle);
                active_win_handle = GetActiveWindowHandle();
            }

            return true;
        }
        
        //restore
        public static bool restore_prev_win(ShowState s_state)
        {
            if (winHandles.Peek() != IntPtr.Zero)
            {
                ShowWindow(winHandles.Pop(), (int)s_state);
                return true;
            }
            return false;
        }


        //set cursor position
        public static void set_cursor_pos(int x, int y)
        {
            SetCursorPos(x, y);
        }

        //simulate mouse event
        public static void Mouse_Event(Mouse_Evnt e, int x, int y)
        {
            mouse_event((int)e, x, y, 0, 0);
        }
    }
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