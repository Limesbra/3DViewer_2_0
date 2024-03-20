#ifndef APP_SRC_VIEW_MAINWINDOW_H
#define APP_SRC_VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

#include "../controller/controller.h"
#include "../model/data.h"
#include "../model/model.h"
#include "app_settings.h"
#include "mediators.h"
#include "ogl_module.h"
#include "screenshots.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace viewer {

/// @brief Application window class.
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /// @brief Application window class constructor.
  explicit MainWindow(Controller *c, QWidget *parent = nullptr);
  /// @brief Application window class destructor.
  ~MainWindow();

 private:
  void show_file_dialog();
  void load_model();
  void ButtonsConnect();
  void init_mediators();
  Ui::MainWindow *ui;
  Controller *controller;
  AppSettings *settings;
  ScrnShotManager *scrn_mngr;
  OGL_Module *ogl;
  QString filepath;

  std::vector<ExtSliderMediator *> aff_sliders;
  std::vector<SliderMediator *> sliders;
  std::vector<ButtonMediator *> buttons;
};

}  // namespace viewer

#endif  // APP_SRC_VIEW_MAINWINDOW_H
