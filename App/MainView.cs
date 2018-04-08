using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;

namespace RemotePlayerPiApp
{
    public class MainView : LinearLayout
    {
        string root;
        string[] folders, files;

        LinearLayout rootLayout;
        TextView rootText;

        public MainView(Context context)
            : base(context)
        {
            Initialize();
        }
        public MainView(Context context, IAttributeSet attrs)
            : base(context, attrs)
        {
            Initialize();
        }

        void Initialize()
        {
            LayoutInflater inflater = LayoutInflater.FromContext(Context);
            inflater.Inflate(Resource.Layout.Main, this);

            rootText = FindViewById<TextView>(Resource.Id.rootText);
            rootLayout = FindViewById<LinearLayout>(Resource.Id.listRoot);

            Network.OnMessageReceived += Network_OnMessageReceived;

            BuildUI();
        }

        private void BuildUI()
        {
            rootText.Text = root;

            rootLayout.RemoveAllViews();
            for (int i = 0; i < 5; i++)
                rootLayout.AddView(new ItemListView(Context, ItemType.Folder, "test_folder", "tst", i));
            for (int i = 0; i < 5; i++)
                rootLayout.AddView(new ItemListView(Context, ItemType.Song, "test_song", "tst", i));
        }

        private void Network_OnMessageReceived(string message)
        {
            string[] mSplit = message.Split(':');
            if (mSplit.Length == 2)
            {
                switch (mSplit[0])
                {
                    case "dir":
                        string[] sSplit = mSplit[1].Split('|');
                        if (sSplit.Length == 3)
                        {
                            root = sSplit[0];
                            folders = sSplit[1].Split('*');
                            files = sSplit[2].Split('*');
                            BuildUI();
                        }
                        break;
                    case "song":

                        break;
                }
            }
        }

        private void SendRequest(string message)
        {
            Network.SendToServer(message);
        }
    }
}