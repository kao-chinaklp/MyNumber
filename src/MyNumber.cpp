#include "MyNumber.h"

template<class T>
T max(const T& a, const T& b){
    return (a>b?a:b);
}

template<class T>
T min(const T& a, const T& b){
    return (a<b?a:b);
}

ll inline ceil(long double num){
    return num-static_cast<ll>(num)>0?static_cast<ll>(num+1):static_cast<ll>(num);
}

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

MyNumber::MyNumber(MyNumber&& num)noexcept{
    this->jump=num.jump=false;
    this->Sign=num.GetSign();num.SetSign(false);
    this->Number=Vector<ui>(num.GetNumber());num.Number.Clear();
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
    int tmp, cnt=num.Size()-1, bit;
    const ui _size=num.Size();
    for(ui i=0, len=ceil(_size/9.0);i<len;i++){
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

MyNumber& MyNumber::operator=(MyNumber&& num)noexcept{
    this->jump=num.jump=false;
    this->Sign=num.GetSign();num.SetSign(false);
    this->Number=Vector<ui>(num.GetNumber());num.Number.Clear();
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

Vector<ui>& MyNumber::GetNumber(){
    return this->Number;
}

void MyNumber::RemoveLeadingZero(){
    while(this->GetSize()>1&&this->Number.Back()==0)
        this->Number.PopBack();
}

void MyNumber::Inverse(MyNumber& num, const ui len){
    ui l=1;
    while(l<len)l<<=1;
    MyNumber tmp1, tmp2, tmp3;
    tmp1.SetSize(l), tmp1.SetSize(l), tmp2.SetSize(l);
    tmp1[0]=FastPow(num[0], mod-2);
    tmp2=tmp1;
    for(ui i=2;i<=l;i<<=1){
        tmp2.NTTInit(i<<1, l);
        tmp3=num;
        NTT(tmp3.GetNumber(), i, 1);
        NTT(tmp2.GetNumber(), i, 1);
        for(ui j=0;j<i;j++)tmp2[j]=1ull*tmp2[j]*tmp3[j]%mod;
        NTT(tmp2.GetNumber(), i, 0);
        for(ui j=0;j<i<<1;j++)tmp2[j]=0;
        tmp3=tmp1;
        NTT(tmp3.GetNumber(), i, 1);
        NTT(tmp2.GetNumber(), i, 1);
        for(ui j=0;j<i;j++)tmp2[j]=1ull*tmp2[j]*tmp3[j]%mod;
        NTT(tmp2.GetNumber(), i, 0);
        for(ui j=i>>1;i<j;j++)tmp1[j]=(tmp1[j]*2-tmp2[j]+mod)%mod;
    }
    num=tmp1;
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

ui& MyNumber::operator[](const ui idx){
    return this->Number[idx];
}

const ui& MyNumber::operator[](const ui idx)const{
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
    if(this->GetSign()==true&&num>=0||
       this->GetSign()==false&&num<0)return false;
    if(this->GetSize()>1)return false;
    if(num<0)num=-num;
    return (*this)[0]==num;
}

bool MyNumber::operator==(const MyNumber& num){
    if(this->GetSize()!=num.GetSize()||this->GetSign()!=num.GetSign())
        return false;
    for(int i=0,len=this->GetSize();i<len;i++)
        if((*this)[i]!=num[i])return false;
    return true;
}

bool MyNumber::operator!=(ll num){
    if(this->GetSign()==false&&num>=0||
       this->GetSign()==true&&num<0)return false;
    if(this->GetSize()>1)return true;
    if(num<0)num=-num;
    return (*this)[0]!=num;
}

bool MyNumber::operator!=(const MyNumber& num){
    return !((*this)==num);
}

bool MyNumber::operator<(ll num){
    if(this->GetSign()==true&&num>=0)return true;
    if(this->GetSign()==false&&num<=0)return false;
    if(num<0){
        num=-num;
        if(this->GetSize()>1)return true;
        else return (*this)[0]>num;
    }
    else
        if(this->GetSize()>1)return false;
        else return (*this)[0]<num;
}

bool MyNumber::operator<(const MyNumber& num){
    if(this->Sign!=num.GetSign())return this->GetSign();
    if(this->GetSize()<num.GetSize())return true;
    if(this->GetSize()>num.GetSize())return false;
    for(int i=0, len=this->GetSize();i<len;i++){
        if((*this)[i]<num[i])return true;
        if((*this)[i]>num[i])return false;
    }
    return false;
}

bool MyNumber::operator>(ll num){
    if(this->GetSign()==true&&num>=0)return false;
    if(this->GetSign()==false&&num<0)return true;
    if(num<0){
        num=-num;
        if(this->GetSize()>1)return false;
        else return (*this)[0]<num;
    }
    else 
        if(this->GetSize()>1)return true;
        else return (*this)[0]>num;
}

bool MyNumber::operator>(const MyNumber& num){
    if(this->Sign!=num.GetSign())return !this->GetSign();
    if(this->GetSize()>num.GetSize())return true;
    if(this->GetSize()<num.GetSize())return false;
    for(int i=0, len=this->GetSize();i<len;i++){
        if((*this)[i]>num[i])return true;
        if((*this)[i]<num[i])return false;
    }
    return false;
}

bool MyNumber::operator<=(ll num){
    return !(*this>num);
}

bool MyNumber::operator<=(const MyNumber& num){
    return !(*this>num);
}

bool MyNumber::operator>=(ll num){
    return !(*this<num);
}

bool MyNumber::operator>=(const MyNumber& num){
    return !(*this<num);
}

MyNumber MyNumber::operator+(ll num){
    return *this+MyNumber(num);
}

MyNumber MyNumber::operator+(MyNumber num){
    MyNumber tmp(*this), ans=0;
    if(num.GetSign())return tmp-(-num);
    else if(tmp.GetSign())return num-(-tmp);
    ui new_size=max(tmp.GetSize(), num.GetSize());
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
    ui new_size=max(tmp.GetSize(), num.GetSize());
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
    MyNumber ans=*this, in=*this;
    if(num<0){
        ans.SetSign(!ans.GetSign());
        num=-num;
    }
    ull tmp=0;
    for(ui i=ans.GetSize();i>=0;i--){
        tmp=1ull*ans[i]*num;
        in[i]=tmp/Lim;
        ans[i]=tmp%Lim;
    }
    tmp=0;
    for(ui i=ans.GetSize()-1;i>=0;i--){
        tmp+=0ull*ans[i]+in[i+1];
        ans[i]=tmp%Lim;
        tmp/=Lim;
    }
    if(tmp!=0)ans.Number.PushBack(tmp);
    return ans;
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
    for(ui i=len-1;i!=(ui)-1;i--)
        str.PushBack(char(num1[i]+'0'));
    return MyNumber((flag?"":"-")+str);
}

MyNumber MyNumber::operator/(ll num){
    return *this/MyNumber(num);
}

MyNumber MyNumber::operator/(MyNumber num){
    if(*this==0||num==0)return MyNumber(0);
    bool flag=this->GetSign()==num.GetSign();
    this->SetSign(false), num.SetSign(false);
    MyNumber tmp=*this, num1, num2;
    String str=this->Str();
    ui len1=str.Size();
    for(Vector<char>::iterator p=str.begin();p!=str.end();p++)
        num1.GetNumber().PushBack(*p-48);
    str=num.Str();
    ui len2=str.Size();
    for(Vector<char>::iterator p=str.begin();p!=str.end();p++)
        num2.GetNumber().PushBack(*p-48);
    ui l=num1.GetSize()-num2.GetSize()+1;
    Reverse(num1.GetNumber().begin(), num1.GetNumber().end());
    Reverse(num2.GetNumber().begin(), num2.GetNumber().end());
    Inverse(num1, num1.GetSize());
    num1*=num2;
    Reverse(num1.GetNumber().begin(), num1.GetNumber().end());
    str.Clear();
    for(ui i=num1.GetSize()-1;i<Lim;i--)
        if(num1[i]>9){
            if(i>0)num1[i-1]--;
            str.PushBack(char(num1[i]%10+'0'));
        }
    return MyNumber((flag?"":"-")+str);
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

void MyNumber::NTTInit(ui len, ui Size){
    rev.Resize(len);
    for(ui i=0;i<len;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(Size-1));
}

void MyNumber::NTT(Vector<ui>& arr, ui n, int inv){
    for(ui i=0;i<n;i++)
        if(i<rev[i])swap(arr[i], arr[rev[i]]);
    for(ui i=1;i<n;i<<=1){
        ll gn=FastPow(inv?g:gi, (mod-1)/(i<<1));
        for(ui j=0;j<n;j+=(i<<1)){
            ll g0=1;
            for(ui k=0;k<i;++k, g0=g0*gn%mod){
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