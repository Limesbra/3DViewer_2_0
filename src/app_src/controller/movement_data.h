#ifndef APP_SRC_CONTROLLER_MOVEMENT_DATA_H
#define APP_SRC_CONTROLLER_MOVEMENT_DATA_H

namespace viewer {

/// @brief Movement data class (reflects parameters used for affine
/// transformation).
class MovementData {
 public:
  /// @brief Movement data class constructor.
  MovementData() { set_default_affine_sets(); };
  /// @brief Movement data class destructor.
  ~MovementData(){};

  /// @brief sets affine parameters to default values.
  void set_default_affine_sets() {
    _move_x = 0;
    _move_y = 0;
    _move_z = 0;
    _rotation_x = 0;
    _rotation_y = 0;
    _rotation_z = 0;
    _scale = 100;
  }

  /// @brief Getter for affine parameters (x axis movement).
  const double& get_mv_x() const { return _move_x; }
  /// @brief Getter for affine parameters (y axis movement).
  const double& get_mv_y() const { return _move_y; };
  /// @brief Getter for affine parameters (z axis movement).
  const double& get_mv_z() const { return _move_z; };
  /// @brief Getter for affine parameters (x axis rotation).
  const double& get_rt_x() const { return _rotation_x; }
  /// @brief Getter for affine parameters (y axis rotation).
  const double& get_rt_y() const { return _rotation_y; }
  /// @brief Getter for affine parameters (z axis rotation).
  const double& get_rt_z() const { return _rotation_z; }
  /// @brief Getter for affine parameters (scaling).
  const double& get_sc() const { return _scale; }

  /// @brief Setter for affine parameters (x axis movement). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_mv_x() { return _move_x; }
  /// @brief Setter for affine parameters (y axis movement). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_mv_y() { return _move_y; }
  /// @brief Setter for affine parameters (z axis movement). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_mv_z() { return _move_z; }
  /// @brief Setter for affine parameters (x axis rotation). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_rt_x() { return _rotation_x; }
  /// @brief Setter for affine parameters (y axis rotation). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_rt_y() { return _rotation_y; }
  /// @brief Setter for affine parameters (z axis rotation). Returns lvalue
  /// reference to variable used in mediator pattern.
  double& link_rt_z() { return _rotation_z; }
  /// @brief Setter for affine parameters (scaling). Returns lvalue reference to
  /// variable used in mediator pattern.
  double& link_scale() { return _scale; }

  //  private:
  double _move_x;
  double _move_y;
  double _move_z;
  double _rotation_x;
  double _rotation_y;
  double _rotation_z;
  double _scale;
};

}  // namespace viewer

#endif  // APP_SRC_CONTROLLER_MOVEMENT_DATA_H