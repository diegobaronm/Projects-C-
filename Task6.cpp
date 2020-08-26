#include<string>
#include<iostream>
#include<cmath>

class Matrix{
     //OVERLOADING OPERATORS FOR INPUT AND OUTPUT
     friend std::ostream & operator<<(std::ostream &os, const Matrix& M);
     friend std::istream & operator>>(std::istream &is, Matrix& M);
     friend Matrix operator*(const double &d , const Matrix& M);
    protected:
        size_t rows{0},columns{0};
        double **entries{nullptr};


    public:
        //DEFAULT CONSTRUCTOR
        Matrix(){std::cout<<"Matrix created"<<std::endl;}
        //PARAMETRIZED CONSTRUCTOR
        Matrix(size_t r, size_t c,std::string default_entries="zeros");
        // COPY CONSTRUCTOR
        Matrix(const Matrix& M);
        // MOVE CONSTRUCTOR
        Matrix(Matrix &&M);
        //Destructor
        ~Matrix(){std::cout<<"Matrix destroyed"<<std::endl;}
        size_t Rows() const{return rows;}
        size_t Columns() const{return columns;}
        //ASSIGNEMENT OPERATOR
        Matrix & operator=(const Matrix &M);
        //OPERATORS TO OVERLOAD [] OPEARTOR AND GET ANY ENTRY
        double get_entry(size_t r, size_t c) const{return entries[r][c];}
        double * & operator[](size_t row) const;
        //OVERLOADING ARITHMETIC OPERATORS
        Matrix operator+(const Matrix& A) const;
        Matrix operator-(const Matrix& A) const;
        Matrix operator*(const Matrix& A) const;
        Matrix operator*(const double &d) const;
        //MATRIX EXCLUSIVE OPERATIONS
        Matrix Minor(size_t r, size_t c) const;
        double Det() const;
        Matrix& Trans();
       




};

Matrix::Matrix(size_t r, size_t c, std::string default_entries){
    rows=r;
    columns=c;
    entries= new double*[rows];
    for (size_t i{};i<rows;i++){
        entries[i] = new double[columns];
    }
    if(default_entries=="zeros"){
        for(size_t i{}; i<rows; i++) 
            for(size_t j{};j<columns;j++){
                entries[i][j] = 0;
            }
        
    } else if(default_entries=="ones"){
        for(size_t i{}; i<rows; i++) 
            for(size_t j{};j<columns;j++){
                entries[i][j] = 1;
            }
        
    } else {
        bool valid_entry=false;
        for(int r{};r<rows;r++){
            for(int c{};c<columns;c++){
                std::cout<<"Enter the element["<<r+1<<","<<c+1<<"]:"<<std::endl;
                std::string entry;
                std::getline(std::cin,entry);
                double element{};
                while(!valid_entry){
                    try{
                        element=stod(entry);
                        valid_entry=true;
                    } catch (const std::exception& e){
                        valid_entry=false;
                        std::cerr << "Entry is not a valid number. Try again." <<std::endl;
                        std::getline(std::cin,entry);
                    }
                }
                entries[r][c]=element;
                valid_entry=false;
            }
        }
    }
}
Matrix::Matrix(const Matrix& M){
    rows=M.Rows();
    columns=M.Columns();
    entries= new double*[M.Rows()];
    for (size_t i{};i<M.Rows();i++){
        entries[i] = new double[M.Columns()];
    }
    for(size_t i{}; i<M.Rows(); i++) 
            for(size_t j{};j<M.Columns();j++){
                entries[i][j] = M[i][j];
    }
}
Matrix::Matrix(Matrix &&M){
    std::cout<<"Move constructor"<<std::endl;
    rows=M.rows;
    columns=M.columns;
    entries=M.entries;
}
Matrix & Matrix::operator=(const Matrix &M){
    if(&M==this) {return *this;}
    delete[] entries ;
    rows=M.Rows();
    columns=M.Columns();
    entries= new double*[M.Rows()];
    for (size_t i{};i<M.Rows();i++){
        entries[i] = new double[M.Columns()];
    }
    for(size_t i{}; i<M.Rows(); i++){
        for(size_t j{};j<M.Columns();j++){
            entries[i][j] = M[i][j];
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& A) const{
    if(rows!= A.rows || columns!=A.columns){
        std::cout<<"Matrices with different dimensions can not be added."<<std::endl;
        throw ;
    } else {
        Matrix Temp(A.rows,A.columns);
        for(int r{};r<rows;r++){
            for(int c{};c<columns;c++){
                Temp[r][c]=entries[r][c]+A.entries[r][c];
            }
        }
        return Temp;
    }
}
Matrix Matrix::operator-(const Matrix& A) const{
    if(rows!= A.rows || columns!=A.columns){
        std::cout<<"Matrices with different dimensions can not be substracted."<<std::endl;
        throw ;
    } else {
        Matrix Temp(A.rows,A.columns);
        for(int r{};r<rows;r++){
            for(int c{};c<columns;c++){
                Temp[r][c]=entries[r][c]-A.entries[r][c];
            }
        }
        return Temp;
    }
}
Matrix Matrix::operator*(const Matrix& A) const{
    if(columns!=A.rows){
        std::cout<<"Matrices with incompatible dimentions can not be multiplied."<<std::endl;
        throw ;
    } else{
        Matrix Temp(rows,A.columns);
        for(int r{};r<rows;r++){
            for(int c{};c<A.columns;c++){
                for (int i{}; i < A.rows; i++)
                {
                    Temp[r][c]=Temp[r][c]+entries[r][i]*A[i][c];
                }
            }
        }
        return Temp;
    }
}
Matrix operator*(const double &d ,const Matrix& M){
    Matrix c_M=M;
    for(size_t r{};r<M.rows;r++){
        for(size_t c{};c<M.columns;c++){
            c_M[r][c]=c_M[r][c]*d;
        }
    }
    return c_M;
}
Matrix Matrix::operator*(const double &d) const{
    Matrix c_M=*this;
    for(size_t r{};r<rows;r++){
        for(size_t c{};c<columns;c++){
            c_M[r][c]=c_M[r][c]*d;
        }
    }
    return c_M;
}
double * & Matrix::operator[](size_t row) const{
  return entries[row];
}  
std::ostream & operator<<(std::ostream &os, const Matrix& M){
    for(size_t i{};i<M.rows;i++){
        os<<"| ";
        for(size_t j{};j<M.columns;j++){
            os<<M[i][j]<<" ";
        }
        os<<"|"<<std::endl;
    }
    return os;
}
std::istream & operator>>(std::istream &is, Matrix& M){
    std::string ro,co;
    size_t r{},c{};
    std::cout<<"Input number of rows"<<std::endl;
    getline(std::cin,ro);
    std::cout<<"Input number of columns"<<std::endl;
    getline(std::cin,co);
    r=stoi(ro);
    c=stoi(co);
    Matrix Input(r,c,"l");
    M=Input;
    return is;
}

Matrix Matrix::Minor(size_t r, size_t c) const{
    if(rows==1 || columns==1){
        std::cout<<"Minor of a one dimensional object not defined.";
        throw ;
    }
    Matrix Minor(rows-1,columns-1);
    for(int ro{};ro<rows;ro++){
        for(int co{};co<columns;co++){
            if(ro<r && co<c){
                Minor[ro][co]=entries[ro][co];
            } else if (ro<r && co>c){
                Minor[ro][co-1]=entries[ro][co];
            } else if (ro>r && co<c){
                Minor[ro-1][co]=entries[ro][co];
            } else if (ro>r && co>c){
                Minor[ro-1][co-1]=entries[ro][co];
            }
        }
    }
    return Minor;
}
double Matrix::Det() const{
    if(rows!=columns){
        std::cout<<"Determinant is not defined for non square matrices.";
        throw ;
    } else if (rows==1){
        return entries[0][0];
    } else if(rows==2){
        return entries[0][0]*entries[1][1]-entries[1][0]*entries[0][1];
    } else {
        double det{};
        for(size_t i{};i<columns;i++){
            det=det+entries[0][i]*pow(-1,i)*(this->Minor(0,i)).Det();
        }
        return det;
    }

    return 0;
}
Matrix& Matrix::Trans(){
    size_t copy_rows{rows};
    double** copy_entries{std::move(entries)};
    rows=columns;
    columns=copy_rows;
    entries= new double*[rows];
    for (size_t i{};i<rows;i++){
        entries[i] = new double[columns];
    }
    for(size_t i{}; i<rows; i++) 
        for(size_t j{};j<columns;j++){
            entries[i][j] = copy_entries[j][i];
        }
    return *this;
}


Matrix Identity(size_t r){
    if(r==0){
        std::cout<<"Identity matrix must have dimensions greater than 0."<<std::endl;    
        throw ;
    } else {
        Matrix I{r,r};
        for(size_t i{};i<r;i++){
            I[i][i]=1;
        }
        return I;
    }
}

class Vector: public Matrix{
    protected:
        bool is_column{true};
        size_t Dimension{0};
    public:
        Vector(){std::cout<<"Column Vector Created"<<std::endl;}
        Vector(size_t dim, std::string default_entries="zeros", bool column_vector=true):Matrix(dim,1,default_entries),Dimension{dim}{
            if(!column_vector){
                is_column=false;
                double** copy_entries{std::move(entries)};      
                rows=1;
                columns=dim;
                entries= new double*[rows];
                for (size_t i{};i<rows;i++){
                    entries[i] = new double[columns];
                }
                for(size_t i{}; i<rows; i++) 
                    for(size_t j{};j<columns;j++){
                        entries[i][j] = copy_entries[j][i];
                    }
            }
        }
        size_t Dim()const;
        double Mag()const;
        Vector operator*(const Vector& B) const;
        double Dot(Vector& V) const;
        double& operator[](size_t entry) const;
        Vector operator+(const Vector& V)const;
        Vector operator-(const Vector& V)const;

};
size_t Vector::Dim()const{
    return Dimension;
}
double& Vector::operator[](size_t entry) const{
    if(is_column){
        return (entries[entry][0]);
    } else {
        return (entries[0][entry]);
    }
}
double Vector::Mag()const{
    double Mag{};
    for(size_t i{};i<rows;i++)
        for(size_t j{};j<columns;j++){
            Mag+=pow(entries[i][j],2);
        }
    return sqrt(Mag);
}
double Vector::Dot(Vector& V) const{
    if(this->Dim()!=V.Dim()){
        std::cout<<"Can not take the dot product of two different dimension vectors"<<std::endl;
        throw;
    } else {
        double dot{};
        for(size_t i{}; i<Dimension; i++) 
                dot+=(*this)[i]*V[i];
        return dot;
    }
}
Vector Vector::operator*(const Vector& V) const{
    if(Dimension!=3 || V.Dimension!=3){
        std::cout<<"Cross product not defined for vectors with dimension different to 3."<<std::endl;
        throw;
    } else{
        Vector Cross(3);
        Cross[0]=(*this)[1]*V[2]-(*this)[2]*V[1];
        Cross[1]=(*this)[0]*V[2]-(*this)[2]*V[0];
        Cross[2]=(*this)[0]*V[1]-(*this)[1]*V[0];
        return Cross;
    }
}
Vector Vector::operator+(const Vector& V) const{
    if(Dimension!=V.Dimension){
        std::cout<<"Vectors with different dimensions can not be added."<<std::endl;
        throw;
    } else {
        Vector Sum(Dimension);
        for(size_t i{0};i<Dimension;i++){
            Sum[i]=(*this)[i]+V[i];
        }
        return Sum;
    }
}
Vector Vector::operator-(const Vector& V) const{
    if(Dimension!=V.Dimension){
        std::cout<<"Vectors with different dimensions can not be added."<<std::endl;
        throw;
    } else {
        Vector Sum(Dimension);
        for(size_t i{0};i<Dimension;i++){
            Sum[i]=(*this)[i]-V[i];
        }
        return Sum;
    }
}

int main(){
    /*Matrix Test(3,2,"n");
    std::cout<<Test<<std::endl;
    std::cout<<Test.Trans()<<std::endl;
    Matrix A(2,2);
    Matrix B(2,2,"n");
    Matrix C{std::move(B)};
    Matrix D=C+A;

    std::cout<<"D"<<std::endl;
    std::cout<<D<<std::endl;
    D[1][1]=10;
    std::cout<<"D"<<std::endl;
    std::cout<<D<<std::endl;
    Matrix E;
    Matrix I=Identity(3);
    std::cout<<I<<std::endl;
    std::cin>>E;
    std::cout<<"Displaying Matrix"<<std::endl;
    Matrix R=(3*I+I*2);
    std::cout<<(3*I+I*2)<<std::endl;
    std::cout<<"Displaying reduced Matrix"<<std::endl;
    std::cout<<R.Minor(1,2)<<std::endl;*/

    Vector V(3,"n",true);
    Vector G(3,"n",false);
    std::cout<<V<<std::endl;
    std::cout<<G<<std::endl;
    std::cout<<G.Mag()<<std::endl;
    std::cout<<V.Dot(G)<<std::endl;
    std::cout<<V<<std::endl;
    std::cout<<G<<std::endl;
    G[2]=3;
    std::cout<<G<<std::endl;
    std::cout<<V*G<<std::endl;
    std::cout<<V+G+V<<std::endl;
    Vector H{V+V+V};
    std::cout<<H<<std::endl;

    return 0;
}
