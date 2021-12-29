#ifndef __BIG_NUM__
#define __BIG_NUM__

#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);
struct Complex  {
    double x, y;
    Complex(double _x=0.0,double _y = 0.0) {
        x = _x;
        y = _y;
    }
    Complex operator -(const Complex &b) const {
        return Complex(x-b.x, y-b.y);
    }
    Complex operator +(const Complex &b) const {
        return Complex(x+b.x, y+b.y);
    }
    Complex operator *(const Complex &b) const {
        return Complex(x*b.x-y*b.y, x*b.y+y*b.x);
    }
};

void change(Complex y[], int len) {
    int i,j,k;
    for(i = 1, j = len/2; i < len-1; i++) {
        if(i < j) swap(y[i],y[j]);
        k = len/2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
void fft(Complex y[], int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0; j <= len; j+= h) {
            Complex w(1,0);
            for(int k = j; k < j+h/2; k++) {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++)
            y[i].x /= len;
}
const int N = 3e6+100;

class BIG_NUM
{
private:
    string num_base;
    int len;
public:
    string Get_Number() const
    {
        return num_base;
    }

    BIG_NUM ()
    {
        num_base="0";
        len=1;
    }

    BIG_NUM(string str)
    {
        for(int i=0;i<str.size();i++)
            if(!(str[i]>'0' && str[i]<='9'))
            {
                cerr<<"error : str can oly contain numbers(0~9)\nNow set to zero";

                num_base="0";
                len=1;

                return ;
            }

        num_base=str;
        len=str.size();
    }

    void set(string str)
    {
        for(int i=0;i<str.size();i++)
            if(!(str[i]>'0' && str[i]<='9'))
            {
                cerr<<"error : str can oly contain numbers(0~9)\nNow set to zero";

                num_base="0";
                len=1;

                return ;
            }

        num_base=str;
        len=str.size();
    }

    BIG_NUM operator*(const BIG_NUM &x) const
    {
        //By CSDN @lixuwei2333

        Complex x1[N]={},x2[N]={};
        int sum[N]={};
        string a=num_base,b=x.Get_Number();
        int flag = 1;
        int len1 = a.length();
        int len2 = b.length();
        reverse(a.begin(),a.end());  //方便之后进位
        reverse(b.begin(),b.end());

        int len = 1;
        while(len < len1*2 || len < len2*2) len <<= 1;
        for(int i = 0; i < len1; i++) x1[i] = Complex(a[i]-'0',0);
        for(int i = len1; i < len; i++) x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++) x2[i] = Complex(b[i]-'0',0);
        for(int i = len2; i < len; i++) x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++) x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);

        for(int i = 0; i < len; i++)
            sum[i] = (int)(x1[i].x+0.5);
        for(int i = 0; i < len; i++) {
            sum[i+1] += sum[i]/10;
            sum[i] %= 10;
        }
        int top = len1+len2-1;
        while(top>0&&sum[top]<=0) top--;

        BIG_NUM ans;
        string str;

        for(int i = top; i >= 0; i--)
            str+=(char)sum[i]+'0';

        ans.set(str);

        return ans;
    }
};
typedef BIG_NUM bign;

#endif
