using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Threading;

namespace Jarvis
{
    class JarvisMouse
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int X;
            public int Y;
            public static implicit operator Point(POINT point)
            {
                return new Point(point.X, point.Y);
            }
        }

        //MOUSE
        [DllImport("user32.dll")]
        public static extern bool GetCursorPos(out POINT lpPoint);
        [DllImport("user32.dll")]
        private static extern bool SetCursorPos(int X, int Y);
        [DllImport("user32.dll")]
        public static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

        Point _point;
        MainScreen mScreen;

        public JarvisMouse(MainScreen mscreen)
        {
            mScreen = mscreen;
        }



        public void query_mouse() 
        {
            _point = GetCursorPosition();

            if (mScreen != null)
            {
                mScreen.label2.Text = "Mouse X : " + _point.X;
                mScreen.label3.Text = "Mouse Y : " + _point.Y;
            }
            Thread.Sleep(100);
            modify_mouse();
            query_mouse();
        }

        public void modify_mouse()
        {
            SetCursorPosition(_point.X, _point.Y);
        }




        public static Point GetCursorPosition()
        {
            POINT lpPoint;
            GetCursorPos(out lpPoint);
            //bool success = GetCursorPos(out lpPoint);
            //if (!success)
                return lpPoint;
            //return new Point(0);
        }

        public static void SetCursorPosition(int x, int y)
        {
            SetCursorPos(x, y);
        }

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
