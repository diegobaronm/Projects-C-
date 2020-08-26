#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<typeinfo>

double energy(int n_i,int n_j,int Z, std::string units)
{
    double E;
    E=13.6*Z*Z*(1/(n_j*n_j)-1/(n_i*n_i)); 
    if(units.compare("eV")==0)
    {
        return E;
    } 
    else 
    {
        return E*1.6e-19;
    }
}

bool format_checker(std::string input)
{
    int space_counter{};
    std::string temp;
    std::vector<std::string> palabras;
    for (int i{}; i < input.length(); i++)
    {
        if (input[i]!=' ')
        {
            temp.push_back(input[i]);
        }
        if (input[i]==' ' || i==(input.length()-1))
        {
            palabras.push_back(temp);
            temp.clear();
        }
    }
    if (palabras.size()==4)
    {
        try
        {
            int n_i = stoi(palabras[0]);
            int n_j = stoi(palabras[1]);
            int Z = stoi(palabras[2]);
        }
        catch(std::invalid_argument& e)
        {
            std::cout<<"Alguno de los numeros ingresados no es un entero. Intente de nuevo."<<std::endl;
            return true;
        }

        int n_i = stoi(palabras[0]);
        int n_j = stoi(palabras[1]);
        int Z = stoi(palabras[2]);

        if (n_j>n_i || n_i==0 || n_j==0)
        {
            std::cout<<"Los numeros cuanticos no tienen sentido fisico. Intente de nuevo."<<std::endl;
            return true;
        }
        if (palabras[3].compare("eV")!=0 && palabras[3].compare("J")!=0)
        {
            std::cout<<palabras[3];
            std::cout<<"Ingrese unidades validas."<<std::endl;
            return true;
        }
    }
    else
    {
        std::cout<<"Entrada invalida: Ingrese el numero correcto de argumentos."<<std::endl;
        return true;
    }
    return false;
}

std::vector<std::string> arguments(std::string input)
{
    int space_counter{};
    std::string temp;
    std::vector<std::string> palabras;
    for (int i{}; i < input.length(); i++)
    {
        if (input[i]!=' ')
        {
            temp.push_back(input[i]);
        }
        if (input[i]==' ' || i==(input.length()-1))
        {
            palabras.push_back(temp);
            temp.clear();
        }
    }
    
    return palabras;
}

int main()
{
    int n_i{},n_j{},Z{};
    std::string units;
    std::string input;
    std::vector<std::string> valid_input;
    bool answer_is=true;
    std::string answer;
    while(answer_is)
    {
        std::cout<<"Ingrese: numero cuantico inicial, numero cuantico final, numero atomico y escoja eV o J. "<<std::endl;
        std::getline(std::cin,input);
        while(format_checker(input))
        {
            std::cout<<"Ingrese: numero cuantico inicial, numero cuantico final, numero atomico y escoja eV o J. "<<std::endl;
            std::getline(std::cin,input);
        }
        valid_input=arguments(input);
        n_i=stoi(valid_input[0]);
        n_j=stoi(valid_input[1]);
        Z=stoi(valid_input[2]);
        units=valid_input[3];
        std::cout<<"La energia liberada en la transicion es: "<<std::endl<<energy(n_i,n_j,Z,units);
        if(units.compare("eV")==0)
        {
            std::cout<<" eV"<<std::endl;
        }
        else
        {
            std::cout<<" J"<<std::endl;
        }
        std::cout<<"Desea ejecutar de nuevo, responda(y/n):"<<std::endl;
        std::getline(std::cin,answer);
        while(answer!="y" && answer!="n")
        {
            std::cout<<"Respuesta invalida, intente de nuevo. (y/n):"<<std::endl;
            std::getline(std::cin,answer);
        }
        if(answer=="y")
        {
            answer_is=true;
        } 
        else 
        {
            answer_is=false;    
        }
    }   
}