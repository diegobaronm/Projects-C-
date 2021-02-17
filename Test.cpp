#include<iostream>
#include<vector>

int main(){
std::vector<uint32_t> list_events;
        list_events={352340,1722400988,359191,2719631360,352340,1722422389,359191,2719568896};
        for(int i;i<list_events.size();i=i+2){
                std::cout<< i; 
                if(list_events.at(i)==10){ 
                        if(list_events.at(i+1)==12){ 
                                std::cout<< true;
                        }
                }
        }
        std::cout<< false;
}