#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <string>

class Complex{
    public:
        Complex(const Complex &init);
        Complex(double r=0, double i=0);
        ~Complex()=default;
        double Imag()const;
        double Real()const;
        double Imag(double val);
        double Real(double val);
        Complex operator+(Complex num);
        Complex operator-(Complex num);
        Complex operator*(Complex num);
        Complex operator+=(Complex num);
        Complex operator-=(Complex num);
        Complex operator*=(Complex num);

        Complex operator+(double num);
        Complex operator-(double num);
        Complex operator*(double num);

        bool operator==(Complex num)const;
        bool operator==(double num)const;
        bool operator!=(Complex num)const;
        bool operator!=(double num)const;

        std::string Str()const;

    private:
        double imag;
        double real;
};

inline Complex operator+(double num1, Complex num2);
inline Complex operator-(double num1, Complex num2);
inline Complex operator*(double num1, Complex num2);
inline Complex operator-(Complex& num);

inline bool operator==(double num1, Complex num2);
inline bool operator!=(double num1, Complex num2);

#endif