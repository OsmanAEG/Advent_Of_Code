//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<set>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////

// Position coordinates
struct Coords {
  int y;
  int x;

  void move_left()  { x -= 1; }
  void move_right() { x += 1; }
  void move_up()    { y -= 1; }
  void move_down()  { y += 1; }
};

// Solution
template<typename Coords_Type>
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)) {
      std::vector<int> row(line.size(), -1);
      for(int i = 0; i < line.size(); ++i) row[i] = line[i] - '0';
      grid.push_back(row);
    }

    M = grid[0].size();
    N = grid.size();
  }

  // Grid Navigation
  Coords_Type left(Coords_Type pos)  { return {pos.y, pos.x - 1}; }
  Coords_Type right(Coords_Type pos) { return {pos.y, pos.x + 1}; }
  Coords_Type up(Coords_Type pos)    { return {pos.y - 1, pos.x}; }
  Coords_Type down(Coords_Type pos)  { return {pos.y + 1, pos.x}; }

  auto idx(const Coords_Type& pos) {
    return pos.y*M + pos.x;
  }

  auto in_bounds(const Coords_Type& pos) {
    return (pos.y >= 0 && pos.y < N && pos.x >= 0 && pos.x < M);
  }

  auto valid_step(const Coords_Type& pos, int prev) {
    return in_bounds(pos) && (grid[pos.y][pos.x] - prev == 1);
  }

  void head_score(const Coords_Type& pos, std::set<int>& set_score, int& distinct_score) {
    auto curr_val = grid[pos.y][pos.x];

    if(grid[pos.y][pos.x] == 9) {
      set_score.insert(idx(pos));
      distinct_score += 1;
    } else {
      if(valid_step(left(pos),  curr_val)) head_score(left(pos),  set_score, distinct_score);
      if(valid_step(right(pos), curr_val)) head_score(right(pos), set_score, distinct_score);
      if(valid_step(up(pos),    curr_val)) head_score(up(pos),    set_score, distinct_score);
      if(valid_step(down(pos),  curr_val)) head_score(down(pos),  set_score, distinct_score);
    }
  }

  auto get_score(bool distinct) {
    int score = 0;

    for(int j = 0; j < N; ++j) {
      for(int i = 0; i < M; ++i) {
        std::set<int> set_score;
        int distinct_score = 0;
        if(grid[j][i] == 0) head_score({j, i}, set_score, distinct_score);
        if(distinct) score += distinct_score;
        else score += set_score.size();
      }
    }

    return score;
  }

  // Question 1
  auto q1() {
    return get_score(false);
  }

  // Question 2
  auto q2() {
    return get_score(true);
  }

private:
  std::vector<std::vector<int>> grid;
  int M;
  int N;
};

int main() {
  // auto solver = Solution<Coords>("example_input.txt");
  auto solver = Solution<Coords>("input.txt");

  const auto val1 = solver.q1();
  const auto val2 = solver.q2();

  std::cout << "Question 1: " << val1 << std::endl;
  std::cout << "Question 2: " << val2 << std::endl;

  return 0;
}