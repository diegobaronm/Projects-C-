#include<string>
#include<iostream>
#include<cmath>

class Particle {
    //---------------------FRIENDS OF THE CLASS-------------------------------
    //OBJECT INFORMATION PRINTER
    friend std::ostream & operator<<(std::ostream &os, const Particle& P);

    protected:
    //PROPERTIES OF THE PARTICLE
    std::string name{"Particle (Default Name)"};
    int charge{0};
    double mass{0}, spin{0.5}, x{0}, y{0}, v_x{0}, v_y{0};
    std::string type{"Lepton"};
    bool point_like{true};

    public:
    //DEFAULT CONSTUCTOR
    Particle(){std::cout<<"Particle created"<<std::endl;}
    //PARAMETRIZED CONSTRUCTOR
    Particle(std::string nme, int c, double m, double s, double x, double y, double vx, double vy, std::string t, bool p_l);
    //Destructor
    ~Particle(){std::cout<<"Particle destroyed"<<std::endl;}

    //SETTERS
    void SetName(std::string nme);
    virtual void SetMass(double m);
    void SetSpin(double s);
    void SetPosX(double xx);
    void SetPosY(double yy);
    void SetVelX(double vx);
    void SetVelY(double vy);
    //GETTERS
    std::string GetName();
    std::string GetType();
    bool IsFundamental();
    int GetCharge();
    double GetMass();
    double GetSpin();
    double GetPosX();
    double GetPosY();
    double GetVelX();
    double GetVelY();
};
//PARAMETRIZED CONSTRUCTOR
Particle::Particle(std::string nme, int c, double m, double s, double posx, double posy, double vx, double vy, std::string t, bool p_l){
    std::cout<<"Particle created"<<std::endl;
    name=nme;
    charge=c;
    mass=m;
    spin=s;
    x=posx;
    y=posy;
    v_x=vx;
    v_y=vy;
    type=t;
    point_like=p_l;
}
// << OVERLOAD OPERATOR
std::ostream & operator<<(std::ostream &os, const Particle& P){
    //CHECK SPIN AND CONVERT IT TO STRING
    std::string spin="1/2";
    if (P.spin==0 || P.spin==1 || P.spin==2)
    {
        spin=std::to_string(P.spin);
    } else if (P.spin==1.5)
    {
        spin="3/2";
    }
    //CHECK IF IT IS POINT LIKE AND CONVERT IT TO STRING
    std::string pl="Yes";
    if(!P.point_like){
        pl="No";
    }
    //CREATE THE OUTPUT STRING
    os<<"Information of "<<P.name<<" :"<<std::endl;
    os<<"Charge: "<<P.charge<<std::endl;
    os<<"Mass: "<<P.mass<<std::endl;
    os<<"Spin: "<<spin<<std::endl;
    os<<"Type: "<<P.type<<std::endl;
    os<<"Point like: "<<pl<<std::endl;
    os<<"Position: "<<"("<<P.x<<","<<P.y<<")"<<std::endl;
    os<<"Velocity: "<<"("<<P.v_x<<","<<P.v_y<<")"<<std::endl;

    return os;
}
//SETTER METHODS
void Particle::SetName(std::string nme){
    name=nme;
}
void Particle::SetMass(double m){
    mass=m;
}
void Particle::SetSpin(double s){
    spin=s;
}
void Particle::SetPosX(double xx){
    x=xx;
}
void Particle::SetPosY(double yy){
    y=yy;
}
void Particle::SetVelX(double vx){
    v_x=vx;
}
void Particle::SetVelY(double vy){
    v_y=vy;
}
//GETTER METHODS
std::string Particle::GetName(){
    return name;
}
std::string Particle::GetType(){
    return type;
}
bool Particle::IsFundamental(){
    return point_like;
}
double Particle::GetMass(){
    return mass;
}
double Particle::GetSpin(){
    return spin;
}
double Particle::GetPosX(){
    return x;
}
double Particle::GetPosY(){
    return y;
}
double Particle::GetVelX(){
    return v_x;
}
double Particle::GetVelY(){
    return v_y;
}
//ELECTRON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Electron : public Particle{
     //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Electron &E){
        std::string status="free.";
        if(E.on_atom){status="bound.";}
        //CAST TO A PARTICLE TYPE TO USE BASE CLASS FRIEND FUNCTION
        os<<(const Particle&)E;
        os<<"Electron is "<<status<<std::endl;
        return os;
    }
    protected :
    bool on_atom{false};

    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Electron() : Particle{"Electron(Default)",-1,0.5,0.5,0,0,0,0,"Lepton",true}{std::cout<<"Electron Created"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Electron(std::string name, double x, double y, double vx, double vy, bool on_at) : Particle{name,-1,0.5,0.5,x,y,vx,vy,"Lepton",true}, on_atom(on_at){std::cout<<"Electron Created"<<std::endl;}
    // DESTRUCTOR
    ~Electron(){std::cout<<"Electron Destroyed"<<std::endl;}

    void SetMass(double m){
        std::cout<<"You can not change the mass of the electron!"<<std::endl;
    }
};

//PROTON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Proton : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Proton &P){
        std::string status="free.";
        if(P.on_atom){status="bound.";}
        //CAST TO A PARTICLE TYPE TO USE BASE CLASS FRIEND FUNCTION
        os<<(const Particle&)P;
        os<<"Proton is "<<status<<std::endl;
        return os;
    }
    protected :
    bool on_atom{false};

    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Proton() : Particle{"Proton(Default)",1,938,0.5,0,0,0,0,"Nucleon",false}{std::cout<<"Proton Created"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Proton(std::string name, double x, double y, double vx, double vy, bool on_at) : Particle{name,1,938,0.5,x,y,vx,vy,"Nucleon",false}, on_atom(on_at){std::cout<<"Proton Created"<<std::endl;}
    // DESTRUCTOR
    ~Proton(){std::cout<<"Proton Destroyed"<<std::endl;}
};

//NEUTRON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Neutron : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Neutron &N){
        std::string status="free.";
        if(N.on_atom){status="bound.";}
        //CAST TO A PARTICLE TYPE TO USE BASE CLASS FRIEND FUNCTION
        os<<(const Particle&)N;
        os<<"Neutron is "<<status<<std::endl;
        return os;
    }
    protected :
    bool on_atom{false};

    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Neutron() : Particle{"Neutron(Default)",0,940,0.5,0,0,0,0,"Nucleon",false}{std::cout<<"Neutron Created"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Neutron(std::string name, double x, double y, double vx, double vy, bool on_at) : Particle{name,0,940,0.5,x,y,vx,vy,"Nucleon",false}, on_atom(on_at){std::cout<<"Neutron Created"<<std::endl;}
    // DESTRUCTOR
    ~Neutron(){std::cout<<"Neutron Destroyed"<<std::endl;}
};

class Atom : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Atom &A){
        //CAST TO A PARTICLE TYPE TO USE BASE CLASS FRIEND FUNCTION
        os<<(const Particle&)A;
        os<<"Atom is "<<A.element<<std::endl;
        os<<"Number of electrons is: "<<A.N_e<<std::endl;
        os<<"Number of protons is: "<<A.Z<<std::endl;
        os<<"Number of neutrons is: "<<(A.A-A.Z)<<std::endl;
        return os;
    }
    protected:
    int Z{0},A{0},N_e{0};
    std::string element{"Empty Space"};
    Particle **particles{nullptr};


    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Atom() : Particle{"Atom(Default)",0,0,0,0,0,0,0,"Atom",true}{std::cout<<"Atom Created"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Atom(std::string name, double x, double y, double vx, double vy, int Z, int A, int N_e, std::string element);
    // DESTRUCTOR
    ~Atom(){std::cout<<"Atom Destroyed"<<std::endl;}

    //METHODS TO ACCESS THE CONSTITUENTS OF THE ATOM
    Particle & operator()(const std::string &type,const int &p);

};

//PARAMETRIZED CONSTRUCTOR OF ATOM CLASS
Atom::Atom(std::string name, double x, double y, double vx, double vy, int Z, int A, int N_e, std::string element) : Particle(name,Z-N_e,((double) A-(double) Z)*940+(double) Z*938,0,x,y,vx,vy,"Atom",false),Z(Z), A(A), N_e(N_e), element(element){
    std::cout<<"Atom Created"<<std::endl;
    // DEFINING THE ARRAY CONTAINING THE POINTERS TO THE PARTICLES OF THE ATOM
    particles = new Particle*[3];
    particles[0]= new Proton[Z];
    particles[1]= new Electron[N_e];
    particles[2]= new Neutron[A-Z];
    for(size_t i{0};i<Z;i++){
        particles[0][i]=Proton(name+"_Proton_"+std::to_string(i),0,0,0,0,true);
    }
    for(size_t i{0};i<N_e;i++){
        particles[1][i]=Electron(name+"_Electron_"+std::to_string(i),0,0,0,0,true);
    }
    for(size_t i{0};i<(A-Z);i++){
        particles[2][i]=Proton(name+"_Neutron_"+std::to_string(i),0,0,0,0,true);
    }
}

Particle & Atom::operator()(const std::string &type, const int &p){
    if(type=="P"){
        return particles[0][p];
    } else if(type=="N"){
        return particles[2][p];
    } else if(type=="E"){
        return particles[1][p];
    } else {
        std::cout<<"Invalid atom particle or index"<<std::endl;
        throw;
    }
}



int main(){
    Particle par1=Particle("Pedro",1,2.5,1,0,0,1,2,"Higgs",true);
    Electron e1=Electron("Ana",1,1,1,1,true);
    Proton p1=Proton("Naomi",0,0,0,0,true);
    Neutron n1=Neutron("Pablo",0,0,0,0,false);
    Atom a1 = Atom("Diego",0,0,0,0,2,4,2,"Helium");

    std::cout<<par1<<std::endl;
    std::cout<<e1<<std::endl;
    std::cout<<p1<<std::endl;
    std::cout<<n1<<std::endl;
    std::cout<<a1<<std::endl;
    std::cout<<(a1("P",1))<<std::endl;

    return 0;
}