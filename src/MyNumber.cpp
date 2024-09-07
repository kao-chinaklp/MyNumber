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
    this->Offset=0;
    this->Number.Clear();
    if(num==0){
        this->Number.PushBack(0);
        this->Sign=false;
        return;
    }
    if(num<0)this->Sign=true, num=-num;
    else this->Sign=false;
    while(num){
        this->Number.PushBack(num%Lim);
        num/=Lim;
    }
}

MyNumber::MyNumber(String num){
    if(num[0]=='-')this->Sign=true, num.Erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    this->Offset=0;

    Vector<ui>& t_num=this->Number;
    String integer, decimal;
    ui point=num.Find("."), tmp=0, cnt=0;
    if(point==static_cast<ui>(-1))point=num.Size();
    else num.Erase(point);

    integer=num.Substr(0, point);
    decimal=num.Substr(point, num.Size()-point);

    if(!decimal.Empty()){
        for(char c:decimal){
            tmp=tmp*10+c-'0';
            if(++cnt==9){
                t_num.PushBack(tmp);
                cnt=tmp=0;
            }
        }
        if(tmp!=0){
            while(++cnt<=9)tmp*=10;
            t_num.PushBack(tmp);
        }
        Reverse(t_num.begin(), t_num.end());
    }
    this->Offset=t_num.Size();

    ui offset=1;
    tmp=cnt=0;
    for(ui p=integer.Size()-1;p!=static_cast<ui>(-1);p--){
        tmp=tmp+(integer[p]-'0')*offset;
        offset*=10;
        if(++cnt==9){
            t_num.PushBack(tmp);
            tmp=cnt=0;
            offset=1;
        }
    }
    if(tmp!=0||integer=="0")t_num.PushBack(tmp);
}

MyNumber::MyNumber(MyNumber& num){
    this->jump=false;
    this->Offset=num.Offset;
    this->Sign=num.Sign;
    this->Number=Vector<ui>(num.GetNumber());
}

MyNumber::MyNumber(MyNumber&& num)noexcept{
    this->jump=num.jump=false;
    this->Offset=num.Offset;num.Offset=0;
    this->Sign=num.Sign;num.Sign=false;
    this->Number=Vector<ui>(num.GetNumber());num.Number.Clear();
}

MyNumber::~MyNumber(){
    this->Number.Clear();
    this->Number.ShrinkToFit();
}

MyNumber& MyNumber::operator=(ll num){
    this->jump=false;
    this->Offset=0;
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
    if(num[0]=='-')this->Sign=true, num.Erase(num.begin());
    else this->Sign=false;
    this->Number.Clear();
    this->Offset=0;

    Vector<ui>& t_num=this->Number;
    String integer, decimal;
    ui point=num.Find("."), tmp=0, cnt=0;
    if(point==static_cast<ui>(-1))point=num.Size();
    else num.Erase(point);

    integer=num.Substr(0, point);
    decimal=num.Substr(point, num.Size()-point);

    if(!decimal.Empty()){
        for(char c:decimal){
            tmp=tmp*10+c-'0';
            if(++cnt==9){
                t_num.PushBack(tmp);
                cnt=tmp=0;
            }
        }
        if(tmp!=0){
            while(++cnt<=9)tmp*=10;
            t_num.PushBack(tmp);
        }
        Reverse(t_num.begin(), t_num.end());
    }
    this->Offset=t_num.Size();

    ui offset=1;
    tmp=cnt=0;
    for(ui p=integer.Size()-1;p!=static_cast<ui>(-1);p--){
        tmp=tmp+(integer[p]-'0')*offset;
        offset*=10;
        if(++cnt==9){
            t_num.PushBack(tmp);
            tmp=cnt=0;
            offset=1;
        }
    }
    if(tmp!=0||integer=="0")t_num.PushBack(tmp);

    return *this;
}

MyNumber& MyNumber::operator=(const MyNumber& num){
    this->Sign=num.Sign;
    this->Offset=num.Offset;
    this->Number=Vector<ui>(num.GetNumber());

    return *this;
}

MyNumber& MyNumber::operator=(MyNumber&& num)noexcept{
    this->jump=num.jump=false;
    this->Offset=num.Offset;num.Offset=0;
    this->Sign=num.Sign;num.Sign=false;
    this->Number=Vector<ui>(num.GetNumber());num.Number.Clear();

    return *this;
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

const Vector<ui> &MyNumber::GetNumber()const{
    return this->Number;
}

void MyNumber::RemoveLeadingZero(){
    for(ui i=this->GetSize();i>this->Offset+1&&this->Number.Back()==0;i--)
        this->Number.PopBack();
}

void MyNumber::RemoveBackZero(){
    if(this->Offset==0||(*this)==0)return;
    ui count=0;
    while(Number[count]==0&&Offset-count>1)count++;
    (*this)>>=count;
}

void MyNumber::Inverse(MyNumber& num, const ui len){
    MyNumber tmp1, tmp2, tmp3;
    ui l=1;

    while(l<len)l<<=1;
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

MyNumber MyNumber::Abs(MyNumber num){
    num.Sign=false;
    return num;
}

MyNumber MyNumber::Int(){
    MyNumber tmp(*this);
    tmp.GetNumber().Erase(0, Offset);
    tmp.Offset=0;
    return tmp;
}

String MyNumber::Str(){
    String out;
    ui point=this->GetSize()-this->Offset;
    Vector<ui> num=this->Number;

    this->RemoveLeadingZero();
    Reverse(num.begin(), num.end());

    for(int p=0;p<point;p++){
        String tmp=ToString(num[p]);
        if(p!=0)while(tmp.Size()<9)tmp.Insert(tmp.begin(), '0');
        out+=tmp;
    }

    if(this->Offset!=0)out.PushBack('.');
    if(out[0]=='.')out.Insert(out.begin(), '0');

    for(ui p=point, len=this->GetSize();p<len;p++){
        String tmp=ToString(num[p]);
        while(tmp.Size()<8)tmp.Insert(tmp.begin(), '0');
        out+=tmp;
    }

    ui cnt=0;
    auto ptr=out.end()-1, tmp=ptr-this->Offset*9;
    while(*(ptr)=='0'&&ptr!=tmp)cnt++, ptr--;
    out.Resize(out.Size()-cnt);
    if(this->Sign&&out!="0")out.Insert(out.begin(), '-');
    if(*(out.end()-1)=='.')out.PopBack();

    return out;
}

String MyNumber::Str()const{
    return const_cast<MyNumber*>(this)->Str();
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

    auto iter=this->Number.begin()+this->Offset;
    auto End=this->Number.end();
    ++(*iter);
    while((++iter)!=End){
        if(*(iter-1)<Lim)break;
        ++(*iter);
        *(iter-1)=0;
    }
    if(this->GetSize()>1&&iter==End||*(iter-1)==Lim){
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
        this->jump=true;
        return ++(*this);
    }

    auto iter=this->Number.begin();
    auto End=this->Number.end();
    --(*iter);
    while((++iter)!=End){
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
    tmp.Sign=!this->Sign;

    return tmp;
}

bool MyNumber::operator==(ll num){
    if(this->Sign==true&&num>=0||
       this->Sign==false&&num<0)return false;
    if(this->GetSize()>1)return false;
    if(num<0)num=-num;

    return (*this)[0]==num;
}

bool MyNumber::operator==(const MyNumber& num){
    if(this->GetSize()!=num.GetSize()||this->Sign!=num.Sign||this->Offset!=num.Offset)
        return false;
    for(ui i=0, len=this->GetSize();i<len;i++)
        if((*this)[i]!=num[i])return false;

    return true;
}

bool MyNumber::operator!=(ll num){
    if(this->Sign==true&&num>=0||
       this->Sign==false&&num<0)return false;
    if(this->GetSize()>1)return true;
    if(num<0)num=-num;

    return (*this)[0]!=num;
}

bool MyNumber::operator!=(const MyNumber& num){
    return !((*this)==num);
}

bool MyNumber::operator<(ll num){
    return (*this)<MyNumber(num);
}

bool MyNumber::operator<(const MyNumber& num){
    String num1=this->Str(), num2=num.Str();
    bool flag=false;

    if(num1[0]=='-'&&num2[0]!='-')return true;
    if(num1[0]!='-'&&num2[0]=='-')return false;
    if(num1[0]=='-'){
        num1.Erase(num1.begin());
        num2.Erase(num2.begin());
        flag=true;
    }

    // Determine the integer part
    bool offset1=num1.Find('.')!=static_cast<ui>(-1);
    bool offset2=num2.Find('.')!=static_cast<ui>(-1);
    ui _size=num1.Size()-offset1;

    if((offset1?num1.Find('.'):num1.Size())<(offset2?num2.Find('.'):num2.Size()))return !flag;
    if((offset1?num1.Find('.'):num1.Size())>(offset2?num2.Find('.'):num2.Size()))return flag;
    if(offset1){
        for(ui i=0, len=num1.Find('.');i<len;i++){
            if(num1[i]<num2[i])return !flag;
            if(num1[i]>num2[i])return flag;
        }
    }
    else{
        for(ui i=0, len=_size;i<len;i++){
            if(num1[i]<num2[i])return !flag;
            if(num1[i]>num2[i])return flag;
        }
    }

    // Determine the decimal part
    String str1=num1.Substr(num1.Size()-this->Offset, this->Offset);
    String str2=num2.Substr(num2.Size()-num.Offset, num.Offset);
    for(ui i=0, len=min(str1.Size(), str2.Size());i<len;i++){
        if(str1[i]<str2[i])return !flag;
        if(str1[i]>str2[i])return flag;
    }

    if(!flag)return str1.Size()<str2.Size();
    else return str1.Size()>str2.Size();
}

bool MyNumber::operator>(ll num){
    return (*this)>MyNumber(num);
}

bool MyNumber::operator>(const MyNumber& num){
    String num1=this->Str(), num2=num.Str();
    bool flag=false;

    if(num1[0]=='-'&&num2[0]!='-')return false;
    if(num1[0]!='-'&&num2[0]=='-')return true;
    if(num1[0]=='-'){
        num1.Erase(num1.begin());
        num2.Erase(num2.begin());
        flag=true;
    }

    // Determine the integer part
    bool offset1=num1.Find('.')!=static_cast<ui>(-1);
    bool offset2=num2.Find('.')!=static_cast<ui>(-1);
    ui _size=num1.Size()-offset1;

    if((offset1?num1.Find('.'):num1.Size())>(offset2?num2.Find('.'):num2.Size()))return !flag;
    if((offset1?num1.Find('.'):num1.Size())<(offset2?num2.Find('.'):num2.Size()))return flag;
    if(offset1){
        for(ui i=0, len=num1.Find('.');i<len;i++){
            if(num1[i]>num2[i])return !flag;
            if(num1[i]<num2[i])return flag;
        }
    }
    else{
        for(ui i=0, len=_size;i<len;i++){
            if(num1[i]>num2[i])return !flag;
            if(num1[i]<num2[i])return flag;
        }
    }

    // Determine the decimal part
    String str1=num1.Substr(num1.Size()-this->Offset, this->Offset);
    String str2=num2.Substr(num2.Size()-num.Offset, num.Offset);
    for(ui i=0, len=min(str1.Size(), str2.Size());i<len;i++){
        if(str1[i]>str2[i])return !flag;
        if(str1[i]<str2[i])return flag;
    }

    if(!flag)return str1.Size()>str2.Size();
    return str1.Size()<str2.Size();
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

    if(num.Sign)return tmp-(-num);
    else if(tmp.Sign)return num-(-tmp);

    ui new_size=max(tmp.GetSize(), num.GetSize());
    ui new_offset=max(tmp.Offset, num.Offset);
    ans.SetSize(new_size+new_offset+1);
    tmp.SetSize(new_size);
    num.SetSize(new_size);
    tmp<<=(new_offset-tmp.Offset);
    num<<=(new_offset-num.Offset);

    for(ui i=0;i<new_size;i++){
        ans[i]+=tmp[i]+num[i];
        ans[i+1]+=ans[i]/Lim;
        ans[i]%=Lim;
    }

    ans.Offset=new_offset;
    ans.RemoveLeadingZero();
    ans.RemoveBackZero();

    return ans;
}

MyNumber MyNumber::operator-(ll num){
    return *this-MyNumber(num);
}

MyNumber MyNumber::operator-(MyNumber num){
    MyNumber tmp(*this), ans=0;

    if(num.Sign)return tmp+(-num);
    else if(tmp.Sign)return -((-tmp)+num);
    if(tmp<num){
        swap(tmp, num);
        ans.Sign=true;
    }

    ui new_size=max(tmp.GetSize(), num.GetSize());
    ui new_offset=max(tmp.Offset, num.Offset);
    ans.SetSize(new_size+new_offset+1);
    tmp.SetSize(new_size);
    num.SetSize(new_size);
    tmp<<=(new_offset-tmp.Offset);
    num<<=(new_offset-num.Offset);

    for(ui i=0;i<new_size;i++){
        ans[i]+=tmp[i]-num[i];
        if(ans[i]>=Lim){
            ans[i]+=Lim;
            ans[i+1]--;
        }
    }

    ans.Offset=new_offset;
    ans.RemoveLeadingZero();
    ans.RemoveBackZero();

    return ans;
}

MyNumber MyNumber::operator*(ll num){
    MyNumber ans=*this, in=*this;

    if(num<0){
        ans.Sign=!ans.Sign;
        num=-num;
    }

    ull tmp;
    for(ui i=ans.GetSize();i<Lim;i--){
        tmp=1ull*ans[i]*num;
        in[i]=tmp/Lim;
        ans[i]=tmp%Lim;
    }

    tmp=0;
    for(ui i=ans.GetSize()-1;i<Lim;i--){
        tmp+=0ull*ans[i]+in[i+1];
        ans[i]=tmp%Lim;
        tmp/=Lim;
    }

    if(tmp!=0)ans.Number.PushBack(tmp);
    ans.RemoveBackZero();

    return ans;
}

MyNumber MyNumber::operator*(MyNumber num){
    if(*this==0||num==0)return {0};

    MyNumber tmp(*this);
    Vector<ui> num1, num2;
    ui tmpp, offset=0;
    bool flag=this->Sign==num.Sign;
    tmp.Sign=num.Sign=false;

    String str=this->Str();
    if((tmpp=str.Find('.'))!=static_cast<ui>(-1))str.Erase(tmpp), offset+=str.Size()-tmpp;
    ui len1=str.Size();
    for(Vector<char>::reverseIterator p=str.rbegin();p!=str.rend();++p)
        num1.PushBack(*p-48);

    str=num.Str();
    if((tmpp=str.Find('.'))!=static_cast<ui>(-1))str.Erase(tmpp), offset+=str.Size()-tmpp;
    ui len2=str.Size();
    for(Vector<char>::reverseIterator p=str.rbegin();p!=str.rend();++p)
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

    for(ui i=0;i<len;i++)num2[i]=0;
    for(ui i=0;i<len;i++){
        num2[i]+=1ll*num1[i]*inv%mod;
        if(i<len-1){
            num2[i+1]+=num2[i]/10;
            num2[i]%=10;
        }
    }

    while(num2[len-1]>9){
        num2.PushBack(num2[len-1]/10);
        num2[len-1]%=10;
        len++;
    }
    while(len>1&&num2[len-1]==0)--len;
    str.Clear();
    for(ui i=len-1;i<Lim;i--)
        str.PushBack(static_cast<char>(num2[i]+'0'));
    if(tmp.Offset+num.Offset>0)str.Insert(str.Size()-offset, '.');
    if(str.Front()=='.')str.Insert(str.begin(), '0');
    auto ptr=str.end()-1;
    while(ptr!=str.begin()+1&&*ptr=='0'){
        str.PopBack(), ptr--;
        if(*ptr=='.')break;
    }

    return MyNumber((flag?"":"-")+str);
}

MyNumber MyNumber::operator/(ll num){
    MyNumber ans=0;
    ll tmp=0, p=this->GetSize();
    ans.GetNumber().Resize(p);
    while(--p>=0){
        tmp=tmp*Lim+(*this)[p];
        ans[p]=tmp/num;
        tmp%=num;
    }
    ans.RemoveLeadingZero();
    ans.RemoveBackZero();
    return ans;
}

MyNumber MyNumber::operator/(MyNumber num){
    assert(num!=0);

    MyNumber x0("0.5"), x1=x0;
    for(ui i=0;i<=10;i++)
        x0*=(2-x0*num);

    MyNumber res1=(*this)*x0, res2=(*this)*(x0+1);
    return (Abs(res1-num)<Abs(res2-num)?res1.Int():res2.Int());
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

MyNumber MyNumber::operator<<(ll num){
    if(num<0)return (*this)>>-num;
    if(num==0)return *this;
    MyNumber tmp(*this);
    while(tmp.Offset>0)tmp.Offset--, num--;
    tmp.Number.Resize(this->GetSize()+num);
    for(ui i=this->GetSize()-1;i>=num;i--)
        tmp.Number[i]=this->Number[i-num];
    for(ui i=num-1;i<Lim;i--)
        tmp.Number[i]=0;
    return tmp;
}

MyNumber MyNumber::operator>>(ll num){
    if(num<0)return (*this)<<-num;
    if(num==0)return *this;
    MyNumber tmp(*this);
    if(num>=tmp.GetSize())return {0};
    for(ui i=0;i<this->GetSize()-num;i++)
        tmp[i]=tmp[i+num];
    for(ui size=this->GetSize(), i=size-num;i<size;i++)
        tmp[i]=0;
    if((tmp.Offset-=num)>Lim)tmp.Offset=0;
    tmp.RemoveLeadingZero();
    return tmp;
}

MyNumber MyNumber::operator<<=(ll num){
    return *this=(*this)<<num;
}

MyNumber MyNumber::operator>>=(ll num){
    return *this=(*this)>>num;
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

inline MyNumber operator+(ll num1, MyNumber num2){
    return num2+num1;
}

inline MyNumber operator-(ll num1, MyNumber num2){
    return MyNumber(num1)-num2;
}

inline MyNumber operator*(ll num1, MyNumber num2){
    return num2*num1;
}

inline MyNumber operator/(ll num1, MyNumber num2){
    return MyNumber(num1)/num2;
}

inline MyNumber operator+=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.Sign)tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator-=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.Sign)tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator*=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.Sign)tmp=-tmp;
    return num1+=tmp;
}

inline MyNumber operator/=(ll& num1, MyNumber num2){
    ll tmp=num2.GetNumber()[0]+num2.GetNumber()[1]*Lim;
    if(num2.Sign)tmp=-tmp;
    return num1+=tmp;
}

std::istream& operator>>(std::istream& i, MyNumber& num){
    String str;
    i>>str;
    num=str;
    return i;
}

std::ostream& operator<<(std::ostream& o, const MyNumber& num){
    o<<num.Str();
    return o;
}

MyNumber abs(MyNumber num){
    num.Sign=false;
    return num;
}