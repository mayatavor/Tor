using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;



namespace gui
{
    
    class SocketT
    {
        private byte[] bytes;
        private Socket sender;
        const string SPACER = "::::";

        public SocketT()
        {
            this.bytes = new byte[1024];
        }

        ~SocketT()
        {
            try
            {
                this.sender.Shutdown(SocketShutdown.Both);
                this.sender.Close();
            }
            catch (Exception e)
            {
                string s = e.Message;
            }
        }

        public string TalkToServer(string req, string code)
        {
            string v = code + getPaddedNumber(req.Length, 3) + req;
            return TalkToServer(v);
        }

        public string TalkToServer(string mas)
        {
            try
            {
                byte[] msg = Encoding.ASCII.GetBytes(mas);
                // Send the data through the socket.
                int bytesSent = this.sender.Send(msg);

                byte[] bytesArr = new byte[3];
                int bytesRec = this.sender.Receive(bytesArr);

                string t = System.Text.Encoding.UTF8.GetString(bytesArr, 0, bytesArr.Length);

                int len2 = int.Parse(t);

                byte[] bytesArr2 = new byte[len2];
                bytesRec = this.sender.Receive(bytesArr2);
                //int len = int.Parse(t);
                //byte[] bytesArr3 = new byte[len];
                //bytesRec = this.sender.Receive(bytesArr3);

                string res = System.Text.Encoding.UTF8.GetString(bytesArr2, 0, bytesArr2.Length);

                return res;
            }
            catch (Exception w)
            {

            }
            return null;
        }

        public bool startSocket()
        {
            try
            {
                IPHostEntry ipHost = Dns.GetHostEntry("localhost");
                IPAddress ipAddr = ipHost.AddressList[1];
                IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 5678);

                // Creation TCP/IP Socket using 
                // Socket Class Costructor
                Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                this.sender = sender;
                // Connect the socket to the remote endpoint. Catch any errors.    
                try
                {
                    // Connect to Remote EndPoint  
                    this.sender.Connect(localEndPoint);

                    Console.WriteLine("Socket connected to {0}", this.sender.RemoteEndPoint.ToString());
                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                    return false;
                }
                catch (SocketException se)
                {
                    Console.WriteLine("SocketException : {0}", se.ToString());
                    return false;
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unexpected exception : {0}", e.ToString());
                    return false;
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return false;
            }
            return true;
        }



        //helpers
        // return string after padding zeros if necessary
        private string getPaddedNumber(int num, int digits)
        {
            string number = num.ToString();
            for (int i = number.Length; i < digits; i++)
            {
                number = "0" + number;
            }
            return number;
        }


    }
}
