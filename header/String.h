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
        String(String&& init) noexcept ;
        String(iterator _start, iterator _end);
        ~String();

        void Assign(ui size, const char& c);
        ui Find(char c, ui pos=0);
        ui Find(const String& str, ui pos=0);
        [[nodiscard]] ui Size()const;
        [[nodiscard]] bool Empty()const;
        char& Front();
        char& Back();

        void PushBack(char c);
        void PopBack();
        void Append(char c);
        void Append(const String& str);
        void Clear();
        void Resize(ui size);
        iterator Insert(ui pos, const char& c);
        iterator Insert(iterator p, const char& c);
        iterator Erase(iterator p);
        iterator Erase(ui pos, ui size=1);
        String Substr(ui pos, ui size=1);
        [[nodiscard]] const iterator& cbegin()const;
        [[nodiscard]] const iterator& cend()const;
        [[nodiscard]] const iterator& begin()const;
        [[nodiscard]] const iterator& end()const;
        [[nodiscard]] const Vector<char>::reverseIterator& crbegin()const;
        [[nodiscard]] const Vector<char>::reverseIterator& crend()const;
        iterator& begin();
        iterator& end();
        Vector<char>::reverseIterator& rbegin();
        Vector<char>::reverseIterator& rend();
        
        String& operator=(const String& str);
        String& operator=(String&& str)noexcept;
        char& operator[](ui pos);
        const char& operator[](ui pos)const;
        String operator+(const String& str);
        String operator+(char c);
        String operator+(const char* p);
        String& operator+=(const String& str);
        String& operator+=(const char& c);
        String& operator+=(const char* p);
        bool operator==(const String& str);
        bool operator!=(const String& str);
        bool operator<(const String& str);
        bool operator>(const String& str);

    private:
        Vector<char>Data;
};

std::istream& operator>>(std::istream& o, String& str);
std::ostream& operator<<(std::ostream& o, const String& str);
String operator+(char c, const String& str);
String operator+(const char* p, const String& str);

String ToString(long long num);
long long ToDigit(String str);

#endif
