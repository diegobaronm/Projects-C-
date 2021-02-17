#include<string>
#include<iostream>
#include<cmath>

class Particle {
    //---------------------FRIENDS OF THE CLASS-------------------------------
    //OBJECT INFORMATION PRINTER
    friend std::ostream & operator<<(std::ostream &os, const Particle& P){
        P.Info();
        return os;
    };

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
    std::string GetName()const;
    std::string GetType()const;
    bool IsFundamental()const;
    int GetCharge()const;
    double GetMass()const;
    double GetSpin()const;
    double GetPosX()const;
    double GetPosY()const;
    double GetVelX()const;
    double GetVelY()const;

    virtual void Info() const;
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
void Particle::Info()const{
    //CHECK SPIN AND CONVERT IT TO STRING
    std::string sspin="1/2";
    if (spin==0 || spin==1 || spin==2)
    {
        sspin=std::to_string(spin);
    } else if (spin==1.5)
    {
        sspin="3/2";
    }
    //CHECK IF IT IS POINT LIKE AND CONVERT IT TO STRING
    std::string pl="Yes";
    if(!point_like){
        pl="No";
    }
    //CREATE THE OUTPUT STRING
    std::cout<<"Information of "<<name<<" :"<<std::endl;
    std::cout<<"Charge: "<<charge<<std::endl;
    std::cout<<"Mass: "<<mass<<std::endl;
    std::cout<<"Spin: "<<sspin<<std::endl;
    std::cout<<"Type: "<<type<<std::endl;
    std::cout<<"Point like: "<<pl<<std::endl;
    std::cout<<"Position: "<<"("<<x<<","<<y<<")"<<std::endl;
    std::cout<<"Velocity: "<<"("<<v_x<<","<<v_y<<")"<<std::endl;

    //return os;
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
std::string Particle::GetName()const{
    return name;
}
int Particle::GetCharge()const{
    return charge;
}
std::string Particle::GetType()const{
    return type;
}
bool Particle::IsFundamental()const{
    return point_like;
}
double Particle::GetMass()const{
    return mass;
}
double Particle::GetSpin()const{
    return spin;
}
double Particle::GetPosX()const{
    return x;
}
double Particle::GetPosY()const{
    return y;
}
double Particle::GetVelX()const{
    return v_x;
}
double Particle::GetVelY()const{
    return v_y;
}
//ELECTRON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Electron : public Particle{
     //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Electron &E){
        E.Info();
        return os;
    }
    protected :
    bool on_atom{false};

    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Electron() : Particle{"Electron(Default)",-1,0.5,0.5,0,0,0,0,"Lepton",true}{std::cout<<"Electron Created(DEFAULT)"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Electron(std::string name, double x, double y, double vx, double vy, bool on_at) : Particle{name,-1,0.5,0.5,x,y,vx,vy,"Lepton",true}, on_atom(on_at){std::cout<<"Electron Created"<<std::endl;}
    // MOVE CONSTRUCTOR
    Electron(Electron &&E){
        std::cout<<"Electron Created(Move)"<<std::endl;
        name=E.name;
        charge=E.charge;
        mass=E.mass;
        spin=E.spin;
        x=E.x;
        y=E.y;
        v_x=E.v_x;
        v_y=E.v_y;
        type=E.type;
        point_like=E.point_like;
        on_atom=E.on_atom;
    }
    // DESTRUCTOR
    ~Electron(){std::cout<<"Electron Destroyed"<<std::endl;}

    //ASSIGNEMENT OPERATOR
    Electron & operator=(const Electron &E){
        std::cout<<"Assignement opeartor for Electron"<<std::endl;
        if(&E==this){return *this;}
        name=E.GetName();
        charge=E.GetCharge();
        mass=E.GetMass();
        spin=E.GetSpin();
        x=E.GetPosX();
        y=E.GetPosY();
        v_x=E.GetVelX();
        v_y=E.GetVelY();
        type=E.GetType();
        point_like=E.IsFundamental();
        on_atom=E.GetBound();
        return *this;
    }
    void SetMass(double m){
        std::cout<<"You can not change the mass of the electron!"<<std::endl;
    }
    void Info() const{
        this->Particle::Info();

        std::string status="free.";
        if(on_atom){status="bound.";}
        std::cout<<"Electron is "<<status<<std::endl;
    };
    bool GetBound()const{return on_atom;}
};

//PROTON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Proton : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Proton &P){
        P.Info();
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
    void Info() const{
        this->Particle::Info();

        std::string status="free.";
        if(on_atom){status="bound.";}
        std::cout<<"Proton is "<<status<<std::endl;
    };
};

//NEUTRON CLASS DEFINITION ---- INHERITS FROM PARTICLE
class Neutron : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Neutron &N){
        N.Info();
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
    void Info() const{
        this->Particle::Info();

        std::string status="free.";
        if(on_atom){status="bound.";}
        std::cout<<"Neutron is "<<status<<std::endl;
    };
};

class Atom : public Particle{
    //-------------FRIENDS-------------------
    friend std::ostream & operator<<(std::ostream &os , Atom &A){
        A.Info();
        return os;
    }
    protected:
    int Z{0},A{0},N_e{0};
    std::string element{"Empty Space"};
    Proton * protons;
    Electron * electrons;
    Neutron * neutrons;

    public :
    // CONSTRUCTORS
    // DEFAULT CONSTRUCTOR
    Atom() : Particle{"Atom(Default)",0,0,0,0,0,0,0,"Atom",true}{std::cout<<"Atom Created"<<std::endl;}
    // PARAMETRIZED CONSTRUCTOR
    Atom(std::string name, double x, double y, double vx, double vy, int Z, int A, int N_e, std::string element);
    // DESTRUCTOR
    ~Atom(){std::cout<<"Atom Destroyed"<<std::endl;}

    //METHODS TO ACCESS THE CONSTITUENTS OF THE ATOM
    Electron & GetElectron(const int &i){return electrons[i-1];}
    Proton & GetProton(const int &i){return protons[i-1];};
    Neutron & GetNeutron(const int &i){return neutrons[i-1];};
    void Info()const{
        this->Particle::Info();
        std::cout<<"Atom is "<<element<<std::endl;
        std::cout<<"Number of electrons is: "<<N_e<<std::endl;
        std::cout<<"Number of protons is: "<<Z<<std::endl;
        std::cout<<"Number of neutrons is: "<<(A-Z)<<std::endl;
    }
};

//PARAMETRIZED CONSTRUCTOR OF ATOM CLASS
Atom::Atom(std::string name, double x, double y, double vx, double vy, int Z, int A, int N_e, std::string element) : Particle(name,Z-N_e,((double) A-(double) Z)*940+(double) Z*938,0,x,y,vx,vy,"Atom",false),Z(Z), A(A), N_e(N_e), element(element){
    std::cout<<"Atom Created"<<std::endl;
    // DEFINING THE ARRAY CONTAINING THE POINTERS TO THE PARTICLES OF THE ATOM
    protons = new Proton[A+N_e];
    electrons = new Electron[A+N_e];
    neutrons = new Neutron[A+N_e];
    for(size_t i{0};i<Z;i++){
        protons[i]=Proton(name+"_Proton_"+std::to_string(i),0,0,0,0,true);
    }
    for(size_t i{0};i<N_e;i++){
        electrons[i]=Electron(name+"_Electron_"+std::to_string(i),1,1,1,1,true);
    }
    for(size_t i{0};i<(A-Z);i++){
        neutrons[i]=Neutron(name+"_Neutron_"+std::to_string(i),0,0,0,0,true);
    }
}




int main(){
    //Particle par1=Particle("Pedro",1,2.5,1,0,0,1,2,"Higgs",true);
    Electron e1=Electron("Ana",1,1,1,1,true);
    Electron e2,e3;
    e3=e2=e1;
    //Proton p1=Proton("Naomi",0,0,0,0,true);
    //Neutron n1=Neutron("Pablo",0,0,0,0,false);
    Atom a1 = Atom("Diego",0,0,0,0,1,1,1,"Hidrogen");
    //n1=Neutron("Pablo Emilio",1,0,1,0,true);
    //std::cout<<par1<<std::endl;
    std::cout<<e1<<std::endl;
    std::cout<<e2<<std::endl;
    std::cout<<e3<<std::endl;
    //std::cout<<n1<<std::endl;
    std::cout<<a1<<std::endl;
    std::cout<<a1.GetElectron(1)<<std::endl;

    return 0;
}