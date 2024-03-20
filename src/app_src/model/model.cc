#include "model.h"

namespace viewer {

Model::Model()
    : parser_(new Parser()), data_(new Data), affine_(new Affine()){};

Model::~Model() {
  delete parser_;
  delete data_;
  delete affine_;
};

void Model::ReadData(const std::string& filename) {
  try {
    ResetScale();
    parser_->Parse(filename, data_);
    this->error_ = "ok";
  } catch (std::invalid_argument& ex) {
    if (std::string(ex.what()) == "file doesn't exist") {
      this->error_ = "file doesn't exist";
    }
  }
};

void Model::InitStrategy(const int& status) { affine_->InitStrategy(status); };

void Model::LetsTransform(const float& value) {
  affine_->MakeTransform(value, data_->GetToTransformVertex());
};

Data* Model::GetData() { return data_; };

const std::string& Model::GetError() const { return error_; }

void Model::ResetScale() { affine_->ResetScale(); }

}  // namespace viewer
