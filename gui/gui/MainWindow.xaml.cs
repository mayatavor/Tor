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
        //need to create a communicator class to talk to the main server
        public MainWindow()
        {
            InitializeComponent();
            this._communicator = new Communicator();
        }

        private void SendMsg(string text)
        {
            string answer = this._communicator.SendMessage(text);
            MessageSent user = new MessageSent(text);
            //user.setText(text);

            this.MessagesList.Items.Add(user);
        }

        private void SendMessage_Click(object sender, RoutedEventArgs e)
        {
            //this.MessagesList.Items.Add(new MessageSent(Message.Text));
            SendMsg(Message.Text);

            //this.MessagesList.Items.Add(new MessageRecived(Message.Text));
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
