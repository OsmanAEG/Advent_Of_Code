//////////////////////////////////////
// STD LIBRARIES
//////////////////////////////////////
#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

//////////////////////////////////////
// SOLUTION
//////////////////////////////////////

// Memory
template<typename Val_T>
struct Memory {
  int low;
  int high;
  int size;
  Val_T val;

  Memory(Val_T val_in, int low_in, int high_in) :
    val(val_in),
    low(low_in),
    high(high_in) {
    size = high - low + 1;
  }

  bool available(Memory& mem_in) {
    if(size >= mem_in.size) return true;
    return false;
  }

  template<typename Vector_T>
  void shift(Vector_T& vec, Memory& mem_in) {
    const auto r = mem_in.size;

    for(int i = low; i < low + r; ++i) vec[i] = mem_in.val;
    for(int i = mem_in.low; i <= mem_in.high; ++i) vec[i] = ".";

    low += r;
    size -= r;
  }
};

// Solution
template<typename Size_T, typename Mem_T>
class Solution {
public:
  Solution(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    for(int i = 0; i < line.size(); ++i) {
      nums.push_back(line[i] - '0');
    }

    Size_T id = 0;
    for(int i = 0; i < nums.size(); ++i) {
      if(i%2 == 0) {
        for(int j = 0; j < nums[i]; ++j) files.push_back(std::to_string(id));
        ++id;
      } else {
        for(int j = 0; j < nums[i]; ++j) files.push_back(".");
      }
    }
  }

  template<typename File_T>
  auto checksum(File_T& my_files) {
    Size_T sum = 0;
    Size_T id = 0;

    while(id < my_files.size()) {
      if(my_files[id] != ".") {
        const auto num = std::stoull(my_files[id]);
        sum += num*id;
      }

      ++id;
    }

    std::cout << sum << std::endl;

    return sum;
  }

  template<typename Data_Vec_T, typename Mem_Vec_T>
  void output(Data_Vec_T vec, Mem_Vec_T& mem) {
    for(int i = 0; i < vec.size(); ++i) std::cout << vec[i];
    std::cout << std::endl;

    for(int i = 0; i < mem.size(); ++i) {
      const auto l = mem[i].low;
      const auto h = mem[i].high;
      const auto v = mem[i].val;
      const auto s = mem[i].size;
      std::cout << "[" << l << ", " << h << "] = " << v << " | " << s << std::endl;
    }

    std::cout << "==============================" << std::endl;
  }

  // Question 1
  auto q1() {
    auto my_files = files;

    int low = 0;
    int high = files.size() - 1;

    while(low < high) {
      if(my_files[low] != ".") ++low;
      else if(my_files[high] == ".") --high;
      else {
        my_files[low] = my_files[high];
        my_files[high] = ".";
      }
    }

    return checksum(my_files);
  }

  // Question 2
  auto q2() {
    auto my_files = files;

    std::vector<Mem_T> free_mems;
    std::vector<Mem_T> data_mems;

    int low = 0;
    int high = 0;

    while(high < my_files.size()) {
      while(high + 1 < my_files.size() && my_files[high + 1] == my_files[low]) ++high;

      if(my_files[low] == ".") free_mems.emplace_back(".", low, high);
      else data_mems.emplace_back(my_files[low], low, high);

      ++high;
      low = high;
    }

    // output(my_files, free_mems);

    for(int i = data_mems.size() - 1; i >= 0; --i) {
      int j = 0;

      while(j < free_mems.size() && free_mems[j].high < data_mems[i].low) {
        if(free_mems[j].available(data_mems[i])) {
          free_mems[j].shift(my_files, data_mems[i]);
          break;
        }

        ++j;
      }
    }

    // output(my_files, free_mems);

    return checksum(my_files);
  }

private:
  std::vector<int> nums;
  std::vector<std::string> files;
};

int main() {
  // auto solver = Solution<std::uint64_t, Memory<std::string>>("example_input.txt");
  auto solver = Solution<std::uint64_t, Memory<std::string>>("input.txt");

  const auto val1 = solver.q1();
  const auto val2 = solver.q2();

  std::cout << "Question 1: " << val1 << std::endl;
  std::cout << "Question 2: " << val2 << std::endl;

  return 0;
}