#ifndef APP_SRC_CONTROLLER_CONTROLLER_H
#define APP_SRC_CONTROLLER_CONTROLLER_H

#include "../model/model.h"
#include "movement_data.h"

namespace viewer {

/// @brief 3D Wiever 2.0 Controller class.
class Controller {
 public:
  /// @brief 3D Wiever 2.0 Controller constructor.
  Controller()
      : _model(nullptr),
        _model_status(false),
        _movement_data(new MovementData()){};
  /// @brief 3D Wiever 2.0 Controller parametrized constructor.
  explicit Controller(Model* model)
      : _model(model),
        _model_status(false),
        _movement_data(new MovementData()){};
  /// @brief 3D Wiever 2.0 Controller destructor.
  ~Controller() { delete _movement_data; };

  /// @brief Loads model from file(filename is parameter) into model class. Sets
  /// status true (some ui features are disabled until that).
  void LoadData(const std::string& filename) {
    _model->ReadData(filename);
    _model_status = true;
  };

  /// @brief Abstract fucntion for affine transformation.
  void Transformation(const int& status, const float& value) {
    if (_model_status == true) {
      _model->InitStrategy(status);
      _model->LetsTransform(value);
    }
  };

  /// @brief Getter for data class (innner class in model).
  Data* SendData() { return _model->GetData(); };
  /// @brief Getter for model status.
  bool model_loaded() { return _model_status; }
  /// @brief Getter for movement data class (reflects parameters used for affine
  /// transformation).
  MovementData* GetMD() { return _movement_data; };

 private:
  Model* _model;
  bool _model_status;
  MovementData* _movement_data;
};

}  // namespace viewer

#endif // APP_SRC_CONTROLLER_CONTROLLER_H