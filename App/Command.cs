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
    public class Command
    {
        const string DIR_PREFIX         =        "dir";
        const string SONG_PREFIX        =        "song";

        public class Factory
        {
            public class Network
            {
                static public string GetConnect()
                {
                    return "@n:connect;";
                }
                static public string GetDisconnect()
                {
                    return "@n:disconnect;";
                }
            }
            public class Data
            {
                static public string GetHome()
                {
                    return "@d:home;";
                }
                static public string GetDir(int id)
                {
                    return "@d:" + id.ToString() + ";";
                }
            }
        }

        static public bool IsDir(string command)
        {
            return command.StartsWith(DIR_PREFIX);
        }
    }
}