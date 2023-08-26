#include "BaseNumber.h"

#include <iostream>

using namespace std;

int main(){
    BaseNumber num;
    string in;
    while(cin>>in){
        num=in;
        cout<<(num<=0)<<endl;
    }
    return 0;
}