#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <mutex>
#include <set>
#include <thread>
#include <unordered_map>
#include <unordered_set>
//二维地图上有一堆坐标点， 找到在共线最多的点数
//输入: points[] = {-1, 1},  {0, 0}, {1, 1},   {2, 2}, {3, 3}, {3, 4}，{6,6}
//输出 : 5
using namespace std;
struct point {
  int x;
  int y;
};
const float FLT_EPSILON = 0.00001;
bool feq(float a, float b) { return fabs(a - b) < FLT_EPSILON; }

struct kAndB {
  float k;
  float b;
  bool operator<(const kAndB &others) {
    if (feq(k, others.k) && feq(b, others.b)) {
      return false;
    }
    if (k < others.k) {
      return true;
    } else if (feq(k, others.k)) {
      return b < others.b;
    } else {
      return false;
    }
  }
};

int fun(std::vector<point> &data) {
  std::map<float, std::map<float, std::set<std::string>>> map_kb_nums;
  for (int i = 0; i < data.size() - 1; i++) {
    for (int j = i + 1; j < data.size(); j++) {
      kAndB temp;
      temp.k = static_cast<float>(data[j].y - data[i].y) /
               static_cast<float>(data[j].x - data[i].x);
      temp.b = static_cast<float>(data[j].y) -
               temp.k * static_cast<float>(data[j].x);
      map_kb_nums[temp.k][temp.b].insert(to_string(data[j].x) + "." +
                                         to_string(data[j].y));
    }
  }
  int maxn = 0;
  for (auto &kb : map_kb_nums) {
    for (const auto &b : kb.second) {
      int n = static_cast<int>(b.second.size());
      maxn = max(n, maxn);
    }
  }
  return maxn + 1;
}
// y = j * x + b     y2 = j * x2 + b
int main() {

  std::vector<point> data{{-1, 1}, {0, 0}, {1, 1}, {2, 2},
                          {3, 3},  {3, 4}, {6, 6}};
  std::vector<point> data2{{-6, -1}, {3, 1}, {12, 3}};
  std::cout << fun(data2) << "\n";
  //

  return 0;
}