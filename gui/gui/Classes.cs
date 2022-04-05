using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gui
{
    public class Response
    {
        public string message { get; set; }
        public int code { get; set; }
        public List<string> objects { get; set; }

        public Response(string msg)
        {
            this.objects = msg.Split('~').ToList();
            this.code = int.Parse(this.objects[0]);
        }
    }

    public class Message
    {
        public string username { get; set; }
        public string message { get; set; }

        public Message(string u, string m)
        {
            this.username = u;
            this.message = m;
        }
            
    }

    public class user
    {
        public string username { get; set; }
        public bool isFavorite { get; set; }
        public bool isGhost { get; set; }

        public user(string u, bool ghost, bool f)
        {
            this.username = u;
            this.isFavorite = f;
            this.isGhost = ghost;
        }
    }



}
