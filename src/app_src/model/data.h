#ifndef APP_SRC_MODEL_DATA_H
#define APP_SRC_MODEL_DATA_H

#include <algorithm>
#include <vector>

namespace viewer {

/// @brief Class for storing data.
class Data {
 public:
  /// @brief Default constructor.
  Data() = default;
  /// @brief Default destructor.
  ~Data() = default;

  /// @brief Getter vector veretexData.
  const std::vector<float>& GetVertexData() const;

  /// @brief Getter vector indexData.
  const std::vector<int>& GetIndexData() const;

  /// @brief Getter for number of vertices.
  const int& GetVertex() const;

  /// @brief Getter for number of faces.
  const int& GetEdges() const;

  /// @brief Getter for max vertex.
  float GetMaxValue() const;

  /// @brief Getter for max edge.
  int& GetMaxIndex();

  /// @brief Converting data into a vertexData vector.
  std::vector<float>& GetToTransformVertex();

  /// @brief Converting data into a indexData vector.
  std::vector<int>& GetToTransformIndex();

  /// @brief Adding a value to a vector veretexData.
  void SetVertexData(const float& f);

  /// @brief Adding a value to a vector indexData.
  void SetIndexData(const unsigned int& u);

  /// @brief Determining and setting the number of vertices.
  void SetVertex();

  /// @brief Determining and setting the number of edges.
  void SetEdges();

  /// @brief Writes the maximum coordinate modulo.
  void SetMaxValue(const float& f);

  /// @brief Writes the maximum index modulo.
  void SetMaxIndex(const int& i);

  /// @brief Determining whether the vector indexData is empty.
  bool EmptyIndexData();

  /// @brief Clear all data.
  void ClearAll();

 private:
  int vertex_;
  int edges_;
  float max_vertex_;
  int max_index_;
  std::vector<float> vertex_data_;
  std::vector<int> index_data_;
};

}  // namespace viewer

#endif  // APP_SRC_MODEL_DATA_H