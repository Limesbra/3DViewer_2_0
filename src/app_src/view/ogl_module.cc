#include "ogl_module.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace viewer {

void OGL_Module::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  initVertexBuffers();
}

void OGL_Module::paintGL() {
  glClearColor(settings->get_bgc_r(), settings->get_bgc_g(),
               settings->get_bgc_b(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (controller->model_loaded()) {
    drawModel();
  }
  update();
}

void OGL_Module::initVertexBuffers() {
  glGenBuffers(1, &vertexBufferID);
  glGenBuffers(1, &indexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OGL_Module::SetProjectionCentr() { this->projection = false; }

void OGL_Module::SetProjectionParallel() { this->projection = true; }

void OGL_Module::initProjection() {
  if (this->projection == 1) {         // parallel
    glOrtho(-1, 1, -1, 1, -1, 1);      // l-r-b-t-near-far
  } else if (this->projection == 0) {  // central
    glFrustum(-1, 1, -1, 1, 10, 200);  // l-r-b-t-near-far
    glTranslatef(0.0, 0.0, -15.0);     // shift of the object
  }
}

void OGL_Module::drawModel() {
  glLoadIdentity();
  initProjection();

  std::vector<float> vertexData = controller->SendData()->GetVertexData();
  std::vector<int> indexData = controller->SendData()->GetIndexData();

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexData.size(),
               vertexData.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexData.size(),
               indexData.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glLineWidth(settings->get_lw());

  if (settings->get_dot_type() != 0) {  // dots
    glColor3f(settings->get_dc_r(), settings->get_dc_g(), settings->get_dc_b());
    glPointSize(settings->get_dot_size());  // circle and square
    if (settings->get_dot_type() == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glDrawElements(GL_POINTS, indexData.size(), GL_UNSIGNED_INT, 0);  // vertex
  }

  if (settings->get_line_type()) {  // lines
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x3333);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glColor3f(settings->get_lc_r(), settings->get_lc_g(), settings->get_lc_b());
  glDrawElements(GL_LINES, indexData.size(), GL_UNSIGNED_INT, 0);  //  edges
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}  // namespace viewer
