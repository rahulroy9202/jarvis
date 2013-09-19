/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/

using System;

namespace Jarvis
{
    internal class VoiceRecognition
    {
        public static void DoIt(Object form1)
        {
            MainFormVR form = form1 as MainFormVR;
            MyUtilMPipeline pp = new MyUtilMPipeline();
            pp.SetForm(form);

            /* Set Audio Source */
            pp.QueryCapture().SetFilter(form.GetCheckedSource());

            /* Set Module */
            pp.EnableVoiceRecognition(form.GetCheckedModule());

            /* Set Language */
            pp.SetProfileIndex(form.GetCheckedLanguage());

            /* Set Command/Control or Dictation */
            if (form.IsCommandControl())
            {
                string[] cmds = form.GetCommands();
                if (cmds == null)
                {
                    form.PrintStatus("No Command List. Dictation instead.");
                    pp.SetVoiceDictation();
                }
                else
                {
                    pp.SetVoiceCommands(cmds);
                }
            }
            else
            {
                pp.SetVoiceDictation();
            }

            /* Initialization */
            form.PrintStatus("Init Started");
            if (pp.Init())
            {
                form.PrintStatus("Init OK");

                /* Set audio volume to 0.2 */
                pp.QueryCapture().device.SetProperty(PXCMCapture.Device.Property.PROPERTY_AUDIO_MIX_LEVEL, 0.2f);

                /* Recognition Loop */
                while (!form.IsStop())
                {
                    if (!pp.AcquireFrame(true)) break;
                    pp.ReleaseFrame();
                }
            }
            else
            {
                form.PrintStatus("Init Failed");
            }

            pp.Close();
            pp.Dispose();
            form.PrintStatus("Stopped");
        }
    }
}