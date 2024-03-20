#ifndef APP_SRC_MODEL_AFFINE_H
#define APP_SRC_MODEL_AFFINE_H

#include <cmath>
#include <vector>

namespace viewer {

/// @brief Abstract parent class strategy_.
class StrategyMode {
 public:
  /// @brief virtual destructor.
  virtual ~StrategyMode() {}

  /// @brief pure virtual function for affine transformations.
  virtual void Transform(std::vector<float>& data, float value) = 0;
};

/// @brief Child class. x-Shift Strategy.
class StrategyMove_x : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    for (size_t i = 0; i <= data.size(); i += 3) {
      data[i] += value;  // сдвиг по оси X
    }
  }
};

/// @brief Child class. y-Shift Strategy.
class StrategyMove_y : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    for (size_t i = 1; i < data.size(); i += 3) {
      data[i] += value;  // сдвиг по оси Y
    }
  }
};

/// @brief Child class. z-Shift Strategy.
class StrategyMove_z : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    for (size_t i = 2; i < data.size(); i += 3) {
      data[i] += value;  // сдвиг по оси Z
    }
  }
};

/// @brief Child class. x-Rotate Strategy.
class StrategyRotate_x : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    value = value * M_PI / 180;
    for (size_t i = 0; i < data.size(); i += 3) {
      auto temp_y = data[i + 1];
      auto temp_z = data[i + 2];
      data[i + 1] = temp_y * std::cos(value) - temp_z * std::sin(value);
      data[i + 2] = temp_y * std::sin(value) + temp_z * std::cos(value);
    }
  };
};

/// @brief Child class. y-Rotate Strategy.
class StrategyRotate_y : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    value = value * M_PI / 180;
    for (size_t i = 0; i < data.size(); i += 3) {
      auto temp_x = data[i];
      auto temp_z = data[i + 2];
      data[i] = temp_x * std::cos(value) + temp_z * std::sin(value);
      data[i + 2] = -temp_x * std::sin(value) + temp_z * std::cos(value);
    }
  };
};

/// @brief Child class. z-Rotate Strategy.
class StrategyRotate_z : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    value = value * M_PI / 180;
    for (size_t i = 0; i < data.size(); i += 3) {
      auto temp_x = data[i];
      auto temp_y = data[i + 1];
      data[i] = temp_x * std::cos(value) - temp_y * std::sin(value);
      data[i + 1] = temp_x * std::sin(value) + temp_y * std::cos(value);
    }
  };
};

/// @brief Child class. Scale Strategy.
class StrategyScale : public StrategyMode {
 public:
  /// @brief Override pure virtual function.
  void Transform(std::vector<float>& data, float value) override {
    new_k_scale += value;
    for (size_t i = 0; i < data.size(); i++) {
      data[i] /= prev_k_scale;  // defaults value
      data[i] *= new_k_scale;   // sets new scale factor
    }
    prev_k_scale = new_k_scale;
  };

  /// @brief Reset scale factor.
  void Reset() {
    new_k_scale = 1;
    prev_k_scale = 1;
  };

 private:
  float prev_k_scale = 1;  // previous scale factor
  float new_k_scale = 1;   // new scale factor
};

/// @brief Class context. Affine transformations.
class Affine {
 public:
  /// @brief constructor.
  Affine() : strategy_(nullptr) {
    strategy_move_x_ = new StrategyMove_x;
    strategy_move_y_ = new StrategyMove_y;
    strategy_move_z_ = new StrategyMove_z;
    strategy_rotate_x_ = new StrategyRotate_x;
    strategy_rotate_y_ = new StrategyRotate_y;
    strategy_rotate_z_ = new StrategyRotate_z;
    strategy_scale_ = new StrategyScale;
  };

  /// @brief destructor.
  ~Affine() {
    strategy_ = nullptr;
    delete strategy_move_x_;
    delete strategy_move_y_;
    delete strategy_move_z_;
    delete strategy_rotate_x_;
    delete strategy_rotate_y_;
    delete strategy_rotate_z_;
    delete strategy_scale_;
    if (strategy_) delete strategy_;
  };

  /// @brief Strategy initialization function.
  void InitStrategy(const int& status) {
    if (status == 1) {
      SetStrategy(strategy_move_x_);
    } else if (status == 2) {
      SetStrategy(strategy_move_y_);
    } else if (status == 3) {
      SetStrategy(strategy_move_z_);
    } else if (status == 4) {
      SetStrategy(strategy_rotate_x_);
    } else if (status == 5) {
      SetStrategy(strategy_rotate_y_);
    } else if (status == 6) {
      SetStrategy(strategy_rotate_z_);
    } else if (status == 7) {
      SetStrategy(strategy_scale_);
    }
  }

  /// @brief Call strategy_ function.
  void MakeTransform(float value, std::vector<float>& data) {
    if (strategy_) {
      strategy_->Transform(data, value);
    }
  }

  void ResetScale() { strategy_scale_->Reset(); }

 private:
  /// @brief Strategy setting function.
  void SetStrategy(StrategyMode* strategy) {
    this->strategy_ = nullptr;
    this->strategy_ = strategy;
  }

  StrategyMove_x* strategy_move_x_;
  StrategyMove_y* strategy_move_y_;
  StrategyMove_z* strategy_move_z_;
  StrategyRotate_x* strategy_rotate_x_;
  StrategyRotate_y* strategy_rotate_y_;
  StrategyRotate_z* strategy_rotate_z_;
  StrategyScale* strategy_scale_;
  StrategyMode* strategy_;
};

}  // namespace viewer

#endif