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

        static TcpClient client;
        static bool connected = false;

        static public async Task<ConnexionResult> Connect(string IP, string port)
        {
            ConnexionResult result = new ConnexionResult();
            client = new TcpClient();
            client.SendTimeout = 3000;

            try
            {
                IPAddress _ip = IPAddress.Parse(IP);
                int _port = int.Parse(port);
                await client.ConnectAsync(_ip, _port);
                connected = client.Connected;
            }
            catch (Exception e)
            {
                result.Message = e.Message;
            }

            result.Connected = connected;
            return result;
        }

        static public void Disconnect()
        {
            connected = false;
        }

        static public bool IsConnected()
        {
            return connected;
        }

        static public string SendToServer(string message)
        {
            if(client == null)
                return null;
            
            NetworkStream ns = client.GetStream();
            ASCIIEncoding enc = new ASCIIEncoding();
            byte[] buffer = enc.GetBytes(message);

            ns.Write(buffer, 0, buffer.Length);

            while(!ns.DataAvailable)
            { }

            buffer = new byte[BUFFER_SIZE];
            int size = ns.Read(buffer, 0, buffer.Length);
            string response = Encoding.ASCII.GetString(buffer);

            ns.Close();
            return response;
        }
    }

    public struct ConnexionResult
    {
        public bool Connected;
        public string Message;
    }
}