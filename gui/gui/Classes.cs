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
        public string password { get; set; }
        public string message { get; set; }

        public Request(string username, string password) //login + signup
        {
            this.username = username;
            this.password = password;
        }

        public Request(string mesaage) //login + signup
        {
            this.message = message;
        }

    }

    public class Response
    {
        public int status { get; set; }
        public string message { get; set; }
    }
}
