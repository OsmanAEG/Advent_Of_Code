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

  bool operator==(const Coords& a) const {
    return y == a.y && x == a.x;
  }

  bool operator!=(const Coords& a) const {
    return y != a.y || x != a.x;
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
      std::vector<char> row;

      for(const auto& c : line) row.push_back(c);
      grid.push_back(row);
    }

    for(int j = 0; j < grid.size(); ++j) {
      for(int i = 0; i < grid[j].size(); ++i) {
        if(grid[j][i] == '^') {
          pos_0 = {j, i};
          break;
        }
      }
    }
  }

  // Rotates character by 90deg
  template<typename Dir_T>
  void rotate(Dir_T& dir) {
    if(dir == '^') dir = '>';
    else if(dir == '>') dir = 'v';
    else if(dir == 'v') dir = '<';
    else dir = '^';
  }

  // Resets the marked grid
  template<typename Grid_T>
  void reset_grid(Grid_T& grid_in) {
    for(int j = 0; j < grid_in.size(); ++j) {
      for(int i = 0; i < grid_in[j].size(); ++i) {
        if(grid[j][i] != '#') grid[j][i] == '.';
      }
    }
  }

  // Gets the next grid position
  auto get_next_position(Coords_Type curr_pos, char dir) {
    auto next_pos = curr_pos;

    if(dir == '^')      next_pos.y -= 1;
    else if(dir == 'v') next_pos.y += 1;
    else if(dir == '>') next_pos.x += 1;
    else                next_pos.x -= 1;

    return next_pos;
  }

  // Advance grid position
  template<typename Grid_T>
  bool advance_position(Grid_T& grid_in, Coords_Type& curr_pos, Coords_Type& next_pos) {
    bool advanced = false;

    if(grid_in[next_pos.y][next_pos.x] == '#') {
      rotate(grid_in[curr_pos.y][curr_pos.x]);
    } else {
      if(grid_in[next_pos.y][next_pos.x] == '.') advanced = true;
      grid_in[next_pos.y][next_pos.x] = grid_in[curr_pos.y][curr_pos.x];
      grid_in[curr_pos.y][curr_pos.x] = 'X';
      curr_pos = next_pos;
    }

    return advanced;
  }

  // Function that initiates map navigation
  template<typename Grid_T>
  auto navigate_map(Grid_T grid_in) {
    bool guard_gone = false;

    int min_x = 0;
    int min_y = 0;
    int max_x = grid[0].size() - 1;
    int max_y = grid.size() - 1;

    Coords_Type curr_pos = pos_0;

    std::vector<std::vector<std::set<char>>> track_steps;
    track_steps.resize(grid_in.size(), std::vector<std::set<char>>(grid_in[0].size()));

    grid_in[curr_pos.y][curr_pos.x] = '^';

    while(!guard_gone) {
      track_steps[curr_pos.y][curr_pos.x].insert(grid_in[curr_pos.y][curr_pos.x]);

      auto next_pos = get_next_position(curr_pos, grid_in[curr_pos.y][curr_pos.x]);

      // Check if position is out of bounds
      if(next_pos.x < min_x || next_pos.x > max_x) guard_gone = true;
      if(next_pos.y < min_y || next_pos.y > max_y) guard_gone = true;

      if(guard_gone == true){
        grid_in[curr_pos.y][curr_pos.x] = 'X';
        break;
      }

      // Advance steps
      if(advance_position(grid_in, curr_pos, next_pos)) ++unique_pos;

      if(track_steps[curr_pos.y][curr_pos.x].find(grid_in[curr_pos.y][curr_pos.x]) != track_steps[curr_pos.y][curr_pos.x].end()) {
        return true;
      }
    }

    return false;
  }

  // Function that finds all obstacle placements
  template<typename Grid_T>
  void find_obstacle_positions(Grid_T grid_in) {
    bool guard_gone = false;

    int min_x = 0;
    int min_y = 0;
    int max_x = grid[0].size() - 1;
    int max_y = grid.size() - 1;

    Coords_Type curr_pos = pos_0;

    while(!guard_gone) {
      auto tmp_grid = grid_in;
      auto next_pos = get_next_position(curr_pos, grid_in[curr_pos.y][curr_pos.x]);

      // Check if position is out of bounds
      if(next_pos.x < min_x || next_pos.x > max_x) guard_gone = true;
      if(next_pos.y < min_y || next_pos.y > max_y) guard_gone = true;

      if(guard_gone == true){
        grid_in[curr_pos.y][curr_pos.x] = 'X';
        break;
      }

      // Advance steps
      if(advance_position(grid_in, curr_pos, next_pos)) {
        tmp_grid[next_pos.y][next_pos.x] = '#';
        reset_grid(tmp_grid);
        if(navigate_map(tmp_grid)) ++bumper;
      };
    }
  }

  // Question 1
  int q1() {
    auto dummy = navigate_map(grid);
    return unique_pos;
  }

  // Question 2
  int q2() {
    find_obstacle_positions(grid);
    return bumper;
  }

private:
  std::vector<std::vector<char>> grid;
  Coords_Type pos_0;
  int unique_pos = 1;
  int bumper = 0;
};

int main() {
  // auto solver = Solution<Coords>("example_input.txt");
  auto solver = Solution<Coords>("input.txt");

  const auto unique_pos = solver.q1();
  const auto bumpers = solver.q2();

  std::cout << "Unique Guard Positions: " << unique_pos << std::endl;
  std::cout << "Unique Bumpers: "         << bumpers    << std::endl;

  return 0;
}
