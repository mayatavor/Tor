using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
        private AcceptMessages _server;
        private string myUserName;
        private string username;
        private ConcurrentQueue<Response> responses;
        private Thread t;
        private Thread t2;
        private bool isOut;

        public MainWindow(string username)
        {
            InitializeComponent();
            this._server = (AcceptMessages)Application.Current.Properties["Server"];
            this._communicator = (Communicator)Application.Current.Properties["Com"];
            this.responses = (ConcurrentQueue<Response>)Application.Current.Properties["Responses"];
            this.myUserName = username;
            this.username = "";
            this.isOut = false;

            //get users from the server
            getUsers(username);

            this.UserNameChats.Text += username;

            this.t2 = new Thread(this._server.StartServer);
            t2.Start();

            this.t = new Thread(this.HandleResponses);
            t.Start();
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

                user.SetToEmpty();

                this.MessagesList.Items.Clear();

                //get the chat history
                List<Message> messages = this._communicator.GetMessages(myUserName, user.GetUsername());
                for (int i = 0; i < messages.Count; i++)
                {
                    if (messages[i].username == myUserName)
                    {
                        MessageSent m = new MessageSent(messages[i].message);
                        this.MessagesList.Items.Add(m);
                    }
                    else
                    {
                        MessageRecived m = new MessageRecived(messages[i].message);
                        this.MessagesList.Items.Add(m);
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

            getUsers(this.myUserName);

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
            this.isOut = this._communicator.Logout(this.username);

            Task.Delay(200).Wait();

            if(!this.isOut)
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


        private void getUsers(string username)
        {
            List<UserInfo> users = this._communicator.GetUsers(username);

            for (int i = 0; i < users.Count; i++)
            {
                if (users[i].GetStar())
                    this.UsersList.Items.Insert(0, users[i]);
                else
                    this.UsersList.Items.Add(users[i]);
            }
        }


        private void HandleResponses()
        {
            Response r;
            string[] sep = new string[] { "::::" };
            while (!this.isOut)
            {
                this.responses = (ConcurrentQueue<Response>)Application.Current.Properties["Responses"];

                if (this.responses.Count() > 0)
                {
                    this.responses.TryDequeue(out r);

                    switch (r.code)
                    {
                        case 320:
                            string[] userInfo;
                            userInfo = r.objects[1].Split(sep, StringSplitOptions.RemoveEmptyEntries);
                            Dispatcher.BeginInvoke((Action)(() =>
                            {
                                this.UsersList.Items.Add(new UserInfo(Convert.ToBoolean(Convert.ToInt16(userInfo[1])), userInfo[0], Convert.ToBoolean(Convert.ToInt16(userInfo[2]))));
                            }));
                            break;

                        case 230:
                            string[] userInfo2;
                            userInfo2 = r.objects[1].Split(sep, StringSplitOptions.RemoveEmptyEntries);
                            Dispatcher.BeginInvoke((Action)(() =>
                            {
                                this.UsersList.Items.Remove(new UserInfo(Convert.ToBoolean(Convert.ToInt16(userInfo2[1])), userInfo2[0], Convert.ToBoolean(Convert.ToInt16(userInfo2[2]))));
                            }));
                            break;

                        case 303:
                            if(this.username == r.objects[1])
                            {
                                Dispatcher.BeginInvoke((Action)(() =>
                                {
                                    MessageRecived m = new MessageRecived(r.objects[2]);
                                    this.MessagesList.Items.Add(m);
                                }));
                                
                                break;
                            }

                            Dispatcher.BeginInvoke((Action)(() =>
                            {
                                for (int i = 0; i < this.UsersList.Items.Count; i++)
                                {
                                    UserInfo usr = (UserInfo)this.UsersList.Items[i];
                                    if (usr.GetUsername() == r.objects[1])
                                    {
                                        ((UserInfo)this.UsersList.Items[i]).SetToBlue();
                                        break;
                                    }
                                }
                            }));
                            break;

                        default:
                            break;
                            
                    }
                }

                Thread.Sleep(200);
            }

        }


    }
}
