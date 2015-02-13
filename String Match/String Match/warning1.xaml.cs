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

namespace String_Match
{
    /// <summary>
    /// warning1.xaml 的交互逻辑
    /// </summary>
    public partial class warning1 : Window
    {
        public warning1()
        {
            InitializeComponent();
        }
        public string file1;
        public string file2;

        private void Window_Closed(object sender, EventArgs e)
        {
            byhand x = new byhand();
            x.hand1.Text = file1;
            x.hand2.Text = file2;
            this.Hide();
            x.ShowDialog();
        }
    }
}
