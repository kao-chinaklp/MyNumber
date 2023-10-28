#include "MyNumber.h"

#include <iostream>

using namespace std;

int main(){
    MyNumber num1, num2;
    string in;
    while(true){
        cin>>in;
        num1=in;
        cin>>in;
        num2=in;
        auto res=num1/num2;
        cout<<res.Str()<<endl;
    }
    return 0;
}