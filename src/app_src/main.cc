#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  viewer::Model model;
  viewer::Controller controller(&model);
  viewer::MainWindow window(&controller);
  window.show();
  return application.exec();
}
