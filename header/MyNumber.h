#ifndef MYNUMBER_H_
#define MYNUMBER_H_
#define ui unsigned int
#define ll long long

#include "String.h"
#include "Vector.h"

const ui Lim=int(1e9);

class MyNumber{
    public:
        MyNumber()=default;
        MyNumber(ll num);
        MyNumber(String num);
        MyNumber(MyNumber& num);
        MyNumber& operator=(ll num);
        MyNumber& operator=(String num);
        MyNumber& operator=(MyNumber num);

    public:
        ~MyNumber();
        bool GetSign()const;
        void SetSign(bool Sign);
        ui GetSize()const;
        void SetSize(ui new_size);
        Vector<ui> GetNumber();
        void RemoveLeadingZero();
        String Str();

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
        MyNumber operator/(ll num);
        MyNumber operator/(MyNumber num);

        MyNumber operator+=(ll num);
        MyNumber operator+=(MyNumber num);
        MyNumber operator-=(ll num);
        MyNumber operator-=(MyNumber num);
        MyNumber operator*=(ll num);
        MyNumber operator*=(MyNumber num);
        MyNumber operator/=(ll num);
        MyNumber operator/=(MyNumber num);

    private:
        const ui mod=998244353;
        const ui g=3, gi=332748118;
        bool Sign; // true == negative  false == positive
        Vector<ui> Number;
        Vector<ui> rev;
        ll FastPow(ll num, ll idx);
        void NTTInit(ui len, ui size);
        void NTT(Vector<ui>& arr, int n, int inv);
        ui CountBits();
};

MyNumber operator+(ll num1, MyNumber num2);
MyNumber operator-(ll num1, MyNumber num2);
MyNumber operator*(ll num1, MyNumber num2);
MyNumber operator/(ll num1, MyNumber num2);
MyNumber operator+=(ll& num1, MyNumber num2);
MyNumber operator-=(ll& num1, MyNumber num2);
MyNumber operator*=(ll& num1, MyNumber num2);
MyNumber operator/=(ll& num1, MyNumber num2);

#endif