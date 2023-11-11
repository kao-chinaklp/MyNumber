#ifndef STRING_H_
#define STRING_H_

#include "Vector.h"

#include <fstream>

class String{
    public:
        typedef char* iterator;
        
    public:
        String()=default;
        String(char* init);
        String(const String& init);
        String(iterator _start, iterator _end);
        ~String();

        void Assign(const ui size, const char& c);
        ui Find(const char c, const ui pos=0);
        ui Find(const String str, const ui pos=0);
        ui Size()const;
        void Append(const char c);
        void Append(const String& str);
        iterator Insert(iterator p, const char c);
        iterator Begin()const;
        iterator End()const;
        iterator begin()const;
        iterator end()const;

        String operator=(String& str);
        String operator=(char* str);
        char& operator[](ui pos);
        const char& operator[](ui pos)const;
        void operator<<(std::ostream& o);
        void operator>>(std::istream& o);
        String operator+(const String& str);
        String operator+(const char c);
        String operator+=(const String& str);
        String operator+=(const char c);
        bool operator==(const String& str);
        bool operator!=(const String& str);
        bool operator<(const String& str);
        bool operator>(const String& str);

    private:
        Vector<char>Data;
};

String operator+(const char c, const String& str);

#endif