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
        private string username;
        public MainWindow(Communicator c)
        {
            InitializeComponent();
            this._communicator = c;
            this._communicator = new Communicator();
            this.username = "maya";

            //get users from the server
            UserInfo user = new UserInfo(true, "maya");
            this.UsersList.Items.Add(user);
            UserInfo user2 = new UserInfo(false, "lihi");
            this.UsersList.Items.Add(user2);
            UserInfo user3 = new UserInfo(false, "adi");
            this.UsersList.Items.Add(user3);
        }

        private void SendMsg(string text)
        {
            bool answer = this._communicator.SendMessage(text);
            if (answer == false)
            {
                MessageError error = new MessageError(text);
                this.MessagesList.Items.Add(error);
            }
            else
            {
                MessageSent user = new MessageSent(text);
                this.MessagesList.Items.Add(user);
            }
            this.Message.Text = "";
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

        private void UsersList_PreviewMouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            var item = (sender as ListView).SelectedItem;
            if (item != null)
            {
                UserInfo user = (UserInfo)item;
                this.UserName.Text = user.GetUsername();
            }

            
        }


        private void searchInUsers(string name)
        {
            for (int i = 0; i < this.UsersList.Items.Count; i++)
            {
                UserInfo user = (UserInfo)this.UsersList.Items[i];

                if (!user.GetUsername().ToUpper().Contains(name.ToUpper()))
                {
                    this.UsersList.Items.RemoveAt(i);
                    i--;
                }
            }
        }

        private void search_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < this.UsersList.Items.Count;)
            {
                this.UsersList.Items.RemoveAt(i);
            }

            UserInfo user = new UserInfo(true, "maya");
            this.UsersList.Items.Add(user);
            UserInfo user2 = new UserInfo(false, "lihi");
            this.UsersList.Items.Add(user2);
            UserInfo user3 = new UserInfo(false, "adi");
            this.UsersList.Items.Add(user3);

            this.SearchBackground.Source = GetImage("Assets/copy.png");
            this.SearchText.Text = "";

        }

        private void SearchInText_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key != Key.Enter)
            {
                string name = this.SearchText.Text;
                name += e.Key.ToString();
                searchInUsers(name);

                this.SearchBackground.Source = GetImage("Assets/xSign.png");
            }
        }

        private static BitmapImage GetImage(string imageUri)
        {
            var bitmapImage = new BitmapImage();

            bitmapImage.BeginInit();
            bitmapImage.UriSource = new Uri(imageUri, UriKind.RelativeOrAbsolute);
            bitmapImage.EndInit();

            return bitmapImage;
        }

        private void LogOut_Click(object sender, RoutedEventArgs e)
        {
            bool res = this._communicator.Logout(this.username);

            if(!res)
            {
                //add popup
            }
            else
            {
                MainWindow wnd = new MainWindow(this._communicator);
                this.Close();
                wnd.ShowDialog();
            }
        }
    }
}
