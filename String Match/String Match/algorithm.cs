using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace String_Match
{
    class algorithm
    {
        [System.Runtime.InteropServices.DllImport("Kernel32.dll")]
        static extern bool QueryPerformanceCounter(ref long count);
        [System.Runtime.InteropServices.DllImport("Kernel32.dll")]
        static extern bool QueryPerformanceFrequency(ref long count);
        public int len = 0;
        public int[] a = new int[1000000];
        public double BF(string s,string p)
        {
            long count = 0;
            long count1 = 0;
            long freq = 0;
            double result = 0;
            QueryPerformanceFrequency(ref freq);//获得机器内部计时器的时钟频率。
            QueryPerformanceCounter(ref count);//开始计时。
            int j, i = 0;
            int lens = s.Length;//主串的长度
            int lenp = p.Length;//模式串的长度
            len = 0;
            while (i <= lens - lenp)
            {
                j = 0;//每次匹配模式串都从0开始。
                while (j < lenp && s[i] == p[j])
                {
                    i++;//如果模式串和主串这一位字符相同，这两个串都往后匹配一位。
                    j++;
                }
                if (j == lenp)//匹配完之后判断匹配上的长度是否等于模式串的长度
                {
                    a[++len] = i - lenp;
                }
                else i = i - j + 1;//没匹配上，主串需要回溯。
            }
            QueryPerformanceCounter(ref count1);//结束计时。
            count = count1 - count;
            result = (double)(count) / (double)freq;
            return result;
        }
        public double RK(string s, string p)//RK匹配算法
        {
            int d = 128;//进制数。
            int q = 127;//mod的数。
            long count = 0;
            long count1 = 0;
            long freq = 0;
            double result = 0;
            QueryPerformanceFrequency(ref freq);//获得机器内部计时器的时钟频率。
            QueryPerformanceCounter(ref count);//开始计时。
            int lenp = p.Length;//模式串长度
            int lens = s.Length;//主串长度。
            int w = 0, t = 0, h = 1, j;//w是模式串哈希值，t是主串哈希值，h是最高位的值。
            len = 0;//统计匹配成功的次数。
            for (int i = 0; i < lenp - 1; i++)
                h = (h * d) % q;//求最高位值
            for (int i = 0; i < lenp && i < lens; i++)
            {
                w = (d * w + p[i]) % q;//求模式串哈希值。
                t = (d * t + s[i]) % q;//求主串哈希值。
            }
            for (int i = 0; i <= lens - lenp; i++)
            {
                if (w == t)//判断模式串哈希值是否等于主串哈希值。
                {
                    for (j = 0; j < lenp; j++)//深入匹配，确认两串是否相等。
                        if (s[i + j] != p[j]) break;
                    if (j == lenp)//判断相同串的长度是否等于模式串的长度。
                    {
                        a[++len] = i;
                    }
                }
                if (i < lens - lenp)//模式串与主串的哈希值不相同，模式串向右移动。
                {
                    t = (d * (t - s[i] * h) + s[i + lenp]) % q;//通过减去最高位的值*进制数+下一位的哈希值来进行巧妙右移。
                    if (t < 0) t += q;
                }
            }
            QueryPerformanceCounter(ref count1);//结束计时
            count = count1 - count;
            result = (double)(count) / (double)freq;
            return result;
        }
        public double KMP(string s,string p)//KMP算法
        {
            long count = 0;
            long count1 = 0;
            long freq = 0;
            double result = 0;
            QueryPerformanceFrequency(ref freq);
            QueryPerformanceCounter(ref count);
            int[] next = new int[1000000];
            int i = 0,j = 0;
            len = 0;//统计匹配成功的次数。
            int lens = s.Length;//主串长度。
            int lenp = p.Length;//模式串长度。
            int k = -1;
            next[0] = -1;//初始化next数组。
            while(i < lenp)
            {
                if(k == -1 || p[i] == p[k])//若p[i]==p[k]，则有p[0..k]==p[i-k,i]，很显然，next[i+1]=next[i]+1=k+1;
                {
                    i++;
                    k++;
                    next[i] = k;
                }
                else k = next[k];//若p[i]!=p[k]，则可以把其看做模式匹配的问题，即匹配失败的时候，k值如何移动，显然k=next[k]。
            }
            i = j = 0;
            while(i < lens)
            {
                if(j == -1 || (j >= 0 && i >= 0 && i < lens && j < lenp && s[i] == p[j])) //这一位相同，就往后一位匹配。
                {
                    i++;
                    j++; 
                }
                else j = next[j];//匹配不上，从next数组中取出模式串
                if(j == lenp)//判断匹配上的长度是否等于模式串长度。
                {
                    a[++len] = i - lenp;
                }
            }
            QueryPerformanceCounter(ref count1);
            count = count1 - count;
            result = (double)(count) / (double)freq;
            return result;
        }
        public int maxtime(double time1, double time2, double time3)
        {
            int x = 0;
            double eps = 1e-12;
            if (time1 < eps && time2 < eps && time3 < eps) return -1;
            double[] time = new double[3];
            time[0] = time1;
            time[1] = time2;
            time[2] = time3;
            double max1 = Math.Max(Math.Max(time1, time2), time3);
            double min1 = Math.Min(Math.Min(time1, time2), time3);
            if (Math.Abs(max1 - min1) < eps) return 0;
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    if (Math.Abs(min1 - time[i]) < eps) x |= (1 << (2 - i));
                }
            }
            return x;
        }
        public int mintime(double time1, double time2, double time3)
        {
            int x = 0;
            double eps = 1e-12;
            if (time1 < eps && time2 < eps && time3 < eps) return -1;
            double[] time = new double[3];
            time[0] = time1;
            time[1] = time2;
            time[2] = time3;
            double max1 = Math.Max(Math.Max(time1, time2), time3);
            double min1 = Math.Min(Math.Min(time1, time2), time3);
            if (Math.Abs(max1 - min1) < eps) return 0;
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    if (Math.Abs(max1 - time[i]) < eps) x |= (1 << (2 - i));
                }
            }
            return x;
        }
    }
}
