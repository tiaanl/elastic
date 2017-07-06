
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"
#include "canvas/utils/color.h"

class CanvasIntegrationWindow : public ca::WindowDelegate {
public:
  CanvasIntegrationWindow() {}
  ~CanvasIntegrationWindow() override {}

  // Override: ca::WindowDelegate
  bool onWindowCreated() override {
    if (!ca::WindowDelegate::onWindowCreated()) {
      return false;
    }

    return true;
  }

  // Override: ca::WindowDelegate
  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 63, 95});
  }

private:
  DISALLOW_COPY_AND_ASSIGN(CanvasIntegrationWindow);
};

CANVAS_APP(CanvasIntegrationWindow);
