#include "app_settings.h"

namespace viewer {

void AppSettings::validate_value(int& c_value, int min, int max, int p_value) {
  if (p_value >= min && p_value <= max) {
    c_value = p_value;
  }
}

void AppSettings::init_settings() {
  std::ifstream file(_settings_path);
  if (file.good()) {
    get_settings_from_file();
    file.close();
  }
}

void AppSettings::get_settings_from_file() {
  validate_value(_projection, 0, 1, parse_value("PROJECTION"));
  validate_value(_dot_type, 0, 1, parse_value("D_TYPE"));
  validate_value(_dot_size, 0, 100, parse_value("D_SIZE"));
  validate_value(_line_type, 0, 1, parse_value("L_TYPE"));
  validate_value(_line_width, 0, 100, parse_value("L_SIZE"));
  validate_value(_background_color.r, 0, 255, parse_value("BG_COLOR_R"));
  validate_value(_background_color.g, 0, 255, parse_value("BG_COLOR_G"));
  validate_value(_background_color.b, 0, 255, parse_value("BG_COLOR_B"));
  validate_value(_dot_color.r, 0, 255, parse_value("D_COLOR_R"));
  validate_value(_dot_color.g, 0, 255, parse_value("D_COLOR_G"));
  validate_value(_dot_color.b, 0, 255, parse_value("D_COLOR_B"));
  validate_value(_line_color.r, 0, 255, parse_value("LN_COLOR_R"));
  validate_value(_line_color.g, 0, 255, parse_value("LN_COLOR_G"));
  validate_value(_line_color.b, 0, 255, parse_value("LN_COLOR_B"));
}

int AppSettings::parse_value(const std::string key) {
  std::ifstream file(_settings_path);
  std::string line;
  std::string result;
  while (std::getline(file, line)) {
    size_t pos = line.find(key);
    if (pos != std::string::npos) {
      result = line.substr(pos + key.size() + 1);
      break;
    }
  }
  return std::stoi(result);
}

void AppSettings::save_settings_to_file() {
  std::ofstream file(_settings_path);
  file << "PROJECTION " << _projection << std::endl;
  file << "D_TYPE " << _dot_type << std::endl;
  file << "D_SIZE " << _dot_size << std::endl;
  file << "L_TYPE " << _line_type << std::endl;
  file << "L_SIZE " << _line_width << std::endl;
  file << "BG_COLOR_R " << _background_color.r << std::endl;
  file << "BG_COLOR_G " << _background_color.g << std::endl;
  file << "BG_COLOR_B " << _background_color.b << std::endl;
  file << "D_COLOR_R " << _dot_color.r << std::endl;
  file << "D_COLOR_G " << _dot_color.g << std::endl;
  file << "D_COLOR_B " << _dot_color.b << std::endl;
  file << "LN_COLOR_R " << _line_color.r << std::endl;
  file << "LN_COLOR_G " << _line_color.g << std::endl;
  file << "LN_COLOR_B " << _line_color.b << std::endl;
  file.close();
}

}  // namespace viewer