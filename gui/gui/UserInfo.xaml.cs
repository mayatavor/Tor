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
        public UserInfo(bool isStar, string username)
        {
            this.star = isStar;
            this.username = username;
            InitializeComponent();

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
            if(this.star == true)
            {
                this.StarBackGround.Source = new BitmapImage(new Uri("Assets/fullHeart.png", UriKind.Relative));
                this.star = false;
            }
            else
            {
                this.StarBackGround.Source = new BitmapImage(new Uri("Assets/emptyHeart.png", UriKind.Relative));
                this.star = true;
            }

        }

        public string GetUsername()
        {
            return this.username;
        }
    }
}
