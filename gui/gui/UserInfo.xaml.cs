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
    /// Interaction logic for UserInfo.xaml
    /// </summary>
    public partial class UserInfo : UserControl
    {
        private bool star;
        private string username;
        private Communicator _communicator;
        public UserInfo(bool isStar, string username, bool g)
        {
            InitializeComponent();
            this.star = isStar;
            this.username = username;

            if (g == true)
            {
                this.StarBackGround.Source = new BitmapImage(new Uri("Assets/ghost.png", UriKind.Relative));
            }
            else
            {
                this.GhostOrPerson.Source = new BitmapImage(new Uri("Assets/face1.png", UriKind.Relative));
            }

            this._communicator = (Communicator)Application.Current.Properties["Com"];

            if (this.star == true)
            {
                this.StarBackGround.Source = new BitmapImage(new Uri("Assets/fullHeart.png", UriKind.Relative));
                this.star = false;
            }
            else
            {
                this.StarBackGround.Source = new BitmapImage(new Uri("Assets/emptyHeart.png", UriKind.Relative));
                this.star = true;
            }

            this.UserName_Name.Text = username;
        }

        private void StarOrNot_Click(object sender, RoutedEventArgs e)
        {
            if (this.star == true)
            {
                if (this._communicator.RemoveFromFavorites(this._communicator.GetUserName(), this.username))
                {
                    this.StarBackGround.Source = new BitmapImage(new Uri("Assets/fullHeart.png", UriKind.Relative));
                    this.star = false;
                }
                else
                {
                    MessageBoxResult result = MessageBox.Show("Could not add to favorites", "Favorites Error", MessageBoxButton.OK);
                }
            }
            else
            {
                if (this._communicator.AddToFavorites(this._communicator.GetUserName(), this.username))
                { 
                    this.StarBackGround.Source = new BitmapImage(new Uri("Assets/emptyHeart.png", UriKind.Relative));
                    this.star = true;
                }
                else
                {
                    MessageBoxResult result = MessageBox.Show("Could not remove from favorites", "Favorites Error", MessageBoxButton.OK);
                }
            }

        }

        public string GetUsername()
        {
            return this.username;
        }

        public bool GetStar()
        {
            return this.star;
        }
    }
}
