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
    /// byhand.xaml 的交互逻辑
    /// </summary>
    public partial class byhand : Window
    {
        public byhand()
        {
            InitializeComponent();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            MainWindow x = new MainWindow();
            x.ShowDialog();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string selectedText = "";
            ComboBoxItem cbi = (ComboBoxItem)choose1.SelectedItem;
            if (cbi != null) selectedText = cbi.Content.ToString();
            if (hand1.Text != "" && hand2.Text != "" && cbi != null)
            {
                bool flagstring1 = false;
                bool flagstring2 = false;
                for (int i = 0; i < hand1.Text.Length; i++)
                    if (hand1.Text[i] < 0 || hand1.Text[i] > 127)
                    {
                        flagstring1 = true;
                        break;
                    }
                for (int i = 0; i < hand2.Text.Length; i++)
                    if (hand2.Text[i] < 0 || hand2.Text[i] > 127)
                    {
                        flagstring2 = true;
                        break;
                    }
                if (flagstring1 == true && flagstring2 == true)
                {
                    this.Hide();
                    warning1 w = new warning1();
                    //w.file1 = filein1.Text;
                    //w.file2 = string2.Text;
                    w.warn2.Text = "英文文本和匹配字符串中都有非英文字符，请重新输入。";
                    w.ShowDialog();
                }
                else if (flagstring1 == false && flagstring2 == true)
                {
                    this.Hide();
                    warning1 w = new warning1();
                    w.file1 = hand1.Text;
                    //w.file2 = string2.Text;
                    w.warn2.Text = "匹配字符串中有非英文字符，请重新输入。";
                    w.ShowDialog();
                }
                else if (flagstring1 == true && flagstring2 == false)
                {
                    this.Hide();
                    warning1 w = new warning1();
                    //w.file1 = filein1.Text;
                    w.file2 = hand2.Text;
                    w.warn2.Text = "英文文本中有非英文字符，请重新输入。";
                    w.ShowDialog();
                }
                else
                {
                    final1 x = new final1();
                    x.string1 = hand1.Text;
                    x.n = hand2.Text.Length;
                    this.Hide();
                    x.file = hand1.Text;
                    x.finaltext.Text = "";
                    if (selectedText == "朴素算法")
                    {
                        algorithm y = new algorithm();
                        double time = y.BF(hand1.Text, hand2.Text);
                        x.finaltext.Text += selectedText + ":\n";
                        if (y.len == 0)
                            x.finaltext.Text += "匹配失败，该串在文本中未出现。";
                        else
                        {
                            x.finaltext.Text += "匹配成功所花的时间是 " + time + "秒（s）\n" + "该串在文本中出现了" + y.len + "次\n初始位置分别是：\n";
                            for (int i = 1; i <= y.len; i++)
                            {
                                x.list.Items.Add(y.a[i]);
                            }
                        }
                        x.ShowDialog();
                    }
                    else if (selectedText == "Rabin-Karp算法")
                    {
                        algorithm y = new algorithm();
                        double time = y.RK(hand1.Text, hand2.Text);
                        x.finaltext.Text += selectedText + ":\n";
                        if (y.len == 0)
                            x.finaltext.Text += "匹配失败，该串在文本中未出现。";
                        else
                        {
                            x.finaltext.Text += "匹配成功所花的时间是 " + time + "秒（s）\n" + "该串在文本中出现了" + y.len + "次\n初始位置分别是：\n";
                            for (int i = 1; i <= y.len; i++)
                            {
                                x.list.Items.Add(y.a[i]);
                            }
                        }
                        x.ShowDialog();
                    }
                    else if (selectedText == "KMP算法")
                    {
                        algorithm y = new algorithm();
                        double time = y.RK(hand1.Text, hand2.Text);
                        x.finaltext.Text += selectedText + ":\n";
                        if (y.len == 0)
                            x.finaltext.Text += "匹配失败，该串在文本中未出现。";
                        else
                        {
                            x.finaltext.Text += "匹配成功所花的时间是 " + time + "秒（s）\n" + "该串在文本中出现了" + y.len + "次\n初始位置分别是：\n";
                            for (int i = 1; i <= y.len; i++)
                            {
                                x.list.Items.Add(y.a[i]);
                            }
                        } 
                        x.ShowDialog();
                    }
                    else if (selectedText == "选择三种算法进行比较")
                    {
                        algorithm y = new algorithm();
                        double time1 = y.BF(hand1.Text, hand2.Text);
                        double time2 = y.RK(hand1.Text, hand2.Text);
                        double time3 = y.KMP(hand1.Text, hand2.Text);
                        x.finaltext.Text += selectedText + ":\n";
                        if (y.len == 0)
                            x.finaltext.Text += "匹配失败，该串在文本中未出现。";
                        else
                        {
                            x.finaltext.Text += "朴素算法匹配所花费的时间是 " + time1 + "秒（s）\n" + "RK算法匹配所花费的时间是 " + time2 + "秒（s）\n" + "KMP算法匹配所花费的时间是 " + time3 + "秒（s）\n";
                            int faster = y.maxtime(time1, time2, time3);
                            int slower = y.mintime(time1, time2, time3);
                            if (faster == 0) x.finaltext.Text = "三种算法用时一样";
                            else
                            {
                                if (faster == 4) x.finaltext.Text += "朴素算法最快\n";
                                else if (faster == 2) x.finaltext.Text += "RK算法最快\n";
                                else if (faster == 1) x.finaltext.Text += "KMP算法最快\n";
                                else if (faster == 6) x.finaltext.Text += "朴素算法和RK算法最快\n";
                                else if (faster == 5) x.finaltext.Text += "朴素算法和KMP算法最快\n";
                                else if (faster == 3) x.finaltext.Text += "RK算法和KMP算法最快\n";
                                if (slower == 4) x.finaltext.Text += "朴素算法最慢\n";
                                else if (slower == 2) x.finaltext.Text += "RK算法最慢\n";
                                else if (slower == 1) x.finaltext.Text += "KMP算法最慢\n";
                                else if (slower == 6) x.finaltext.Text += "朴素算法和RK算法最慢\n";
                                else if (slower == 5) x.finaltext.Text += "朴素算法和KMP算法最慢\n";
                                else if (slower == 3) x.finaltext.Text += "RK算法和KMP算法最慢\n";
                            }
                            x.finaltext.Text += "该串在文本中出现了" + y.len + "次\n初始位置分别是：\n";
                            for (int i = 1; i <= y.len; i++)
                            {
                                x.list.Items.Add(y.a[i]);
                            }
                        }
                        x.ShowDialog();
                    }
                }
            }
        }
    }
}
