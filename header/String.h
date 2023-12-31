#ifndef STRING_H_
#define STRING_H_

#include "Vector.h"

#include <fstream>

class String{
    public:
        typedef char* iterator;
        
    public:
        String():String(""){};
        String(const char* init);
        String(const String& init);
        String(iterator _start, iterator _end);
        ~String();

        void Assign(const ui size, const char& c);
        ui Find(const char c, const ui pos=0);
        ui Find(const String str, const ui pos=0);
        ui Size()const;
        char& Front();
        char& Back();

        void PushBack(const char c);
        void PopBack();
        void Append(const char c);
        void Append(const String str);
        void Clear();
        void Resize(ui size);
        iterator Insert(const ui pos, const char& c);
        iterator Insert(iterator p, const char& c);
        iterator Erase(iterator p);
        iterator Erase(const ui pos, const ui size);
        String Substr(const ui pos, const ui size);
        const iterator& cbegin()const;
        const iterator& cend()const;
        const iterator& begin()const;
        const iterator& end()const;
        const Vector<char>::reverseIterator& crbegin()const;
        const Vector<char>::reverseIterator& crend()const;
        iterator& begin();
        iterator& end();
        Vector<char>::reverseIterator& rbegin();
        Vector<char>::reverseIterator& rend();
        
        String& operator=(const String& str);
        String& operator=(String&& str)noexcept;
        char& operator[](ui pos);
        const char& operator[](ui pos)const;
        String operator+(const String& str);
        String operator+(const char c);
        String operator+(const char* p);
        String& operator+=(const String& str);
        String& operator+=(const char& c);
        String& operator+=(char* p);
        bool operator==(const String& str);
        bool operator!=(const String& str);
        bool operator<(const String& str);
        bool operator>(const String& str);

    private:
        Vector<char>Data;
};

std::istream& operator>>(std::istream& o, String& str);
std::ostream& operator<<(std::ostream& o, const String& str);
String operator+(const char c, const String& str);
String operator+(const char* p, const String& str);

String ToString(long long num);
long long ToDigit(String str);

#endif
