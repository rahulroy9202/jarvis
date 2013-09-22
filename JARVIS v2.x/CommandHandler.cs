using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Jarvis
{
    class CommandHandler
    {
        ExtProgramHandle[] ext_prog=new ExtProgramHandle[3];
        static ExtProgramHandle curr_prog;
        static int last_word_length;


        public CommandHandler()
        {
            /*
            string chrom_path = @"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe";
            ext_prog[0] = new ExtProgramHandle(chrom_path, "Chrome_WidgetWin_1", "New Tab - Google Chrome");

            string ie_path = @"C:\Program Files\Internet Explorer\iexplore.exe";
            string ie_win_class = "IEFrame";
            string ie_win_nm = "New Tab - Windows Internet Explorer";
            ext_prog[1] = new ExtProgramHandle(ie_path, ie_win_class, ie_win_nm);

            */

        }

        static bool drag;
        static int counter=0;
        static PXCMGesture.Gesture[] prevGesture=new PXCMGesture.Gesture[2];
        public static void gestureHandler(PXCMGesture.Gesture[] x)
        {
            
            for (int i = 0; i < 2; i++)
            {
                /*
                if (x[0].label == x[1].label)
                {
                    if(x[1].label==PXCMGesture.Gesture.Label.LABEL_NAV_SWIPE_DOWN)
                        ExtProgramHandle.set_show_state(ShowState.SW_MINIMIZE);

                    if (x[1].label == PXCMGesture.Gesture.Label.LABEL_NAV_SWIPE_UP)
                        ExtProgramHandle.set_show_state(ShowState.SW_RESTORE);

                    return;
                }
               */

                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_POSE_THUMB_DOWN)
                {
                    //ExtProgramHandle.restore_prev_win(ShowState.SW_MAXIMIZE);
                    ExtProgramHandle.pass_string("{PGDN}");
                }
                
                
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_NAV_SWIPE_DOWN)
                {
                    //ExtProgramHandle.pass_string("{PGDN}");
                    ExtProgramHandle.set_show_state(ShowState.SW_MINIMIZE);
                }

                //
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_NAV_SWIPE_UP)
                {
                    ExtProgramHandle.restore_prev_win(ShowState.SW_RESTORE);
                    //ExtProgramHandle.pass_string("{PGUP}");
                }
                
                //go back
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_NAV_SWIPE_LEFT)
                    ExtProgramHandle.pass_string("{BACKSPACE}");
                
                



                //SingleClick
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_POSE_BIG5 & prevGesture[i].label!=PXCMGesture.Gesture.Label.LABEL_POSE_BIG5)
                    JarvisMouse.leftClick();
                
                //DoubleClick
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_POSE_PEACE & prevGesture[i].label != PXCMGesture.Gesture.Label.LABEL_POSE_PEACE)
                    JarvisMouse.mousDoubleClick();
                
                /*
                //Drag&Drop Check
                if (x[i].label == PXCMGesture.Gesture.Label.LABEL_POSE_BIG5)
                    counter++;
                else
                    counter = 0;

                //DragfDropExecute
                if (counter > 500)
                {
                    drag = true;
                    JarvisMouse.Mouse_Event(Mouse_Evnt.Left_button_Down);
                }
                else if (counter == 0)
                    JarvisMouse.Mouse_Event(Mouse_Evnt.Left_button_Up);
                */
            }

            prevGesture[0] = x[0];
            prevGesture[1] = x[1];

        }




        public static void parseCommand(string command)
        {
            string[] com_array = command.Split(' ');

            const string com_init = "Love";
            const string search_it = "Like";

            if (com_array[0].Equals(com_init))
            {
                switch (com_array[1])
                {
                    case search_it:
                        string chrom_path = @"C:\Users\Rahul Roy\AppData\Local\Google\Chrome\Application\chrome.exe";
                        ExtProgramHandle chrome = new ExtProgramHandle(chrom_path, "Chrome_WidgetWin_1", "New Tab - Google Chrome");
                        chrome.start_Program();
                        chrome.bring_to_ForeGround();
                        Thread.Sleep(50);
                        for (int i = 1; i < com_array.Length; i++)
                        {
                            SendKeys.SendWait(com_array[i]);
                            last_word_length = com_array[i].Length;
                        }
                        break;

                    case "BackSpace":
                        for (int i = 0; i < last_word_length; i++)
                        {
                            SendKeys.SendWait("{BACKSPACE}");
                        }
                        break;

                    case "Dictation":
                        for (int i = 1; i < com_array.Length; i++)
                        {
                            SendKeys.SendWait(com_array[i]);
                            last_word_length = com_array[i].Length;
                        }
                        break;
                }

            }
        }
    }

    enum comandHandlerState
    {
        Dictation,
        Browsing,

    }
}
