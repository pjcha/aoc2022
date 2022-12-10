#include <iostream>
#include <string>
#include <vector>
#include <fstream>

constexpr MAX_SIZE = 100000;

struct folder
{
    folder * left;
    folder * right;
    folder * up;
    int size;
};

int main()
{
    std::cout << "Please feed me string input" << std::endl;

    std::string input;
    std::ifstream file("data.txt");

    if(file.is_open())
    {
        std::getline(file,input);
    }

    
    return 0;
}