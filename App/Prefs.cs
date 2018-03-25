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
    public class Prefs
    {
        static ISharedPreferences prefs;

        static Prefs()
        {
            prefs = Application.Context.GetSharedPreferences("RemotePlayerPi", FileCreationMode.Private);
        }

        static public string GetSavedIP()
        {
            if (!prefs.Contains("ip"))
                return null;

            return prefs.GetString("ip", "");
        }

        static public void SaveIP(string ip)
        {
            var edit = prefs.Edit();
            edit.PutString("ip", ip);
            edit.Commit();
        }
    }
}