#include "Complex.h"

Complex::Complex(const Complex &init){
    this->Real(init.Real());
    this->Imag(init.Imag());
}

Complex::Complex(double r, double i){
    this->real=r;
    this->imag=i;
}

double Complex::Imag()const{
    return imag;
}

double Complex::Real()const{
    return real;
}

double Complex::Imag(double val){
    return this->imag=val;
}

double Complex::Real(double val){
    return this->real=val;
}

Complex Complex::operator+(Complex num){
    return Complex(this->Real()+num.Real(), this->Imag()+num.Imag());
}

Complex Complex::operator-(Complex num){
    return Complex(this->Real()-num.Real(), this->Imag()-num.Imag());
}

Complex Complex::operator*(Complex num){
    return Complex(this->Real()*num.Real()-this->Imag()*num.Imag(), 
                   this->Real()*num.Imag()+this->Imag()*num.Real());
}

Complex Complex::operator+=(Complex num){
    return (*this)=(*this)+num;
}

Complex Complex::operator-=(Complex num){
    return (*this)=(*this)-num;
}

Complex Complex::operator*=(Complex num){
    return (*this)=(*this)*num;
}

Complex Complex::operator+(double num){
    return Complex(this->Real()+num, this->Imag());
}

Complex Complex::operator-(double num){
    return Complex(this->Real()-num, this->Imag());
}

Complex Complex::operator*(double num){
    return Complex(this->Real()*num, this->Imag()*num);
}

bool Complex::operator==(Complex num)const{
    return this->real==num.Real()&&this->imag==num.Imag();
}

bool Complex::operator==(double num)const{
    return this->real==num&&this->imag==0;
}

bool Complex::operator!=(Complex num)const{
    return this->real!=num.Real()||this->imag!=num.Imag();
}

bool Complex::operator!=(double num)const{
    return this->real!=num||this->imag!=0;
}

std::string Complex::Str()const{
    std::string num=std::to_string((int)this->real);
    if(this->imag==0)return num;
    if(this->imag<0)return num+'-'+std::to_string(-(int)this->imag)+'i';
    if(this->imag>0)return num+'+'+std::to_string((int)this->imag)+'i';
    return "";
}

inline Complex operator+(double num1, Complex num2){
    return num2+num1;
}

inline Complex operator-(double num1, Complex num2){
    return num2+num1;
}

inline Complex operator*(double num1, Complex num2){
    return num2+num1;
}

inline Complex operator-(Complex& num){
    return Complex(-num.Real(), -num.Imag());
}

inline Complex operator-(Complex num){
    return Complex(-num.Real(), -num.Imag());
}

inline bool operator==(double num1, Complex num2){
    return num2==num1;
}

inline bool operator!=(double num1, Complex num2){
    return num2!=num1;
}