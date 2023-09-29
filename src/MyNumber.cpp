#include "MyNumber.h"

#include <algorithm>

using std::string, std::vector, std::complex;
using std::ceil, std::reverse, std::max;

MyNumber::MyNumber(ll num){
    this->jump=false;
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.clear();
    while(num){
        this->Number.push_back(num%Lim);
        num/=Lim;
    }
}

MyNumber::MyNumber(string num){
    this->jump=false;
    if(num[0]=='-')this->Sign=true,num.erase(num.begin());
    else this->Sign=false;
    this->Number.clear();
    ui tmp;
    string cache;
    while(!num.empty()){
        auto iter=num.begin();
        auto _end=num.end();
        cache="",tmp=0;
        while(iter!=_end){
            tmp=tmp*10+*iter-48;
            ++iter;
            if(tmp<Lim)continue;
            cache.push_back(tmp%Lim);
            tmp/=Lim;
        }
        this->Number.push_back(tmp);
        num=cache;
    }
}

MyNumber::MyNumber(MyNumber& num){
    this->jump=false;
    this->Sign=num.GetSign();
    this->Number=vector<ui>(num.GetNumber());
}

MyNumber::~MyNumber(){
    this->Number.clear();
    this->Number.shrink_to_fit();
}

MyNumber& MyNumber::operator=(ll num){
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.clear();
    while(num){
        this->Number.push_back(num%Lim);
        num/=Lim;
    }
    return *this;
}

MyNumber& MyNumber::operator=(string num){
    if(num[0]=='-')this->Sign=true,num.erase(num.begin());
    else this->Sign=false;
    this->Number.clear();
    int tmp,cnt=num.size()-1,bit;
    const ui _size=num.size();
    for(ui i=0,len=ceil(_size/9.0);i<len;i++){
        tmp=0,bit=1;
        while(bit!=Lim&&cnt>=0){
            tmp+=(num[cnt]-48)*bit;
            --cnt;
            bit*=10;
        }
        this->Number.push_back(tmp);
    }
    return *this;
}

MyNumber& MyNumber::operator=(MyNumber& num){
    this->Sign=num.GetSign();
    this->Number=vector<ui>(num.GetNumber());
    return *this;
}

bool MyNumber::GetSign()const{
    return this->Sign;
}

void MyNumber::SetSign(bool Sign){
    this->Sign=Sign;
}

ui MyNumber::GetSize()const{
    return this->Number.size();
}

void MyNumber::SetSize(ui new_size){
    this->Number.resize(new_size, 0);
}

vector<ui> MyNumber::GetNumber(){
    return this->Number;
}

void MyNumber::RemoveLeadingZero(){
    while(this->GetSize()>1&&this->Number.back()==0)
        this->Number.pop_back();
}

string MyNumber::OutPut(){
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
    auto iter=this->Number.begin();
    auto _end=this->Number.end();
    ++(*iter);
    while((++iter)!=_end){
        if(*(iter-1)!=Lim)break;
        ++(*iter);
        *(iter-1)=0;
    }
    if(this->GetSize()>1&&iter==_end||*(iter-1)==Lim){
        (*iter)=0;
        this->Number.push_back(1);
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
    auto _end=this->Number.end();
    --(*iter);
    while((++iter)!=_end){
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
        swap(tmp,num);
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
    string str="";
    complex<double> t;
    MyNumber tmp(*this);
    vector<complex<double> > ans;
    ui new_size=max(tmp.GetSize(),num.GetSize()),len=0;
    tmp.SetSize(new_size);
    num.SetSize(new_size);
    for(ui i=0;i<new_size;i++){
        ui t1=tmp[i], t2=num[i], cnt=0;
        while(++cnt<=9){
            if(i==new_size-1&&!t1&&!t2)break;
            t.real(t1%10);
            t.imag(t2%10);
            ans.push_back(t);
            t1/=10, t2/=10;
            len++;
        }
    }
    ui l1=len, l2=len;
    while(ans[l1-1].real()==0)l1--;
    while(ans[l2-1].imag()==0)l2--;
    len=1<<max((int)ceil(log2(l1+l2)), 1);
    FFTInit(len);
    FFT(ans, len, 1);
    for(int i=0;i<len;i++)
        ans[i]*=ans[i];
    FFT(ans, len, -1);
    for(int i=0;i<new_size;i++)
        str.push_back(ans[i].imag()/2/len+eps+48);
    return MyNumber(str);
}

void MyNumber::FFTInit(ui len){
    rev.resize(len);
    for(ui i=0;i<len;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(max((int)ceil(log2(len)), 1)-1));
}

void MyNumber::FFT(vector<complex<double>>& arr, int n, int inv){
    for(ui i=0;i<n;i++)
        if(i<rev[i])swap(arr[i], arr[rev[i]]);
    for(ui i=1;i<n;i<<=1){
        complex<double> wn(cos(2*pi/i), inv*sin(2*pi/i));
        for(ui j=0;j<n;j+=(i<<1)){
            complex<double> w0(1,0);
            for(ui k=0;k<i;k++, w0*=wn){
                complex<double> x=arr[j+k], y=w0*arr[i+j+k];
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