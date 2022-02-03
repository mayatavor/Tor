using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using System.Windows;
using System.Collections.Concurrent;

namespace gui
{
    class AcceptMessages
    {
        private int port { get; set; }
        private ConcurrentQueue<Response> responses;
        public AcceptMessages()
        {
            port = FindPort();
            Application.Current.Properties["Responses"] = new ConcurrentQueue<Response>();

            this.responses = (ConcurrentQueue<Response>)Application.Current.Properties["Responses"];
        }

        public int GetPort()
        {
            return port;
        }

        public void StartServer()
        {
            IPHostEntry host = Dns.GetHostEntry("localhost");
            IPAddress ipAddress = host.AddressList[1];
            IPEndPoint localEndPoint = new IPEndPoint(ipAddress, port);

            try
            {
                // Create a Socket that will use Tcp protocol
                Socket listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                listener.Bind(localEndPoint);
                listener.Listen(10);

                Console.WriteLine("Waiting for a connection...");

                while (true)
                {
                    Socket handler = listener.Accept();
                    //recive the data from the socket
                    byte[] bytesArr = new byte[5];
                    int bytesRec = handler.Receive(bytesArr);
                    string t = System.Text.Encoding.UTF8.GetString(bytesArr, 0, bytesArr.Length);

                    int lenMsg = int.Parse(t);
                    byte[] bytesArr3 = new byte[lenMsg];
                    bytesRec = handler.Receive(bytesArr3);

                    string res = System.Text.Encoding.UTF8.GetString(bytesArr3, 0, bytesArr3.Length);

                    Response r = new Response(res);
                    this.responses.Enqueue(r);
                
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }

            }
            catch (Exception e)
            {
                e.ToString();
            }
        }



        //helpers
        //find a port to run the server on
        public static int FindPort()
        {
            for (int i = 6789; i < 65535; i++)
            {
                if (!PortInUse(i))
                    return i;
            }

            return 0;
        }
        public static bool PortInUse(int port)
        {
            bool inUse = false;

            IPGlobalProperties ipProperties = IPGlobalProperties.GetIPGlobalProperties();
            IPEndPoint[] ipEndPoints = ipProperties.GetActiveTcpListeners();

            foreach (IPEndPoint endPoint in ipEndPoints)
            {
                if (endPoint.Port == port)
                {
                    inUse = true;
                    break;
                }
            }

            return inUse;
        }
    }
}
