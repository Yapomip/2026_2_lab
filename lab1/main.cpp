
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

struct statistic {
  std::vector<double> data;

  void from_file(const std::string &file_name) {
    std::ifstream in(file_name);
    if (in.is_open()) {
      char buf[100];
      in.getline(buf, 100, ';');
      in.getline(buf, 100);

      size_t number;
      char delimer;
      double measure;
      for (; in >> number >> delimer >> measure;) {
        data.push_back(measure);
      }
    }
  }
  friend std::ostream &operator<<(std::ostream &out, statistic s) {
    for (auto x : s.data) {
      out << std::setprecision(4) << x << " ";
    }
    return out;
  }

  double get_median() const {
    double res;
    for (auto x : data) {
      res += x;
    }
    if (!data.empty()) {
      res /= data.size();
    }
    return res;
  }

  double calculate_square(double p) {
    double res;
    for (auto x : data) {
      res += (x - p) * (x - p);
    }
    return res;
  }
};

int main() {
  std::cout << "lab: 1, file: data_raw.csv" << std::endl;

  statistic s;

  s.from_file("data_raw.csv");
  std::cout << "data: " << s << std::endl;

  auto median = s.get_median();
  std::cout << "median " << median << std::endl;

  return 0;
}
