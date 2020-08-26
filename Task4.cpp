#include<iostream>
#include<string>
#include<vector>
#include<cmath>
class galaxy
{
private:
  std::string hubble_type{"E0"};
  double redshift{1};
  double total_mass{pow(10,10)};
  double stellar_mass_fraction{0.01};
  std::vector<galaxy> satellites{};

public:
  // Constructors
    galaxy()=default;
    galaxy(std::string type, double red, double mass, double stelar_fraction);
  // Destructor
  ~galaxy(){std::cout<<"Destroying...Galaxy!"<<hubble_type<<std::endl;}
  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass();
  // Change galaxy's Hubble type
  void change_type(std::string type);
  // Prototyp   e for function to print out an object's data
  void print_data();
  // Add satellite galaxy
  void add_satellite(galaxy satellite_galaxy);
};

galaxy::galaxy(std::string type, double red, double mass, double stellar_fraction)
{
    if (type!="E0" && type!="E7" && type!="S0" && type!="Sa" && type!="Sb" && type!="Sc" && type!="SBa" && type!="SBb" && type!="SBc" && type!="Irr" )
    {
        std::cout<<"ADVERTENCIA: Se asigno un tipo de galaxia invalido. Se ha asignado el tipo E0 por defecto."<<std::endl;
        hubble_type="E0";
    }
    else
    {
        hubble_type=type;
    }
    if (red<=0.0 || red>=10.0)
    {
        std::cout<<"ADVERTENCIA: Se asigno un reshift invalido. Se ha asignado el valor 1 por defecto."<<std::endl;
        redshift=1.0;
    }
    else
    {
        redshift=red;
    }
    if (mass<=pow(10,7) || mass>=pow(10,12))
    {
        std::cout<<"ADVERTENCIA: Se asigno una masa invalida. Se ha asignado el valor 10e10 por defecto."<<std::endl;
        total_mass=pow(10,10);
    }
    else
    {
        total_mass=mass;
    }
    if (stellar_fraction<=0.0 || stellar_fraction>=0.05)
    {
        std::cout<<"ADVERTENCIA: Se asigno una fraccion de masa estelar invalida. Se ha asignado el valor 0.01 por defecto."<<std::endl;
        stellar_mass_fraction=0.01;
    }
    else
    {
        stellar_mass_fraction=stellar_fraction;
    }
}

void galaxy::change_type(std::string type)
{
    if (type!="E0" && type!="E7" && type!="S0" && type!="Sa" && type!="Sb" && type!="Sc" && type!="SBa" && type!="SBb" && type!="SBc" && type!="Irr" )
    {
        std::cout<<"ADVERTENCIA: Se asigno un tipo de galaxia invalido. Se ha asignado el tipo E0 por defecto."<<std::endl;
        hubble_type="E0";
    }
    else
    {
        hubble_type=type;
    }
}

void galaxy::print_data(){
    std::cout<<"Galaxy type: "<<hubble_type<<std::endl;
    std::cout<<"Redshift: "<<redshift<<std::endl;
    std::cout<<"Total mass: "<<total_mass<<std::endl;
    std::cout<<"Stelar mass fraction: "<<stellar_mass_fraction<<std::endl;
    if(satellites.size()==0){
        std::cout<<"The galaxy has no satellite galaxies."<<std::endl;
    } else {
        std::vector<galaxy>::iterator iter;
        std::cout<<"Satellite galaxies: "<<std::endl;
        for(iter=satellites.begin();iter<satellites.end();++iter){
            std::cout<<"Galaxy type: "<<iter->hubble_type<<std::endl;
            std::cout<<"Redshift: "<<iter->redshift<<std::endl;
            std::cout<<"Total mass: "<<iter->total_mass<<std::endl;
            std::cout<<"Stelar mass fraction: "<<iter->stellar_mass_fraction<<std::endl;
        }
    }

}
double galaxy::stellar_mass(){
    return total_mass*stellar_mass_fraction;
}

void galaxy::add_satellite(galaxy satellite_galaxy){
    satellites.push_back(satellite_galaxy);
}
// Print out an object's data

// End of class and associated member functions

// Main program
int main()
{

  // Example using default constructor
  galaxy g1; 
  galaxy g2("PIJA",2,pow(10,8),0.02);
  galaxy g3("E7",100,pow(10,9),0.1);
  galaxy g4("Sc",3,pow(10,10),0.04);
  // Example using parameterised constructor

  // print out data
    std::cout<<"G1"<<std::endl;
    g1.print_data();
    std::cout<<"G2"<<std::endl;
    g2.print_data();
    std::cout<<"G3"<<std::endl;
    g3.print_data();
  // Get and print out stellar mass
    std::cout<<"G3 Stellar mass: "<<g3.stellar_mass()<<std::endl;
  // Change Hubble type from Irr to S0
   g2.change_type("hola");
   g2.change_type("Irr");

    std::cout<<"G2"<<std::endl;
    g2.print_data();
  // Add satellite galaxies
    g1.add_satellite(g2);
    g1.add_satellite(g3);
    g3.add_satellite(g4);
    std::cout<<"G1"<<std::endl;
    g1.print_data();
    std::cout<<"G3"<<std::endl;
    g3.print_data();



  return 0;
}