#include<iostream>
#include<string>
#include<cmath>

class general_vector{
    friend std::ostream & operator<<(std::ostream &os, const general_vector &V);
    protected :

    int dimension{};
    double *components{nullptr};

    public :
    // DEFAULT CONSTRUCTOR
    general_vector(){std::cout<<"Vector has been created"<<std::endl;}
    // DESTRUCTOR
    ~general_vector(){std::cout<<"Vector has been destroyed"<<std::endl;}
    // PARAMETRIZED CONSTRUCTORS
    general_vector(int dim);
    general_vector(int dim,std::string manual);
    // COPY CONSTRUCTOR
    general_vector(const general_vector &V);
    // MOVE CONSTURCTOR
    general_vector(general_vector &&V);


    //OPERATORS OVERLOADING
    // ASSIGNMENT OPERATOR (COPY AND MOVE)
    general_vector & operator=(general_vector &V);
    general_vector & operator=(general_vector &&V);
    // INDEXING OPERATOR
    double & operator[](int position);

    // DOT PRODUCT
    double operator*(const general_vector &V) const;

    //GETTERS
    int get_dim(){return dimension;}

    //SETTERS
    void set_dim(int dim){dimension=dim;}

};

// PARAMETRIZED CONSTRUCTOR
general_vector::general_vector(int dim){
    dimension=dim;
    components = new double[dim];
    for (size_t i = 0; i < dim; i++){
        components[i]=0;
    }
    std::cout<<"Vector has been created"<<std::endl;
}
general_vector::general_vector(int dim, std::string manual){
    if(manual=="y"){
        dimension=dim;
        components = new double[dim];
        for (size_t i = 0; i < dim; i++){
            std::cout<<"Input the "<<std::to_string(i)<<" component of the vector."<<std::endl;
            std::string input{};
            std::getline(std::cin, input);
            components[i]=stod(input);
        }
        std::cout<<"Vector has been created"<<std::endl;
    } if (manual=="n"){
        general_vector(dim);
    } else {
        std::cout<<"Invalid list of parameters"<<std::endl;
    }
}
// COPY CONSTUCTOR
general_vector::general_vector(const general_vector &V){
    dimension=V.dimension;
    components = new double[V.dimension];
    for (size_t i{} ;i<V.dimension;i++){
        components[i]=V.components[i];
    }
    std::cout<<"Vector has been created (copy)"<<std::endl;
}
//MOVE CONSTRUCTOR
general_vector::general_vector(general_vector &&V){
    std::cout<<"Move constructor"<<std::endl;
    dimension=V.dimension;
    components=V.components;
    V.dimension=0;
    V.components=nullptr;
}
// OVERLOADING << OPERATOR
std::ostream & operator<<(std::ostream &os, const general_vector &V){
    os<<"( ";
    for(size_t i=0;i<V.dimension;i++){
        os<<V.components[i]<<" ";
    }
    os<<")"<<std::endl;

    return os;
}
// OVERLOADING = OPERATOR
general_vector & general_vector::operator=(general_vector &V){
    if(&V==this){return *this;}

    delete [] components; dimension=0;

    dimension=V.dimension;
    components = new double[dimension];
    for (size_t i{} ;i<V.dimension;i++){
        components[i]=V.components[i];
    }
    return *this;
}
general_vector & general_vector::operator=(general_vector &&V){
    std::cout<<"Move assignement"<<std::endl;
    std::swap(dimension,V.dimension);
    std::swap(components,V.components);
    return *this;
}
// OVERLOADING [] OPERATOR
double & general_vector::operator[](int position){
    if (position<dimension){return components[position];}
    else {std::cout<<"Position out of range of the vector."<<std::endl;}
}
// OVERLOADING * OPERATOR
double general_vector::operator*(const general_vector &V) const{
    if (dimension==V.dimension)
    {
        double dot_product{};
        for(size_t i=0;i<dimension;i++){
            dot_product+=components[i]*V.components[i];
        }
        return dot_product;
    } else {
        std::cout<<"Dimension of the vectors must be equal."<<std::endl;
        return 0;
    }
}


class four_vector : public general_vector{


    public:
    //DEFAULT CONSTRUCTOR
    four_vector(){std::cout<<"4-Vector created."; dimension=4; components=new double[4]; components[0]=0;
    components[1]=0; components[2]=0;components[3]=0;}
    //PARAMETRIZED CONSTRUCTORS
    four_vector(double t,double x,double y,double z);
    four_vector(double t,general_vector &V);
    // DESTRUCTOR
    ~four_vector(){std::cout<<"4-Vector destroyed.";}
    // COPY CONSTRUCTOR
    four_vector(const four_vector &V);
    // MOVE CONSTRUCTOR
    four_vector(four_vector &&V);

    // OVERLOADING OPERATORS
    // COPY ASSIGNEMENT
    four_vector & operator=(const four_vector &V);
    // MOVE ASSIGNEMENT
    four_vector & operator=(four_vector &&V);

    //GETTERS
    // GET COMPONENTS
    double get_t(const four_vector &V){return components[0];}
    double get_x(const four_vector &V){return components[1];}
    double get_y(const four_vector &V){return components[2];}
    double get_z(const four_vector &V){return components[3];}

    // DOT PRODUCT
    double operator*(const four_vector &V);
    // LORENTZ BOOST
    four_vector lorentz_boost(general_vector &V);

};

// PARAMETRIZED CONSTRUCTORS
four_vector::four_vector(double t,double x,double y,double z){
    dimension=4;
    components=new double[4];
    components[0]=t;
    components[1]=x;
    components[2]=y;
    components[3]=z;
    std::cout<<"4-Vector created."<<std::endl;
}
four_vector::four_vector(double t,general_vector &V){
    if (V.get_dim()!=3){
        std::cout<<"Check dimension of the 3-vector."<<std::endl;
    } else {
        dimension=4;
        components=new double[4];
        components[0]=t;
        components[1]=V[0];
        components[2]=V[1];
        components[3]=V[2];
        std::cout<<"4-Vector created."<<std::endl;
    }
}
// COPY CONSTRUCTOR
four_vector::four_vector(const four_vector &V){
    dimension=V.dimension;
    components = new double[V.dimension];
    for (size_t i{} ;i<V.dimension;i++){
        components[i]=V.components[i];
    }
    std::cout<<"4-Vector created (copy)."<<std::endl;
}
// MOVE CONSTRUCTOR
four_vector::four_vector(four_vector &&V){
    dimension=V.dimension;
    components=V.components;
    V.dimension=0;
    V.components=nullptr;
    std::cout<<"4-Vector created (move)."<<std::endl;
}
// OVERLOADED OPERATORS
// COPY ASSIGNEMENT
four_vector & four_vector::operator=(const four_vector &V){
    if(&V==this){return *this;}

    delete [] components; dimension=0;
    dimension=V.dimension;
    components = new double[dimension];
    for (size_t i{} ;i<V.dimension;i++){
        components[i]=V.components[i];
    }
    return *this;
}

// MOVE ASSIGNEMENT
four_vector & four_vector::operator=(four_vector &&V){
    std::cout<<"Move assignement."<<std::endl;
    std::swap(dimension,V.dimension);
    std::swap(components,V.components);
    return *this;
}
//DOT PRODUCT
double four_vector::operator*(const four_vector &V){
    if (dimension!=V.dimension){std::cout<<"Dimensions of the vectors do not match."<<std::endl;
    return 0;}
    double dot_product{};
    dot_product=(-1)*components[0]*V.components[0];
    for(size_t i=1;i<dimension;i++){
        dot_product+=components[i]*V.components[i];
    }
    return (-1)*dot_product;
}
// LORENTZ BOOST
four_vector four_vector::lorentz_boost(general_vector &V){
    four_vector boosted_vector{};
    if(V.get_dim()!=3){std::cout<<"3-vector needed to perform Lorentz boost, check dimensions."<<std::endl; return boosted_vector;}
    else {
        double norm = sqrt(V*V);
        if (norm>=1){std::cout<<"Check velocity vector, velocity is equal or greater than c=speed of light."<<std::endl; return boosted_vector;}
        else {
            double gamma = (1/sqrt(1-norm*norm));
            double beta_times_r=V[0]*components[1]+V[1]*components[2]+V[2]*components[3];
            boosted_vector[0]=gamma*(components[0]-beta_times_r);
            boosted_vector[1]=components[1]+((gamma-1)*(beta_times_r/(norm*norm))-gamma*components[0]);
            boosted_vector[2]=components[2]+((gamma-1)*(beta_times_r/(norm*norm))-gamma*components[0]);
            boosted_vector[3]=components[3]+((gamma-1)*(beta_times_r/(norm*norm))-gamma*components[0]);
            return boosted_vector;
        }

    }

}

class particle{
    protected:
    four_vector position{};
    double mass{0};
    general_vector velocity{3};

    public:
    particle(){std::cout<<"Particle created."<<std::endl;}
};

int main(){
    general_vector a{3,"y"};
    general_vector b{std::move(a)};
    //a[2]=7;
    general_vector c=b;
    general_vector d;
    d=a;
    a=std::move(b);

    std::cout<<a;
    //std::cout<<a[2]<<std::endl;
    std::cout<<b;
    std::cout<<c;
    std::cout<<d;
    std::cout<<a*c;



    four_vector x{1,a};
    four_vector y(1,2,3,4);
    four_vector z{y};
    four_vector w{std::move(y)};

    four_vector boosted_z=z.lorentz_boost(a);
    std::cout<<x;
    std::cout<<y;
    std::cout<<z;
    std::cout<<w;
    std::cout<<x*z<<std::endl;
    std::cout<<boosted_z;

    return 0;
}