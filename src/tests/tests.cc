#include <gtest/gtest.h>

#include "../app_src/model/s21_model.h"

namespace s21 {

TEST(Model, test1_open) {
  std::string filename = "tests/box.txt";
  Model model;
  model.ReadData(filename);

  EXPECT_EQ(model.GetError(), "ok");
  EXPECT_EQ(model.GetData()->GetEdges(), 36);
  EXPECT_EQ(model.GetData()->GetVertex(), 8);

  auto v = model.GetData()->GetVertexData();  // float
  auto e = model.GetData()->GetIndexData();   // unsigned int

  std::vector<float> res_v = {1, -1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1};
  std::vector<unsigned int> res_e = {4, 0, 0, 3, 3, 4, 4, 3, 3, 7, 7, 4};

  for (int i = 0; i < 12; i++) {
    EXPECT_NEAR(v[i], res_v[i], 0.0000001f);
  }

  for (int i = 0; i < 12; i++) {
    EXPECT_EQ(e[i], res_e[i]);
  }
}

TEST(Model, test2_open) {
  std::string filename = "aboba.txt";
  Model model;
  model.ReadData(filename);

  EXPECT_EQ(model.GetError(), "file doesn't exist");
}

TEST(Model, test3_move) {
  std::string filename = "tests/box.txt";
  Model model;
  model.ReadData(filename);
  model.InitStrategy(1);
  model.LetsTransform(2.0);
  model.InitStrategy(2);
  model.LetsTransform(2.0);
  model.InitStrategy(3);
  model.LetsTransform(2.0);

  auto v = model.GetData()->GetVertexData();  // float

  std::vector<float> res_v = {3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1};

  for (int i = 0; i < 12; i++) {
    EXPECT_NEAR(v[i], res_v[i], 0.0000001f);
  }
}

TEST(Model, test4_scale) {
  std::string filename = "tests/box.txt";
  Model model;
  model.ReadData(filename);
  model.InitStrategy(7);
  model.LetsTransform(0.5);

  auto v = model.GetData()->GetVertexData();  // float

  std::vector<float> res_v = {1.5,  -1.5, -1.5, 1.5,  -1.5, 1.5,
                              -1.5, -1.5, 1.5,  -1.5, -1.5, -1.5};

  for (int i = 0; i < 12; i++) {
    EXPECT_NEAR(v[i], res_v[i], 0.0000001f);
  }
}

TEST(Model, test5_rotate) {
  std::string filename = "tests/box.txt";
  Model model;
  model.ReadData(filename);
  model.InitStrategy(4);
  model.LetsTransform(30);
  model.InitStrategy(5);
  model.LetsTransform(30);
  model.InitStrategy(6);
  model.LetsTransform(30);

  auto v = model.GetData()->GetVertexData();  // float

  std::vector<float> res_v = {0.3415063,   -0.22548094, -1.6830127,
                              1.5915062,   -0.6584937,  -0.18301272,
                              0.091506362, -1.5245191,  0.81698728,
                              -1.1584936,  -1.0915064,  -0.68301272};

  for (int i = 0; i < 12; i++) {
    EXPECT_NEAR(v[i], res_v[i], 0.0000001f);
  }
}

}  // namespace s21
