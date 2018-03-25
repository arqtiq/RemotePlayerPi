using System;
using System.Text;
using System.IO;

using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using Android.Widget;

namespace RemotePlayerPiApp
{
    public class Network
    {
        static public readonly int PORT = 1234;
        static public readonly int BUFFER_SIZE = 512;

        static UdpClient client;
        static IPEndPoint ip;
        static bool connected = false;

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
            if(client == null)
                return;


        }
    }

    public struct ConnexionResult
    {
        public bool Connected;
        public string Message;
    }
}