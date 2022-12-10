#include <iostream>
#include <string>
#include <vector>
#include <fstream>

auto visible(const std::vector<std::string>& forest) -> int
{
    std::cout << "Processing.." << std::endl;
    int ret = (forest.size() + forest.at(0).size() -2) * 2;
    
    auto max_scenic = 0;
    
    // std::cout << "Starting loop for " << forest.size() << " " << forest.at(0).size() << std::endl;
    
    for(int i = 1; i < forest.size() - 1; i++)
    {
        for(int j = 1; j < forest[0].size() - 1; j++)
        {
            bool lvisible = true;
            bool rvisible = true;
            bool uvisible = true;
            bool dvisible = true;
            auto l = 0;
            auto r = 0;
            auto u = 0;
            auto d = 0;
            auto scenic = 0;
            
            for(int n = j-1; (n >= 0); n--)
            {
                l = j - n;
                if(forest[i][n] >= forest[i][j])
                {
                    lvisible = false;
                    break;
                }
            }

            // right check - freeze [i][]
            for(int n = j+1; (n < forest.at(0).size()) ; n++)
            {
                r = n - j;
                if(forest[i][n] >= forest[i][j])
                {
                    rvisible = false;
                    break;
                }
            }

            // up check - freeze [][j]
            for(int n = i-1; (n >= 0) ; n--)
            {
                u = i - n;
                if(forest[n][j] >= forest[i][j])
                {
                    uvisible = false;
                    break;
                }
            }

            // down check - freeze [][j]
            for(int n = i+1; (n < forest.size() ) ; n++)
            {
                // std::cout << forest[n][j] << " n " << forest[i][j] << std::endl;
                d = n - i;
                if(forest[n][j] >= forest[i][j])
                {
                    dvisible = false;
                    break;
                }
            }

            if(lvisible || rvisible || uvisible || dvisible) 
            {
                // std::cout << i << " incr " << j << std::endl;
                ret++;
            }

            scenic = l * r * u * d;
            
            // part 2
            if(max_scenic < scenic)
            {
                max_scenic = scenic;
            }
        }
    }
    
    return max_scenic;
}

int main()
{
    std::string input;
    std::vector<std::string> forest_test;
    std::vector<std::string> forest_act;
    std::ifstream test("day8_small.txt");
    std::ifstream actual("day8.txt");

    std::cout << "Got the data" << std::endl;
    
    if(test.is_open())
    {
        while(std::getline(test,input))
        {
            forest_test.push_back(input);
        }
    }
    auto ret = visible(forest_test);
    std::cout << "total visible trees are : " << ret << std::endl;

    if(actual.is_open())
    {
        while(std::getline(actual,input))
        {
            forest_act.push_back(input);
        }
    }
    ret = visible(forest_act);
    
    std::cout << "total actual visible trees are : " << ret << std::endl;
    return 0;
}