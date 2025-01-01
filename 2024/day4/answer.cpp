//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    bool include = true;

    while(std::getline(file, line)) {
      letter.push_back(line);
    }
  }

  int q1() {
    int num_xmas = 0;

    const int min_x = 0;
    const int min_y = 0;
    const int max_x = letter[0].size() - 1;
    const int max_y = letter.size() - 1;

    for(int i = 0; i < letter.size(); ++i) {
      for(int j = 0; j < letter[i].size(); ++j) {
        std::string word_x  = "";
        std::string word_y  = "";
        std::string word_xy = "";
        std::string word_yx = "";

        // Horizontal XMAS
        if(i <= max_x - 3) for(int k = 0; k <= 3; ++k) word_x.push_back(letter[i + k][j]);

        // Vertical XMAS
        if(j <= max_y - 3) for(int k = 0; k <= 3; ++k) word_y.push_back(letter[i][j + k]);

        // Diagonal Left-Right XMAS
        if(i <= max_x - 3 && j <= max_y - 3) for(int k = 0; k <= 3; ++k) word_xy.push_back(letter[i + k][j + k]);

        // Diagonal Right-Left XMAS
        if(i >= min_x + 3 && j <= max_y + 3) for(int k = 0; k <= 3; ++k) word_yx.push_back(letter[i - k][j + k]);

        if(word_x  == "XMAS" || word_x  == "SAMX") ++num_xmas;
        if(word_y  == "XMAS" || word_y  == "SAMX") ++num_xmas;
        if(word_xy == "XMAS" || word_xy == "SAMX") ++num_xmas;
        if(word_yx == "XMAS" || word_yx == "SAMX") ++num_xmas;
      }
    }

    return num_xmas;
  }

  int q2() {
    int num_xmas = 0;

    const int min_x = 0;
    const int min_y = 0;
    const int max_x = letter[0].size() - 1;
    const int max_y = letter.size() - 1;

    for(int i = 0; i < letter.size(); ++i) {
      for(int j = 0; j < letter[i].size(); ++j) {
        bool valid_xy = false;
        bool valid_yx = false;
        std::string word_xy = "";
        std::string word_yx = "";

        // Diagonal Left-Right XMAS
        for(int k = -1; k <= 1; ++k) {
          bool in_bound_x = (i + k >= min_x && i + k <= max_x);
          bool in_bound_y = (j + k >= min_y && j + k <= max_y);
          if(in_bound_x && in_bound_y) word_xy.push_back(letter[i + k][j + k]);
        }

        // Diagonal Right-Left XMAS
        for(int k = -1; k <= 1; ++k) {
          bool in_bound_x = (i - k >= min_x && i - k <= max_x);
          bool in_bound_y = (j + k >= min_y && j + k <= max_y);
          if(in_bound_x && in_bound_y) word_yx.push_back(letter[i - k][j + k]);
        }

        if(word_xy == "MAS" || word_xy == "SAM") valid_xy = true;
        if(word_yx == "MAS" || word_yx == "SAM") valid_yx = true;

        if(valid_xy && valid_yx) ++num_xmas;
      }
    }

    return num_xmas;
  }

private:
  std::vector<std::string> letter;
};

int main() {
  auto solver = Solution("input.txt");

  const auto xmas  = solver.q1();
  const auto x_mas = solver.q2();

  std::cout << "XMAS: "  << xmas  << std::endl;
  std::cout << "X-MAS: " << x_mas << std::endl;

  return 0;
}