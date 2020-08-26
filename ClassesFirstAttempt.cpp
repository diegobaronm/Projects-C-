#include<iostream>
#include <vector> 

using namespace std;

struct Animal{
    char tipo[10];
    bool sexo;
    int edad;
    int ejemplares;
};
bool sexo(Animal f){
    if (f.sexo)
    {
        cout<<"Macho";
        return 1;
    }
    else
    {
        cout<<"Hembra";
        return 0;
    }
    
};
void tipo(Animal f){

    cout<<f.tipo;

};


int main()

{

cout<<"Hola\n";

Animal Ninya={"Perro",0,2};
Animal Ninyo={"Perro",1,4};
Animal Tom={"Gato",1,5};
Animal Jerry={"Raton",1,3};
Animal Jill={"Gato",0,2};

vector<Animal> Animales={Ninya,Ninyo,Tom,Jerry,Jill};

for (int i = 0; i < Animales.size(); i++)
{
    cout<<Animales[i].tipo;
    cout<
}



}