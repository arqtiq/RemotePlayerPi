using System;
using System.Text;
using System.IO;

using System.Net;
using System.Net.Sockets;

namespace RemotePlayerPiApp
{
    public class Network
    {
        static public readonly int PORT = 1234;
        static public readonly int BUFFER_SIZE = 512;

        static TcpClient client;
        static bool connected = false;

        static public bool Connect(string IP, string port)
        {
            bool _connected = false;
            try
            {
                client = new TcpClient();
                IPAddress _ip = IPAddress.Parse(IP);
                int _port = int.Parse(port);
                client.Connect(_ip, _port);
                _connected = true;
            }
            catch
            {
                _connected = false;
            }
            finally
            {
                connected = _connected;
            }

            return _connected;
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
            string response = ASCIIEncoding.ASCII.GetString(buffer);

            ns.Close();
            return response;
        }
    }
}