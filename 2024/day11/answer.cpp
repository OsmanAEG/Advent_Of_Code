//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////
template<typename Size_T>
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::string num;

    std::getline(file, line);
    std::stringstream ss(line);

    while(ss >> num) nums.push_back(std::stoi(num));
  }

  Size_T blink(Size_T num, int num_blinks) {
    if(num_blinks == 0) return 1;

    if(blink_dict[num].find(num_blinks) != blink_dict[num].end()) {
      return blink_dict[num][num_blinks];
    }

    const std::string str_num = std::to_string(num);

    if(num == 0) {
      blink_dict[1][num_blinks - 1] = blink(1, num_blinks - 1);
      return blink_dict[1][num_blinks - 1];
    } else if(str_num.size() % 2 == 0) {
      std::string str1 = {str_num.begin(), str_num.end() - str_num.size()/2};
      std::string str2 = {str_num.begin() + str_num.size()/2, str_num.end()};

      const auto num1 = std::stoull(str1);
      const auto num2 = std::stoull(str2);

      blink_dict[num1][num_blinks - 1] = blink(num1, num_blinks - 1);
      blink_dict[num2][num_blinks - 1] = blink(num2, num_blinks - 1);
      return blink_dict[num1][num_blinks - 1] + blink_dict[num2][num_blinks - 1];
    } else {
      blink_dict[2024*num][num_blinks - 1] = blink(2024*num, num_blinks - 1);
      return blink_dict[2024*num][num_blinks - 1];
    }
  }

  // Question 1
  auto q1() {
    Size_T sum = 0;

    for(const auto& num : nums) {
      sum += blink(num, 25);
    }

    return sum;
  }

  // Question 2
  auto q2() {
    Size_T sum = 0;

    for(const auto& num : nums) {
      sum += blink(num, 75);
    }

    return sum;
  }

private:
  std::vector<Size_T> nums;
  std::unordered_map<Size_T, std::unordered_map<int, Size_T>> blink_dict;
};

int main() {
  // auto solver = Solution<std::uint64_t>("example_input.txt");
  auto solver = Solution<std::uint64_t>("input.txt");

  const auto val1 = solver.q1();
  const auto val2 = solver.q2();

  std::cout << "Question 1: " << val1 << std::endl;
  std::cout << "Question 2: " << val2 << std::endl;

  return 0;
}