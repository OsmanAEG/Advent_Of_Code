//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<regex>
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

    std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don\'t\(\))");
    std::smatch match;

    bool include = true;

    while(std::getline(file, line)) {
      std::string::const_iterator str_itr(line.cbegin());

      while(std::regex_search(str_itr, line.cend(), match, pattern)) {
        if(match[0].str() == "do()") {
          include = true;
        } else if(match[0].str() == "don't()") {
          include = false;
        } else {
          int val1 = std::stoi(match[1].str());
          int val2 = std::stoi(match[2].str());

          mul_pairs.push_back({val1, val2});
          include_mul.push_back(include);
        }

        str_itr = match.suffix().first;
      }
    }
  }

  int q1() {
    int mul_sum = 0;

    for(const auto& pair : mul_pairs) {
      mul_sum += pair.first*pair.second;
    }

    return mul_sum;
  }

  int q2() {
    int mul_sum = 0;

    for(int i = 0; i < mul_pairs.size(); ++i) {
      if(include_mul[i] == true) mul_sum += mul_pairs[i].first*mul_pairs[i].second;
    }

    return mul_sum;
  }

private:
  std::vector<std::pair<int, int>> mul_pairs;
  std::vector<bool> include_mul;
};

int main() {
  auto solver = Solution("input.txt");

  const auto mul_sum     = solver.q1();
  const auto acc_mul_sum = solver.q2();

  std::cout << "Multiplied sum: "          << mul_sum     << std::endl;
  std::cout << "Accurate Multiplied sum: " << acc_mul_sum << std::endl;

  return 0;
}