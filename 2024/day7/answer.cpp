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
      std::vector<long long> op;

      const auto idx_colon = line.find(":");
      auto sum = std::stoll(line.substr(0, idx_colon));
      op.push_back(sum);

      std::stringstream stream(line.substr(idx_colon + 1));

      long long num;

      while(stream >> num) op.push_back(num);
      ops.push_back(op);
    }
  }

  void check_ops() {
    for(const auto& row : ops) {
      std::cout << row[0] << ": ";
      for(int i = 1; i < row.size(); ++i) {
        std::cout << row[i] << ", ";
      }
      std::cout << std::endl;
    }
  }

  template<typename Size_T>
  auto concatenate(Size_T num1, Size_T num2) {
    const auto num_str = std::to_string(num1) + std::to_string(num2);
    return std::stoll(num_str);
  }

  template<typename Vector_T, typename Scalar_T>
  bool is_valid(Vector_T& nums, Scalar_T sum, int idx) {
    if(sum == nums[0] && idx == nums.size()) return true;
    if(idx >= nums.size()) return false;

    return is_valid(nums, sum + nums[idx], idx + 1) || is_valid(nums, sum * nums[idx], idx + 1);
  }

  template<typename Vector_T, typename Scalar_T>
  bool is_valid_plus(Vector_T& nums, Scalar_T sum, int idx) {
    if(sum == nums[0] && idx == nums.size()) return true;
    if(idx >= nums.size()) return false;

    return is_valid_plus(nums, sum + nums[idx], idx + 1) ||
           is_valid_plus(nums, sum * nums[idx], idx + 1) ||
           is_valid_plus(nums, concatenate(sum, nums[idx]), idx + 1);
  }

  // Question 1
  auto q1() {
    long long sum = 0;

    for(const auto& op : ops) {
      if(is_valid(op, op[1], 2)) sum += op[0];
    }

    return sum;
  }

  // Question 2
  auto q2() {
    long long sum = 0;

    for(const auto& op : ops) {
      if(is_valid_plus(op, op[1], 2)) sum += op[0];
    }

    return sum;
  }

private:
  std::vector<std::vector<long long>> ops;
};

int main() {
  auto solver = Solution("input.txt");
  // auto solver = Solution("example_input.txt");
  // solver.check_ops();

  const auto val1 = solver.q1();
  const auto val2 = solver.q2();

  std::cout << "Question 1: " << val1 << std::endl;
  std::cout << "Question 2: " << val2 << std::endl;

  return 0;
}