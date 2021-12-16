using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    public class Communicator
    {
        private SocketT _socket;
        private string DIVIDER = "~";

        public Communicator()
        {
            this._socket = new SocketT();
            this._socket.startSocket();
        }

        ~Communicator()
        {

        }


        public string Login(string username, string password)
        {
            string reqInfo = "101" + DIVIDER + username + DIVIDER + password;

            Response res = this._socket.FirstTalkWithServer(reqInfo);

            if (res.code == 400)
                return res.objects[1];
            return "";
        }
        public string SignUp(string username, string password)
        {
            string reqInfo = "102" + DIVIDER + username + DIVIDER + password;

            Response res = this._socket.FirstTalkWithServer(reqInfo);

            if (res.code == 400)
                return res.objects[1];
            return "";
        }
        public string Ghost()
        {
            string reqInfo = "103" + DIVIDER + "adding a ghost name or not";

            Response res = this._socket.FirstTalkWithServer(reqInfo);

            if (res.code == 400)
                return res.objects[1];
            return "";
        }

        public Message GetMessages(string username1, string username2, string msg)
        {
            string reqInfo = "code" + DIVIDER + username1 + DIVIDER + username2 + DIVIDER + msg;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            return new Message();
        }

        public bool Logout(string username)
        {
            string reqInfo = "212" + DIVIDER + username;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            return res.code == 200;
        }

        
        public bool SendMessage(string msg)
        {
            string reqInfo = "200" + DIVIDER + msg;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len+reqInfo);
            if (res == null)
                return false;
            else if (res.code == 0)
                return false;
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
