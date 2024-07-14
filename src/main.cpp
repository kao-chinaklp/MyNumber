#include "MyNumber.h"

#include <iostream>

using namespace std;

int main(){
    MyNumber num1, num2;
    while(true){
        cin>>num1;
        cin>>num2;
        auto res=num1/num2;
        cout<<res.Str()<<"\n";
    }
    return 0;
}