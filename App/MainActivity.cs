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
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            RequestWindowFeature(WindowFeatures.NoTitle);
            SetContentView(new MainView(BaseContext));            
        }
        
        protected override void Network_OnMessageReceived(string message)
        {

        }
    }
}