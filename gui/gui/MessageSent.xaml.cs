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
    /// Interaction logic for MessageSent.xaml
    /// </summary>
    public partial class MessageSent : UserControl
    {
        private string text;
        public MessageSent()
        {
            text = "67";
            this.AddText(text);
            InitializeComponent();
        }

        public void setText(string newText)
        {
            this.text = newText;
            this.AddText(text);
        }

    }
}
