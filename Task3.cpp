
// Simple code to store courses using vectors and strings

#include<iostream>
#include<string>
#include<sstream>
#include<vector>

bool good_input(std::string& raw_input, int& code, std::string& course, bool& assign){
    int space_counter{};
    std::string temp;
    std::vector<std::string> words;
    assign=false;

    for (int i{}; i < raw_input.size(); i++){
        if (raw_input[i]!=' '){
            temp.push_back(raw_input[i]);
        }
        if (raw_input[i]==' ' || i==(raw_input.size()-1)){
            words.push_back(temp);
            temp.clear();
        }
    }
    if(words.size()==2){
        try{
            code=stoi(words[0]);
            try{
                stoi(words[1]);
                std::cout<<"Both inputs are numbers, try again: "<<std::endl;
                return true;
            }
            catch(std::invalid_argument& e)
            {
                course=words[1];
                assign=true;
                return true;
                
            }
            
        } catch(std::invalid_argument& e){
            try{
               code=stoi(words[1]);
                std::cout<<"WARNING: Your input is in the reversed way... storing your first word as the course name."<<std::endl;
                course=words[0];
                assign=true;
                return true;     
            }
            catch(const std::exception& e)
            {
                std::cout<<"Both inputs are strings, try again: "<<std::endl;
                return true;
            }
        }
        
    }else{
        if (words.size()==1 && words[0]=="x")
        {
            return false;    
        }
        else
        {
        std::cout<<"Input with more than two words or a single one that is not the exit flag (x), try again: "<<std::endl;
        return true;
        }
    }
}

int main()
{
  const std::string degreeCode("PHYS");
  std::string course_name;
  int course_code{};
  std::vector<std::string> full_title;
  std::ostringstream course_title;
  std::string raw_input;
  bool assigned{false};

  std::cout<<"Ingrese el nombre del curso:"<<std::endl;
  getline(std::cin,raw_input);

  while(good_input(raw_input,course_code, course_name,assigned))
  {
    if(assigned)
    {
    course_title<<degreeCode<<" "<<course_code<<" "<<course_name;
    full_title.push_back(course_title.str());
    course_title.str("");
    std::cout<<"Ingrese otro curso:"<<std::endl;
    }
    getline(std::cin,raw_input);
  }
  std::vector<std::string>::iterator vector_begin{full_title.begin()};
  std::vector<std::string>::iterator vector_end{full_title.end()};
  std::vector<std::string>::iterator vector_iterator;
  for (vector_iterator=vector_begin; vector_iterator<vector_end; ++vector_iterator)
  {
    std::cout<<*vector_iterator<<std::endl;
  }
  
  return 0;
}
