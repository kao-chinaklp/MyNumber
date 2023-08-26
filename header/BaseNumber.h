#ifndef BASENUMBER_H_
#define BASENUMBER_H_
#define ui unsigned int
#define ll long long

#include <string>
#include <vector>

class BaseNumber{
    public:
        BaseNumber()=default;
        BaseNumber(ll num);
        BaseNumber(std::string num);
        BaseNumber(BaseNumber& num);
        BaseNumber& operator=(ll num);
        BaseNumber& operator=(std::string num);
        BaseNumber& operator=(BaseNumber& num);

    public:
        ~BaseNumber();
        bool GetSign()const;
        std::vector<ui> GetNumber();
        size_t GetSize()const;
        ui& operator[](ui idx);
        BaseNumber operator++();
        BaseNumber operator++(int);
        BaseNumber operator--();
        BaseNumber operator--(int);
        bool operator==(ll num);
        bool operator==(BaseNumber num);
        bool operator!=(ll num);
        bool operator!=(BaseNumber num);
        bool operator<(ll num);
        bool operator<(BaseNumber num);
        bool operator>(ll num);
        bool operator>(BaseNumber num);
        bool operator<=(ll num);
        bool operator<=(BaseNumber num);
        bool operator>=(ll num);
        bool operator>=(BaseNumber num);
        void RemoveLeadingZero();
        std::string OutPut();
        bool jump;

    private:
        const ui Lim=int(1e9);
        bool Sign; // true == negative  false == positive
        std::vector<ui> Number;
};

#endif