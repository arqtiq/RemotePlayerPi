using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Net;
using System.Net.Sockets;

namespace RemotePlayerPiApp
{
    public class Network
    {
        static public readonly int PORT = 1234;

        static TcpClient client;
        static bool connected = false;

        static Network()
        {
            client = new TcpClient();
        }

        static public bool Connect(string IP, string port)
        {
            bool _connected = false;
            try
            {
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

        static public bool IsConnected()
        {
            return connected;
        }
    }
}