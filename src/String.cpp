#include "String.h"

String::String(char* init){
    ui size=sizeof(init);
    Data.Resize(size);Data.ShrinkToFit();
    for(ui i=0;i<size;i++)
        Data[i]=init[i];
}

String::String(const String& init){
    Data=init.Data;
}

String::String(String::iterator _start, String::iterator _end){
    ui size=_end-_start;
    Data.Resize(size);Data.ShrinkToFit();
    for(ui i=0;i<size;i++)
        Data[i]=_start[i];
}

String::~String(){
    Data.Clear();
    Data.ShrinkToFit();
}

ui String::Find(const char c, const ui pos){
    for(ui p=pos;p<this->Size();p++)
        if(c==Data[p])return p;
    return -1;
}

ui String::Find(const String str, const ui pos){
    if(str.Size()>this->Size())return -1;
    // KMP
    ui* nxt=new ui[this->Size()];
    ui j=0, len=str.Size();
    for(int i=0;i<len;i++){
        while(j!=0&&str[i]!=str[j])j=nxt[j-1];
        if(str[i]==str[j])j++;
        nxt[i]=j;
    }
    j=0;
    ui lim=this->Size();
    for(ui i=pos;i<lim;i++){
        while(j!=0&&Data[i]==str[j])j=nxt[j-1];
        if(Data[i]==str[j])j++;
        if(j==len)return i;
    }
    return -1;
}

ui String::Size()const{
    return Data.Size();
}

String String::operator=(String& str){
    Data=str.Data;
    return *this;
}

String String::operator=(char* str){
    ui size=sizeof(str);
    Data.Resize(size);Data.ShrinkToFit();
    for(ui i=0;i<size;i++)
        Data[i]=str[i];
    return *this;
}

char& String::operator[](ui pos){
    return Data[pos];
}

const char& String::operator[](ui pos)const{
    return Data[pos];
}

void String::operator<<(std::ostream& o){
    for(char c:Data)o<<c;
}

void String::operator>>(std::istream& o){
    char tmp;
    Data.Clear();
    while(true){
        tmp=o.get();
        if(tmp==' '||tmp=='\n'||tmp==EOF)break;
        Data.PushBack(tmp);
    }
}

String String::operator+(const String& str){
    ui old_size=this->Size();
    ui new_size=this->Size()+str.Size();
    Data.Resize(new_size);
    for(ui p=old_size;p<new_size;p++)
        Data[p]=str[p-old_size];
    return *this;
}

String String::operator+(const char c){
    this->Append(c);
    return *this;
}

String String::operator+=(const String& str){
    String tmp=*this+str;
    return *this=tmp;
}

bool String::operator==(const String& str){
    if(this->Size()!=str.Size())return false;
    ui len=this->Size();
    for(ui i=0;i<len;i++)
        if(Data[i]!=str[i])return false;
    return true;
}

bool String::operator!=(const String& str){
    return !(*this==str);
}

bool String::operator<(const String& str){
    if(this->Size()==str.Size()){
        for(ui i=0, len=this->Size();i<len;i++)
            if(Data[i]>=str[i])return false;
        return true;
    }
    else {
        ui len=0;
        bool flag=false;
        if(this->Size()>str.Size())
            len=str.Size(), flag=false;
        else 
            len=this->Size(), flag=true;
        for(ui i=0;i<len;i++)
            if(Data[i]>=str[i])return false;
        return flag;
    }
}

bool String::operator>(const String& str){
    if(this->Size()==str.Size()){
        for(ui i=0, len=this->Size();i<len;i++)
            if(Data[i]<=str[i])return false;
        return true;
    }
    else {
        ui len=0;
        bool flag=false;
        if(this->Size()>str.Size())
            len=str.Size(), flag=true;// Different from less
        else 
            len=this->Size(), flag=false;
        for(ui i=0;i<len;i++)
            if(Data[i]<=str[i])return false;
        return flag;
    }
}

String operator+(const char c, const String& str){
    String tmp(str);
    tmp.Insert(tmp.Begin(), c);
    return tmp;
}