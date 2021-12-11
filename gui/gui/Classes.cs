using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    public class Response
    {
        private string DIVIDER = "≡";
        public int status { get; set; }
        public string message { get; set; }

        public int code { get; set; }
        public List<string> objects { get; set; }

        public Response(string msg)
        {
            this.objects = msg.Split('≡').ToList();
        }
    }

    public class Message
    {
        public string username1 { get; set; }
        public string username2 { get; set; }
        public string message { get; set; }
    }
}
