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
    std::ifstream codes(filename);

    while(std::getline(codes, code)) {
      std::istringstream code_stream(code);

      code_stream >> first_code >> second_code;

      first_codes.push_back(std::stoi(first_code));
      second_codes.push_back(std::stoi(second_code));
    }

    std::sort(first_codes.begin(), first_codes.end());
    std::sort(second_codes.begin(), second_codes.end());
  }

  int q1() {
    int sum = 0;

    for(int i = 0; i < first_codes.size(); ++i) {
      sum += std::abs(first_codes[i] - second_codes[i]);
    }

    return sum;
  }

  int q2() {
    int score = 0;

    for(int i = 0; i < second_codes.size(); ++i) {
      times_second[second_codes[i]] += 1;
    }

    for(int i = 0; i < first_codes.size(); ++i) {
      score += first_codes[i]*times_second[first_codes[i]];
    }

    return score;
  }

private:
  std::vector<int> first_codes;
  std::vector<int> second_codes;

  std::unordered_map<int, int> times_second;

  std::string code;
  std::string first_code;
  std::string second_code;
};

int main() {
  auto solver = Solution("input.txt");

  const auto sum = solver.q1();
  const auto score = solver.q2();

  std::cout << "The total distance apart is: " << sum << std::endl;
  std::cout << "The similarity score is: " << score << std::endl;

  return 0;
}