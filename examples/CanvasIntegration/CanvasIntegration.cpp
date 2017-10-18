
#include <elastic/views/ColorView.h>
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"
#include "elastic/context.h"

class MyContext : public el::Context {
public:
  MyContext() : el::Context() {}
  virtual ~MyContext() {}

  ca::Font* getFont(const std::string& name) override { return nullptr; }
};

class CanvasIntegrationWindow : public ca::WindowDelegate {
public:
  CanvasIntegrationWindow() {}
  ~CanvasIntegrationWindow() override {}

  // Override: ca::WindowDelegate
  bool onWindowCreated() override {
    if (!ca::WindowDelegate::onWindowCreated()) {
      return false;
    }

    el::ColorView* colorView = new el::ColorView(&m_ui, ca::Color(255, 0, 0, 0));
    colorView->setExpand(el::View::ExpandBoth);
    m_ui.getRoot()->addChild(colorView);

    return true;
  }

  void onMouseMoved(const ca::MouseEvent& evt) override {
    ca::WindowDelegate::onMouseMoved(evt);
    m_ui.onMouseMoved(evt);
  }

  void onMousePressed(const ca::MouseEvent& evt) override {
    ca::WindowDelegate::onMousePressed(evt);
    m_ui.onMouseMoved(evt);
  }

  void onMouseReleased(const ca::MouseEvent& evt) override {
    ca::WindowDelegate::onMouseReleased(evt);
    m_ui.onMouseReleased(evt);
  }

  void onMouseWheel(const ca::MouseWheelEvent& evt) override {
    ca::WindowDelegate::onMouseWheel(evt);
    m_ui.onMouseWheel(evt);
  }

  void onKeyPressed(const ca::KeyEvent& evt) override {
    ca::WindowDelegate::onKeyPressed(evt);
    m_ui.onKeyPressed(evt);
  }

  void onKeyReleased(const ca::KeyEvent& evt) override {
    ca::WindowDelegate::onKeyReleased(evt);
    m_ui.onKeyReleased(evt);
  };

  // Override: ca::WindowDelegate
  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 63, 95});

    m_ui.render(canvas);
  }

private:
  MyContext m_ui;

  DISALLOW_COPY_AND_ASSIGN(CanvasIntegrationWindow);
};

CANVAS_APP(CanvasIntegrationWindow);
