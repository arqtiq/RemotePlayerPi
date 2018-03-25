using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;

namespace RemotePlayerPiApp
{
    [Activity(Label = "MainActivity")]
    public class MainActivity : NetActivity
    {
        string root;
        string[] folders, files;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            RequestWindowFeature(WindowFeatures.NoTitle);
            SetContentView(Resource.Layout.Main);

            GoHome();
        }

        private void BuildUI()
        {
            FindViewById<TextView>(Resource.Id.rootText).Text = root;
        }

        protected override void Network_OnMessageReceived(string message)
        {
            string[] mSplit = message.Split(':');
            if(mSplit.Length == 2)
            {
                switch(mSplit[0])
                {
                    case "dir_desc":
                        string[] sSplit = mSplit[1].Split('|');
                        if(sSplit.Length == 3)
                        {
                            root = sSplit[0];
                            folders = sSplit[1].Split('*');
                            files = sSplit[2].Split('*');
                            BuildUI();
                        }
                        break;
                }
            }
        }

        // ---------------------------------------------------------------------

        private void GoHome()
        {
            SendRequest("@d:home;");
        }
    }
}