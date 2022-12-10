#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

auto calcTpos(const std::pair<int, int>& h, std::pair<int, int>& t) -> std::pair<int, int>
{
    const int hx = std::get<0>(h);
    const int hy = std::get<1>(h);
    const int tx = std::get<0>(t);
    const int ty = std::get<1>(t);

    if(h == t)
    {
        // std::cout << "same loc - no movement" << std::endl;
        return t;
    }

    if( 
        ((hx == tx) && (std::abs(hy - ty)) < 2) || 
        ((hy == ty) && (std::abs(hx - tx)) < 2) 
        )
    {
        // std::cout << "same row or column within 1 block - no movement" << std::endl;
        return t;
    }

    if( 
        (std::abs(hy - ty) == 1) && (std::abs(hx - tx) == 1)
        )
    {
        // std::cout << "diag touching - no movement" << std::endl;
        return t;
    }

    if(
        ((hx == tx) && (std::abs(hy - ty)) == 2) || 
        ((hy == ty) && (std::abs(hx - tx)) == 2)
    )
    {
        // std::cout << "same row/column and diff is 2 - move 1 row/column" << std::endl;
        int xdir = hx - tx;
        int ydir = hy - ty;
        auto ret = std::pair<int, int>( tx + static_cast<int>(((xdir > 0) - (xdir < 0))), 
                                        ty + static_cast<int>(((ydir > 0) - (ydir < 0))) );
        return ret;
    }

    // diff row and column, and not diag -> move diag towards
    if(
        ((std::abs(hx - tx) == 1) && (std::abs(hy - ty) == 2)) ||
        ((std::abs(hx - tx) == 2) && (std::abs(hy - ty) == 1))
        )
    {
        int xdir, ydir = 0;
        xdir = static_cast<int>(((hx - tx) > 0) - ((hx - tx) < 0));
        ydir = static_cast<int>(((hy - ty) > 0) - ((hy - ty) < 0));

        auto ret = std::pair<int, int>( tx + xdir, ty + ydir);
        return ret;
    }

    std::cout << "no condition detected" << std::endl;
    return t;
}

auto print_tpos(const std::set<std::pair<int, int>>& t) -> void
{
    for(const auto& i: t)
    {
        std::cout << "tx " << std::get<0>(i) << " ,ty " << std::get<0>(i) << std::endl;
    }
}

auto process(const std::vector<std::pair<int, int>>& instr) -> int
{
    std::set<std::pair<int,int>> Tpos{std::pair<int,int>(0,0)};
    std::pair<int, int> h = std::pair<int,int>(0,0);
    std::pair<int, int> t = std::pair<int,int>(0,0);

    // make H moves
    for(auto const& move: instr)
    {
        auto x = std::get<0>(move);
        auto y = std::get<1>(move);

        for(int i=0; i < std::abs(x+y); i++)
        {
            if(x==0)
            {
                h = std::pair<int, int>(std::get<0>(h) + static_cast<int>((y > 0) - (y < 0)), std::get<1>(h));
            }
            else
            {
                h = std::pair<int, int>(std::get<0>(h), std::get<1>(h) + static_cast<int>((x > 0) - (x < 0)));
            }

            t = calcTpos(h, t);
            std::cout << "h " << std::get<0>(h) << " " << std::get<1>(h) << ", t " << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
            Tpos.insert(t);
        }
    }
    // print_tpos(Tpos);
    return Tpos.size();
}

auto getMoves(const std::string& input) -> std::pair<int,int>
{
    int x, y = 0;
    auto dist = input.substr(2,input.size()-1);

    // checks can be added for sanity of data
    // R
    if(input.starts_with("R"))
    {   
        x = std::stoi(dist);
        y = 0;
    }
    else if(input.starts_with("U"))
    {
        x = 0;
        y = std::stoi(dist);
    }
    else if(input.starts_with("L"))
    {
        x = -1 * std::stoi(dist);
        y = 0;
    }
    else if(input.starts_with("D"))
    {
        x = 0;
        y = -1 * std::stoi(dist);
    }
    else
    {
        std::cout << "invalid" << std::endl; 
    }

    std::cout << "x " << x << " ,y " << y << std::endl;
    return std::pair<int, int> (x, y);
}


int main()
{
    std::ifstream test("day9_small.txt");
    std::ifstream actual("day9.txt");
    std::vector<std::pair<int, int>> instr_data;
    std::string input;

    if(test.is_open())
    {
        while(std::getline(actual,input))
        {
            instr_data.push_back(getMoves(input));
        }
    }

    std::cout << "Got the data, now processing.. " << instr_data.size() << std::endl;

    auto ret = process(instr_data);
    
    std::cout << "total pos of T are : " << ret << std::endl;
    return 0;
}