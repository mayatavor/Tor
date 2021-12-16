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
            this._communicator = new Communicator();
        }

        private void EnterGhost_Click(object sender, RoutedEventArgs e)
        {
            string res = this._communicator.Ghost();

            if (res != "")
            {
                this.ErrorGhost.Text = res;
            }
            else
            {
                MainWindow wnd = new MainWindow(this._communicator);
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
            else
            {
                string res = this._communicator.Login(this.UserNameLogIn.Text, this.PasswordLogIn.Text);

                if (res != "")
                {
                    this.ErrorLogIn.Text = res;
                }
                else
                {
                    MainWindow wnd = new MainWindow(this._communicator);
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
            else
            {
                string res = this._communicator.SignUp(this.UserNameSignUp.Text, this.PasswordSignUp.Text);

                if (res != "")
                {
                    this.ErrorSignUp.Text = res;
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
}
