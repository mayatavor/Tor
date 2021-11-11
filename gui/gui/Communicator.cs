using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    class Communicator
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

        public string SendMessage(string msg)
        {
            string res = this._socket.TalkToServer(msg);
            return res;
        }

    }
}
