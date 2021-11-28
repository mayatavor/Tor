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
        private string userName;

        public Communicator()
        {
            this._socket = new SocketT();
            this._socket.startSocket();
            this.userName = "";
        }

        public void SetUserName(string userName)
        {
            this.userName = userName;
        }

        public bool SendMessage(string msg)
        {
            Request newReq = new Request(msg);

            Response res = this._socket.TalkToServer(newReq, "200");
            if (res == null)
                return false;
            else if (res.status == 0)
                return false;
            return true;
        }

        public bool Login(string username, string password)
        {
            Request newReq = new Request(username, password);

            Response res = this._socket.TalkToServer(newReq, "101");

            if (res == null)
                return false;
            else if (res.status == 0)
                return false;
            return true;
        }

        public bool SignUp(string username, string password)
        {
            Request newReq = new Request(username, password);

            Response res = this._socket.TalkToServer(newReq, "102");

            if (res == null)
                return false;
            else if (res.status == 0)
                return false;
            return true;
        }

    }
}
