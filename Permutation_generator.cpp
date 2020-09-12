#include<iostream>
#include<vector>
#include <algorithm>

// FUNCTION TO CALCULATE FACTORIAL

int factorial(const int& x){
    int fact{1};
    if(x==1||x==0){
        fact=1;
    } else {
        fact=x*factorial(x-1);
    }
    return fact;
}

// FUNCTION TO OVERRIDE << OPERATOR FOR VECTORS

std::ostream& operator<<(std::ostream& os ,const std::vector<std::vector<float>> perm){
    for(size_t i{};i<perm.size();i++){
        for(size_t j{};j<perm.at(i).size();j++){
            os<<perm.at(i).at(j);
        }
        os<<std::endl; 
    }
    return os;
}

/* FUNCTION TO OBTAIN THE PERMUTATIONS. THE PERMUATIONS ARE OBTAINED WITH THE FOLLOWING METHOD: 
FOR A VECTOR OF n DIFFERENT ELEMENTS
1. WE KNOW THE NUMBER OF PERMUATIONS CONTAINING THE FIRST ELEMENT IN THE FIRST POSITIONS IS (n-1)!.
2. EACH OF THIS PERMUTATIONS CONTAIN THE SECOND ELEMENT IN THE SECOND POSITION (n-2)! NUMBER OF TIMES.
3. THE PROCESS IS REPEATED UNTIL ALL PERMUTATIONS ARE FILLED.
*/

std::vector<std::vector<float>> permutation(const std::vector<float>& vector, float& performance){
    size_t size=vector.size();
    float n_permutations=factorial(size);
    std::vector<std::vector<float>> permutations; //VECTORS WHERE ALL THE PERMUTATIONS ARE STORED
    
    //ELEMENT THAT IS NEVER IN THE VECTOR (DEFINED AS THE SUM). THIS IS USED TO COMPARE AGAINST ALL THE OTHER ELEMENTS.
    float element_never_in_vector{}; 
    for (size_t i = 0; i < vector.size(); i++){
        element_never_in_vector+=vector.at(i);
    }

    //FILLING THE VECTOR THAT WILL CONTAIN ALL THE PERMUATIONS
    std::vector<float> aux_vector;
    for (size_t i = 0; i < vector.size(); i++){
        aux_vector.push_back(element_never_in_vector);
    }
    for (size_t i = 0; i < n_permutations; i++){
        permutations.push_back(aux_vector);
    }

    // VARIABLE USED FOR KNOWING WHAT IS THE NUMBER OF TIMES THE x ELEMENT SHOULD BE PLACED ON THE nth POSITION.
    float period{size-1}; 
    // LOOPING OVER EACH POSITION IN THE PERMUTATION VECTOR
    for(size_t i{0};i<size;i++){
        int aux_counter{0};
        // LOOP OVER THE NUMBER OF PERMUTATIONS
        for (size_t k{0}; k < n_permutations; k++){
            size_t index=(aux_counter/factorial(period))%size; // FUNCTION TO GENERATE A PERIODIC INDEX WITH PERIOD (n-1)! 
            float value=vector.at(index); // VALUE THAT IS GOING TO BE STORED 
            int number_checks{0}; // VARIABLE USED TO PREVENT THAT AT THE FINAL CHECK THAT IS DONE IN THE NEXT STEPS GOES OUT WHEN ALL THE VECTO IS CHECKED
            /* THIS WHILE CHECKS THAT THE NUMBER THAT IS GOING TO BE STORED IS NOT ALREADY IN THE PERMUTATION
                1.WHEN THIS HAPPENS THE COUNTER THAT GENERATES THE PERIOD GOES INTO THE NEXT NUMBER
                2. VALUE IS SHIFTED AT THE NEXT ONE
            */
            while((std::find(permutations.at(k).begin(),permutations.at(k).end(),value)!=permutations.at(k).end()) && number_checks<size){
                performance++;
                aux_counter+=factorial(period);
                value=vector.at((index+1)%size);
                index++;
                number_checks++;
            }
            permutations.at(k).at(i)=value; //VALUE STORED IN THE PERMUTATIONS
            aux_counter++;
        }
        period+=-1;
        performance++;
    }
    //RETURN THE VECTOR FILLED WITH PERMUTATION VECTORS
    return permutations;
}

// MAIN PROGRAM TO ILLUSTRATE THE USAGE OF THE PERMUTATIONS FUCTION AND THE OUTPUT STREAM METHOD

int main(){
    float performance{0};
    std::cout<<factorial(4)<<std::endl;
    std::vector<float> sample{1,2,3,4,5,6,7,8,9,10};
    std::cout<<permutation(sample,performance)<<std::endl;
    std::vector<float> checks;
    /*for(size_t i{2};i<12;i++){
        sample.push_back(i);
        permutation(sample,performance);
        checks.push_back(performance);
        performance=0;
    }
    for(size_t i{0};i<checks.size();i++){
        std::cout<<checks.at(i)<<std::endl;
    }*/
    return 0;
}