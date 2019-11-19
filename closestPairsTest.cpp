//
// Created by Zachary Kurmas on 2019-11-07.
//
// Important:  floating point equality is very precise.
//             Statements like 0.5 + 0.5 == 2.0 may end up false.
//             If you use a calculation to generate an input point,
//             You need to use an identical calculation to set up the
//             expected output.

// Important:  These tests are still a work in progress.
//             Don't edit this file, because  you will need to overwrite it with a new version
//             later.  If you want to add more tests now, put them in a separate .cpp file.

#include "ClosestPairs.h"
#include "catch.hpp"
#include<iostream>
#include<random>



/*****************************************************
 *
 * Brute Force
 *
 *****************************************************/

//
// Empty List
//
TEST_CASE("bf noTies noRound empty list") {

  ClosestPairs::PointVector p;

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(0 == out.size());
}

//
// One point
//
TEST_CASE("bf noTies noRound one point") {

  ClosestPairs::PointVector p({{1.0, 2.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(0 == out.size());
}

//
// Two points
//
TEST_CASE("bf noTies noRound two points") {

  ClosestPairs::PointVector p({{1.0, 2.0},
                               {3.0, 4.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{1.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}

TEST_CASE("bf noTies noRound two points properly ordered (a)") {

  ClosestPairs::PointVector p({{3.0, 4.0},
                               {1.0, 2.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{1.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}

TEST_CASE("bf noTies noRound two points properly ordered (b)") {

  ClosestPairs::PointVector p({{3.0, 4.0},
                               {3.0, 2.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{3.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}


//
// Three points
//
TEST_CASE("bf noTies noRound three points (first pair closet)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 1.0},
                               {3.0, 3.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{0.0, 0.0},
                                   {1.0, 1.0}}) == *out.begin());
}

TEST_CASE("bf noTies noRound three points (second pair closest)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {2.0, 2.0},
                               {3.0, 3.0}});

  auto out = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{2.0, 2.0},
                                   {3.0, 3.0}}) == *out.begin());
}

TEST_CASE("bf tie noRound three points tie between 1st two and 2nd two") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 1.0},
                               {2.0, 2.0}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {1.0, 1.0}},
                                              {{1.0, 1.0}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}

TEST_CASE("bf tie noRound three points three-way tie") {

  // Remember, it is important to use identical calculations when setting up
  // input and expected output.  (See note above.)
  double h = sqrt(0.75);
  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 0.0},
                               {0.5, h}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(3 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.5, h}},
                                              {{0.0, 0.0}, {1.0, 0.0}},
                                              {{0.5, h},   {1.0, 0.0}}});
  REQUIRE(expected == observed);
}

//
// Four points
//
TEST_CASE("bf noTie noRound four points") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {0.0, 1.0},
                               {2.0, 1.0},
                               {5.0, 0.0}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("bf tie noRound four points two-way tie (rectangle)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {0.0, 1.0},
                               {5.0, 0.0},
                               {5.0, 1.0}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{5.0, 0.0}, {5.0, 1.0}}});
  REQUIRE(expected == observed);
}

TEST_CASE("bf tie noRound four points two-way tie (rectangle different order)") {

  ClosestPairs::PointVector p({{5.0, 1.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {5.0, 0.0}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{5.0, 0.0}, {5.0, 1.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("bf tie noRound four points four-way tie (square)") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(4 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{0.0, 0.0}, {1.0, 0.0}},
                                              {{0.0, 1.0}, {1.0, 1.0}},
                                              {{1.0, 0.0}, {1.0, 1.0}}});
  REQUIRE(expected == observed);
}

//
// Five points
//
TEST_CASE("bf noTie noRound five points") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {1.1, 1.1}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{1.0, 1.0}, {1.1, 1.1}}});
  REQUIRE(expected == observed);
}

TEST_CASE("bf tie noRound five points") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {0.5, 0.5}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(4 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.5, 0.5}},
                                              {{0.0, 1.0}, {0.5, 0.5}},
                                              {{0.5, 0.5}, {1.0, 0.0}},
                                              {{0.5, 0.5}, {1.0, 1.0}}});
  REQUIRE(expected == observed);
}

//
// Six points
//
TEST_CASE("bf noTie noRound six points") {

  ClosestPairs::PointVector p({{1.0,  1.0},
                               {1.0,  0.0},
                               {0.0,  1.0},
                               {0.0,  0.0},
                               {0.45, 0.55},
                               {0.55, 0.45}});

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.45, 0.55}, {0.55, 0.45}}});
  REQUIRE(expected == observed);
}

//
// Misc
//

TEST_CASE("bf tie noRound two clusters") {

  ClosestPairs::PointVector p({{1.0,  1.0},
                               {1.0,  0.0},
                               {0.0,  1.0},
                               {0.0,  0.0},

                               {10.0, 10.0},
                               {10.0, 11.0},
                               {11.0, 10.0},
                               {11.0, 11.0}
                              });

  auto observed = ClosestPairs::closestPairsBruteForce(p);
  REQUIRE(8 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0,  0.0},  {0.0,  1.0}},
                                              {{0.0,  0.0},  {1.0,  0.0}},
                                              {{0.0,  1.0},  {1.0,  1.0}},
                                              {{1.0,  0.0},  {1.0,  1.0}},

                                              {{10.0, 10.0}, {10.0, 11.0}},
                                              {{10.0, 10.0}, {11.0, 10.0}},
                                              {{10.0, 11.0}, {11.0, 11.0}},
                                              {{11.0, 10.0}, {11.0, 11.0}},
                                             });
  REQUIRE(expected == observed);
}

//
// With rounding
//


TEST_CASE("bf tie round three points not quite a tie between") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.03, 1.03},
                               {2.0, 2.0}});

  // Notice the really big tolerance.  Even so, there should be no tie.
  auto observed = ClosestPairs::closestPairsBruteForce(p, 0.05);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{1.03, 1.03}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("bf tie round three points tie between 1st two and 2nd two") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.03, 1.03},
                               {2.0, 2.0}});

  // Notice the really big tolerance.  This should make the two points a "tie"
  auto observed = ClosestPairs::closestPairsBruteForce(p, 0.1);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {1.03, 1.03}},
                                              {{1.03, 1.03}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}

/*****************************************************
 *
 * Divide and conquer
 *
 *****************************************************/

//
// Empty List
//
TEST_CASE("dc noTies noRound empty list") {

  ClosestPairs::PointVector p;

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(0 == out.size());
}

//
// One point
//
TEST_CASE("dc noTies noRound one point") {

  ClosestPairs::PointVector p({{1.0, 2.0}});

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(0 == out.size());
}

//
// Two points
//
TEST_CASE("dc noTies noRound two points") {

  ClosestPairs::PointVector p({{1.0, 2.0},
                               {3.0, 4.0}});

  auto out = ClosestPairs::closestPairs(p);

  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{1.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}

TEST_CASE("dc noTies noRound two points properly ordered (a)") {

  ClosestPairs::PointVector p({{3.0, 4.0},
                               {1.0, 2.0}});

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{1.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}

TEST_CASE("dc noTies noRound two points properly ordered (b)") {

  ClosestPairs::PointVector p({{3.0, 4.0},
                               {3.0, 2.0}});

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{3.0, 2.0},
                                   {3.0, 4.0}}) == *out.begin());
}

//
// Three points
//
TEST_CASE("dc noTies noRound three points (first pair closet)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 1.0},
                               {3.0, 3.0}});

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{0.0, 0.0},
                                   {1.0, 1.0}}) == *out.begin());
}

TEST_CASE("dc noTies noRound three points (second pair closest)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {2.0, 2.0},
                               {3.0, 3.0}});

  auto out = ClosestPairs::closestPairs(p);
  REQUIRE(1 == out.size());
  REQUIRE(ClosestPairs::PointPair({{2.0, 2.0},
                                   {3.0, 3.0}}) == *out.begin());
}

TEST_CASE("dc tie noRound three points tie between 1st two and 2nd two") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 1.0},
                               {2.0, 2.0}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {1.0, 1.0}},
                                              {{1.0, 1.0}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}

TEST_CASE("dc tie noRound three points three-way tie") {

  // Remember, it is important to use identical calculations when setting up
  // input and expected output.  (See note above.)
  double h = sqrt(0.75);
  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.0, 0.0},
                               {0.5, h}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(3 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.5, h}},
                                              {{0.0, 0.0}, {1.0, 0.0}},
                                              {{0.5, h},   {1.0, 0.0}}});
  REQUIRE(expected == observed);
}

//
// Four points
//
TEST_CASE("dc noTie noRound four points") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {0.0, 1.0},
                               {2.0, 1.0},
                               {5.0, 0.0}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("dc tie noRound four points two-way tie (rectangle)") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {0.0, 1.0},
                               {5.0, 0.0},
                               {5.0, 1.0}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{5.0, 0.0}, {5.0, 1.0}}});
  REQUIRE(expected == observed);
}

TEST_CASE("dc tie noRound four points two-way tie (rectangle different order)") {

  ClosestPairs::PointVector p({{5.0, 1.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {5.0, 0.0}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{5.0, 0.0}, {5.0, 1.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("dc tie noRound four points four-way tie (square)") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(4 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.0, 1.0}},
                                              {{0.0, 0.0}, {1.0, 0.0}},
                                              {{0.0, 1.0}, {1.0, 1.0}},
                                              {{1.0, 0.0}, {1.0, 1.0}}});
  REQUIRE(expected == observed);
}


//
// Five points
//
TEST_CASE("dc noTie noRound five points") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {1.1, 1.1}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{1.0, 1.0}, {1.1, 1.1}}});
  REQUIRE(expected == observed);
}

TEST_CASE("dc tie noRound five points") {

  ClosestPairs::PointVector p({{1.0, 1.0},
                               {1.0, 0.0},
                               {0.0, 1.0},
                               {0.0, 0.0},
                               {0.5, 0.5}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(4 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {0.5, 0.5}},
                                              {{0.0, 1.0}, {0.5, 0.5}},
                                              {{0.5, 0.5}, {1.0, 0.0}},
                                              {{0.5, 0.5}, {1.0, 1.0}}});
  REQUIRE(expected == observed);
}

//
// Six points
//
TEST_CASE("dc noTie noRound six points") {

  ClosestPairs::PointVector p({{1.0,  1.0},
                               {1.0,  0.0},
                               {0.0,  1.0},
                               {0.0,  0.0},
                               {0.45, 0.55},
                               {0.55, 0.45}});

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.45, 0.5577}, {0.55, 0.45}}});
  REQUIRE(expected == observed);
}

//
// Misc
//
TEST_CASE("dc tie noRound two clusters") {

  ClosestPairs::PointVector p({{1.0,  1.0},
                               {1.0,  0.0},
                               {0.0,  1.0},
                               {0.0,  0.0},

                               {10.0, 10.0},
                               {10.0, 11.0},
                               {11.0, 10.0},
                               {11.0, 11.0}
                              });

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(8 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0,  0.0},  {0.0,  1.0}},
                                              {{0.0,  0.0},  {1.0,  0.0}},
                                              {{0.0,  1.0},  {1.0,  1.0}},
                                              {{1.0,  0.0},  {1.0,  1.0}},

                                              {{10.0, 10.0}, {10.0, 11.0}},
                                              {{10.0, 10.0}, {11.0, 10.0}},
                                              {{10.0, 11.0}, {11.0, 11.0}},
                                              {{11.0, 10.0}, {11.0, 11.0}},
                                             });
  REQUIRE(expected == observed);
}


TEST_CASE("dc tie noRound two clusters unbalanced") {

  ClosestPairs::PointVector p({{1.0,  1.0},
                               {1.0,  0.0},
                               {0.0,  1.0},
                               {0.0,  0.0},

                               {10.0, 10.0},
                               {10.0, 11.0},
                               {11.0, 10.0},
                               {11.0, 11.0},

                               {15.0, 8.0},
                               {15.0, 9.0}
                              });

  auto observed = ClosestPairs::closestPairs(p);
  REQUIRE(9 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0,  0.0},  {0.0,  1.0}},
                                              {{0.0,  0.0},  {1.0,  0.0}},
                                              {{0.0,  1.0},  {1.0,  1.0}},
                                              {{1.0,  0.0},  {1.0,  1.0}},

                                              {{10.0, 10.0}, {10.0, 11.0}},
                                              {{10.0, 10.0}, {11.0, 10.0}},
                                              {{10.0, 11.0}, {11.0, 11.0}},
                                              {{11.0, 10.0}, {11.0, 11.0}},

                                              {{15.0, 8.0},  {15.0, 9.0}}
                                             });
  REQUIRE(expected == observed);
}


//
// With rounding
//


TEST_CASE("dc tie round three points not quite a tie between") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.03, 1.03},
                               {2.0, 2.0}});

  // Notice the really big tolerance.  Even so, there should be no tie.
  auto observed = ClosestPairs::closestPairs(p, 0.05);
  REQUIRE(1 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{1.03, 1.03}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}


TEST_CASE("dc tie round three points tie between 1st two and 2nd two") {

  ClosestPairs::PointVector p({{0.0, 0.0},
                               {1.03, 1.03},
                               {2.0, 2.0}});

  // Notice the really big tolerance.  This should make the two points a "tie"
  auto observed = ClosestPairs::closestPairs(p, 0.1);
  REQUIRE(2 == observed.size());
  auto expected = ClosestPairs::PointPairSet({{{0.0, 0.0}, {1.03, 1.03}},
                                              {{1.03, 1.03}, {2.0, 2.0}}});
  REQUIRE(expected == observed);
}


//
// Big tests
//
class Data {
public:
  static ClosestPairs::PointVector uniform1;
};

TEST_CASE("big noTie noRound uniformly random") {

  auto observed = ClosestPairs::closestPairs(Data::uniform1);
  auto expected = ClosestPairs::PointPairSet({{{30.4146, 98.4274}, {30.4328, 98.422}}});
  REQUIRE(1 == observed.size());
  REQUIRE(expected == observed);
}


TEST_CASE("big tie noRound uniformly random offset by 1") {

  ClosestPairs::PointVector points(Data::uniform1);
  for (const auto &p : Data::uniform1) {
    points.push_back({p.first + 1.0, p.second + 1.0});
  }
  auto observed = ClosestPairs::closestPairs(points);
  auto expected = ClosestPairs::PointPairSet({{{30.4146, 98.4274}, {30.4328, 98.422}},
                                              {{31.4146, 99.4274}, {31.4328, 99.422}}});
  REQUIRE(2 == observed.size());
  REQUIRE(expected == observed);
}

TEST_CASE("big tie noRound uniformly random offset 3 times") {

  ClosestPairs::PointVector points(Data::uniform1);
  for (const auto &p : Data::uniform1) {
    points.push_back({p.first + 1.0, p.second + 1.0});
    points.push_back({p.first + 1.0, p.second});
    points.push_back({p.first, p.second - 1.0});

  }
  auto observed = ClosestPairs::closestPairs(points);
  auto expected = ClosestPairs::PointPairSet({{{30.4146, 98.4274}, {30.4328, 98.422}},
                                              {{31.4146, 99.4274}, {31.4328, 99.422}},
                                              {{31.4146, 98.4274}, {31.4328, 98.422}},
                                              {{30.4146, 97.4274}, {30.4328, 97.422}}});
  REQUIRE(2 == observed.size());
  REQUIRE(expected == observed);
}

TEST_CASE("big tie noRound uniformly random mirror image separate") {

  ClosestPairs::PointVector points(Data::uniform1);
  for (const auto &p : Data::uniform1) {
    points.push_back({200.0 - p.first, 200.0 - p.second});
  }
  auto observed = ClosestPairs::closestPairs(points);

  // Remember, it is important to use identical calculations when setting up
  // input and expected output.  (See note above.)
  auto expected = ClosestPairs::PointPairSet({{{30.4146,98.4274}, {30.4328, 98.422}},
                                              {{200.0 - 30.4328, 200.0 - 98.422},
                                               {200.0 - 30.4146, 200.0 - 98.4274}
                                              }});
  REQUIRE(2 == observed.size());
  REQUIRE(expected == observed);
}

TEST_CASE("big tie noRound uniformly random mirror image overlap") {

  ClosestPairs::PointVector points(Data::uniform1);
  for (const auto &p : Data::uniform1) {
    points.push_back({100.0 - p.first, 100.0 - p.second});
  }
  auto observed = ClosestPairs::closestPairs(points);

  // Remember, it is important to use identical calculations when setting up
  // input and expected output.  (See note above.)
  auto expected = ClosestPairs::PointPairSet({{{100.0-92.3231, 100.0-98.1703},{7.67831, 1.81904}},
                                              {{100.0-7.67831, 100.0-1.81904},
                                               {92.3231, 98.1703}}});

  REQUIRE(2 == observed.size());
  REQUIRE(expected == observed);
}


ClosestPairs::PointVector Data::uniform1({
                                             {8.50324,   89.1611},
                                             {18.969,    39.8008},
                                             {74.3512,   56.039},
                                             {80.9567,   51.1713},
                                             {99.5085,   96.6611},
                                             {42.6051,   65.2999},
                                             {96.1533,   85.7987},
                                             {29.4026,   41.4645},
                                             {51.4893,   78.9785},
                                             {54.4273,   9.36299},
                                             {43.226,    84.4927},
                                             {77.2846,   19.1859},
                                             {78.0367,   18.1343},
                                             {57.9141,   31.4131},
                                             {41.1985,   99.2305},
                                             {16.3922,   33.4848},
                                             {7.62182,   17.4524},
                                             {3.72999,   46.7415},
                                             {67.4113,   6.67033},
                                             {38.9782,   16.5399},
                                             {99.0804,   87.0639},
                                             {67.2653,   58.7706},
                                             {25.5014,   59.3045},
                                             {27.172,    27.0481},
                                             {9.59302,   63.2556},
                                             {15.1273,   94.8862},
                                             {4.26043,   73.5089},
                                             {46.5497,   22.254},
                                             {57.1484,   60.4569},
                                             {69.8002,   66.4686},
                                             {17.3652,   75.1495},
                                             {82.4917,   75.3096},
                                             {31.9049,   53.2551},
                                             {14.7554,   79.2628},
                                             {91.2531,   79.4381},
                                             {0.94084,   51.0053},
                                             {29.5594,   55.9919},
                                             {50.4173,   31.0016},
                                             {98.2579,   96.4455},
                                             {44.8564,   30.3514},
                                             {5.62084,   80.1919},
                                             {98.3813,   5.10626},
                                             {23.9803,   10.4699},
                                             {53.4797,   52.1407},
                                             {32.9979,   31.7638},
                                             {97.7858,   73.5087},
                                             {95.3617,   4.94682},
                                             {57.2538,   6.08454},
                                             {81.1628,   97.9186},
                                             {22.5825,   40.6369},
                                             {61.9046,   75.4556},
                                             {91.5988,   3.64922},
                                             {83.0576,   90.3643},
                                             {17.5992,   56.6783},
                                             {32.8182,   39.4569},
                                             {46.4552,   18.3268},
                                             {25.75,     61.0549},
                                             {19.6504,   14.1293},
                                             {66.9344,   80.1833},
                                             {15.5896,   47.1428},
                                             {25.5728,   99.3978},
                                             {69.8761,   84.7351},
                                             {6.93813,   19.1786},
                                             {0.814663,  43.9653},
                                             {38.9613,   13.5657},
                                             {24.9231,   46.1392},
                                             {69.8389,   20.6857},
                                             {18.2262,   39.4393},
                                             {14.2462,   71.5652},
                                             {47.312,    36.172},
                                             {0.0310001, 97.2109},
                                             {24.2597,   65.428},
                                             {94.02,     59.6257},
                                             {90.3858,   33.1532},
                                             {30.4043,   67.5398},
                                             {44.9785,   40.9032},
                                             {61.8305,   74.4505},
                                             {4.73447,   67.6037},
                                             {1.81979,   53.4675},
                                             {93.8174,   37.8044},
                                             {49.2311,   67.5751},
                                             {78.4188,   89.3682},
                                             {72.7119,   32.1514},
                                             {14.5237,   23.7183},
                                             {21.1923,   21.5503},
                                             {57.8177,   75.2816},
                                             {79.0235,   13.3438},
                                             {38.0455,   37.355},
                                             {30.4522,   64.4799},
                                             {82.2678,   78.2788},
                                             {52.4381,   20.916},
                                             {63.4027,   63.9567},
                                             {73.8946,   68.0354},
                                             {39.9406,   0.70856},
                                             {26.2852,   86.3901},
                                             {64.4201,   62.4378},
                                             {62.6034,   58.9567},
                                             {96.6505,   61.5464},
                                             {46.828,    62.1017},
                                             {15.8794,   14.2496},
                                             {86.501,    9.67811},
                                             {45.4215,   32.5748},
                                             {51.4359,   13.365},
                                             {6.97475,   2.95329},
                                             {98.3548,   95.8699},
                                             {0.201616,  37.944},
                                             {40.5739,   20.097},
                                             {35.6173,   73.465},
                                             {62.5217,   35.6788},
                                             {11.7113,   66.0441},
                                             {85.2671,   17.3169},
                                             {17.9815,   63.3661},
                                             {48.024,    43.1296},
                                             {75.3998,   2.89346},
                                             {8.20452,   60.8019},
                                             {65.124,    85.408},
                                             {27.669,    65.0933},
                                             {7.1351,    14.2347},
                                             {12.5875,   94.5738},
                                             {93.6528,   91.847},
                                             {11.4143,   73.2253},
                                             {73.8761,   49.8233},
                                             {68.8348,   73.0259},
                                             {90.7376,   88.3554},
                                             {80.5097,   86.6969},
                                             {42.0333,   48.0598},
                                             {77.1371,   21.6878},
                                             {1.53988,   89.8071},
                                             {59.3205,   8.55107},
                                             {16.5678,   28.9766},
                                             {98.7377,   92.5162},
                                             {83.9067,   83.1568},
                                             {18.3894,   65.713},
                                             {22.2198,   38.9359},
                                             {70.0861,   5.46572},
                                             {86.0483,   67.5776},
                                             {67.0838,   1.05974},
                                             {4.59554,   66.3368},
                                             {94.0818,   30.6636},
                                             {95.1851,   10.8658},
                                             {93.3384,   37.4462},
                                             {14.8801,   24.3328},
                                             {39.3446,   15.6439},
                                             {38.4292,   97.53},
                                             {82.6041,   31.9116},
                                             {18.4839,   47.2118},
                                             {84.3494,   34.4329},
                                             {66.5252,   43.4407},
                                             {39.332,    76.2639},
                                             {79.3802,   94.1105},
                                             {51.6577,   96.3232},
                                             {19.3779,   32.9543},
                                             {54.0672,   89.9801},
                                             {20.1562,   47.8998},
                                             {80.3223,   82.358},
                                             {28.9239,   94.6806},
                                             {13.806,    71.7166},
                                             {76.6961,   21.9825},
                                             {16.1285,   11.1707},
                                             {88.8836,   65.1704},
                                             {92.0424,   92.924},
                                             {48.5562,   56.8964},
                                             {14.643,    73.8897},
                                             {89.1826,   38.3913},
                                             {3.85231,   25.2323},
                                             {83.0802,   76.5449},
                                             {47.0517,   92.3535},
                                             {40.4527,   89.2015},
                                             {60.8089,   29.9643},
                                             {41.236,    71.2823},
                                             {60.7795,   47.9709},
                                             {30.3242,   16.1047},
                                             {45.8142,   27.915},
                                             {86.452,    43.9408},
                                             {72.7976,   82.7775},
                                             {2.62505,   20.5282},
                                             {57.3655,   16.3278},
                                             {40.5304,   23.5695},
                                             {48.5246,   63.7483},
                                             {71.9688,   53.4007},
                                             {9.12164,   63.2732},
                                             {65.5232,   8.13654},
                                             {15.3727,   61.7354},
                                             {53.5478,   23.3607},
                                             {43.0678,   29.3607},
                                             {93.2374,   62.9655},
                                             {52.7628,   70.2241},
                                             {49.4331,   91.9976},
                                             {73.7948,   96.319},
                                             {83.1739,   11.7769},
                                             {55.2269,   65.7861},
                                             {90.3466,   76.5855},
                                             {97.9569,   50.0738},
                                             {43.966,    87.727},
                                             {3.73822,   5.82227},
                                             {55.8282,   19.9841},
                                             {54.6504,   65.6868},
                                             {19.5703,   30.0967},
                                             {51.8615,   71.7647},
                                             {37.9368,   61.5479},
                                             {28.5639,   74.7458},
                                             {51.1947,   57.6751},
                                             {97.0931,   96.3475},
                                             {72.5824,   2.8323},
                                             {76.9641,   71.3023},
                                             {48.0289,   26.4079},
                                             {26.2432,   63.4632},
                                             {93.8381,   54.0332},
                                             {64.1024,   38.7907},
                                             {20.9801,   94.9028},
                                             {91.378,    35.0553},
                                             {27.5542,   3.91331},
                                             {64.879,    69.0569},
                                             {96.262,    68.3256},
                                             {86.6886,   84.7565},
                                             {77.0069,   5.74203},
                                             {10.4384,   40.9641},
                                             {54.8115,   85.0982},
                                             {4.61741,   96.6129},
                                             {78.8809,   53.6898},
                                             {31.2851,   37.7259},
                                             {87.9432,   96.9592},
                                             {73.4735,   0.10921},
                                             {45.6776,   93.8507},
                                             {40.3343,   34.6504},
                                             {24.2611,   76.445},
                                             {71.7889,   51.6605},
                                             {97.2064,   86.4972},
                                             {24.2022,   75.2667},
                                             {2.42205,   96.0805},
                                             {64.8536,   58.8493},
                                             {27.9666,   44.0737},
                                             {86.3561,   76.8427},
                                             {27.1256,   5.91111},
                                             {21.6611,   70.7951},
                                             {29.3286,   45.3037},
                                             {13.0023,   84.8383},
                                             {25.171,    28.967},
                                             {15.6653,   1.2467},
                                             {72.755,    37.7291},
                                             {10.8918,   59.747},
                                             {53.7663,   67.0127},
                                             {46.5865,   34.9263},
                                             {62.6122,   77.7133},
                                             {27.3623,   87.3216},
                                             {78.0272,   53.8314},
                                             {95.1297,   47.1028},
                                             {61.6622,   88.2469},
                                             {47.7555,   5.9823},
                                             {18.1906,   19.9854},
                                             {96.6909,   75.1426},
                                             {80.7205,   27.5357},
                                             {75.389,    67.8208},
                                             {10.3811,   36.0704},
                                             {7.39426,   96.9518},
                                             {50.2809,   69.4652},
                                             {23.8067,   42.4599},
                                             {17.7678,   69.8122},
                                             {17.4436,   8.53613},
                                             {86.8365,   17.1566},
                                             {14.3704,   59.5552},
                                             {82.0108,   35.098},
                                             {62.6634,   82.149},
                                             {49.7383,   16.8595},
                                             {8.52593,   17.025},
                                             {15.4878,   84.0426},
                                             {26.6086,   44.3551},
                                             {69.5623,   81.2974},
                                             {13.9959,   24.6827},
                                             {8.30893,   94.7277},
                                             {18.7182,   48.1181},
                                             {28.1852,   66.2019},
                                             {89.0016,   34.5154},
                                             {35.2114,   0.567196},
                                             {24.0072,   90.5018},
                                             {21.2172,   7.78649},
                                             {0.969241,  82.1175},
                                             {71.2817,   62.8033},
                                             {59.6228,   47.6353},
                                             {52.4537,   38.1069},
                                             {7.50378,   31.0293},
                                             {92.5825,   31.4265},
                                             {74.3183,   63.2745},
                                             {1.37543,   18.1354},
                                             {23.9059,   88.3039},
                                             {39.3426,   83.0624},
                                             {98.4777,   0.672626},
                                             {33.7464,   38.1996},
                                             {65.1388,   11.3374},
                                             {19.3926,   32.9294},
                                             {76.1963,   76.1043},
                                             {62.9271,   99.7822},
                                             {83.0123,   43.2113},
                                             {3.379,     56.8975},
                                             {6.14455,   98.2639},
                                             {44.2336,   41.6256},
                                             {8.99155,   60.5371},
                                             {52.0749,   50.8059},
                                             {6.98596,   46.9328},
                                             {20.2492,   11.3603},
                                             {86.4868,   46.9249},
                                             {93.2906,   8.39401},
                                             {30.9944,   69.3469},
                                             {71.4836,   41.7866},
                                             {54.4646,   52.6091},
                                             {52.9465,   79.8684},
                                             {0.771932,  2.83131},
                                             {24.1819,   92.0646},
                                             {41.3971,   38.6983},
                                             {52.8079,   74.9273},
                                             {88.0767,   96.5618},
                                             {59.0841,   26.8697},
                                             {59.8582,   77.3216},
                                             {22.0366,   46.2876},
                                             {52.3232,   96.2734},
                                             {17.037,    0.102755},
                                             {19.4032,   59.1003},
                                             {69.3759,   80.1826},
                                             {72.5217,   67.6876},
                                             {49.365,    55.1381},
                                             {29.7964,   83.0561},
                                             {76.2863,   25.2165},
                                             {88.1491,   19.3723},
                                             {97.8034,   11.8089},
                                             {48.8961,   19.6549},
                                             {75.4801,   81.9947},
                                             {21.0704,   51.1793},
                                             {74.1087,   33.0083},
                                             {43.6775,   65.6042},
                                             {90.5949,   40.332},
                                             {47.7535,   82.1595},
                                             {3.57031,   4.31364},
                                             {19.8879,   79.8054},
                                             {0.509617,  70.1739},
                                             {45.2526,   99.8998},
                                             {10.388,    60.6889},
                                             {23.5203,   35.5647},
                                             {56.8267,   54.7833},
                                             {49.2642,   10.2296},
                                             {10.8561,   34.7077},
                                             {82.3512,   88.6479},
                                             {70.739,    18.0723},
                                             {84.8783,   23.8816},
                                             {88.8733,   76.8194},
                                             {95.0308,   51.3583},
                                             {42.4851,   26.3964},
                                             {34.4586,   45.2748},
                                             {16.7924,   9.87453},
                                             {39.931,    30.1253},
                                             {90.787,    3.22133},
                                             {16.9066,   32.2536},
                                             {8.54003,   16.939},
                                             {92.7069,   36.7295},
                                             {29.5652,   55.5814},
                                             {54.837,    16.5077},
                                             {67.3868,   6.91267},
                                             {50.6288,   96.5578},
                                             {81.667,    43.7649},
                                             {23.8694,   54.8793},
                                             {60.943,    74.6686},
                                             {56.8082,   31.7728},
                                             {16.4096,   63.7623},
                                             {21.8803,   20.9062},
                                             {26.7558,   76.0196},
                                             {26.7624,   61.2647},
                                             {46.0993,   87.5574},
                                             {96.5323,   70.9484},
                                             {3.12936,   75.1843},
                                             {90.0392,   4.98195},
                                             {90.5971,   61.8654},
                                             {75.6973,   78.0924},
                                             {50.9298,   83.3863},
                                             {74.8288,   77.0988},
                                             {88.0797,   88.4103},
                                             {81.1015,   98.2077},
                                             {17.6828,   46.9851},
                                             {77.6101,   92.2865},
                                             {62.1242,   41.2138},
                                             {52.0953,   55.1894},
                                             {78.8843,   13.8554},
                                             {44.6438,   9.85661},
                                             {96.7558,   5.75847},
                                             {17.4549,   13.1063},
                                             {64.1676,   37.4172},
                                             {6.83005,   25.8233},
                                             {19.9171,   79.0558},
                                             {6.48664,   55.4006},
                                             {91.653,    92.7077},
                                             {19.1403,   83.3546},
                                             {27.3908,   35.3023},
                                             {38.1864,   29.2186},
                                             {88.2768,   90.2372},
                                             {54.3277,   95.6004},
                                             {45.7926,   72.1343},
                                             {53.5967,   34.1131},
                                             {97.7154,   32.8377},
                                             {4.19638,   27.1127},
                                             {0.396024,  20.5169},
                                             {33.6783,   1.08462},
                                             {84.9704,   35.8579},
                                             {80.2512,   22.3454},
                                             {92.0234,   32.1345},
                                             {86.7348,   0.931581},
                                             {40.2768,   63.4426},
                                             {7.66197,   32.224},
                                             {6.36168,   36.8063},
                                             {30.2424,   98.9437},
                                             {70.6756,   15.296},
                                             {57.7212,   75.8009},
                                             {92.3035,   46.3339},
                                             {6.31324,   36.2841},
                                             {67.1447,   20.4294},
                                             {48.0944,   32.5256},
                                             {95.4283,   4.69705},
                                             {94.0035,   76.2385},
                                             {59.2794,   98.946},
                                             {74.6045,   38.7476},
                                             {15.147,    62.3647},
                                             {93.1327,   70.2275},
                                             {58.0681,   98.0493},
                                             {7.67831,   1.81904},
                                             {97.8185,   85.334},
                                             {87.3721,   9.9504},
                                             {68.7142,   75.765},
                                             {34.7997,   99.4683},
                                             {31.7745,   73.4023},
                                             {17.4333,   86.9387},
                                             {41.6906,   86.365},
                                             {45.8574,   3.72111},
                                             {28.9558,   75.3242},
                                             {36.5355,   57.8206},
                                             {80.1967,   99.3814},
                                             {36.7265,   15.9118},
                                             {93.4928,   26.7763},
                                             {25.6533,   33.254},
                                             {67.576,    5.82924},
                                             {61.0078,   91.7989},
                                             {96.1187,   87.107},
                                             {17.7456,   80.3048},
                                             {92.4608,   97.8534},
                                             {42.0971,   34.6472},
                                             {40.5378,   11.7067},
                                             {94.2431,   84.369},
                                             {76.0746,   62.0877},
                                             {51.3018,   61.1539},
                                             {43.894,    25.7473},
                                             {92.4523,   81.4678},
                                             {26.5724,   38.5557},
                                             {37.6631,   97.2776},
                                             {87.7996,   32.1136},
                                             {14.8007,   46.2022},
                                             {59.2116,   84.8214},
                                             {42.1008,   84.8326},
                                             {73.1976,   54.9003},
                                             {29.1262,   15.3573},
                                             {14.5684,   25.468},
                                             {82.6524,   2.26366},
                                             {12.2347,   19.3965},
                                             {29.76,     0.584454},
                                             {62.6244,   31.0083},
                                             {27.6647,   35.4661},
                                             {62.0428,   29.4847},
                                             {6.75762,   48.7484},
                                             {85.1033,   11.3255},
                                             {77.8048,   15.7147},
                                             {62.9827,   14.5953},
                                             {72.1103,   22.9431},
                                             {29.2159,   41.6835},
                                             {22.2402,   92.4839},
                                             {53.5315,   51.0573},
                                             {65.8513,   82.9022},
                                             {39.2633,   69.1149},
                                             {44.3361,   52.0556},
                                             {73.7918,   39.526},
                                             {46.0821,   41.6889},
                                             {44.6874,   10.0021},
                                             {57.431,    39.5236},
                                             {77.694,    72.4751},
                                             {66.3319,   95.7441},
                                             {98.1746,   78.0637},
                                             {26.1339,   62.1518},
                                             {49.7855,   73.5832},
                                             {31.4323,   15.591},
                                             {34.7605,   95.4481},
                                             {31.8872,   72.9446},
                                             {68.3283,   24.0376},
                                             {58.1099,   79.8449},
                                             {50.7355,   79.1056},
                                             {34.3373,   55.7355},
                                             {83.2239,   42.99},
                                             {92.9742,   19.1887},
                                             {78.0614,   3.48646},
                                             {16.2707,   58.7445},
                                             {0.101656,  74.7973},
                                             {43.1974,   49.7626},
                                             {61.9798,   88.3261},
                                             {99.1448,   24.41},
                                             {4.14355,   34.1957},
                                             {6.9504,    55.4926},
                                             {25.8226,   0.784963},
                                             {82.8622,   60.8706},
                                             {18.8876,   89.7254},
                                             {96.3319,   56.25},
                                             {40.4984,   42.7829},
                                             {46.4826,   38.1766},
                                             {92.3877,   53.8259},
                                             {50.6222,   53.3434},
                                             {38.8234,   34.4969},
                                             {47.4198,   15.5512},
                                             {94.7652,   83.9581},
                                             {63.8508,   42.8719},
                                             {97.3529,   0.0261231},
                                             {26.8613,   11.8715},
                                             {87.5407,   32.7681},
                                             {30.6671,   58.5496},
                                             {98.7237,   11.3256},
                                             {48.5442,   34.1906},
                                             {82.7708,   10.2667},
                                             {49.7382,   45.9361},
                                             {43.5362,   4.75406},
                                             {25.6028,   43.479},
                                             {5.47117,   35.0732},
                                             {83.888,    99.8776},
                                             {36.4972,   76.3204},
                                             {16.9433,   52.9846},
                                             {1.05388,   28.3594},
                                             {83.1822,   45.0004},
                                             {66.7335,   13.7349},
                                             {57.2556,   97.1873},
                                             {84.1625,   55.1999},
                                             {80.0974,   79.0931},
                                             {69.2636,   82.6893},
                                             {30.4146,   98.4274},
                                             {71.3964,   53.8214},
                                             {25.9723,   97.0867},
                                             {95.2354,   95.8884},
                                             {80.3229,   12.5382},
                                             {37.1252,   41.2212},
                                             {51.8172,   88.2835},
                                             {71.476,    23.4538},
                                             {36.3714,   79.0457},
                                             {32.1833,   34.2086},
                                             {97.9834,   17.5605},
                                             {30.4493,   52.058},
                                             {14.4012,   38.1806},
                                             {24.2993,   66.1674},
                                             {85.0055,   8.19652},
                                             {0.939233,  4.02329},
                                             {79.0422,   36.5893},
                                             {23.4696,   69.5314},
                                             {92.6153,   81.9252},
                                             {24.8368,   93.5766},
                                             {29.8072,   78.786},
                                             {99.7756,   54.3465},
                                             {9.67319,   26.2294},
                                             {15.0387,   56.7246},
                                             {86.5782,   46.3254},
                                             {80.9594,   45.8866},
                                             {50.7715,   11.7997},
                                             {52.0007,   60.389},
                                             {65.8447,   80.6046},
                                             {54.9757,   81.7636},
                                             {15.748,    79.2281},
                                             {30.5807,   74.6364},
                                             {1.17875,   68.36},
                                             {69.1813,   93.8028},
                                             {39.8937,   0.0633027},
                                             {55.6917,   52.7448},
                                             {50.0547,   36.9044},
                                             {46.6321,   59.518},
                                             {67.1054,   74.3325},
                                             {85.0854,   91.9226},
                                             {73.7864,   56.9991},
                                             {45.4674,   57.4525},
                                             {14.5542,   88.9195},
                                             {16.8588,   51.906},
                                             {69.9169,   9.41509},
                                             {94.7205,   72.3612},
                                             {62.15,     32.478},
                                             {84.2461,   0.328016},
                                             {79.9525,   62.2677},
                                             {87.6375,   91.7101},
                                             {90.7131,   28.8195},
                                             {31.8623,   71.7154},
                                             {13.7602,   60.2784},
                                             {24.3732,   53.5438},
                                             {95.1335,   74.5379},
                                             {18.654,    65.6904},
                                             {39.0541,   37.4688},
                                             {87.7846,   5.90312},
                                             {83.8792,   69.5363},
                                             {18.4097,   78.5742},
                                             {80.2515,   78.2143},
                                             {94.7946,   57.9593},
                                             {57.9417,   3.5139},
                                             {37.025,    93.7779},
                                             {48.8847,   98.1907},
                                             {76.6842,   46.5453},
                                             {5.18235,   38.0565},
                                             {3.31825,   19.5044},
                                             {59.0702,   15.376},
                                             {14.6906,   22.7692},
                                             {94.0077,   51.9948},
                                             {4.33267,   32.4838},
                                             {68.7046,   33.4459},
                                             {39.1731,   94.258},
                                             {99.0613,   89.8495},
                                             {66.411,    44.2309},
                                             {45.4743,   33.392},
                                             {88.4456,   26.6835},
                                             {93.0169,   48.0891},
                                             {73.2396,   59.2212},
                                             {34.1364,   12.8958},
                                             {82.3251,   91.6758},
                                             {89.0165,   28.0314},
                                             {57.5401,   65.4557},
                                             {85.0078,   60.222},
                                             {4.62913,   68.1307},
                                             {93.4459,   17.4183},
                                             {16.357,    41.5437},
                                             {79.7094,   22.6548},
                                             {96.4384,   12.588},
                                             {87.4042,   10.8249},
                                             {47.293,    92.2766},
                                             {59.6743,   56.435},
                                             {73.3219,   1.83556},
                                             {45.3837,   23.0046},
                                             {33.6792,   21.7037},
                                             {11.5561,   31.6531},
                                             {11.7336,   27.6809},
                                             {66.4337,   81.62},
                                             {75.8346,   45.4694},
                                             {9.51899,   85.4454},
                                             {6.04206,   49.3956},
                                             {73.4947,   23.0474},
                                             {71.2003,   82.3278},
                                             {79.1143,   25.9133},
                                             {42.058,    9.43014},
                                             {65.6036,   95.3066},
                                             {54.143,    86.4878},
                                             {56.2864,   58.327},
                                             {64.1689,   27.2783},
                                             {76.7533,   54.9309},
                                             {53.8756,   38.1796},
                                             {24.32,     55.6599},
                                             {57.5987,   4.6482},
                                             {41.8028,   7.09409},
                                             {32.9449,   16.5514},
                                             {75.5295,   3.83602},
                                             {49.035,    12.5105},
                                             {67.3138,   32.0711},
                                             {77.0086,   85.2346},
                                             {23.0346,   79.6613},
                                             {67.3469,   20.1598},
                                             {90.5529,   62.4458},
                                             {62.2229,   74.0476},
                                             {6.70421,   75.8122},
                                             {36.656,    80.6832},
                                             {76.8748,   91.4168},
                                             {1.97105,   33.7281},
                                             {35.2821,   28.2481},
                                             {25.9154,   56.1306},
                                             {76.4938,   67.9418},
                                             {90.9471,   75.3389},
                                             {83.8917,   57.7333},
                                             {79.5788,   52.2046},
                                             {37.2459,   25.1395},
                                             {89.6437,   86.4017},
                                             {8.84917,   5.87052},
                                             {73.0043,   32.5499},
                                             {92.5389,   58.0887},
                                             {45.5776,   74.0072},
                                             {80.8743,   22.3184},
                                             {5.45567,   55.5132},
                                             {70.0139,   32.7293},
                                             {46.6989,   87.425},
                                             {6.29628,   69.8014},
                                             {2.24929,   37.7078},
                                             {13.9488,   71.02},
                                             {0.0164407, 72.6559},
                                             {6.07068,   25.0221},
                                             {63.755,    99.3162},
                                             {38.8871,   22.1728},
                                             {25.73,     54.0651},
                                             {74.1036,   35.7284},
                                             {3.64297,   80.2591},
                                             {72.5909,   46.0256},
                                             {24.4233,   11.8917},
                                             {90.6417,   4.38879},
                                             {16.4009,   41.2547},
                                             {77.1278,   71.8259},
                                             {10.6306,   84.9716},
                                             {38.6221,   85.6018},
                                             {87.5224,   10.8766},
                                             {35.1769,   77.2957},
                                             {16.2903,   75.0605},
                                             {74.6946,   18.2344},
                                             {39.8303,   57.2747},
                                             {38.3743,   38.7595},
                                             {98.045,    34.1909},
                                             {59.8416,   7.51199},
                                             {61.611,    88.5585},
                                             {81.0727,   2.00289},
                                             {62.1462,   31.8506},
                                             {59.1888,   67.3822},
                                             {28.3919,   94.333},
                                             {1.75754,   31.3285},
                                             {25.5407,   36.3331},
                                             {48.611,    90.5252},
                                             {24.7464,   99.6692},
                                             {16.8494,   80.9087},
                                             {54.7626,   18.16},
                                             {60.2265,   75.5716},
                                             {87.2616,   1.79687},
                                             {79.4439,   74.8826},
                                             {28.0563,   88.7964},
                                             {10.0581,   15.6289},
                                             {95.0487,   25.3731},
                                             {52.025,    76.3611},
                                             {20.9784,   5.26158},
                                             {15.7426,   81.3402},
                                             {25.5219,   48.511},
                                             {41.14,     44.5645},
                                             {98.2955,   21.9747},
                                             {93.2272,   64.4709},
                                             {12.1391,   83.746},
                                             {34.2854,   41.1309},
                                             {20.0999,   18.0121},
                                             {51.2971,   35.758},
                                             {62.7276,   72.017},
                                             {16.1489,   62.6798},
                                             {2.39553,   83.1342},
                                             {94.2354,   16.0336},
                                             {48.2678,   53.4716},
                                             {40.3285,   65.507},
                                             {8.95896,   35.9927},
                                             {71.1508,   2.21574},
                                             {4.84439,   96.2694},
                                             {92.0292,   89.6727},
                                             {31.0606,   92.9054},
                                             {76.3557,   9.46686},
                                             {42.8936,   90.0186},
                                             {38.1988,   26.4708},
                                             {78.1485,   60.2851},
                                             {33.7636,   5.6839},
                                             {91.1139,   66.418},
                                             {23.4868,   70.1497},
                                             {9.86706,   3.48275},
                                             {35.1997,   54.2832},
                                             {57.1549,   44.956},
                                             {64.2274,   82.6188},
                                             {30.1034,   6.84951},
                                             {67.9249,   81.7641},
                                             {18.124,    13.8424},
                                             {30.37,     83.3812},
                                             {78.4534,   5.45987},
                                             {58.7466,   62.8278},
                                             {81.0678,   99.7712},
                                             {36.3039,   51.9566},
                                             {13.4503,   14.7014},
                                             {93.9398,   5.03768},
                                             {3.35074,   97.4292},
                                             {51.2937,   67.2527},
                                             {23.121,    96.8925},
                                             {2.6824,    22.0851},
                                             {70.3981,   89.2556},
                                             {96.9214,   18.0042},
                                             {15.5337,   20.8321},
                                             {2.9289,    23.831},
                                             {55.2331,   98.4022},
                                             {48.6127,   75.925},
                                             {97.6015,   82.1536},
                                             {28.5146,   9.32537},
                                             {65.5428,   99.6172},
                                             {57.7356,   88.6741},
                                             {30.4328,   98.422},
                                             {53.5585,   32.1111},
                                             {78.2692,   87.4146},
                                             {36.2498,   15.5631},
                                             {86.2125,   31.574},
                                             {72.6494,   18.5107},
                                             {15.9809,   71.1104},
                                             {79.9528,   18.8776},
                                             {95.8912,   57.5717},
                                             {19.1945,   83.1187},
                                             {85.4813,   90.8645},
                                             {0.535883,  16.9646},
                                             {90.1749,   32.5107},
                                             {33.7229,   6.16616},
                                             {61.3879,   61.6843},
                                             {52.1935,   99.1992},
                                             {66.5319,   64.5537},
                                             {38.7331,   13.5774},
                                             {72.4131,   4.18574},
                                             {56.7342,   0.904173},
                                             {2.42403,   76.8301},
                                             {74.6995,   32.1222},
                                             {42.7045,   78.8734},
                                             {27.6457,   35.5688},
                                             {78.4567,   63.6274},
                                             {69.373,    60.346},
                                             {30.4035,   57.1154},
                                             {68.0604,   83.2466},
                                             {18.3984,   30.1898},
                                             {92.6636,   75.518},
                                             {82.9953,   79.4369},
                                             {24.2433,   72.1067},
                                             {68.8433,   19.6021},
                                             {59.2098,   67.284},
                                             {19.6215,   38.1248},
                                             {44.7921,   78.7378},
                                             {98.635,    81.4782},
                                             {54.0822,   63.3877},
                                             {82.3474,   45.3408},
                                             {36.9629,   74.3064},
                                             {99.1664,   41.6349},
                                             {54.7755,   11.5794},
                                             {1.6549,    16.2842},
                                             {45.5053,   31.0424},
                                             {95.3892,   46.811},
                                             {13.5043,   94.6741},
                                             {78.8649,   84.8918},
                                             {70.7936,   92.5668},
                                             {47.482,    78.3515},
                                             {85.4279,   45.1295},
                                             {80.0785,   62.3988},
                                             {56.8968,   17.99},
                                             {47.1287,   44.6122},
                                             {97.1776,   36.5135},
                                             {41.8835,   55.1614},
                                             {69.3776,   1.51687},
                                             {95.6701,   60.8211},
                                             {61.2499,   71.3528},
                                             {93.7137,   58.4853},
                                             {75.8393,   29.923},
                                             {29.1015,   70.646},
                                             {94.9971,   81.329},
                                             {80.2904,   48.794},
                                             {61.1795,   36.4972},
                                             {89.5505,   78.197},
                                             {21.0045,   56.2426},
                                             {57.3895,   91.9556},
                                             {60.2501,   80.2659},
                                             {3.1372,    6.01131},
                                             {83.3309,   76.6338},
                                             {89.6948,   84.8126},
                                             {94.6815,   98.7667},
                                             {67.7797,   0.566544},
                                             {44.5655,   78.0694},
                                             {79.6607,   36.8397},
                                             {86.1321,   12.0619},
                                             {54.1405,   60.5444},
                                             {43.222,    5.08262},
                                             {10.8748,   78.6901},
                                             {76.5377,   5.55969},
                                             {38.3633,   63.1585},
                                             {18.2938,   49.016},
                                             {1.74403,   98.8066},
                                             {87.6666,   51.9191},
                                             {45.1544,   3.78205},
                                             {72.8643,   47.6818},
                                             {3.99084,   28.528},
                                             {21.8974,   86.7655},
                                             {62.4534,   11.5589},
                                             {40.2271,   72.8754},
                                             {28.1271,   32.1194},
                                             {55.6084,   31.9765},
                                             {51.9716,   32.619},
                                             {83.8261,   55.2029},
                                             {61.5212,   18.3005},
                                             {86.8595,   59.6967},
                                             {35.3337,   68.9809},
                                             {66.2933,   15.0923},
                                             {77.834,    24.3472},
                                             {23.4887,   28.1899},
                                             {11.2463,   64.0209},
                                             {24.4862,   30.3409},
                                             {89.7877,   15.9924},
                                             {71.9092,   59.6425},
                                             {39.3255,   44.3583},
                                             {4.14156,   18.0892},
                                             {89.3804,   95.6322},
                                             {32.9924,   87.3483},
                                             {77.2834,   96.9112},
                                             {38.7185,   86.079},
                                             {15.8949,   80.14},
                                             {56.4375,   54.1071},
                                             {53.5637,   5.48071},
                                             {38.07,     88.7811},
                                             {85.994,    92.0713},
                                             {98.654,    37.9343},
                                             {39.8664,   1.8804},
                                             {69.2397,   47.3344},
                                             {56.4525,   39.9578},
                                             {84.8978,   7.78398},
                                             {94.0713,   17.3088},
                                             {83.603,    66.721},
                                             {51.9521,   31.9656},
                                             {36.4759,   38.9922},
                                             {25.6011,   78.259},
                                             {82.4097,   89.7701},
                                             {14.6231,   10.3206},
                                             {57.8371,   10.8474},
                                             {31.9866,   91.337},
                                             {45.1702,   69.1001},
                                             {19.6586,   38.1546},
                                             {70.4259,   92.247},
                                             {83.9766,   82.4104},
                                             {23.4047,   33.4937},
                                             {64.9343,   30.3875},
                                             {61.9492,   58.3183},
                                             {48.2892,   64.6666},
                                             {34.9896,   36.1434},
                                             {87.5197,   1.63321},
                                             {58.209,    6.54644},
                                             {31.3704,   10.4431},
                                             {80.6326,   25.5126},
                                             {32.2227,   24.1913},
                                             {60.9054,   10.3331},
                                             {9.47113,   73.0982},
                                             {77.6801,   47.0104},
                                             {54.4282,   33.135},
                                             {57.6825,   3.0238},
                                             {12.4991,   94.2986},
                                             {42.3677,   26.8044},
                                             {6.96739,   95.3772},
                                             {8.32511,   78.1047},
                                             {10.9701,   42.1142},
                                             {23.1443,   95.0459},
                                             {90.247,    95.1189},
                                             {93.6337,   47.8085},
                                             {91.745,    92.9818},
                                             {46.8578,   64.0551},
                                             {82.2971,   31.216},
                                             {11.9403,   64.8722},
                                             {27.3194,   44.9561},
                                             {69.0258,   44.3677},
                                             {48.8881,   60.2777},
                                             {83.6917,   53.4492},
                                             {55.0114,   37.2489},
                                             {76.2807,   2.64673},
                                             {74.919,    52.5127},
                                             {92.3231,   98.1703},
                                             {51.5434,   82.2839},
                                             {77.0169,   49.1342},
                                             {56.8011,   88.2674},
                                             {95.5137,   5.45349},
                                             {12.8494,   37.2523},
                                             {20.4822,   65.9641},
                                             {34.486,    69.8054},
                                             {68.8943,   28.5757},
                                             {87.7374,   83.2844},
                                             {90.8742,   93.0875},
                                             {55.4471,   46.0415},
                                             {48.201,    70.9323},
                                             {12.0156,   2.28144},
                                             {63.7241,   66.9834},
                                             {59.4728,   55.8664},
                                             {26.8049,   19.4461},
                                             {6.40219,   0.0115707},
                                             {77.7931,   67.8516},
                                             {92.4814,   72.6288},
                                             {23.0444,   12.8998},
                                             {31.2432,   82.3395},
                                             {61.3378,   62.4861},
                                             {68.3584,   47.06},
                                             {78.5434,   83.6026},
                                             {32.3504,   47.0262},
                                             {7.42058,   87.0713},
                                             {36.1475,   6.69166},
                                             {41.4605,   72.4982},
                                             {11.6519,   92.1234},
                                             {75.2648,   97.2307},
                                             {50.0599,   6.6611},
                                             {52.2775,   6.9416},
                                             {27.5837,   73.7241},
                                             {62.2453,   51.6944},
                                             {24.5406,   75.7997},
                                             {84.5825,   35.7484},
                                             {76.4818,   9.27604},
                                             {5.75374,   54.4536},
                                             {4.74073,   57.126},
                                             {71.711,    33.9005},
                                             {72.3303,   88.9669},
                                             {64.7368,   95.6514},
                                             {11.1614,   39.9468},
                                             {26.2573,   19.7266},
                                             {23.7136,   40.2596},
                                             {82.8662,   80.3185},
                                             {78.4856,   42.7389},
                                             {92.7576,   61.4066},
                                             {52.5367,   51.8234},
                                             {4.93558,   79.7008},
                                             {10.2295,   44.4961},
                                             {78.8974,   3.15597},
                                             {79.0038,   42.2985},
                                             {81.6464,   9.81424},
                                             {28.2212,   52.3019},
                                             {20.9923,   89.0686},
                                             {63.6079,   81.9958}
                                         });
