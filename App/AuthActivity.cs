using Android.App;
using Android.Widget;
using Android.OS;
using Android.Views;
using System;
using System.Threading.Tasks;
using Android;
using System.Collections.Generic;
using Android.Content;

namespace RemotePlayerPiApp
{
    [Activity(Label = "Authentication", MainLauncher = true, Icon = "@drawable/icon")]
    public class AuthActivity : NetActivity
    {
        bool connecting = false;

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

            Network.Init();
        }

        private void connexionBtnClick(object sender, EventArgs e)
        {
            Start();return;
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

            Network.SendToServer(Command.Factory.Network.GetConnect());
            connecting = true;
        }

        private void Start()
        {
            var act = new Intent(this, typeof(MainActivity));

            StartActivity(typeof(MainActivity));
            Finish();
        }

        private void RequestDir()
        {
            SendRequest(Command.Factory.Data.GetHome());
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

        protected override void Network_OnMessageReceived(string message)
        {
            if (!connecting)
                return;
            
            if (message == "0")
                Toast.MakeText(ApplicationContext, "Server refused the connection", ToastLength.Long).Show();
            else if (message == "1")
            {
                Toast.MakeText(ApplicationContext, "Connected", ToastLength.Short).Show();
                Start();
            }
            else if(Command.IsDir(message))
            {

            }
        }
    }
}