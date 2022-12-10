#include <iostream>
#include <string>
#include <vector>
#include <fstream>

auto const identicalLen = 14;

auto notUnique(const std::vector<char>& obj, const int res) -> bool
{
    std::cout << ".";
    for(int i=0; i<identicalLen-1; i++)
    {
        for(int j=i+1; j<identicalLen; j++)
        {
            if(obj.at(i)==obj.at(j))
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::cout << "Please feed me string input" << std::endl;

    std::string input;
    std::ifstream file("data.txt");

    if(file.is_open())
    {
        std::getline(file,input);
    }

    // algo to find match
    int res = identicalLen;
    std::vector<char> obj(identicalLen);

    for(int i=0; i<obj.size(); i++)
    {
        obj.at(i) = input.at(i);
    }

    while(!notUnique(obj, res))
    {
        obj.at(res % identicalLen) = input.at(res-1);
        res++;
    }

    std::cout << "Result is " << res-1 << std::endl;
    return 0;
}