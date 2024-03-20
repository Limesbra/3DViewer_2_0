#ifndef APP_SRC_MODEL_PARSER_H
#define APP_SRC_MODEL_PARSER_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "data.h"

namespace viewer {

/// @brief The class that implements methods for data parsing.
class Parser {
 public:
  /// @brief Default constructor.
  Parser(){};

  /// @brief Default destructor.
  ~Parser();

  /// @brief File parsing function.
  void Parse(const std::string& filename, Data* data);

  /// @brief Clear all data.
  void ClearData(Data* data);

 private:
  /// @brief Recording vertex coordinates.
  void PushVertex(std::string& line, Data* data);

  /// @brief Writing vertex indices.
  void PushIndex(std::string& line, Data* data);

  /// @brief Calculation of the number of vertices.
  void NumberOfVertex(Data* data);

  /// @brief Calculation of the number of edges.
  void CountOfEdges(Data* data);

  /// @brief Eliminating negative indices.
  // void FixNegativeNumbers(Data* _data);
  void FixNegative(Data* data, int& num);

  /// @brief Set start scale for model.
  void SetStartScale(Data* data);
};

}  // namespace viewer

#endif  // APP_SRC_MODEL_PARSER_H