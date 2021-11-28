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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    { 
        private Communicator _communicator;
        public IObservable<string> ListItems { get; set; }
        public MainWindow(/*Communicator c*/)
        {
            InitializeComponent();
            //this._communicator = c;
        }

        private void SendMsg(string text)
        {
            //bool answer = this._communicator.SendMessage(text);
            //MessageSent user = new MessageSent(text);
            //this.MessagesList.Items.Add(user);
            bool answer = false;
            if (answer == false)
            {
                MessageError error = new MessageError(text);
                this.MessagesList.Items.Add(error);

            }
        }

        private void SendMessage_Click(object sender, RoutedEventArgs e)
        {
            SendMsg(Message.Text);
        }

     

        private void Message_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMsg(Message.Text);
            }
        }
    }
}
