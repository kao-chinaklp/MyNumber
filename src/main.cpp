#include "MyNumber.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    MyNumber num1, num2;
    auto t=clock();
    while(true){
        cin>>num1;
        cin>>num2;
        t=clock();
        auto res=num1/num2;
        cerr<<res.Str()<<" costs: "<<clock()-t<<" ms"<<"\n";
    }
    return 0;
}