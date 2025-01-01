//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    bool adding_rules = true;

    while(std::getline(file, line)) {
      if(line.size() == 0) {
        adding_rules = false;
      } else if(adding_rules) {
        std::string num1_str = "";
        std::string num2_str = "";

        num1_str.push_back(line[0]);
        num1_str.push_back(line[1]);

        num2_str.push_back(line[3]);
        num2_str.push_back(line[4]);

        const int num1 = std::stoi(num1_str);
        const int num2 = std::stoi(num2_str);

        rules[num1].push_back(num2);
      } else {
        std::string num = "";
        std::vector<int> list = {};
        for(const auto& c : line) {
          if(c == ',') {
            list.push_back(std::stoi(num));
            num = "";
          } else {
            num.push_back(c);
          }
        }

        list.push_back(std::stoi(num));
        orders.push_back(list);
      }
    }
  }

  // Check if the order list is valid
  bool check_valid(std::vector<int>& order) {
    bool valid = true;
    std::unordered_set<int> nums;

    for(const auto& entry : order) {
      for(const auto& num : rules[entry]) {
        if(nums.find(num) != nums.end()) valid = false;
      }

      nums.insert(entry);
    }

    return valid;
  }

  // Make the order list is valid
  void make_valid(std::vector<int>& order) {
    auto func = [&](int a, int b) {
      const auto rules_a = rules[a];

      for(const auto& num : rules_a) {
        if(b == num) return true;
      }

      return false;
    };

    std::sort(order.begin(), order.end(), func);
  }

  // Question 1
  int q1() {
    int middle_total = 0;

    for(auto& order : orders) {
      const auto valid = check_valid(order);
      if(valid) middle_total += order[order.size()/2];
      else inc_orders.push_back(order);
    }

    return middle_total;
  }

  // Question 2
  int q2() {
    int middle_total = 0;

    for(auto& order : inc_orders) {
      make_valid(order);
      middle_total += order[order.size()/2];
    }

    return middle_total;
  }

private:
  std::unordered_map<int, std::vector<int>> rules;
  std::vector<std::vector<int>> orders;
  std::vector<std::vector<int>> inc_orders;
};

int main() {
  auto solver = Solution("input.txt");

  const auto mid_sum    = solver.q1();
  const auto mid_sum_re = solver.q2();

  std::cout << "Middle sum: "           << mid_sum    << std::endl;
  std::cout << "Middle sum reordered: " << mid_sum_re << std::endl;

  return 0;
}