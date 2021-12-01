using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    class Request
    {
        public string username { get; set; }
        public string messageTo { get; set; }
        public string password { get; set; }
        public string message { get; set; }
        public string ip { get; set; }

        public Request(string username, string password, string ip) //login + signup
        {
            this.username = username;
            this.password = password;
            this.ip = ip;
        }

        public Request(string username, string to)
        {
            this.username = username;
            this.messageTo = to;
        }

        //public Request(string mesaage, string username, string to) //send a message
        //{
        //    this.message = message;
        //    this.username = username; //the username to send the message to
        //    this.messageTo = to;
        //}

        public Request(string ip) //connect as a ghost
        {
            this.ip = ip;
        }

    }

    public class Response
    {
        public int status { get; set; }
        public string message { get; set; }
    }

    public class Message
    {
        public string username1 { get; set; }
        public string username2 { get; set; }
        public string message { get; set; }
    }
}
