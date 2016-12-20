#include <chrono>
#include <iostream>
#include <string>
#include <vector>

std::vector<int>
string_to_int_vector(const std::string& s) {
  std::cout << "++++++++++++++++++++++++++++++" << std::endl
      << __func__ << std::endl
      << "s='" << s << "'" << std::endl
      << "s.size()='" << s.size() << "'" << std::endl;
  std::vector<int> result;
  for (const auto& c: s) {
    if (c > '9' or c < '0')
      throw 666;
    result.push_back(c - '0');
  }
  std::cout << "result=[";
  for (const auto& i: result) {
    if (&i == &result.front())
      std::cout<< i << " ... ";
    if (&i == &result.back())
      std::cout<< i;
  }
  std::cout << "]" << std::endl
      << "result.size()='" << result.size() << "'" << std::endl
      << "++++++++++++++++++++++++++++++" << std::endl;
  return result;
}
int main(int argc, char** argv) {

  const std::string x_str =
      "3141592653589793238462643383279502884197169399375105820974944592";
  const std::string y_str =
      "2718281828459045235360287471352662497757247093699959574966967627";
  const std::vector<int> x = string_to_int_vector(x_str);
  const std::vector<int> y = string_to_int_vector(y_str);
  /*
  auto before = std::chrono::system_clock::now();
  const auto product = x * y;
  auto after = std::chrono::system_clock::now();

  std::cout << "product=" << product << std::endl;
  std::cout << "time elapsed=" << (after - before) << std::endl;
  */
  return 0;
}
