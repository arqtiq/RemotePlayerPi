using System;
using System.Text;
using System.IO;

using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using Android.Widget;
using System.Threading;

namespace RemotePlayerPiApp
{
    public class Network
    {
        static public readonly int PORT = 1234;
        static public readonly int BUFFER_SIZE = 512;

        static UdpClient client;
        static IPEndPoint ip;
        static bool connected = false;

        static Timer receiveTimer;
        static TimerCallback timerDelegate;
        public delegate void NetworkEvent(string message);
        static public event NetworkEvent OnMessageReceived;

        static public void Init()
        {
            timerDelegate = new TimerCallback(ReceiveTick);
            receiveTimer = new Timer(timerDelegate, receiveTimer, 0, 100);            
        }

        static public ConnexionResult Connect(string IP, string port)
        {
            ConnexionResult result = new ConnexionResult();
            client = new UdpClient();
            ip = new IPEndPoint(IPAddress.Parse(IP), int.Parse(port));

            try
            {
                client.Connect(ip);
                connected = true;
            }
            catch (Exception e)
            {
                result.Message = e.Message;
                connected = false;
            }

            result.Connected = connected;
            return result;
        }

        static public void Disconnect()
        {
            connected = false;
            client.Close();
        }

        static public bool IsConnected()
        {
            return connected;
        }

        static public void SendToServer(string message)
        {
            if(!connected || client == null)
                return;

            byte[] data = Encoding.UTF8.GetBytes(message);
            client.Send(data, data.Length);
        }

        static void ReceiveTick(object state)
        {
            if (!connected)
                return;

            var endPoint = new IPEndPoint(IPAddress.Any, PORT);
            byte[] data = client.Receive(ref endPoint);
            string message = Encoding.UTF8.GetString(data);
            if(!string.IsNullOrWhiteSpace(message))
                OnMessageReceived?.Invoke(message);
        }
    }

    public struct ConnexionResult
    {
        public bool Connected;
        public string Message;
    }
}