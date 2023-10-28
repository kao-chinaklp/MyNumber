#ifndef STRING_H_
#define STRING_H_

#include "Vector.h"

#include <ostream>

class String{
    public:
        String()=default;
        String(char* init);
        String(const String& init);
        String(char* _start, char* _end);
        ~String();

        ui find(const char c);

        void operator<<(std::ostream& o);
        String operator+(const String& str);
        String operator+=(const String& str);

    private:
        Vector<char>Data;
};

#endif