
#include<print>
#include "img.hpp"



int main(int, char**){
    
    Image img("test.jpg");
    img.scale(5);
  
    img.write("output.jpg");

}
