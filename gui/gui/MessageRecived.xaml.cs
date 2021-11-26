using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace gui
{
    /// <summary>
    /// Interaction logic for MessageRecived.xaml
    /// </summary>
    public partial class MessageRecived : UserControl
    {
        private string text;
        public MessageRecived(string msg)
        {
            this.text = msg;
            InitializeComponent();
            this.MessageText.Text = text;
        }

        public void setText(string newText)
        {
            this.text = newText;
            this.MessageText.Text = text;
        }
    }
}
