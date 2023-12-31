#include "MyNumber.h"

using std::ceil, std::max;

MyNumber::MyNumber(ll num){
    this->jump=false;
    this->Number.Clear();
    if(num==0){
        this->Number.PushBack(0);
        this->Sign=false;
        return;
    }
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    while(num){
        this->Number.PushBack(num%Lim);
        num/=Lim;
    }
}

MyNumber::MyNumber(String num){
    this->jump=false;
    if(num[0]=='-')this->Sign=true,num.Erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    String tmp;
    for(int i=0, len=num.Size();i<len;i+=9){
        tmp=num.Substr(i, std::min(9, len-i));
        this->Number.PushBack(ToDigit(tmp));
    }
    Reverse(this->Number.begin(), this->Number.end());
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
    this->jump=false;
    this->Number.Clear();
    if(num==0){
        this->Number.PushBack(0);
        this->Sign=false;
        return *this;
    }
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    while(num){
        this->Number.PushBack(num%Lim);
        num/=Lim;
    }
    return *this;
}

MyNumber& MyNumber::operator=(String num){
    if(num[0]=='-')this->Sign=true,num.Erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    int tmp,cnt=num.Size()-1,bit;
    const ui _size=num.Size();
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

MyNumber& MyNumber::operator=(MyNumber num){
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

String MyNumber::Str(){
    this->RemoveLeadingZero();
    String out;
    for(int p=0, len=this->GetSize();p<len;p++){
        String tmp=ToString(this->Number[p]);
        if(p<len-1)while(tmp.Size()<9)tmp.Insert(tmp.begin(), '0');
        out=tmp+out;
    }
    if(this->Sign&&out!="0")out.Insert(out.begin(), '-');
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
    auto iter=this->Number.begin();
    auto _End=this->Number.end();
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
    auto iter=this->Number.begin();
    auto _End=this->Number.end();
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
    return (*this)==MyNumber(num);
}

bool MyNumber::operator==(MyNumber num){
    if(this->GetSize()!=num.GetSize()||this->GetSign()!=num.GetSign())
        return false;
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
    return *this<MyNumber(num);
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
    return *this<MyNumber(num);
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
    return *this+MyNumber(num);
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
    return *this-MyNumber(num);
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
    return *this*MyNumber(num);
}

MyNumber MyNumber::operator*(MyNumber num){
    if(*this==0||num==0)return MyNumber(0);
    bool flag=this->GetSign()==num.GetSign();
    this->SetSign(false), num.SetSign(false);
    Vector<ui> num1, num2;
    String str=this->Str();
    ui len1=str.Size();
    for(Vector<char>::reverseIterator p=str.rbegin();p!=str.rend();p++)
        num1.PushBack(*p-48);
    str=num.Str();
    ui len2=str.Size();
    for(Vector<char>::reverseIterator p=str.rbegin();p!=str.rend();p++)
        num2.PushBack(*p-48);
    ui len=1, l=0;
    while(len<len1+len2)len<<=1, l++;
    num1.Resize(len), num2.Resize(len);
    NTTInit(len, l);
    NTT(num1, len, 1);
    NTT(num2, len, 1);
    for(ui i=0;i<len;i++)
        num1[i]=1ull*num1[i]*num2[i]%mod;
    NTT(num1, len, 0);
    ll inv=FastPow(len, mod-2);// Inverse
    for(ui i=0;i<len;i++){
        num1[i]=1ll*num1[i]*inv%mod;
        if(i<len-1){
            num1[i+1]+=num1[i]/10;
            num1[i]%=10;
        }
    }
    while(num1[len-1]>9){
        num1.PushBack(num1[len-1]/10);
        num1[len-1]%=10;
        len++;
    }
    while(len>1&&num1[len-1]==0)--len;
    str.Clear();
    for(ui i=len-1;i!=-1;i--)
        str.PushBack(char(num1[i]+'0'));
    return MyNumber((flag?"":"-")+str);
}

MyNumber MyNumber::operator/(ll num){
    return *this/MyNumber(num);
}

MyNumber MyNumber::operator/(MyNumber num){
    // To do ...
    // MyNumber ans(*this), x0(1);
    // ui times=max(1, int(ceil(num.CountBits()/0.301)));
    // for(int i=1;i<=times;i++){
    //     x0*=2-num*x0;
    //     printf("%s\n",x0.Str().c_str());
    // }
    // return ans*x0;
    return MyNumber(0);
}

MyNumber MyNumber::operator+=(MyNumber num){
    return *this=*this*num;
}

MyNumber MyNumber::operator+=(ll num){
    return *this=*this+MyNumber(num);
}

MyNumber MyNumber::operator-=(MyNumber num){
    return *this=*this*num;
}

MyNumber MyNumber::operator-=(ll num){
    return *this=*this-MyNumber(num);
}

MyNumber MyNumber::operator*=(MyNumber num){
    return *this=*this*num;
}

MyNumber MyNumber::operator*=(ll num){
    return *this=*this*MyNumber(num);
}

MyNumber MyNumber::operator/=(MyNumber num){
    return *this=*this/num;
}

MyNumber MyNumber::operator/=(ll num){
    return *this=*this/MyNumber(num);
}

ll MyNumber::FastPow(ll num, ll idx){
    ll res=1;
    while(idx){
        if(idx&1)res=(res*num)%mod;
        num=(num*num)%mod;
        idx>>=1;
    }
    return res;
}

void MyNumber::FFTInit(ui len, ui Size){
    rev.Resize(len);
    for(ui i=0;i<len;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(Size-1));
}

void MyNumber::NTTInit(ui len, ui Size){
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

void MyNumber::NTT(Vector<ui>& arr, int n, int inv){
    for(ui i=0;i<n;i++)
        if(i<rev[i])swap(arr[i], arr[rev[i]]);
    for(ui i=1;i<n;i<<=1){
        ll gn=FastPow(inv?g:gi, (mod-1)/(i<<1));
        for(ui j=0;j<n;j+=(i<<1)){
            ll g0=1;
            for(int k=0;k<i;++k, g0=g0*gn%mod){
                ll x=arr[j+k], y=g0*arr[i+j+k]%mod;
                arr[j+k]=(x+y)%mod;
                arr[i+j+k]=(x-y+mod)%mod;
            }
        }
    }
}

ui MyNumber::CountBits(){
    return std::to_string(this->Number.Back()).size()+(this->GetSize()-1)*9;
}

inline MyNumber operator+(ll num1, MyNumber num2){
    return num2+num1;
}

inline MyNumber operator-(ll num1, MyNumber num2){
    return num2-num1;
}

inline MyNumber operator*(ll num1, MyNumber num2){
    return num2*num1;
}

inline MyNumber operator/(ll num1, MyNumber num2){
    return num2/num1;
}

inline MyNumber operator+=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.GetSign())tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator-=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.GetSign())tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator*=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.GetSign())tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator/=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.GetSign())tmp=-tmp;
    return num1+=tmp;
}