//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<unordered_map>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////

// Position coordinates
struct Coords {
  int y;
  int x;

  bool operator==(const Coords& a) const {
    return y == a.y && x == a.x;
  }

  bool operator!=(const Coords& a) const {
    return y != a.y || x != a.x;
  }

  Coords operator-(const Coords& a) const {
    return {y-a.y, x-a.x};
  }

  Coords operator+(const Coords& a) const {
    return {y+a.y, x+a.x};
  }
};

// Solution
template<typename Coords_Type>
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)) {
      std::vector<char> row(line.size(), '.');
      antinodes.push_back(row);

      for(int i = 0; i < line.size(); ++i) row[i] = line[i];
      grid.push_back(row);
    }

    for(int j = 0; j < grid.size(); ++j) {
      for(int i = 0; i < grid[0].size(); ++i) {
        if(grid[j][i] != '.') frequencies[grid[j][i]].push_back({j, i});
      }
    }
  }

  // Greatest common denominator
  template<typename Size_T>
  auto gcd(Size_T a, Size_T b) {
    Size_T tmp;

    while(b != 0) {
      tmp = b;
      b = a % b;
      a = tmp;
    }

    return a;
  }

  // Place the antinodes
  void get_antinodes(bool extra = false) {
    const int min_x = 0;
    const int max_x = grid[0].size() - 1;
    const int min_y = 0;
    const int max_y = grid.size() - 1;

    for(const auto& it : frequencies) {
      for(int i = 0; i < it.second.size(); ++i) {
        for(int j = i + 1; j < it.second.size(); ++j) {
          const auto pt1 = it.second[i];
          const auto pt2 = it.second[j];

          const auto dist = pt1 - pt2;

          const auto a1 = pt1 + dist;
          const auto a2 = pt2 - dist;

          if(a1.y >= min_y && a1.y <= max_y && a1.x >= min_x && a1.x <= max_x) {
            antinodes[a1.y][a1.x] = '#';
          }

          if(a2.y >= min_y && a2.y <= max_y && a2.x >= min_x && a2.x <= max_x) {
            antinodes[a2.y][a2.x] = '#';
          }

          if(extra) {
            Coords_Type nav1 = pt1;
            Coords_Type nav2 = pt1;

            const auto factor = gcd(std::abs(dist.y), std::abs(dist.x));

            const Coords_Type reduced_dist = {dist.y / factor, dist.x / factor};

            while(nav1.y >= min_y && nav1.y <= max_y && nav1.x >= min_x && nav1.x <= max_x) {
              antinodes[nav1.y][nav1.x] = '#';
              nav1 = nav1 + reduced_dist;
            }

            while(nav2.y >= min_y && nav2.y <= max_y && nav2.x >= min_x && nav2.x <= max_x) {
              antinodes[nav2.y][nav2.x] = '#';
              nav2 = nav2 - reduced_dist;
            }
          }
        }
      }
    }
  }

  // Question 1
  int q1() {
    int num_antinodes = 0;
    get_antinodes();

    for(int j = 0; j < antinodes.size(); ++j) {
      for(int i = 0; i < antinodes[j].size(); ++i) {
        if(antinodes[j][i] == '#') ++num_antinodes;
      }
    }

    return num_antinodes;
  }

  // Question 2
  int q2() {
    int num_antinodes = 0;
    get_antinodes(true);

    for(int j = 0; j < antinodes.size(); ++j) {
      for(int i = 0; i < antinodes[j].size(); ++i) {
        if(antinodes[j][i] == '#') ++num_antinodes;
      }
    }

    return num_antinodes;
  }

private:
  std::vector<std::vector<char>> grid;
  std::vector<std::vector<char>> antinodes;
  std::unordered_map<char, std::vector<Coords_Type>> frequencies;
};

int main() {
  // auto solver = Solution<Coords>("example_input.txt");
  auto solver = Solution<Coords>("input.txt");

  const auto num_antinodes = solver.q1();
  const auto val2 = solver.q2();

  std::cout << "Number of Antinodes: " << num_antinodes << std::endl;
  std::cout << "Question 2: " << val2 << std::endl;

  return 0;
}
