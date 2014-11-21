#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <string>
#define d 128//ascii���128���ַ���
#define q 127//RK�㷨��hashģ��һ��������
#define maxn 10000//������󳤶ȡ����Ը�������޸ġ�
using namespace std;
void BF(char *s,char *p)//����ƥ��
{
    LARGE_INTEGER BegainTime ;//����ʱ�����������ƥ��ʱ�䡣
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    bool flag = false;//�ж��Ƿ�ƥ�䵽��
    int j,i = 0;
    int ans = 0;//ͳ��ƥ��ɹ��Ĵ�����
    int lens = strlen(s);//�����ĳ���
    int lenp = strlen(p);//ģʽ���ĳ���
    while(i <= lens - lenp)
    {
        j = 0;//ÿ��ƥ��ģʽ������0��ʼ��
        while(s[i] == p[j] && j < lenp)
        {
            i++;//���ģʽ����������һλ�ַ���ͬ����������������ƥ��һλ��
            j++;
        }
        if(j == lenp)//ƥ����֮���ж�ƥ���ϵĳ����Ƿ����ģʽ���ĳ���
        {
            if(!flag) QueryPerformanceCounter(&EndTime);
            flag = true;
            ans++;
            cout<<"find "<<p<<" in position "<<i - lenp<<endl;//ƥ��ɹ������ƥ��ɹ�����ʼλ�á�
        }
        else i = i - j + 1;//ûƥ���ϣ�������Ҫ���ݡ�
    }
    if(flag) cout << p <<" �� "<< s <<" �г����� "<< ans <<" �Ρ�"<<endl;
    if(flag) cout << "�����㷨ƥ��ɹ������ѵ�ʱ��Ϊ����λ��s����" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //�����һ��ƥ�䵽�����ѵ�ʱ�䡣
    else cout<<"Can't find "<<p<<endl;//ƥ�䲻�ɹ���
}
void RK(char *s, char *p)//RKƥ���㷨
{
    LARGE_INTEGER BegainTime ;//����ʱ�����������ƥ��ʱ�䡣
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    int lenp = strlen(p);//ģʽ������
    int lens = strlen(s);//�������ȡ�
    int w = 0,t = 0,h = 1,j;//w��ģʽ����ϣֵ��t��������ϣֵ��h�����λ��ֵ��
    bool flag = false;
    int ans = 0;//ͳ��ƥ��ɹ��Ĵ�����
    for(int i = 0; i < lenp - 1; i++)
        h = (h * d) % q;//�����λֵ
    for(int i = 0; i < lenp; i++)
    {
        w = (d * w + p[i]) % q;//��ģʽ����ϣֵ��
        t = (d * t + s[i]) % q;//��������ϣֵ��
    }
    for(int i = 0; i <= lens - lenp; i++)
    {
        if(w == t)//�ж�ģʽ����ϣֵ�Ƿ����������ϣֵ��
        {
            for(j = 0; j < lenp; j++)//����ƥ�䣬ȷ�������Ƿ���ȡ�
                if(s[i + j] != p[j]) break;
            if(j == lenp)//�ж���ͬ���ĳ����Ƿ����ģʽ���ĳ��ȡ�
            {
                if(!flag) QueryPerformanceCounter(&EndTime);
                flag = true;
                ans++;
                cout<<"find "<<p<<" in position "<<i<<endl;//ƥ��ɹ������ƥ��ɹ��ĳ�ʼλ�á�
            }
        }
        if(i < lens - lenp)//ģʽ���������Ĺ�ϣֵ����ͬ��ģʽ�������ƶ���
        {
            t = (d *(t - s[i] * h) + s[i+lenp])%q;//ͨ����ȥ���λ��ֵ*������+��һλ�Ĺ�ϣֵ�������������ơ�
            if(t < 0) t += q;
        }
    }
    if(flag) cout << p <<" �� "<< s <<" �г����� "<< ans <<" �Ρ�"<<endl;
    if(flag) cout << "RK�㷨ƥ��ɹ������ѵ�ʱ��Ϊ����λ��s����" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //ƥ��ɹ��������һ��ƥ��ɹ������ѵ�ʱ�䡣
    else cout<<"Can't find "<<p<<endl;//ƥ�䲻�ɹ���
}
void getnext(char * t,int *next)//Ԥ����next���顣
{
    int lenp = strlen(t);//ģʽ���ĳ��ȡ�
    int i = 0,k = -1;
    next[0] = -1;//��ʼ��next���顣
    while(i < lenp)
    {
        if(k == -1 || t[i] == t[k])//��t[i]==t[k]������t[0..k]==t[i-k,i]������Ȼ��next[i+1]=next[i]+1=k+1;
        {
            i++;
            k++;
            next[i] = k;
        }
        else k = next[k];//��t[i]!=t[k]������԰��俴��ģʽƥ������⣬��ƥ��ʧ�ܵ�ʱ��kֵ����ƶ�����Ȼk=next[k]��
    }
}
void KMP(char *s,char *p)//KMP�㷨
{
    LARGE_INTEGER BegainTime ;//����ʱ�������
    LARGE_INTEGER EndTime ;
    LARGE_INTEGER Frequency ;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);
    int next[maxn];
    int i = 0,j = 0;
    int ans = 0;//ͳ��ƥ��ɹ��Ĵ�����
    bool flag = false;
    int lens = strlen(s);//�������ȡ�
    int lenp = strlen(p);//ģʽ�����ȡ�
    getnext(p,next);//Ԥ����next���顣
    while(i < lens)
    {
        if(j == -1 || s[i] == p[j]) //��һλ��ͬ��������һλƥ�䡣
        {
            i++;
            j++;
        }
        else j = next[j];//ƥ�䲻�ϣ���next������ȡ��ģʽ��
        if(j == lenp)//�ж�ƥ���ϵĳ����Ƿ����ģʽ�����ȡ�
        {
            if(!flag) QueryPerformanceCounter(&EndTime);
            flag = true;
            ans++;
            cout<<"find "<<p<<" in position "<<i - lenp<<endl;//ƥ��ɹ������ƥ��ɹ�����ʼλ�á�
        }
    }
    if(flag) cout << p <<" �� "<< s <<" �г����� "<< ans <<" �Ρ�"<<endl;
    if(flag) cout << "KMP�㷨ƥ��ɹ������ѵ�ʱ��Ϊ����λ��s����" <<(double)( EndTime.QuadPart - BegainTime.QuadPart )/ Frequency.QuadPart <<endl;
    //�����һ��ƥ��ɹ������ѵ�ʱ�䡣
    else cout<<"Can't find "<<p<<endl;//ƥ��ʧ�ܡ�
}
bool menu()//�˵�������
{
    cout<<"ѡ����ļ���ȡ��ƥ���ı����߼����ƥ���ı�:"<<endl;
    cout<<"���ļ���ȡ��ƥ���ı�������1�������ƥ���ı�������2:"<<endl;
    int x;
    cin>>x;
    getchar();
    if(x == 1) return false;
    else return true;
}
void in(char *s,int len)//���ļ����������ļ��ж�ȡ
{
    string f;
    cin>>f;//�����ļ�����
    getchar();
    fstream file;
    file.open(f.c_str(),ios::in);
    file.getline(s,len);//��ȡһ���ַ�����
    file.close();
}
bool check(char *p)//�ж�������ַ��Ƿ�Ϸ������������Ӣ���ı�������ַ���
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
        char s[maxn],p[maxn];//������ģʽ����
        bool flag = menu();//ѡ�����������ʽ��
        if(!flag)
        {
            cout<<"�������ļ����Լ���չ��:"<<endl;
            int len = sizeof(s);
            in(s,len);
            while(!check(s))
            {
                cout<<"������ı����зǷ��ַ������޸ĺ����������ļ����Լ���չ��:"<<endl;
                in(s,len);
            }
        }
        else
        {
            cout<<"�������ƥ���ַ���:"<<endl;
            gets(s);
            while(!check(s))
            {
                cout<<"������ַ���������������:"<<endl;
                gets(s);
            }
        }
        int flag2 = true;
        while(flag2)
        {
            cout<<"������ƥ���ַ���:"<<endl;
            gets(p);
            while(!check(p))
            {
                cout<<"������ַ���������������:"<<endl;
                gets(p);
            }
            cout<<"BF�㷨:"<<endl;
            BF(s,p);
            cout<<"RK�㷨:"<<endl;
            RK(s,p);
            cout<<"KMP�㷨:"<<endl;
            KMP(s,p);
            cout<<"����ƥ��ô�ƥ�䴮������1����һ����ƥ�䴮ƥ��������2���˳�����������3��"<<endl;
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
    cout<<"�������,�ٻ�."<<endl;
    return 0;
}
