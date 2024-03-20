#ifndef APP_SRC_VIEW_OGL_MODULE_H
#define APP_SRC_VIEW_OGL_MODULE_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../controller/controller.h"
#include "app_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace viewer {
/// @brief Open GL class.
class OGL_Module : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  /// @brief Open GL class constructor.
  explicit OGL_Module(viewer::AppSettings *s, viewer::Controller *c)
      : QOpenGLWidget(), projection(false), settings(s), controller(c){};
  /// @brief Open GL class destructor.
  ~OGL_Module(){};

  /// @brief Sets projection type to central.
  void SetProjectionCentr();
  /// @brief Sets projection type to parallel.
  void SetProjectionParallel();

 protected:
  void initializeGL() override;
  void paintGL() override;

 private:
  GLuint vertexBufferID;
  GLuint indexBufferID;
  bool projection;
  void initVertexBuffers();
  void drawModel();
  void initProjection();
  viewer::AppSettings *settings;
  viewer::Controller *controller;
};

}  // namespace viewer

#endif  // APP_SRC_VIEW_OGL_MODULE_H