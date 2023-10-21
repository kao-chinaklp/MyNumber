#include "MyNumber.h"

#include <algorithm>

using std::string;
using std::ceil, std::reverse, std::max;

MyNumber::MyNumber(ll num){
    this->jump=false;
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.Clear();
    while(num){
        this->Number.PushBack(num%Lim);
        num/=Lim;
    }
}

MyNumber::MyNumber(string num){
    this->jump=false;
    if(num[0]=='-')this->Sign=true,num.erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    string tmp;
    for(int i=0, len=num.size();i<len;i+=9){
        tmp=num.substr(i,std::min(9, len-i));
        this->Number.PushBack(atoi(tmp.c_str()));
    }
    reverse(this->Number.Begin(), this->Number.End());
}

MyNumber::MyNumber(MyNumber& num){
    this->jump=false;
    this->Sign=num.GetSign();
    this->Number=Vector<ui>(num.GetNumber());
}

MyNumber::~MyNumber(){
    this->Number.Clear();
    this->Number.ShrinkToFit();
}

MyNumber& MyNumber::operator=(ll num){
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.Clear();
    while(num){
        this->Number.PushBack(num%Lim);
        num/=Lim;
    }
    return *this;
}

MyNumber& MyNumber::operator=(string num){
    if(num[0]=='-')this->Sign=true,num.erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    int tmp,cnt=num.size()-1,bit;
    const ui _size=num.size();
    for(ui i=0,len=ceil(_size/9.0);i<len;i++){
        tmp=0, bit=1;
        while(bit!=Lim&&cnt>=0){
            tmp+=(num[cnt]-48)*bit;
            --cnt;
            bit*=10;
        }
        this->Number.PushBack(tmp);
    }
    return *this;
}

MyNumber& MyNumber::operator=(MyNumber& num){
    this->Sign=num.GetSign();
    this->Number=Vector<ui>(num.GetNumber());
    return *this;
}

bool MyNumber::GetSign()const{
    return this->Sign;
}

void MyNumber::SetSign(bool Sign){
    this->Sign=Sign;
}

ui MyNumber::GetSize()const{
    return this->Number.Size();
}

void MyNumber::SetSize(ui new_size){
    this->Number.Resize(new_size, 0);
}

Vector<ui> MyNumber::GetNumber(){
    return this->Number;
}

void MyNumber::RemoveLeadingZero(){
    while(this->GetSize()>1&&this->Number.Back()==0)
        this->Number.PopBack();
}

string MyNumber::Str(){
    string out="";
    for(int p=0,len=this->GetSize();p<len;p++){
        ui tmp=this->Number[p];
        int cnt=0;
        while(++cnt<=9&&tmp>0){
            out.push_back(tmp%10+48);
            tmp/=10;
        }
    }
    while(out.size()>1&&out.back()=='0')out.pop_back();
    reverse(out.begin(),out.end());
    if(this->Sign)out.insert(out.begin(),'-');
    return out;
}

ui& MyNumber::operator[](ui idx){
    return this->Number[idx];
}

MyNumber MyNumber::operator++(){
    if(this->Sign&&!this->jump){
        this->jump=true;
        return --(*this);
    }
    auto iter=this->Number.Begin();
    auto _End=this->Number.End();
    ++(*iter);
    while((++iter)!=_End){
        if(*(iter-1)!=Lim)break;
        ++(*iter);
        *(iter-1)=0;
    }
    if(this->GetSize()>1&&iter==_End||*(iter-1)==Lim){
        (*iter)=0;
        this->Number.PushBack(1);
    }
    this->jump=false;
    return *this;
}

MyNumber MyNumber::operator++(int){
    MyNumber tmp(*this);
    ++(*this);
    return tmp;
}

MyNumber MyNumber::operator--(){
    if(this->Sign&&!this->jump){
        if(this->Sign){
            this->jump=true;
            return ++(*this);
        }
        if((*this)==0){
            this->Sign=true;
            this->jump=true;
            return ++(*this);
        }
    }
    auto iter=this->Number.Begin();
    auto _End=this->Number.End();
    --(*iter);
    while((++iter)!=_End){
        if(*(iter-1)<Lim)break;
        --(*iter);
        *(iter-1)=Lim-1;
    }
    this->RemoveLeadingZero();
    if(this->GetSize()==1){
        if(this->Sign&&*(iter)==0)this->Sign=false;
        if(!this->Sign&&*(iter-1)>=Lim)this->Sign=true,*(iter-1)=1;
    }
    this->jump=false;
    return (*this);
}

MyNumber MyNumber::operator--(int){
    MyNumber tmp(*this);
    --(*this);
    return tmp;
}

MyNumber MyNumber::operator-(){
    MyNumber tmp(*this);
    tmp.SetSign(!this->Sign);
    return tmp;
}

bool MyNumber::operator==(ll num){
    MyNumber tmp(num);
    return (*this)==tmp;
}

bool MyNumber::operator==(MyNumber num){
    if(this->GetSize()!=num.GetSize())return false;
    if(this->GetSign()!=num.GetSign())return false;
    for(int i=0,len=this->GetSize();i<len;i++)
        if((*this)[i]!=num[i])return false;
    return true;
}

bool MyNumber::operator!=(ll num){
    MyNumber tmp(num);
    return !((*this)==tmp);
}

bool MyNumber::operator!=(MyNumber num){
    return !((*this)==num);
}

bool MyNumber::operator<(ll num){
    MyNumber tmp(num);
    return *this<tmp;
}

bool MyNumber::operator<(MyNumber num){
    if(this->Sign!=num.GetSign())return this->GetSign();
    if(this->GetSize()<num.GetSize())return true;
    if(this->GetSize()>num.GetSize())return false;
    for(int i=0,len=this->GetSize();i<len;i++){
        if((*this)[i]<num[i])return true;
        if((*this)[i]>num[i])return false;
    }
    return false;
}

bool MyNumber::operator>(ll num){
    MyNumber tmp(num);
    return *this<tmp;
}

bool MyNumber::operator>(MyNumber num){
    if(this->Sign!=num.GetSign())return !this->GetSign();
    if(this->GetSize()>num.GetSize())return true;
    if(this->GetSize()<num.GetSize())return false;
    for(int i=0,len=this->GetSize();i<len;i++){
        if((*this)[i]>num[i])return true;
        if((*this)[i]<num[i])return false;
    }
    return false;
}

bool MyNumber::operator<=(ll num){
    return !(*this>num);
}

bool MyNumber::operator<=(MyNumber num){
    return !(*this>num);
}

bool MyNumber::operator>=(ll num){
    return !(*this<num);
}

bool MyNumber::operator>=(MyNumber num){
    return !(*this<num);
}

MyNumber MyNumber::operator+(ll num){
    MyNumber tmp(num);
    return *this+tmp;
}

MyNumber MyNumber::operator+(MyNumber num){
    MyNumber tmp(*this), ans=0;
    if(num.GetSign())return tmp-(-num);
    else if(tmp.GetSign())return num-(-tmp);
    ui new_size=max(tmp.GetSize(),num.GetSize());
    ans.SetSize(new_size+1);
    tmp.SetSize(new_size);
    num.SetSize(new_size);
    for(ui i=0;i<new_size;i++){
        ans[i]=tmp[i]+num[i];
        ans[i+1]+=ans[i]/Lim;
        ans[i]%=Lim;
    }
    ans.RemoveLeadingZero();
    return ans;
}

MyNumber MyNumber::operator-(ll num){
    MyNumber tmp(num);
    return *this-tmp;
}

MyNumber MyNumber::operator-(MyNumber num){
    MyNumber tmp(*this), ans=0;
    if(num.GetSign())return tmp+(-num);
    else if(tmp.GetSign())return -((-tmp)+num);
    if(tmp<num){
        swap(tmp, num);
        ans.SetSign(true);
    }
    ui new_size=max(tmp.GetSize(),num.GetSize());
    ans.SetSize(new_size+1);
    tmp.SetSize(new_size);
    num.SetSize(new_size);
    for(ui i=0;i<new_size;i++){
        ans[i]=tmp[i]-num[i];
        if(ans[i]>=Lim){
            ans[i]+=Lim;
            ans[i+1]--;
        }
    }
    ans.RemoveLeadingZero();
    return ans;
}

MyNumber MyNumber::operator*(ll num){
    MyNumber tmp(num);
    return *this*tmp;
}

MyNumber MyNumber::operator*(MyNumber num){
    Vector<Complex> ans, num1, num2;
    Vector<ui> res;
    string str=this->Str();
    int len1=str.size();
    for(auto i=str.rbegin();i!=str.rend();i++)
        num1.PushBack(Complex(double(*i-48)));
        /////////////////////////bug
    for(auto i=0;i!=5;i++)
        printf("%s ",num1[i].Str().c_str());
    str=num.Str();
    int len2=str.size();
    for(auto i=str.rbegin();i!=str.rend();i++)
        num2.PushBack(Complex(double(*i-48)));
    int len=1, l=0;
    while(len<len1+len2)len<<=1,l++;
    ans.Resize(len);
    res.Resize(len);
    num1.Resize(len), num2.Resize(len);
    FFTInit(len, l);
    FFT(num1, len, 1);
    FFT(num2, len, 1);
    for(int i=0;i<len;i++)
        ans[i]=num1[i]*num2[i];
    FFT(ans, len, -1);
    for(int i=0;i<len;i++){
        res[i]+=ans[i].Real()/len+eps;
        if(i<len-1){
            res[i+1]+=res[i]/10;
            res[i]%=10;
        }
    }
    if(res.Back()>9){
        res.PushBack(res.Back()/10);
        *(res.End()-2)%=10;
        len++;
    }
    while(res[len-1]==0&&len>0)len--;
    while(len>0&&res[len-1]==0)len--;
    str.clear();
    for(int i=len-1;i>=0;i--)
        str.push_back(res[i]+48);
    return MyNumber(str);
}

void MyNumber::FFTInit(ui len, ui Size){
    rev.Resize(len);
    for(ui i=0;i<len;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(Size-1));
}

void MyNumber::FFT(Vector<Complex>& arr, int n, int inv){
    for(ui i=0;i<n;i++)
        if(i<rev[i])swap(arr[i], arr[rev[i]]);
    for(ui i=1;i<n;i<<=1){
        Complex wn(cos(pi/i), inv*sin(pi/i));
        for(ui j=0;j<n;j+=(i<<1)){
            Complex w0(1,0);
            for(ui k=0;k<i;k++, w0*=wn){
                Complex x=arr[j+k], y=w0*arr[i+j+k];
                arr[j+k]=x+y;
                arr[i+j+k]=x-y;
            }
        }
    }
}

void swap(MyNumber& x, MyNumber& y){
    MyNumber tmp=x;
    x=y;
    y=tmp;
}

void swap(Complex& x, Complex& y){
    Complex tmp=x;
    x=y;
    y=tmp;
}