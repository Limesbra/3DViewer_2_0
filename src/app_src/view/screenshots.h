#ifndef APP_SRC_VIEW_SCREENSHOTS_H
#define APP_SRC_VIEW_SCREENSHOTS_H

#include <QDateTime>
#include <QImage>
#include <QMovie>
#include <QTimer>
#include <chrono>
#include <filesystem>
#include <string>
#include <thread>

#include "../external/gif.h"
#include "ogl_module.h"

namespace s21 {

/// @brief Screen shot manager class.
class ScrnShotManager : public QObject {
 public:
  /// @brief Screen shot manager class constructor.
  explicit ScrnShotManager(OGL_Module* o) : _ogl(o){};
  /// @brief Screen shot manager class destructor.
  ~ScrnShotManager(){};
  /// @brief Takes a jpeg screenshot.
  void get_jpeg() {
    check_folder();
    QImage image = _ogl->grabFramebuffer();
    image.save(make_filename(".jpeg"), "JPG");
  }
  /// @brief Takes a bmp screenshot.
  void get_bmp() {
    check_folder();
    QImage image = _ogl->grabFramebuffer();
    image.save(make_filename(".bmp"), "BMP");
  }
  /// @brief Takes a short gif screencast.
  void get_screencast() {
    check_folder();
    std::vector<QImage> images;
    for (int i = 0; i < 50; ++i) {
      QImage frame =
          _ogl->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio);
      images.push_back(frame);
      shortDelay(100);
    }
    QString filename = make_filename(".gif");
    GifWriter g_writer = GifWriter();
    GifBegin(&g_writer, filename.toStdString().c_str(), 640, 480, 10, 8, false);
    for (QImage image : images) {
      GifWriteFrame(&g_writer,
                    image.convertToFormat(QImage::Format_Indexed8)
                        .convertToFormat(QImage::Format_RGBA8888)
                        .constBits(),
                    640, 480, 10, 8, false);
    }
    GifEnd(&g_writer);
  }

 private:
  void check_folder() {
    if (!std::filesystem::exists(_folder_path)) {
      std::filesystem::create_directory(_folder_path);
    }
  }

  QString make_filename(QString extension) {
    QString path = QString::fromStdString(_folder_path);
    QString filename =
        QDateTime::currentDateTime().toString("dd_MM_yyyy-hh:mm:ss") +
        extension;
    path += "/" + filename;
    return path;
  }

  void shortDelay(int interval) {
    QTimer timer;
    timer.setSingleShot(true);
    timer.setInterval(interval);
    QEventLoop loop;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
  }

  std::string _folder_path =
      QCoreApplication::applicationDirPath().toStdString() + "/screenshots";
  OGL_Module* _ogl;
};

}  // namespace viewer

#endif  // APP_SRC_VIEW_SCREENSHOTS_H