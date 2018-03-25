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
    public class NetActivity : Activity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            Network.OnMessageReceived += Network_OnMessageReceived;
        }

        virtual protected void Network_OnMessageReceived(string message)
        { }

        protected void SendRequest(string message)
        {
            Network.SendToServer(message);
        }
    }
}