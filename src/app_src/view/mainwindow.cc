#include "mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "ui_mainwindow.h"

namespace viewer {

MainWindow::MainWindow(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);
  settings = new AppSettings();
  init_mediators();
  ogl = new OGL_Module(settings, controller);
  scrn_mngr = new ScrnShotManager(ogl);
  ui->OGL_Container->addWidget(ogl);
  ButtonsConnect();
}

MainWindow::~MainWindow() {
  delete ui;
  delete settings;
  delete ogl;
  delete scrn_mngr;
  for (ButtonMediator *button : buttons) {
    delete button;
  }
  for (SliderMediator *slider : sliders) {
    delete slider;
  }
  for (ExtSliderMediator *slider : aff_sliders) {
    delete slider;
  }
}

void MainWindow::show_file_dialog() {
  QFileDialog dialog;
  dialog.setFileMode(QFileDialog::ExistingFile);
  if (dialog.exec()) {
    QStringList files = dialog.selectedFiles();
    filepath = files.at(0);
    load_model();
  }
}

void MainWindow::load_model() {
  ui->lbl_filename->setText(
      "File: " +
      filepath.right(filepath.length() - filepath.lastIndexOf('/') - 1));
  controller->LoadData(filepath.toStdString());
  ui->lbl_edges->setText("Edges: " +
                         QString::number(controller->SendData()->GetEdges()));
  ui->lbl_verts->setText("Vertices: " +
                         QString::number(controller->SendData()->GetVertex()));
  controller->GetMD()->set_default_affine_sets();
  for (ExtSliderMediator *mediator : aff_sliders) {
    mediator->init_ui();
  }
}

// функция с коннектами
void MainWindow::ButtonsConnect() {
  connect(ui->btn_pr_t_central, &QPushButton::clicked, this->ogl,
          &OGL_Module::SetProjectionCentr);
  connect(ui->btn_pr_t_parallel, &QPushButton::clicked, this->ogl,
          &OGL_Module::SetProjectionParallel);
  connect(ui->btn_select_file, &QPushButton::clicked, this,
          &MainWindow::show_file_dialog);
  connect(ui->btn_screenshot_bmp, &QPushButton::clicked, this->scrn_mngr,
          &ScrnShotManager::get_bmp);
  connect(ui->btn_screenshot_jpg, &QPushButton::clicked, this->scrn_mngr,
          &ScrnShotManager::get_jpeg);
  connect(ui->btn_screencast, &QPushButton::clicked, this->scrn_mngr,
          &ScrnShotManager::get_screencast);
}

void MainWindow::init_mediators() {
  // clang-format off
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_mx, ui->b_mx, controller, controller->GetMD()->link_mv_x(), 1, 0.01));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_my, ui->b_my, controller, controller->GetMD()->link_mv_y(), 2, 0.01));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_mz, ui->b_mz, controller, controller->GetMD()->link_mv_z(), 3, 0.01));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_rx, ui->b_rx, controller ,controller->GetMD()->link_rt_x(), 4, 1));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_ry, ui->b_ry, controller,controller->GetMD()->link_rt_y(), 5, 1));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_rz, ui->b_rz, controller,controller->GetMD()->link_rt_z(), 6, 1));
  aff_sliders.push_back(new ExtSliderMediator(ui->sl_sc, ui->b_sc, controller, controller->GetMD()->link_scale(), 7, 0.01));
  sliders.push_back(new SliderMediator(ui->slider_dot_size, ui->spinbox_dot_size, settings->link_dot_size()));
  sliders.push_back(new SliderMediator(ui->slider_line_size, ui->spinbox_line_size, settings->link_line_width()));
  sliders.push_back(new SliderMediator(ui->slider_dot_r, ui->spinbox_dot_r, settings->link_dot_color_r()));
  sliders.push_back(new SliderMediator(ui->slider_dot_g, ui->spinbox_dot_g, settings->link_dot_color_g()));
  sliders.push_back(new SliderMediator(ui->slider_dot_b, ui->spinbox_dot_b, settings->link_dot_color_b()));
  sliders.push_back(new SliderMediator(ui->slider_line_r, ui->spinbox_line_r, settings->link_line_color_r()));
  sliders.push_back(new SliderMediator(ui->slider_line_g, ui->spinbox_line_g, settings->link_line_color_g()));
  sliders.push_back(new SliderMediator(ui->slider_line_b, ui->spinbox_line_b, settings->link_line_color_b()));
  sliders.push_back(new SliderMediator(ui->slider_bg_r, ui->spinbox_bg_r, settings->link_background_color_r()));
  sliders.push_back(new SliderMediator(ui->slider_bg_g, ui->spinbox_bg_g, settings->link_background_color_g()));
  sliders.push_back(new SliderMediator(ui->slider_bg_b, ui->spinbox_bg_b, settings->link_background_color_b()));
  buttons.push_back(new ButtonMediator(ui->btn_pr_t_central, ui->btn_pr_t_parallel, settings->link_projection()));
  buttons.push_back(new ButtonMediator(ui->btn_line_t_solid, ui->btn_line_t_dashed, settings->link_line_type()));
  buttons.push_back(new ButtonMediator(ui->btn_dot_t_none, ui->btn_dot_t_circle, ui->btn_dot_t_square, settings->link_dot_type()));
  // clang-format on
}

}  // namespace viewer
