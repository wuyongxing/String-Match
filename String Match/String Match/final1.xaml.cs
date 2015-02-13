﻿using System;
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
    /// final1.xaml 的交互逻辑
    /// </summary>
    public partial class final1 : Window
    {
        public final1()
        {
            InitializeComponent();
        }
        public string file;
        public string string1;
        public int n;
        private void Window_Closed(object sender, EventArgs e)
        {
            byhand x = new byhand();
            x.hand1.Text = file;
            x.ShowDialog();
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var lst = sender as System.Windows.Controls.ListBox;
            showtxt x = new showtxt();
            x.show.Text = string1;
            int index = (int)lst.SelectedItem;
            x.show.Select(index, n);
            x.show.Focus();
            //x.show.LineUp();
            x.ShowDialog();
        }
    }
}
