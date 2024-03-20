#ifndef APP_SRC_MODEL_MODEL_H
#define APP_SRC_MODEL_MODEL_H

#include <iomanip>
#include <iostream>

#include "affine.h"
#include "parser.h"

namespace viewer {

/// @brief Сlass model stores and accesses basic data and performs operations
/// determined by the business logic of the program based on requests.
class Model {
 public:
  /// @brief Default constructor.
  Model();
  /// @brief Destructor.
  ~Model();

  /*Methods*/
  /// @brief File reading and data parsing function.
  void ReadData(const std::string& filename);

  /// @brief Strategy initialization function.
  void InitStrategy(const int& status);

  /// @brief Strategy call function.
  void LetsTransform(const float& value);

  /// @brief Reset scale.
  void ResetScale();

  /// @brief Function for receiving data.
  Data* GetData();

  /// @brief Function for receiving error_.
  const std::string& GetError() const;

 private:
  /*Fields*/
  Parser* parser_;
  Data* data_;
  Affine* affine_;
  std::string error_;
};

}  // namespace viewer

#endif // APP_SRC_MODEL_MODEL_H