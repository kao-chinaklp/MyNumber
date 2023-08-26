#include "BaseNumber.h"

#include <cmath>
#include <algorithm>

using std::string,std::vector,std::ceil,std::reverse;

BaseNumber::BaseNumber(ll num){
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.clear();
    while(num){
        this->Number.push_back(num%Lim);
        num/=Lim;
    }
}

BaseNumber::BaseNumber(string num){
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

BaseNumber::BaseNumber(BaseNumber& num){
    this->Sign=num.GetSign();
    this->Number=vector<ui>(num.GetNumber());
}

BaseNumber::~BaseNumber(){
    this->Number.clear();
    this->Number.shrink_to_fit();
}

BaseNumber& BaseNumber::operator=(ll num){
    if(num<0)this->Sign=true,num=-num;
    else this->Sign=false;
    this->Number.clear();
    while(num){
        this->Number.push_back(num%this->Lim);
        num/=this->Lim;
    }
    return *this;
}

BaseNumber& BaseNumber::operator=(string num){
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

BaseNumber& BaseNumber::operator=(BaseNumber& num){
    this->Sign=num.GetSign();
    this->Number=vector<ui>(num.GetNumber());
    return *this;
}

bool BaseNumber::GetSign()const{
    return this->Sign;
}

vector<ui> BaseNumber::GetNumber(){
    return this->Number;
}

size_t BaseNumber::GetSize()const{
    return this->Number.size();
}

ui& BaseNumber::operator[](ui idx){
    return this->Number[idx];
}

BaseNumber BaseNumber::operator++(){
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

BaseNumber BaseNumber::operator++(int){
    BaseNumber tmp(*this);
    ++(*this);
    return tmp;
}

BaseNumber BaseNumber::operator--(){
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

BaseNumber BaseNumber::operator--(int){
    BaseNumber tmp(*this);
    --(*this);
    return tmp;
}

bool BaseNumber::operator==(ll num){
    BaseNumber tmp(num);
    return (*this)==tmp;
}

bool BaseNumber::operator==(BaseNumber num){
    if(this->GetSize()!=num.GetSize())return false;
    if(this->GetSign()!=num.GetSign())return false;
    for(int i=0,len=this->GetSize();i<len;i++)
        if((*this)[i]!=num[i])return false;
    return true;
}

bool BaseNumber::operator!=(ll num){
    BaseNumber tmp(num);
    return !((*this)==tmp);
}

bool BaseNumber::operator!=(BaseNumber num){
    return !((*this)==num);
}

bool BaseNumber::operator<(ll num){
    BaseNumber tmp(num);
    return *this<tmp;
}

bool BaseNumber::operator<(BaseNumber num){
    if(this->Sign!=num.GetSign())return this->GetSign();
    if(this->GetSize()<num.GetSize())return true;
    if(this->GetSize()>num.GetSize())return false;
    for(int i=0,len=this->GetSize();i<len;i++){
        if((*this)[i]<num[i])return true;
        if((*this)[i]>num[i])return false;
    }
    return false;
}

bool BaseNumber::operator>(ll num){
    BaseNumber tmp(num);
    return *this<tmp;
}

bool BaseNumber::operator>(BaseNumber num){
    if(this->Sign!=num.GetSign())return !this->GetSign();
    if(this->GetSize()>num.GetSize())return true;
    if(this->GetSize()<num.GetSize())return false;
    for(int i=0,len=this->GetSize();i<len;i++){
        if((*this)[i]>num[i])return true;
        if((*this)[i]<num[i])return false;
    }
    return false;
}

bool BaseNumber::operator<=(ll num){
    return !(*this>num);
}

bool BaseNumber::operator<=(BaseNumber num){
    return !(*this>num);
}

bool BaseNumber::operator>=(ll num){
    return !(*this<num);
}

bool BaseNumber::operator>=(BaseNumber num){
    return !(*this<num);
}

void BaseNumber::RemoveLeadingZero(){
    while(this->GetSize()>1&&this->Number.back()==0)
        this->Number.pop_back();
}

string BaseNumber::OutPut(){
    string out="";
    for(int p=0,len=this->GetSize();p<len;p++){
        ui tmp=this->Number[p];
        int cnt=0;
        while(++cnt<=9){
            out.push_back(tmp%10+48);
            tmp/=10;
        }
    }
    while(out.size()>1&&out.back()=='0')out.pop_back();
    reverse(out.begin(),out.end());
    if(this->Sign)out.insert(out.begin(),'-');
    return out;
}