#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main()
{
    std::string input;
    std::ifstream file("data.txt");
    std::vector<int> max_cal = {0,0,0};
    
    int max_elf = 1;
    int curr_cal = 0;
    int curr_elf = 1;

    if(file.is_open())
    {
        while(std::getline(file,input))
        {
            if(!input.empty())
            {
                curr_cal += std::stoi(input);
            }
            else
            {
                curr_elf++;
                if(curr_cal > max_cal.at(0))
                {
                    max_cal.at(0) = curr_cal;
                    std::sort(max_cal.begin(), max_cal.end());
                    max_elf = curr_elf;
                }
                curr_cal = 0;
            }
        }
    }

    std::cout << "Elf " << max_elf << " had max cal " << max_cal.at(0)+max_cal.at(1)+max_cal.at(2) << std::endl;
    
    return 0;
}