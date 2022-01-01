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
using System.Windows.Shapes;

namespace gui
{
    /// <summary>
    /// Interaction logic for Connection.xaml
    /// </summary>
    public partial class Connection : Window
    {
        private Communicator _communicator;
        public Connection()
        {
            InitializeComponent();
            Application.Current.Properties["Com"] = new Communicator();
            this._communicator = (Communicator)Application.Current.Properties["Com"];
        }

        private void EnterGhost_Click(object sender, RoutedEventArgs e)
        {
            (int code, string msg) res = this._communicator.Ghost();

            if (res.code == 400)
            {
                this.ErrorGhost.Text = res.msg;
            }
            else
            {
                this._communicator.SetUserName(res.msg);
                MainWindow wnd = new MainWindow(res.msg);
                this.Close();
                wnd.ShowDialog();
            }
        }

        private void EnterLogIn_Click(object sender, RoutedEventArgs e)
        {
            if (this.PasswordLogIn.Text == " " || this.UserNameLogIn.Text == " ")
            {
                this.ErrorLogIn.Text = "Please enter all needed values";
            }
            if(this.PasswordLogIn.Text.Contains('~') || this.UserNameLogIn.Text.Contains('~'))
            {
                this.ErrorLogIn.Text = "Please do not enter username or password that contains '~'";
            }
            else
            {
                string res = this._communicator.Login(this.UserNameLogIn.Text, this.PasswordLogIn.Text);

                if (res != "")
                {
                    this.ErrorLogIn.Text = res;
                }
                else
                {
                    this._communicator.SetUserName(this.UserNameLogIn.Text);
                    MainWindow wnd = new MainWindow(this.UserNameLogIn.Text);
                    this.Close();
                    wnd.ShowDialog();
                }
            }
        }

        private void EnterSignUp_Click(object sender, RoutedEventArgs e)
        {
            if (this.PasswordSignUp.Text == " " || this.PasswordConfirmSignUp.Text == " " || this.UserNameSignUp.Text == " ")
            {
                this.ErrorSignUp.Text = "Please enter all needed values";
            }
            else if (this.PasswordSignUp.Text != this.PasswordConfirmSignUp.Text)
            {
                this.ErrorSignUp.Text = "Passwords does not match";
            }

            if (this.PasswordSignUp.Text.Contains('~') || this.UserNameSignUp.Text.Contains('~'))
            {
                this.ErrorSignUp.Text = "Please do not enter username or password that contains '~'";
            }
            else
            {
                string res = this._communicator.SignUp(this.UserNameSignUp.Text, this.PasswordSignUp.Text);

                if (res != "")
                {
                    this.ErrorSignUp.Text = res;
                }
                else
                {
                    this._communicator.SetUserName(UserNameSignUp.Text);
                    MainWindow wnd = new MainWindow(this.UserNameSignUp.Text);
                    this.Close();
                    wnd.ShowDialog();
                }
            }
        }
    }
}
