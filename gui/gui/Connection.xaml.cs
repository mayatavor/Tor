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

        }

        private void EnterLogIn_Click(object sender, RoutedEventArgs e)
        {

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
                bool res = this._communicator.Login(this.UserNameSignUp.Text, this.PasswordSignUp.Text);

                if (res == false)
                {
                    this.ErrorSignUp.Text = "The user can't be logged";
                }
                else
                {
                   // MainWindow wnd = new MainWindow(this._communicator);
                   // this.Close();
                   // wnd.ShowDialog();
                }
            }
        }
    }
}
