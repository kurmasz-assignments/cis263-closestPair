//
// Created by Zachary Kurmas on 2019-11-07.
//

#ifndef CLOSESTPAIR_H
#define CLOSESTPAIR_H

#include<vector>
#include<set>
#include<ostream>
#include<cmath>

namespace cis263 {

  using namespace std;

  class ClosestPairs {

  public:

    using Point = std::pair<double, double>;
    using PointVector = vector<Point>;
    using PointPair = std::pair<Point, Point>;
    using PointPairSet = set<PointPair>;

    static PointPairSet closestPairs(const PointVector &pairs, double tolerance = 0.000001);

    static PointPairSet closestPairsBruteForce(const PointVector &pairs,
                                               double tolerance = 0.000001);


  private:

    // Declare helper methods here. (but implement them in the .cpp file)
    // 

  };

}

// This code is in the global namespace so Catch will pick it up and display
// more helpful error messages (instead of {?} == {?})
using namespace std;
using namespace cis263;

inline ostream &operator<<(ostream &out, const ClosestPairs::Point &p) {
  return out << "{" << p.first << ", " << p.second << "}";
}

inline ostream &operator<<(ostream &out, const ClosestPairs::PointPair &p) {
  return out << "{" << p.first << "->" << p.second << "} ";
}

inline ostream &operator<<(ostream &out, const ClosestPairs::PointPairSet &pps) {
  bool comma = false;
  for (const auto &i : pps) {
    if (comma) {
      out << ", ";
    }
    out << i << " ";
    comma = true;
  }
  return out;
}


#endif //GETTINGSTARTED_CLOSESTPAIR_H
