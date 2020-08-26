#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>

using namespace std;

double mean(double myarray[], int N)
{
    double sum{};
    double mean{};
    for (int i{}; i < N; i++)
    {
        sum+=myarray[i];
    }
    mean=sum/N;
    return mean;
}

double std_dev(double myarray[], int N, double mu)
{
    double sum{};
    double sigma{};
    for (int i{}; i < N; i++)
    {
        sum+=(myarray[i]-mu)*(myarray[i]-mu);
    }
    sigma=sqrt(sum/(N-1));
    myarray[2]=500.0;
    return sigma;
}

bool input_checker(string& n_data_points, int &n){
    try {
        if (n_data_points==""){
            n=50;
            return false;    
        }
        n=stoi(n_data_points);
        return false;
    } catch (invalid_argument& e) {
        return true;
    }
}

bool filename_checker(string& filename, ifstream& data){
    data.open(filename);
    if (data.is_open()){
        return false;
    } else {
        return true;
    }
}

int main()
{
    string n_data_points;
    string filename;
    ifstream data;
    string line;
    int file_line{0};
    int valid_lines{0};
    int n{0};
    cout << "Ingrese el numero de datos a usar o presione enter para usarlos todos: "<<endl;
    getline(cin,n_data_points);
    while(input_checker(n_data_points,n)){
        cout << "Entrada no valida, intente de nuevo: " << endl;
        getline(cin,n_data_points);
    }
    cout << "Ingrese el nombre del archivo que contiene los datos: "<<endl;
    getline(cin,filename);
    while (filename_checker(filename,data)){
        cout << "No hay ningun archivo llamado "<<filename<<" , intente de nuevo."<<endl;
        getline(cin,filename);
    }
    while (getline(data,line)){
        file_line++;
        try {
            stod(line);
            valid_lines++;
        } catch (invalid_argument& e){
            cout << "WARNING: "<<line<<" in line number"<<file_line<<" is not a number"<<endl;
        } 
    }
    if (valid_lines<n){
        cout << "Your data have less data points than the number you requested... working with the maximum."<<endl;
        n=valid_lines;
    }
    data.close();
    data.open(filename);
    double data_points[n];
    file_line=0;
    while (getline(data,line) && file_line<n){
        try {
            data_points[file_line]=stod(line);
            file_line++;
        } catch (invalid_argument& e){
            file_line+=-1;
        }
         
    }
    double media=mean(data_points,n);
    double desv_est=std_dev(data_points,n,media);

    std::cout<<"La media es: "<<media<<std::endl;
    std::cout<<"La desviacion estandar es: "<<desv_est<<std::endl;


  return 0;
}
