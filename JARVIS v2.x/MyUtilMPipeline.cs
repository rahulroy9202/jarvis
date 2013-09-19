/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/

namespace Jarvis
{
    internal class MyUtilMPipeline : UtilMPipeline
    {
        public void SetForm(MainFormVR form)
        {
            this.form = form;
        }

        public void SetProfileIndex(uint pidx)
        {
            this.pidx = pidx;
        }

        public override void OnVoiceRecognitionSetup(ref PXCMVoiceRecognition.ProfileInfo pinfo)
        {
            QueryVoiceRecognition().QueryProfile(pidx, out pinfo);
        }

        public override void OnRecognized(ref PXCMVoiceRecognition.Recognition data)
        {
            if (data.label < 0)
            {
                form.PrintConsole(data.dictation);
            }
            else
            {
                form.ClearScores();
                for (int i = 0; i < 4; i++)
                {
                    int label = data.nBest[i].label;
                    uint confidence = data.nBest[i].confidence;
                    if (label < 0 || confidence == 0) continue;
                    form.SetScore(label, confidence);
                }
            }
        }

        public override void OnAlert(ref PXCMVoiceRecognition.Alert data)
        {
            form.PrintStatus(form.AlertToString(data.label));
        }

        protected uint pidx;
        protected MainFormVR form;
    }
}