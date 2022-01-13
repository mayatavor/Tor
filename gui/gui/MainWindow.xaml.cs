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
        private string myUserName;
        private string username;

        public MainWindow(string username)
        {
            InitializeComponent();
            this._communicator = (Communicator)Application.Current.Properties["Com"];
            this.myUserName = username;
            this.username = "";

            //get users from the server
            getUsers();
        }

        private void SendMsg(string text)
        {
            bool answer = this._communicator.SendMessage(text,this.username, this.myUserName);
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
                this.username = user.GetUsername();

                //get the chat history
                List<Message> messages = this._communicator.GetMessages(myUserName, user.GetUsername());
                for (int i = 0; i < messages.Count; i++)
                {
                    if (messages[i].username == myUserName)
                    {
                        MessageSent m = new MessageSent(messages[i].message);
                        this.MessagesList.Items.Add(messages[i]);
                    }
                    else
                    {
                        MessageRecived m = new MessageRecived(messages[i].message);
                        this.MessagesList.Items.Add(messages[i]);
                    }
                }
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

            getUsers();

            this.SearchBackground.Source = GetImage("Assets/search.png");
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
            bool res = false;//this._communicator.Logout(this.username);

            if(!res)
            {
                MessageBoxResult result = MessageBox.Show("Could not log out, please try again", "LogOut Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                MainWindow wnd = new MainWindow(username);
                this.Close();
                wnd.ShowDialog();
            }
        }


        private void getUsers()
        {
            //List<UserInfo> users = this._communicator.GetUsers();

            //for (int i = 0; i < users.Count; i++)
            //{
            //    this.UsersList.Items.Add(users[i]);
            //}

            UserInfo user = new UserInfo(true, "maya", true);
            this.UsersList.Items.Add(user);
            UserInfo user2 = new UserInfo(false, "lihi", true);
            this.UsersList.Items.Add(user2);
            UserInfo user3 = new UserInfo(false, "adi", false);
            this.UsersList.Items.Add(user3);
        }



    }
}
