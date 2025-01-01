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

    while(std::getline(file, line)) {
      std::istringstream iss(line);
      std::vector<int> series;

      int n;

      while(iss >> n) series.push_back(n);

      reports.push_back(series);
    }
  }

  bool check_valid(std::vector<int> series, bool increasing) {
    bool valid = true;
    int low = 0;
    int high = 1;

    for(int i = 1; i < series.size(); ++i) {
      int diff = 0;

      if(increasing) diff = series[i] - series[i-1];
      else diff = series[i-1] - series[i];

      if(diff < 1 || diff > 3) valid = false;
    }

    return valid;
  }

  int q1() {
    int num_valid = 0;

    for(const auto& series : reports) {
      const auto increasing = check_valid(series, true);
      const auto decreasing = check_valid(series, false);

      if(increasing == true || decreasing == true) num_valid += 1;
    }

    return num_valid;
  }

  int q2() {
    int num_valid = 0;

    for(const auto& series : reports) {
      bool found_valid = false;
      for(int i = 0; i < series.size(); ++i) {
        auto rm_series = series;
        rm_series.erase(rm_series.begin() + i);
        const auto increasing = check_valid(rm_series, true);
        const auto decreasing = check_valid(rm_series, false);

        if(increasing == true || decreasing == true) {
          found_valid = true;
          break;
        }
      }

      if(found_valid == true) num_valid += 1;
    }

    return num_valid;
  }

private:
  std::vector<std::vector<int>> reports;
};

int main() {
  auto solver = Solution("input.txt");

  const auto num       = solver.q1();
  const auto num_fixed = solver.q2();

  std::cout << "Valid reports: "       << num       << std::endl;
  std::cout << "Valid fixed reports: " << num_fixed << std::endl;

  return 0;
}