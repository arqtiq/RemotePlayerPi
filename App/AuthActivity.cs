using Android.App;
using Android.Widget;
using Android.OS;
using Android.Views;
using System;
using System.Threading.Tasks;
using Android;
using System.Collections.Generic;

namespace RemotePlayerPiApp
{
    [Activity(Label = "Authentication", MainLauncher = true, Icon = "@drawable/icon")]
    public class AuthActivity : Activity
    {
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            RequestWindowFeature(WindowFeatures.NoTitle);
            SetContentView(Resource.Layout.Auth);

            string _ip = Prefs.GetSavedIP();
            if (_ip != null)
                FindViewById<EditText>(Resource.Id.serverIPinput).Text = _ip;
            FindViewById<EditText>(Resource.Id.serverPortInput).Text = Network.PORT.ToString();
            FindViewById<Button>(Resource.Id.connexionBtn).Click += connexionBtnClick;

            HandlePermissions();
        }

        private void connexionBtnClick(object sender, EventArgs e)
        {
            string ip = FindViewById<EditText>(Resource.Id.serverIPinput).Text;
            string port = FindViewById<EditText>(Resource.Id.serverPortInput).Text;

            Prefs.SaveIP(ip);

            if (string.IsNullOrWhiteSpace(ip) || string.IsNullOrWhiteSpace(port))
            {
                Toast.MakeText(ApplicationContext, "Input IP Adress or Port is empty", ToastLength.Long).Show();
                return;
            }

            ConnexionResult res = Network.Connect(ip, port);
            if (!res.Connected)
            {
                Toast.MakeText(ApplicationContext, "Unable to connect : " + res.Message, ToastLength.Long).Show();
                return;
            }

            Start();
        }

        private void Start()
        {
            StartActivity(typeof(MainActivity));
            Finish();
        }

        private void HandlePermissions()
        {
            if ((int)Build.VERSION.SdkInt < 23)
                return;

            string[] permissions =
            {
                Manifest.Permission.AccessNetworkState,
                Manifest.Permission.Internet
            };

            List<string> denied = new List<string>();
            foreach (string s in permissions)
                if (CheckSelfPermission(s) != Android.Content.PM.Permission.Granted)
                    denied.Add(s);

            if(denied.Count > 0)
                RequestPermissions(denied.ToArray(), 0);
        }
    }
}