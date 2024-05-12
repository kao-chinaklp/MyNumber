#ifndef MYNUMBER_H_
#define MYNUMBER_H_
typedef long long ll;
typedef unsigned long long ull;

#include "String.h"
#include "Vector.h"

const ui Lim=ui(1e9);
const ui mod=998244353;
const ui g=3, gi=332748118;

class MyNumber{
    public:
        MyNumber()=default;
        MyNumber(ll num);
        MyNumber(String num);
        MyNumber(MyNumber& num);
        MyNumber(MyNumber&& num)noexcept;
        MyNumber& operator=(ll num);
        MyNumber& operator=(String num);
        MyNumber& operator=(MyNumber& num);
        MyNumber& operator=(MyNumber&& num)noexcept;

    public:
        ~MyNumber();
        String Str();

    public:
        ui& operator[](const ui idx);
        const ui& operator[](const ui idx)const;
        MyNumber operator++();
        MyNumber operator++(int);
        MyNumber operator--();
        MyNumber operator--(int);
        MyNumber operator-();
        bool operator==(ll num);
        bool operator==(const MyNumber& num);
        bool operator!=(ll num);
        bool operator!=(const MyNumber& num);
        bool operator<(ll num);
        bool operator<(const MyNumber& num);
        bool operator>(ll num);
        bool operator>(const MyNumber& num);
        bool operator<=(ll num);
        bool operator<=(const MyNumber& num);
        bool operator>=(ll num);
        bool operator>=(const MyNumber& num);
        bool jump;

    public:
        MyNumber operator+(ll num);
        MyNumber operator+(MyNumber num);
        MyNumber operator-(ll num);
        MyNumber operator-(MyNumber num);
        MyNumber operator*(ll num);
        MyNumber operator*(MyNumber num);
        MyNumber operator/(ll num);
        MyNumber operator/(MyNumber num); // To do

        MyNumber operator+=(ll num);
        MyNumber operator+=(MyNumber num);
        MyNumber operator-=(ll num);
        MyNumber operator-=(MyNumber num);
        MyNumber operator*=(ll num);
        MyNumber operator*=(MyNumber num);
        MyNumber operator/=(ll num);
        MyNumber operator/=(MyNumber num);
        friend MyNumber operator+=(ll& num1, MyNumber num2);
        friend MyNumber operator-=(ll& num1, MyNumber num2);
        friend MyNumber operator*=(ll& num1, MyNumber num2);
        friend MyNumber operator/=(ll& num1, MyNumber num2);

    protected:
        MyNumber operator<<(ll num);
        MyNumber operator>>(ll num);
        MyNumber operator<<=(ll num);
        MyNumber operator>>=(ll num);
        bool GetSign()const;
        void SetSign(bool Sign);
        ui GetSize()const;
        void SetSize(ui new_size);
        Vector<ui>& GetNumber();
        void RemoveLeadingZero();
        void Inverse(MyNumber& num, const ui len);

    private:
        bool Sign; // true == negative  false == positive
        ui Offset;
        Vector<ui> Number;
        Vector<ui> rev;
        ll FastPow(ll num, ll idx);
        void NTTInit(ui len, ui size);
        void NTT(Vector<ui>& arr, ui n, int inv);
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