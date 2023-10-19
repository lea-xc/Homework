#include<iostream>
#include<cmath>
#include <time.h>　
#include <windows.h>　
#include<string>
using namespace std;
int* Good(string pat)
{
    int n = pat.length();
    int num = 0;
    int* SS = new int[n];
    //for (int i = 0; i < n; i++)
    SS[n - 1] = n;
    for (int i = n - 2; i >= 0; i--)
    {
        int k = n - 1;
        num = 0;
        for (int j = i; j >= 0; j--, k--)
            if (pat[j] == pat[k])
                num++;
            else break;
        SS[i] = num;
    }
    int* GS = new int[n];
    for (int i = 0; i < n; i++)
        GS[i] = n;
    for (int i = 0; i < n - 1; i++)
        if (SS[i] != 0)
        {
            for (int j = 0; j < n - SS[i]; j++)
                if (GS[j] > n - SS[i])
                    GS[j] = n - SS[i];
        }
    for (int i = 0; i < n - 1; i++)
    {
        int k = SS[i];
        if (GS[n - 1 - k] > n-1-i)
            GS[n - 1 - k] = n-1-i;
    }

  //  for (int i = 0; i < n; i++)
  //      cout << pat[i] << ' ' << GS[i] << endl;

    return GS;
}
int Bad(string& pat, int i,char ch)
{
    /*int* bad;
    bad=new int[256];
    int n = pat.length();
    for (int i = 0; i < 256; i++)
        bad[i] = -1;
    for (int i = 0; i < n; i++)
        bad[(int)pat[i]] = i;
        */
    int badskip;
    for (badskip = 1; i - badskip >= 0; badskip++)
        if (pat[i - badskip] == ch)
            break;
    return badskip;
}
void BM(string mainstr, string patstr)
{
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    int m = mainstr.length();
    int n = patstr.length();
    int mainstr_p = n;
    //int* bad = Bad(patstr);
    int* good = Good(patstr);
    int badskip, goodskip, skip;
    int j = mainstr_p - 1;
    int i = n - 1;
    int num = 0;
    for (; i >= 0 && mainstr_p <= m; j--, i--)
    {
        num++;
        if (patstr[i] == mainstr[j])
        {
            //cout << "i=" << i << endl;
            continue;
        }
        else
        {
            goodskip = good[i];
           // badskip = i - bad[(int)mainstr[j]];
            badskip = Bad(patstr, i, mainstr[j]);
           // if (badskip < 0)
             //   badskip = 1;
            // cout << "i" << i<<" "<< bad[(int)mainstr[j]];
             //cout <<" good"<< goodskip << " bad" << badskip << endl;
            skip = max(goodskip, badskip);
            mainstr_p += skip;
            i = n;
            j = mainstr_p;
            // cout << "skip=" << skip << " j=" << j << endl;

        }
    }
    QueryPerformanceCounter(&t2);
    double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    cout << "BM算法对比了" << num << "次" <<"耗费了"<<time <<"us"<< endl;
    if (i == -1)
        cout << j - i << endl;
    else
        cout << "no" << endl;
}
void KMP(string mainstr, string patstr)
{
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    int n = patstr.length();
    int m = mainstr.length();
    int next[50];
    int j = 0;
    next[0] = -1;
    int k = -1;
    int num = 0;
    while (j < n)
    {
        if (k == -1 || patstr[j] == patstr[k])
            next[++j] = ++k;
        else
            k = next[k];
    }
    for (int i = 1; i < n; i++)
        if (patstr[i] == patstr[next[i]])
            next[i] = next[next[i]];
    k = -1;
    j = -1;
    while (j < m && k < n)
    {
        num++;
        if (k == -1 || mainstr[j] == patstr[k])
        {
            //cout << "k=" << k << " j=" << j << endl;
            j++;
            k++;

        }
        else
        {
            k = next[k];
        }
    }
    QueryPerformanceCounter(&t2);
    double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    cout << "KMP算法对比了" << num << "次" << "耗费了" << time << "us" << endl;
    if (k == n)
        cout << j - k << endl;
    else
        cout << "no";
    
}
int main()
{
    string mainstr, patstr;
    while (getline(cin,mainstr)&&getline(cin,patstr))
    {
        BM(mainstr, patstr);
        KMP(mainstr, patstr);
    }
    return 0;
}
