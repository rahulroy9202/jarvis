using System.Drawing;
using System.Windows.Forms;
using System;
using System.Threading;

namespace Jarvis
{
    internal class GestureRecognition
    {
        private MainFormGR form;
        private bool disconnected = false;
        private PXCMGesture.GeoNode[][] nodes = new PXCMGesture.GeoNode[2][] { new PXCMGesture.GeoNode[11], new PXCMGesture.GeoNode[11] };
        private PXCMGesture.Gesture[] gestures = new PXCMGesture.Gesture[2];
        private PXCMGesture.GeoNode[] myNodes = new PXCMGesture.GeoNode[2];
        Point myPoint,prevPoint=new Point(0,0);
        MainScreen  mscreen;

        //PXCMImage.ImageData mydata;
        int imgWidth, imgHeight;

        public GestureRecognition(MainFormGR form,MainScreen mscreen)
        {
            this.form = form;
            this.mscreen = mscreen;
        }

        private bool DisplayDeviceConnection(bool state)
        {
            if (state)
            {
                if (!disconnected) form.UpdateStatus("Device Disconnected");
                disconnected = true;
            }
            else
            {
                if (disconnected) form.UpdateStatus("Device Reconnected");
                disconnected = false;
            }
            return disconnected;
        }

        private void DisplayPicture(PXCMImage depth, PXCMGesture gesture)
        {
            PXCMImage image = depth;
            bool dispose = false;
            if (form.GetLabelmapState())
            {
                if (gesture.QueryBlobImage(PXCMGesture.Blob.Label.LABEL_SCENE, 0, out image) < pxcmStatus.PXCM_STATUS_NO_ERROR) return;
                dispose = true;
            }

            PXCMImage.ImageData data;
            if (image.AcquireAccess(PXCMImage.Access.ACCESS_READ, PXCMImage.ColorFormat.COLOR_FORMAT_RGB32, out data) >= pxcmStatus.PXCM_STATUS_NO_ERROR)
            {
                PXCMImage.ImageInfo imageInfo = image.imageInfo;
                form.DisplayBitmap(data.ToBitmap(imageInfo.width, imageInfo.height));
                imgWidth =(int) imageInfo.width;
                imgHeight =(int) imageInfo.height;
                image.ReleaseAccess(ref data);
            }

            if (dispose) image.Dispose();
        }

        private void DisplayGeoNodes(PXCMGesture gesture)
        {
            

            if (form.GetGeoNodeState())
            {
                gesture.QueryNodeData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_PRIMARY, nodes[0]);
                gesture.QueryNodeData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_SECONDARY, nodes[1]);
                gesture.QueryNodeData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_ELBOW_PRIMARY, out nodes[0][nodes.Length - 1]);
                gesture.QueryNodeData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_ELBOW_SECONDARY, out nodes[1][nodes.Length - 1]);
                form.DisplayGeoNodes(nodes);

                //Invoke_Mouse();
                newMouseInvoke();
            }
            else
            {
                form.DisplayGeoNodes(null);
            }
        }


        static PXCMGesture.GeoNode[] hand_main=new PXCMGesture.GeoNode[2];
        static PXCMGesture.GeoNode[] fingers=new PXCMGesture.GeoNode[5];
        
        
        public int[] finger_gesture()
        {
            int[] res = new int[2];
            /*
            for (int i = 0; i < nodes.Length; i++)
            {
                for (int j = 0; j < nodes[i].Length; j++)
                {
                    if (nodes[i][j].body == PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_PRIMARY)
                    {
                        hand_main[i] = nodes[i][j];
                        break;
                    }
                    //if (nodes[i][j].body == PXCMGesture.GeoNode.Label.LABEL_HAND_UPPER)
                    //    fingers[j] = nodes[i][j];
                }

                
                int dist_threshold = 10, dist = 0, x, y, x1, y1;
                    for (int j = 0; j < nodes[i].Length; j++)
                    {
                        if (nodes[i][j].body == PXCMGesture.GeoNode.Label.LABEL_HAND_UPPER)
                        {
                            x = (int)hand_main[i].positionImage.x;
                            y = (int)hand_main[i].positionImage.y;

                            x1 = (int)nodes[i][j].positionImage.x;
                            y1 = (int)nodes[i][j].positionImage.y;

                            dist = (int)Math.Sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
                            if (dist > dist_threshold)
                                res[i]++;
                        }
                    }
                
            }
            */
            return res;
        }





        int count=-1,x_displacement,y_displacement,XD,YD;
        Point mousePoint;
        float sensitivity=9.5f;
        private void newMouseInvoke()
        {
            for (int x = 0; x < 2; x++)
            {
                for (int i = 0; i < 11; i++)
                {
                    if (nodes[x][i].body == PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_PRIMARY)
                        myNodes[0] = nodes[x][i];
                }
            }
            //myNodes[0] = nodes[0][0];
            
            
            myPoint.X = (int)myNodes[0].positionImage.x;
            myPoint.Y = (int)myNodes[0].positionImage.y;
            if (count == -1) { prevPoint = myPoint; }
            x_displacement = (int)((myPoint.X - prevPoint.X) * sensitivity*1.3f);
            y_displacement = (int)((myPoint.Y - prevPoint.Y) * sensitivity);

            XD += x_displacement;
            YD += y_displacement;

            if (count == 3)
            {
                count = 0;
                mousePoint = JarvisMouse.GetCursorPosition();
                mousePoint.X -= XD/3;
                mousePoint.Y += YD/3;         
                JarvisMouse.modify_mouse(mousePoint);
                //Thread.Sleep(50);
                XD = 0; YD = 0;
                prevPoint = myPoint;
            }
            count++;


            try
            {
                mscreen.Invoke(new Action(delegate { mscreen.label5.Text = "X" + x_displacement; mscreen.label6.Text = "Y" + y_displacement; }));
            }
            catch (Exception i) { mscreen.label5.Text = "X" + myPoint.X.ToString() + i.Message; mscreen.label6.Text = "Y" + myPoint.Y.ToString(); }

        }


        private void Invoke_Mouse()
        {
            float adjust=1.1f;
            int screenWidth = 1333, screenHeight = 768;
            /*
            for (int i = 0; i < nodes[0].Length; i++)
            {
                if(nodes[0][i].body == PXCMGesture.GeoNode.Label.LABEL_HAND_MIDDLE)
                    myNodes[0] = nodes[0][i];
            }
            */

            myNodes[0] = nodes[0][0];
            myPoint.X = (int)(myNodes[0].positionImage.x *screenWidth/imgWidth * adjust);
            myPoint.Y = (int)(myNodes[0].positionImage.y * screenHeight/imgHeight*adjust);
            //myPoint.X = (int)myNodes[0].positionImage.x;
            //myPoint.Y = (int)myNodes[0].positionImage.y;

            try
            {
                mscreen.Invoke(new Action(delegate { mscreen.label5.Text = "X" + myPoint.X.ToString(); mscreen.label6.Text = "Y" + myPoint.Y.ToString(); }));
            }
            catch (Exception i) { mscreen.label5.Text = "X" + myPoint.X.ToString() + i.Message; mscreen.label6.Text = "Y" + myPoint.Y.ToString(); }


            //myPoint.X = prevPoint.X + myPoint.X / 2;
            //myPoint.Y = prevPoint.Y + myPoint.Y / 2;

            

            if(myPoint.X!=0&&myPoint.Y!=0)
            JarvisMouse.modify_mouse(myPoint);
            
            prevPoint = myPoint;

            

        }

        private void DisplayGesture(PXCMGesture gesture)
        {
            gesture.QueryGestureData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_PRIMARY, 0, out gestures[0]);
            gesture.QueryGestureData(0, PXCMGesture.GeoNode.Label.LABEL_BODY_HAND_SECONDARY, 0, out gestures[1]);
            
            /*
            //int fingr = 0;
            for (int i = 0; i < 2; i++)
            {
                if ((finger_gesture()[i] > 3) & (gestures[i].label == PXCMGesture.Gesture.Label.LABEL_ANY))
                    gestures[i].label = PXCMGesture.Gesture.Label.LABEL_SET_CUSTOMIZED;
                if (finger_gesture()[i] > 1)
                    gestures[i].label = PXCMGesture.Gesture.Label.LABEL_HAND_CIRCLE;

                mscreen.Invoke(new Action(delegate { mscreen.label5.Text = "1: " + finger_gesture()[0]; mscreen.label6.Text = "2: " + finger_gesture()[1]; }));
            }

            */
            CommandHandler.gestureHandler(gestures);
            
            form.DisplayGestures(gestures);

        }

        public void SimplePipeline()
        {
            bool sts = true;
            UtilMPipeline pp = null;
            disconnected = false;

            /* Set Source */
            if (form.GetRecordState())
            {
                pp = new UtilMPipeline(form.GetRecordFile(), true);
                pp.QueryCapture().SetFilter(form.GetCheckedDevice());
            }
            else if (form.GetPlaybackState())
            {
                pp = new UtilMPipeline(form.GetPlaybackFile(), false);
            }
            else
            {
                pp = new UtilMPipeline();
                pp.QueryCapture().SetFilter(form.GetCheckedDevice());
            }

            /* Set Module */
            pp.EnableGesture(form.GetCheckedModule());

            /* Initialization */
            form.UpdateStatus("Init Started");
            if (pp.Init())
            {
                form.UpdateStatus("Streaming");

                while (!form.stop)
                {
                    if (!pp.AcquireFrame(true)) break;
                    if (!DisplayDeviceConnection(pp.IsDisconnected()))
                    {
                        /* Display Results */
                        PXCMGesture gesture = pp.QueryGesture();
                        PXCMImage depth = pp.QueryImage(PXCMImage.ImageType.IMAGE_TYPE_DEPTH);
                        DisplayPicture(depth, gesture);
                        DisplayGeoNodes(gesture);
                        DisplayGesture(gesture);
                        form.UpdatePanel();
                    }
                    pp.ReleaseFrame();
                }
            }
            else
            {
                form.UpdateStatus("Init Failed");
                sts = false;
            }

            pp.Close();
            pp.Dispose();
            if (sts) form.UpdateStatus("Stopped");
        }

        public void AdvancedPipeline()
        {
            PXCMSession session;
            pxcmStatus sts = PXCMSession.CreateInstance(out session);
            if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR)
            {
                form.UpdateStatus("Failed to create an SDK session");
                return;
            }

            /* Set Module */
            PXCMSession.ImplDesc desc = new PXCMSession.ImplDesc();
            desc.friendlyName.set(form.GetCheckedModule());

            PXCMGesture gesture;
            sts = session.CreateImpl<PXCMGesture>(ref desc, PXCMGesture.CUID, out gesture);
            if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR)
            {
                form.UpdateStatus("Failed to create the gesture module");
                session.Dispose();
                return;
            }

            UtilMCapture capture = null;
            if (form.GetRecordState())
            {
                capture = new UtilMCaptureFile(session, form.GetRecordFile(), true);
                capture.SetFilter(form.GetCheckedDevice());
            }
            else if (form.GetPlaybackState())
            {
                capture = new UtilMCaptureFile(session, form.GetPlaybackFile(), false);
            }
            else
            {
                capture = new UtilMCapture(session);
                capture.SetFilter(form.GetCheckedDevice());
            }

            form.UpdateStatus("Pair moudle with I/O");
            for (uint i = 0; ; i++)
            {
                PXCMGesture.ProfileInfo pinfo;
                sts = gesture.QueryProfile(i, out pinfo);
                if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR) break;
                sts = capture.LocateStreams(ref pinfo.inputs);
                if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR) continue;
                sts = gesture.SetProfile(ref pinfo);
                if (sts >= pxcmStatus.PXCM_STATUS_NO_ERROR) break;
            }
            if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR)
            {
                form.UpdateStatus("Failed to pair the gesture module with I/O");
                capture.Dispose();
                gesture.Dispose();
                session.Dispose();
                return;
            }

            form.UpdateStatus("Streaming");
            PXCMImage[] images = new PXCMImage[PXCMCapture.VideoStream.STREAM_LIMIT];
            PXCMScheduler.SyncPoint[] sps = new PXCMScheduler.SyncPoint[2];
            while (!form.stop)
            {
                PXCMImage.Dispose(images);
                PXCMScheduler.SyncPoint.Dispose(sps);
                sts = capture.ReadStreamAsync(images, out sps[0]);
                if (DisplayDeviceConnection(sts == pxcmStatus.PXCM_STATUS_DEVICE_LOST)) continue;
                if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR) break;

                sts = gesture.ProcessImageAsync(images, out sps[1]);
                if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR) break;

                sts = PXCMScheduler.SyncPoint.SynchronizeEx(sps);
                if (DisplayDeviceConnection(sps[0].Synchronize() == pxcmStatus.PXCM_STATUS_DEVICE_LOST)) continue;
                if (sts < pxcmStatus.PXCM_STATUS_NO_ERROR) break;

                /* Display Results */
                PXCMImage depth = capture.QueryImage(images, PXCMImage.ImageType.IMAGE_TYPE_DEPTH);
                DisplayPicture(depth, gesture);
                DisplayGeoNodes(gesture);
                DisplayGesture(gesture);
                form.UpdatePanel();
            }
            PXCMImage.Dispose(images);
            PXCMScheduler.SyncPoint.Dispose(sps);

            capture.Dispose();
            gesture.Dispose();
            session.Dispose();
            form.UpdateStatus("Stopped");
        }
    }
}