using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    public class Response
    {
        public int status { get; set; }
        public string message { get; set; }

        public int code { get; set; }
        public List<string> objects { get; set; }
    }

    public class Message
    {
        public string username1 { get; set; }
        public string username2 { get; set; }
        public string message { get; set; }
    }
}
