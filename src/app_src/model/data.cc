#ifndef APP_SRC_MODEL_DATA_CC
#define APP_SRC_MODEL_DATA_CC

#include "data.h"

namespace viewer {

const std::vector<float>& Data::GetVertexData() const { return vertex_data_; }

const std::vector<int>& Data::GetIndexData() const { return index_data_; }

const int& Data::GetVertex() const { return this->vertex_; }

const int& Data::GetEdges() const { return this->edges_; }

float Data::GetMaxValue() const { return this->max_vertex_; }

std::vector<float>& Data::GetToTransformVertex() { return vertex_data_; }

std::vector<int>& Data::GetToTransformIndex() { return index_data_; }

void Data::SetVertexData(const float& f) { vertex_data_.push_back(f); }

void Data::SetIndexData(const unsigned int& u) { index_data_.push_back(u); }

void Data::SetVertex() { this->vertex_ = vertex_data_.size() / 3; }

void Data::SetEdges() { this->edges_ = index_data_.size() / 2; }

void Data::SetMaxValue(const float& f) { this->max_vertex_ = f; }

bool Data::EmptyIndexData() { return index_data_.empty(); }

void Data::ClearAll() {
  vertex_data_.clear();
  index_data_.clear();
  vertex_ = edges_ = 0;
  max_vertex_ = 0;
  max_index_ = 0;
}

void Data::SetMaxIndex(const int& i) { max_index_ = i; }

int& Data::GetMaxIndex() { return max_index_; }
}  // namespace viewer

#endif  // APP_SRC_MODEL_DATA_CC