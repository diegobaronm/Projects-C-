#include<iostream>
using namespace std;

class NComplejo{
    private:
    double real,imagi;


    public:
    NComplejo();
    ~NComplejo();
    
    NComplejo(double r,double i);
    void asigna_real(double r);
    void asigna_comp(double i);
    double parte_real();
    double parte_imag();
    void suma(const NComplejo& a,const NComplejo& b);

};

void NComplejo::asigna_real(double r){
    real=r;
}
double NComplejo::parte_real(){
    return real;
}
double NComplejo::parte_imag(){
    return imagi;
}
void NComplejo::suma(const NComplejo& a,const NComplejo& b){
    real=a.real+b.real;
    imagi=a.imagi+b.imagi;
}
NComplejo::NComplejo(){
    real=1;
    imagi=0;
}
NComplejo::~NComplejo(){

}
NComplejo::NComplejo(double r,double i){
    real=r;
    imagi=i;
}

class VComplejo{
    private:
        NComplejo v[3];
    public:
        VComplejo();
        VComplejo(NComplejo& a,NComplejo& b,NComplejo& c);
        ~VComplejo();
        void asignar(int i, const NComplejo& c);
        NComplejo acceder(int i);
        void suma(const VComplejo& a, const VComplejo& b);
};


VComplejo::VComplejo(){

}
VComplejo::~VComplejo(){

}
VComplejo::VComplejo(NComplejo& a,NComplejo& b,NComplejo& c){
    v[0]=a;
    v[1]=b;
    v[2]=c;

}
void VComplejo::asignar(int i,const NComplejo& c){
    v[i]=c;
}
NComplejo VComplejo::acceder(int i){
    return v[i];
}


int main(){
    NComplejo j,i,k;
    
    NComplejo v[10];
    j.asigna_real(3);
    cout<<"Parte real: "<<j.parte_real();

    cout<<v[2].parte_real();

    


    
}