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
    removeFavoriteUser = 111,
    getUsers = 302,
}

namespace gui
{
    public class Communicator
    {
        private SocketT _socket;
        private string DIVIDER = "~";
        private string myUsername;

        public Communicator()
        {
            this._socket = new SocketT();
            this._socket.startSocket();
        }

        ~Communicator()
        {

        }

        public void SetUserName(string u)
        {
            this.myUsername = u;
        }

        public string GetUserName()
        {
            return this.myUsername;
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
            string reqInfo = (int)MessageCodes.ghostLogIn + "";

            Response res = this._socket.FirstTalkWithServer(reqInfo);

            return (res.code, res.objects[1]);
        }

        public List<Message> GetMessages(string username1, string username2)
        {
            string reqInfo = (int)MessageCodes.getChatHistory + DIVIDER + username1 + DIVIDER + username2;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            List<Message> messages = new List<Message>();
            string[] sep = new string[] { "::::" };
            string[] userInfo;

            for (int i = 1; i < res.objects.Count() - 1; i++)
            {
                userInfo = res.objects[i].Split(sep, StringSplitOptions.RemoveEmptyEntries);
                messages.Add(new Message(userInfo[0], userInfo[1]));
            }

            return messages;
        }

        public List<user> GetUsers()
        {
            string reqInfo = (int)MessageCodes.getUsers + "";
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);

            List<user> users = new List<user>();
            string[] sep = new string[] { "::::" };
            string[] userInfo;

            for (int i = 1; i < res.objects.Count() - 1; i++)
            {
                userInfo = res.objects[i].Split(sep, StringSplitOptions.RemoveEmptyEntries);
                users.Add(new user(userInfo[0], Convert.ToBoolean(userInfo[1]), Convert.ToBoolean(userInfo[2])));
            }

            return users;
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

        public bool AddToFavorites(string myUsername, string otherUsername)
        {
            string reqInfo = (int)MessageCodes.favoriteUser + DIVIDER + myUsername + DIVIDER + otherUsername;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);
            if (res == null)
                return false;
            else if (res.code == 0)
                return false;
            return true;
        }

        public bool RemoveFromFavorites(string myUsername, string otherUsername)
        {
            string reqInfo = (int)MessageCodes.removeFavoriteUser + DIVIDER + myUsername + DIVIDER + otherUsername;
            string len = getPaddedNumber(reqInfo.Length, 5);

            Response res = this._socket.TalkToServer(len + reqInfo);
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
