using Android.App;
using Android.Widget;
using Android.OS;
using Android.Views;
using System;

namespace RemotePlayerPiApp
{
    [Activity(Label = "RemotePlayerPiApp", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            RequestWindowFeature(WindowFeatures.NoTitle);
            SetContentView(Resource.Layout.Main);

            FindViewById<EditText>(Resource.Id.serverPortInput).Text = Network.PORT.ToString();
            FindViewById<Button>(Resource.Id.connexionBtn).Click += connexionBtnClick;
        }

        private void connexionBtnClick(object sender, EventArgs e)
        {
            string ip = FindViewById<EditText>(Resource.Id.serverIPinput).Text;
            string port = FindViewById<EditText>(Resource.Id.serverPortInput).Text;

            if (string.IsNullOrWhiteSpace(ip) || string.IsNullOrWhiteSpace(port))
            {
                Toast.MakeText(ApplicationContext, "Input IP Adress or Port is empty", ToastLength.Long).Show();
                return;
            }

            if(Network.Connect(ip, port))
            {

            }
        }
    }
}