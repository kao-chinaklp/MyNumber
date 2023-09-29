#ifndef MYNUMBER_H_
#define MYNUMBER_H_
#define ui unsigned int
#define ll long long

#include <cmath>
#include <string>
#include <vector>
#include <complex>

const ui Lim=int(1e9);
const double eps=0.49, pi=acos(-1.0);

class MyNumber{
    public:
        MyNumber()=default;
        MyNumber(ll num);
        MyNumber(std::string num);
        MyNumber(MyNumber& num);
        MyNumber& operator=(ll num);
        MyNumber& operator=(std::string num);
        MyNumber& operator=(MyNumber& num);

    public:
        ~MyNumber();
        bool GetSign()const;
        void SetSign(bool Sign);
        ui GetSize()const;
        void SetSize(ui new_size);
        std::vector<ui> GetNumber();
        void RemoveLeadingZero();
        std::string OutPut();

    public:
        ui& operator[](ui idx);
        MyNumber operator++();
        MyNumber operator++(int);
        MyNumber operator--();
        MyNumber operator--(int);
        MyNumber operator-();
        bool operator==(ll num);
        bool operator==(MyNumber num);
        bool operator!=(ll num);
        bool operator!=(MyNumber num);
        bool operator<(ll num);
        bool operator<(MyNumber num);
        bool operator>(ll num);
        bool operator>(MyNumber num);
        bool operator<=(ll num);
        bool operator<=(MyNumber num);
        bool operator>=(ll num);
        bool operator>=(MyNumber num);
        bool jump;

    public:
        MyNumber operator+(ll num);
        MyNumber operator+(MyNumber num);
        MyNumber operator-(ll num);
        MyNumber operator-(MyNumber num);
        MyNumber operator*(ll num);
        MyNumber operator*(MyNumber num);

    private:
        bool Sign; // true == negative  false == positive
        std::vector<ui> Number;
        std::vector<ui> rev;
        void FFTInit(ui len);
        void FFT(std::vector<std::complex<double> >& arr, int n, int inv);
};

void swap(MyNumber& x, MyNumber& y);

#endif