#include<iostream>

int& GetValue(){
    static int value=10;
    return value;
}

int main(){
    int i = GetValue();
    std::cout<<i<<std::endl;
    GetValue()=5;
    std::cout<<i<<std::endl;
    std::cout<<GetValue()<<std::endl;
}