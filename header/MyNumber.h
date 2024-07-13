#ifndef MYNUMBER_H_
#define MYNUMBER_H_

#define DEBUG printf("DEBUG\n")

typedef long long ll;
typedef unsigned long long ull;

#include "String.h"
#include "Vector.h"

const constexpr ui Lim=static_cast<ui>(1e9);
const constexpr ui mod=998244353;
const constexpr ui g=3, gi=332748118;

class MyNumber{
    public:
        MyNumber():MyNumber(0){}
        MyNumber(ll num);
        explicit MyNumber(String num);
        MyNumber(MyNumber& num);
        MyNumber(MyNumber&& num)noexcept;
        MyNumber& operator=(ll num);
        MyNumber& operator=(String num);
        MyNumber& operator=(const MyNumber& num);
        MyNumber& operator=(MyNumber&& num)noexcept;

    public:
        ~MyNumber();
        String Str();
        [[nodiscard]] String Str()const;

    public:
        ui& operator[](ui idx);
        const ui& operator[](ui idx)const;
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
        [[nodiscard]] ui GetSize()const;
        void SetSize(ui new_size);
        Vector<ui>& GetNumber();
        [[nodiscard]] const Vector<ui>& GetNumber()const;
        void RemoveLeadingZero();
        void RemoveBackZero();
        void Inverse(MyNumber& num, ui len);

    private:
        bool jump{};
        bool Sign; // true == negative  false == positive
        ui Offset; // 0 - Offset is decimal part, Offset - size is integer part
        Vector<ui> Number;
        Vector<ui> rev;
        static ll FastPow(ll num, ll idx);
        void NTTInit(ui len, ui size);
        void NTT(Vector<ui>& arr, ui n, int inv);
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