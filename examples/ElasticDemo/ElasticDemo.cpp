
#include "canvas/App.h"
#include "elastic/Context.h"
#include "elastic/Views/ColorView.h"
#include "nucleus/FilePath.h"
#include "nucleus/Streams/FileInputStream.h"

class ElasticDemo : public ca::WindowDelegate {
public:
  ElasticDemo() : ca::WindowDelegate("ElasticDemo") {}

  bool onWindowCreated(ca::Renderer* renderer) override {
    if (!WindowDelegate::onWindowCreated(renderer)) {
      return false;
    }

    auto* stackedSizerView = new el::StackedSizerView(&m_context);
    m_context.getRootView()->addChild(stackedSizerView);

    auto* colorView1 = new el::ColorView(&m_context, ca::Color::red);
    stackedSizerView->addChild(colorView1);
    colorView1->setName("colorView1");
    colorView1->setExpansion(el::Expansion::Both);

    return true;
  }

  void onRender(ca::Renderer* renderer) override {
    m_context.render(renderer);
  }

private:
  DELETE_COPY_AND_MOVE(ElasticDemo);

  el::Context m_context;
};

CANVAS_APP(ElasticDemo)
