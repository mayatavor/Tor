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
        //need to create a communicator class to talk to the main server
        public MainWindow()
        {
            InitializeComponent();
            this._communicator = new Communicator();
        }

        private void SendMessage_Click(object sender, RoutedEventArgs e)
        {
            //this.MessagesList.Items.Add(new MessageSent(Message.Text));
            string answer = this._communicator.SendMessage(Message.Text);
            UserControl user = new MessageSent();
            
            this.MessagesList.Items.Add(user);

            //this.MessagesList.Items.Add(new MessageRecived(Message.Text));
        }

        /* trying to detect the "Enter" click in order to send the message without having to click the send button
        private void Message_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                MessageBox.Show("Pressed enter.");
            }
        }

        private void OnKeyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                UserName.Text = "hi maya";
            }
        }
        */
    }
}
