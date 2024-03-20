#ifndef APP_SRC_VIEW_APP_SETTINGS_H
#define APP_SRC_VIEW_APP_SETTINGS_H

#include <QCoreApplication>
#include <QString>
#include <fstream>
#include <iostream>

namespace viewer {

typedef struct {
  int r;
  int g;
  int b;
} RgbType;

/// @brief Application setting class (used to manage settings, load and save it
/// to file).
class AppSettings {
 public:
  /// @brief Application setting class constructor.
  AppSettings() { init_settings(); };
  /// @brief Application setting destructor.
  ~AppSettings() { save_settings_to_file(); };

  /// @brief Setter for projection type. Returns lvalue reference to variable
  /// used in mediator pattern.
  int& link_projection() { return _projection; }
  /// @brief Setter for dot type. Returns lvalue reference to variable used in
  /// mediator pattern.
  int& link_dot_type() { return _dot_type; }
  /// @brief Setter for dot size. Returns lvalue reference to variable used in
  /// mediator pattern.
  int& link_dot_size() { return _dot_size; }
  /// @brief Setter for line type. Returns lvalue reference to variable used in
  /// mediator pattern.
  int& link_line_type() { return _line_type; }
  /// @brief Setter for line width. Returns lvalue reference to variable used in
  /// mediator pattern.
  int& link_line_width() { return _line_width; }
  /// @brief Setter for background color (red component). Returns lvalue
  /// reference to variable used in mediator pattern.
  int& link_background_color_r() { return _background_color.r; }
  /// @brief Setter for background color (green component). Returns lvalue
  /// reference to variable used in mediator pattern.
  int& link_background_color_g() { return _background_color.g; }
  /// @brief Setter for background color (blue component). Returns lvalue
  /// reference to variable used in mediator pattern.
  int& link_background_color_b() { return _background_color.b; }
  /// @brief Setter for dot color (red component). Returns lvalue reference to
  /// variable used in mediator pattern.
  int& link_dot_color_r() { return _dot_color.r; }
  /// @brief Setter for dot color (green component). Returns lvalue reference to
  /// variable used in mediator pattern.
  int& link_dot_color_g() { return _dot_color.g; }
  /// @brief Setter for dot color (blue component). Returns lvalue reference to
  /// variable used in mediator pattern.
  int& link_dot_color_b() { return _dot_color.b; }
  /// @brief Setter for line color (red component). Returns lvalue reference to
  /// variable used in mediator pattern.
  int& link_line_color_r() { return _line_color.r; }
  /// @brief Setter for line color (green component). Returns lvalue reference
  /// to variable used in mediator pattern.
  int& link_line_color_g() { return _line_color.g; }
  /// @brief Setter for line color (blue component). Returns lvalue reference to
  /// variable used in mediator pattern.
  int& link_line_color_b() { return _line_color.b; }

  /// @brief Getter for projection type.
  int get_projection() { return _projection; }
  /// @brief Getter for dot type.
  int get_dot_type() { return _dot_type; }
  /// @brief Getter for dot size.
  int get_dot_size() { return _dot_size; }
  /// @brief Getter for line type.
  int get_line_type() { return _line_type; }
  /// @brief Getter for line width.
  float get_lw() { return static_cast<float>(_line_width); }
  /// @brief Setter for background color (red component).
  float get_bgc_r() { return static_cast<float>(_background_color.r) / 255.0f; }
  /// @brief Setter for background color (green component).
  float get_bgc_g() { return static_cast<float>(_background_color.g) / 255.0f; }
  /// @brief Setter for background color (blue component).
  float get_bgc_b() { return static_cast<float>(_background_color.b) / 255.0f; }
  /// @brief Setter for dot color (red component).
  float get_dc_r() { return static_cast<float>(_dot_color.r) / 255.0f; }
  /// @brief Setter for dot color (green component).
  float get_dc_g() { return static_cast<float>(_dot_color.g) / 255.0f; }
  /// @brief Setter for dot color (blue component).
  float get_dc_b() { return static_cast<float>(_dot_color.b) / 255.0f; }
  /// @brief Setter for line color (red component).
  float get_lc_r() { return static_cast<float>(_line_color.r) / 255.0f; }
  /// @brief Setter for line color (green component).
  float get_lc_g() { return static_cast<float>(_line_color.g) / 255.0f; }
  /// @brief Setter for line color (blue component).
  float get_lc_b() { return static_cast<float>(_line_color.b) / 255.0f; }

 private:
  void init_settings();
  void get_settings_from_file();
  void save_settings_to_file();
  void validate_value(int& c_value, int min, int max, int p_value);
  int parse_value(std::string key);
  std::string _settings_path =
      QCoreApplication::applicationDirPath().toStdString() + "/settings";

  // default settings
  int _projection = 0;
  int _dot_type = 0;
  int _dot_size = 1;
  int _line_type = 0;
  int _line_width = 1;
  RgbType _background_color = {115, 149, 235};
  RgbType _dot_color = {255, 30, 0};
  RgbType _line_color = {255, 255, 255};
};

}  // namespace viewer

#endif  // APP_SRC_VIEW_APP_SETTINGS_H