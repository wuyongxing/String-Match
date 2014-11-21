#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <string>
#define d 128//ascii表的128个字符。
#define q 127//RK算法里hash模的一个素数。
#define maxn 10000//串的最大长度。可以根据情况修改。
using namespace std;
void BF(char *s,char *p)//朴素匹配
{
    LARGE_INTEGER BegainTime ;//设置时间变量，测试匹配时间。
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    bool flag = false;//判断是否匹配到。
    int j,i = 0;
    int ans = 0;//统计匹配成功的次数。
    int lens = strlen(s);//主串的长度
    int lenp = strlen(p);//模式串的长度
    while(i <= lens - lenp)
    {
        j = 0;//每次匹配模式串都从0开始。
        while(s[i] == p[j] && j < lenp)
        {
            i++;//如果模式串和主串这一位字符相同，这两个串都往后匹配一位。
            j++;
        }
        if(j == lenp)//匹配完之后判断匹配上的长度是否等于模式串的长度
        {
            if(!flag) QueryPerformanceCounter(&EndTime);
            flag = true;
            ans++;
            cout<<"find "<<p<<" in position "<<i - lenp<<endl;//匹配成功，输出匹配成功的起始位置。
        }
        else i = i - j + 1;//没匹配上，主串需要回溯。
    }
    if(flag) cout << p <<" 在 "<< s <<" 中出现了 "<< ans <<" 次。"<<endl;
    if(flag) cout << "朴素算法匹配成功所花费的时间为（单位：s）：" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //输出第一次匹配到所花费的时间。
    else cout<<"Can't find "<<p<<endl;//匹配不成功。
}
void RK(char *s, char *p)//RK匹配算法
{
    LARGE_INTEGER BegainTime ;//设置时间变量，测试匹配时间。
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    int lenp = strlen(p);//模式串长度
    int lens = strlen(s);//主串长度。
    int w = 0,t = 0,h = 1,j;//w是模式串哈希值，t是主串哈希值，h是最高位的值。
    bool flag = false;
    int ans = 0;//统计匹配成功的次数。
    for(int i = 0; i < lenp - 1; i++)
        h = (h * d) % q;//求最高位值
    for(int i = 0; i < lenp; i++)
    {
        w = (d * w + p[i]) % q;//求模式串哈希值。
        t = (d * t + s[i]) % q;//求主串哈希值。
    }
    for(int i = 0; i <= lens - lenp; i++)
    {
        if(w == t)//判断模式串哈希值是否等于主串哈希值。
        {
            for(j = 0; j < lenp; j++)//深入匹配，确认两串是否相等。
                if(s[i + j] != p[j]) break;
            if(j == lenp)//判断相同串的长度是否等于模式串的长度。
            {
                if(!flag) QueryPerformanceCounter(&EndTime);
                flag = true;
                ans++;
                cout<<"find "<<p<<" in position "<<i<<endl;//匹配成功，输出匹配成功的初始位置。
            }
        }
        if(i < lens - lenp)//模式串与主串的哈希值不相同，模式串向右移动。
        {
            t = (d *(t - s[i] * h) + s[i+lenp])%q;//通过减去最高位的值*进制数+下一位的哈希值来进行巧妙右移。
            if(t < 0) t += q;
        }
    }
    if(flag) cout << p <<" 在 "<< s <<" 中出现了 "<< ans <<" 次。"<<endl;
    if(flag) cout << "RK算法匹配成功所花费的时间为（单位：s）：" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //匹配成功，输出第一次匹配成功所花费的时间。
    else cout<<"Can't find "<<p<<endl;//匹配不成功。
}
void getnext(char * t,int *next)//预处理next数组。
{
    int lenp = strlen(t);//模式串的长度。
    int i = 0,k = -1;
    next[0] = -1;//初始化next数组。
    while(i < lenp)
    {
        if(k == -1 || t[i] == t[k])//若t[i]==t[k]，则有t[0..k]==t[i-k,i]，很显然，next[i+1]=next[i]+1=k+1;
        {
            i++;
            k++;
            next[i] = k;
        }
        else k = next[k];//若t[i]!=t[k]，则可以把其看做模式匹配的问题，即匹配失败的时候，k值如何移动，显然k=next[k]。
    }
}
void KMP(char *s,char *p)//KMP算法
{
    LARGE_INTEGER BegainTime ;//设置时间变量。
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    int next[maxn];
    int i = 0,j = 0;
    int ans = 0;//统计匹配成功的次数。
    bool flag = false;
    int lens = strlen(s);//主串长度。
    int lenp = strlen(p);//模式串长度。
    getnext(p,next);//预处理next数组。
    while(i < lens)
    {
        if(j == -1 || s[i] == p[j]) //这一位相同，就往后一位匹配。
        {
            i++;
            j++;
        }
        else j = next[j];//匹配不上，从next数组中取出模式串
        if(j == lenp)//判断匹配上的长度是否等于模式串长度。
        {
            if(!flag) QueryPerformanceCounter(&EndTime);
            flag = true;
            ans++;
            cout<<"find "<<p<<" in position "<<i - lenp<<endl;//匹配成功，输出匹配成功的起始位置。
        }
    }
    if(flag) cout << p <<" 在 "<< s <<" 中出现了 "<< ans <<" 次。"<<endl;
    if(flag) cout << "KMP算法匹配成功所花费的时间为（单位：s）：" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //输出第一次匹配成功所花费的时间。
    else cout<<"Can't find "<<p<<endl;//匹配失败。
}
bool menu()//菜单函数。
{
    cout<<"选择从文件读取待匹配文本或者键入待匹配文本:"<<endl;
    cout<<"从文件读取待匹配文本请输入1，键入待匹配文本请输入2:"<<endl;
    int x;
    cin>>x;
    getchar();
    if(x == 1) return false;
    else return true;
}
void in(char *s,int len)//读文件函数。从文件中读取
{
    string f;
    cin>>f;//读入文件名。
    getchar();
    fstream file;
    file.open(f.c_str(),ios::in);
    file.getline(s,len);//读取一行字符串。
    file.close();
}
bool check(char *p)//判断输入的字符是否合法。不允许出现英文文本以外的字符。
{
    for(int i = 0; i < (int) strlen(p); i++)
     {
         int x = p[i];
         if(x < 0 || x > 256) return false;
     }
    return true;
}
int main()
{
    bool flag1 = true;
    while(flag1)
    {
        char s[maxn],p[maxn];//主串和模式串。
        bool flag = menu();//选择读入主串方式。
        if(!flag)
        {
            cout<<"请输入文件名以及扩展名:"<<endl;
            int len = sizeof(s);
            in(s,len);
            while(!check(s))
            {
                cout<<"读入的文本中有非法字符，请修改后重新输入文件名以及扩展名:"<<endl;
                in(s,len);
            }
        }
        else
        {
            cout<<"请输入待匹配字符串:"<<endl;
            gets(s);
            while(!check(s))
            {
                cout<<"输入的字符有误，请重新输入:"<<endl;
                gets(s);
            }
        }
        int flag2 = true;
        while(flag2)
        {
            cout<<"请输入匹配字符串:"<<endl;
            gets(p);
            while(!check(p))
            {
                cout<<"输入的字符有误，请重新输入:"<<endl;
                gets(p);
            }
            cout<<"BF算法:"<<endl;
            BF(s,p);
            cout<<"RK算法:"<<endl;
            RK(s,p);
            cout<<"KMP算法:"<<endl;
            KMP(s,p);
            cout<<"继续匹配该待匹配串请输入1，换一个待匹配串匹配请输入2，退出程序请输入3。"<<endl;
            int x;
            cin>>x;
            getchar();
            if(x == 2) flag2 = false;
            else if(x == 3)
            {
                flag1 = true;
                flag2 = false;
            }
        }
    }
    cout<<"程序结束,再会."<<endl;
    return 0;
}
