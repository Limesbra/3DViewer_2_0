#ifndef APP_SRC_VIEW_MEDIATORS_H
#define APP_SRC_VIEW_MEDIATORS_H

#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <iostream>

#include "../controller/controller.h"

namespace viewer {
/// @brief Abstract extended mediator class to manage interface sliders and
/// spinboxes related with model transformations
class ExtSliderMediator : public QObject {
 public:
  /// @brief Extended slider mediator constructor
  ExtSliderMediator(QSlider *s, QSpinBox *b, s21::Controller *c, double &v,
                    int strategy, double k)
      : _slider(s),
        _box(b),
        _controller(c),
        _value(v),
        _strategy(strategy),
        _k_scale(k) {
    connect(_slider, &QSlider::valueChanged, this,
            &ExtSliderMediator::slider_moved);
    connect(_box, &QSpinBox::editingFinished, this,
            &ExtSliderMediator::entry_changed);
    init_ui();
  };
  /// @brief Extended slider mediator destructor
  ~ExtSliderMediator() {
    disconnect(_slider, &QSlider::valueChanged, this,
               &ExtSliderMediator::slider_moved);
    disconnect(_box, &QSpinBox::editingFinished, this,
               &ExtSliderMediator::entry_changed);
  }

  void init_ui() {
    _slider->setValue(_value);
    _box->setValue(_value);
  }

 private:
  void slider_moved() {
    double prev_v = _value;
    _value = _slider->value();
    _box->setValue(_value);
    _controller->Transformation(_strategy, (_value - prev_v) * _k_scale);
  };
  void entry_changed() {
    double prev_v = _value;
    _value = _box->value();
    _slider->setValue(_value);
    _controller->Transformation(_strategy, (_value - prev_v) * _k_scale);
  };

  QSlider *_slider;
  QSpinBox *_box;
  s21::Controller *_controller;
  double &_value;
  int _strategy;
  double _prev_value;
  double _change;
  double _k_scale;
};

/// @brief Abstract mediator class to manage interface sliders and spinboxes
class SliderMediator : public QObject {
 public:
  /// @brief Slider mediator constructor
  SliderMediator(QSlider *s, QSpinBox *b, int &v)
      : _slider(s), _box(b), _value(v) {
    connect(_slider, &QSlider::valueChanged, this,
            &SliderMediator::slider_moved);
    connect(_box, &QSpinBox::editingFinished, this,
            &SliderMediator::entry_changed);
    init_ui();
  };
  /// @brief Slider mediator destructor
  ~SliderMediator() {
    disconnect(_slider, &QSlider::valueChanged, this,
               &SliderMediator::slider_moved);
    disconnect(_box, &QSpinBox::editingFinished, this,
               &SliderMediator::entry_changed);
  }

 private:
  void slider_moved() {
    _value = _slider->value();
    _box->setValue(_value);
  };
  void entry_changed() {
    _value = _box->value();
    _slider->setValue(_value);
  };

  void init_ui() {
    _slider->setValue(_value);
    _box->setValue(_value);
  }

  QSlider *_slider;
  QSpinBox *_box;
  int &_value;
};

/// @brief Abstract mediator class to manage interface buttons
class ButtonMediator : public QObject {
 public:
  /// @brief Button mediator constructor for 2 buttons
  ButtonMediator(QPushButton *b1, QPushButton *b2, int &v)
      : _button_1(b1), _button_2(b2), _button_3(nullptr), _value(v) {
    connect(_button_1, &QPushButton::clicked, this,
            &ButtonMediator::button_1_clicked);
    connect(_button_2, &QPushButton::clicked, this,
            &ButtonMediator::button_2_clicked);
    set_ui();
  }
  /// @brief Button mediator constructor for 3 buttons
  ButtonMediator(QPushButton *b1, QPushButton *b2, QPushButton *b3, int &v)
      : _button_1(b1), _button_2(b2), _button_3(b3), _value(v) {
    connect(_button_1, &QPushButton::clicked, this,
            &ButtonMediator::button_1_clicked);
    connect(_button_2, &QPushButton::clicked, this,
            &ButtonMediator::button_2_clicked);
    connect(_button_3, &QPushButton::clicked, this,
            &ButtonMediator::button_3_clicked);
    set_ui();
  }

  /// @brief Button mediator destructor
  ~ButtonMediator() {
    disconnect(_button_1, &QPushButton::clicked, this,
               &ButtonMediator::button_1_clicked);
    disconnect(_button_2, &QPushButton::clicked, this,
               &ButtonMediator::button_2_clicked);
    if (_button_3 != nullptr) {
      disconnect(_button_3, &QPushButton::clicked, this,
                 &ButtonMediator::button_3_clicked);
    }
  }

 private:
  void button_1_clicked() {
    _value = 0;
    set_ui();
  }

  void button_2_clicked() {
    _value = 1;
    set_ui();
  }
  void button_3_clicked() {
    _value = 2;
    set_ui();
  }

  void set_ui() {
    if (_value == 0) {
      _button_1->setStyleSheet(active);
      _button_2->setStyleSheet(disabled);
      if (_button_3 != nullptr) {
        _button_3->setStyleSheet(disabled);
      }
    } else if (_value == 1) {
      _button_1->setStyleSheet(disabled);
      _button_2->setStyleSheet(active);
      if (_button_3 != nullptr) {
        _button_3->setStyleSheet(disabled);
      }
    } else if (_button_3 != nullptr && _value == 2) {
      _button_1->setStyleSheet(disabled);
      _button_2->setStyleSheet(disabled);
      _button_3->setStyleSheet(active);
    }
  }

  QPushButton *_button_1;
  QPushButton *_button_2;
  QPushButton *_button_3;
  const QString active = "background-color: white";
  const QString disabled = "background-color: lightgrey";
  int &_value;
};

}  // namespace viewer

#endif  // APP_SRC_VIEW_MEDIATORS_H