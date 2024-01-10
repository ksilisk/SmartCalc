#include <gtest/gtest.h>

#include "../backend/calculator.hpp"
#include "../backend/parser.hpp"

using namespace s21;

Parser parser;
Calculator model(parser);

TEST(SC, test_1) {
  double result = model.calculate(
      "-(1+3*(5mod(3)+100))/50/1*20+(50^2*(5+3^2)mod(3*2)+31*20/"
      "(10*5^(2+1)))+39^2*48*10*123-50-10",
      0);
  ASSERT_EQ(result, 89799659.695999995);
}

TEST(SC, test_1_with_spaces) {
  double result = model.calculate(
      "-(1+3 *(5mod(3)+ 100))/50 / 1*20+( 50^2*(5+3^2  "
      ")mod(3*2)+31*20/(10*5^(2+1)) )+39^2*48*10*123-50-10",
      0);
  ASSERT_EQ(result, 89799659.695999995);
}

TEST(SC, test_2_long_values) {
  double result = model.calculate("15120.150+4961254.9271/2.5^2", 0);
  ASSERT_EQ(result, 808920.938336);
}

TEST(SC, test_3_functions) {
  double result = model.calculate(
      "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)", 0);
  ASSERT_EQ(result, 1.593531);
}

TEST(SC, test_4_log_ln_sqrt) {
  double result =
      model.calculate("(ln(50)+100)mod(2+2.5)+(log(100)*20)^(2+2)+sqrt(25)", 0);
  ASSERT_EQ(result, 2560005.412023);
}

TEST(SC, test_5_unary_minis) {
  double result = model.calculate("-(cos(20)+10)mod(2)", 0);
  ASSERT_EQ(result, -0.408082);
}

TEST(SC, test_2) {
  double result = model.calculate("(1 + 2 + 4 * 3 - 3 * 7) / 4", 0);
  ASSERT_EQ(result, -1.5);
}

TEST(SC, test_3) {
  double result = model.calculate(
      "acos(cos(sin(atan(ln(sqrt((8 * ((1 + 2 + 4 * 3 - 3 * 7) / 4)) + "
      "133))))))",
      0);
  ASSERT_EQ(result, 0.922957);
}

TEST(SC, test_4) {
  double result = model.calculate("(-4 + 5) * 2", 0);
  ASSERT_EQ(result, 2);
}

TEST(SC, test_5) {
  double result = model.calculate("asin(0.2)", 0);
  ASSERT_EQ(result, 0.201358);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}