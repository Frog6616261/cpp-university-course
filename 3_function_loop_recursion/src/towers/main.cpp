#include <iostream>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <cmath>

using uint = unsigned int;
using way_stack = std::vector<std::pair<uint, uint>>;

struct Towers {

    uint m_count_towers;
    uint m_sz_tower;
    std::vector<std::stack<uint>> m_towers;

    Towers() = delete;
    Towers(const Towers&) = delete;

    Towers(uint count_towers, uint sz_tower)
        : m_count_towers(count_towers)
        , m_sz_tower(sz_tower)
        , m_towers(count_towers)
    {
        for (uint i = m_sz_tower; i > 0; --i) {
            m_towers[0].push(i);
        }
    }
};

void hanoi(uint n, uint from, uint to, uint temp, way_stack& way) {
    if (n == 0) {
        return;
    }

    hanoi(n - 1, from, temp, to, way);

    way.emplace_back(from, to);

    hanoi(n - 1, temp, to, from, way);
}

void search_hanonian(Towers& T, way_stack& optimal_way)
{
    if (T.m_count_towers != 3) {
        std::cout << "This optimized version supports only 3 towers\n";
        return;
    }

    hanoi(T.m_sz_tower, 0, 2, 1, optimal_way);
}


uint MAX_ITER;
way_stack optimal_way;
way_stack cur_way;

void search_hanonian_bruforce(Towers& T, way_stack& optimal_way, way_stack& cur_way)
{
    if (cur_way.size() >= MAX_ITER) {
        return;
    }

    if (T.m_towers.back().size() == T.m_sz_tower) {
        if (optimal_way.empty() && cur_way.size() > 0) {
            optimal_way = cur_way;
            MAX_ITER = static_cast<uint>(optimal_way.size());
        }

        if (cur_way.size() < optimal_way.size()) {
            optimal_way = cur_way;
            MAX_ITER = static_cast<uint>(optimal_way.size());
        }

        return;
    }

    for (uint num_tower_start = 0; num_tower_start < T.m_count_towers; ++num_tower_start) {
        for (uint num_tower_end = 0; num_tower_end < T.m_count_towers; ++num_tower_end) {

            if (num_tower_start == num_tower_end) {
                continue;
            }

            if (T.m_towers[num_tower_start].empty()) {
                continue;
            }

            if (!cur_way.empty() && cur_way.back().first != num_tower_end  
            && cur_way.back().second != num_tower_start){
                continue;
            }

            if (!T.m_towers[num_tower_start].empty() 
                && (T.m_towers[num_tower_end].empty() 
                || T.m_towers[num_tower_start].top() < T.m_towers[num_tower_end].top())
            ) {
                    uint disk = T.m_towers[num_tower_start].top();
                    T.m_towers[num_tower_start].pop();
                    T.m_towers[num_tower_end].push(disk);
                    cur_way.emplace_back(num_tower_start, num_tower_end);

                    search_hanonian_bruforce(T, optimal_way, cur_way);

                    cur_way.pop_back();
                    T.m_towers[num_tower_end].pop();
                    T.m_towers[num_tower_start].push(disk);
            }
        }
    }
}


int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: towers <number of plates> <number of towers>" << std::endl;
        return 1;
    }

    uint numb_of_plates = static_cast<uint>(std::stoi(argv[1]));
    uint numb_of_towers = static_cast<uint>(std::stoi(argv[2]));

    MAX_ITER = std::pow(2, numb_of_plates) + numb_of_plates;

    // if (numb_of_plates == 0 || numb_of_towers != 3) {
    //     std::cout << "Invalid input. Use positive plates count and exactly 3 towers." << std::endl;
    //     return 1;
    // }

    Towers T(numb_of_towers, numb_of_plates);

    way_stack optimal_way;

    if (numb_of_towers == 3){
        search_hanonian_bruforce(T, optimal_way, cur_way); // search_hanonian(T, optimal_way);
    }
    else {
        search_hanonian_bruforce(T, optimal_way, cur_way);
    }
    
    for (const auto& move : optimal_way) {
        std::cout << move.first << " -> " << move.second << std::endl;
    }

    return 0;
}