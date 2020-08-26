#include<iostream>
#include<string>
#include<math.h>

class complex{
    friend std::ostream & operator<<(std::ostream &os, const complex &z);
    friend std::istream & operator>>(std::istream &is, complex& z);
    private:
        double x{};
        double y{};
    public:
        complex()=default;
        complex(double x_in, double y_in) : x{x_in}, y{y_in}{}
        ~complex(){std::cout<<"Destroying complex number"<<std::endl;}

        void set_x(double x_in){x=x_in;}
        void set_y(double y_in){y=y_in;}

        double Re() const {return x;}
        double Im() const {return y;}

        double Mod() const {return sqrt(x*x+y*y);}
        double Arg() const {
            if(x==0 && y==0){
                throw std::invalid_argument( "Complex number z=0+0i has no defined argument" );
            } else {
            return atan(y/x);}
        }

        complex dagger() const {
            complex temp(x,-y);
            return temp;
        }
        complex operator+(const complex &z)
        {
            complex temp{x+z.x,y+z.y};
            return temp;
        }

        complex operator-(const complex &z)
        {
            complex temp{x-z.x,y-z.y};
            return temp;
        }

        complex operator*(const complex &z)
        {
            complex temp{x*z.x-y*z.y,x*z.y+y*z.x};
            return temp;
        }

        complex operator/(const complex &z)
        {
            complex temp{(x*z.x+y*z.y)/(x*z.x+y*z.y),(y*z.x-x*z.y)/(x*z.x+y*z.y)};
            return temp;
        }

        



};
std::istream & operator>>(std::istream &is, complex& z)
{
    std::string a;
    is>>a;
    std::string real,imaginario;
    int pos{};
    int signo{1};
    for(auto it=a.begin();it<a.end();++it){
        if(*it=='+'){
            break;
        } 
        if(*it=='-'){
            signo=-1;
            break;
        }
        pos+=1;
    }
    int c{};
    for(auto it=a.begin();it<a.end();++it){
        if(c<pos){
            real.push_back(*it);
        } 
        if(c>pos){
            imaginario.push_back(*it);
        }
        c+=1;
    }

    z.set_x(stoi(real));
    z.set_y(signo*stoi(imaginario));
    return is;
}


std::ostream & operator<<(std::ostream &os, const complex &z){
    if(z.y>=0){
        os<<z.x<<"+"<<z.y<<"i"<<std::endl;
        return os;
    } else {
        os<<z.x<<z.y<<"i"<<std::endl;
        return os;
    }
}


int main(){

    complex z;
    complex a{1,1},b{1,0},c{0,1};

    std::cout<<"z"<<std::endl;
    std::cout<<z.Re()<<","<<z.Im()<<std::endl;

    std::cout<<"a"<<std::endl;
    std::cout<<a.Re()<<","<<a.Im()<<std::endl;

    std::cout<<"b"<<std::endl;
    std::cout<<b.Re()<<","<<b.Im()<<std::endl;

    std::cout<<"c"<<std::endl;
    std::cout<<c.Re()<<","<<c.Im()<<std::endl;

    z.set_x(2);
    z.set_y(22);

    std::cout<<"z"<<std::endl;
    std::cout<<"Mod: "<<z.Mod()<<","<<"Arg: "<<z.Arg()<<std::endl;

    std::cout<<"a"<<std::endl;
    std::cout<<"Mod: "<<a.Mod()<<","<<"Arg: "<<a.Arg()<<std::endl;

    std::cout<<"b"<<std::endl;
    std::cout<<"Mod: "<<b.Mod()<<","<<"Arg: "<<b.Arg()<<std::endl;

    std::cout<<"c"<<std::endl;
    std::cout<<"Mod: "<<c.Mod()<<","<<"Arg: "<<c.Arg()<<std::endl;

    std::cout<<z;

    complex zz;
    std::cin>>zz;

    std::cout<<zz;

    std::cout<<zz.Mod()<<std::endl;


    return 0;
}