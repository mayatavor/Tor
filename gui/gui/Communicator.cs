using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public enum MessageCodes
{
    secondaryServerConnected = 100,
    logIn = 101,
    signUp = 102,
    logout = 212,
    ghostLogIn = 103,
    sendChatMessage = 300,
    getChatHistory = 301,
    error = 400,
    success = 200,
    ghostName = 201,
    favoriteUser = 110,
}

namespace gui
{
    public class Communicator
    {
        private SocketT _socket;
        private string DIVIDER = "~";
        private MessageCodes codes;

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

            if (res.code == (int)MessageCodes.error)
                return res.objects[1];
            return "";
        }
        public (int, string) Ghost()
        {
            string reqInfo = (int)MessageCodes.ghostLogIn + DIVIDER + "adding a ghost name or not";

            Response res = this._socket.FirstTalkWithServer(reqInfo);

            return (res.code, res.objects[1]);
        }

        public Message GetMessages(string username1, string username2, string msg)
        {
            string reqInfo = (int)MessageCodes.getChatHistory + DIVIDER + username1 + DIVIDER + username2 + DIVIDER + msg;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            return new Message();
        }

        public bool Logout(string username)
        {
            string reqInfo = (int)MessageCodes.logout + DIVIDER + username;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            return res.code == (int)MessageCodes.success;
        }
        
        public bool SendMessage(string msg, string username, string myUserName)
        {
            string reqInfo = (int)MessageCodes.sendChatMessage + DIVIDER + myUserName + DIVIDER + username + DIVIDER + msg;
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
