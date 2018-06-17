
#include "canvas/App.h"
#include "canvas/Rendering/Canvas.h"
#include "elastic/Context.h"
#include "elastic/Views/ColorView.h"
#include "elastic/Views/TextView.h"
#include "nucleus/FilePath.h"
#include "nucleus/Streams/FileInputStream.h"

class App : public ca::WindowDelegate {
public:
  App() : ca::WindowDelegate("Minimal"), m_context(&m_resourceManager) {}

  bool onWindowCreated() override {
    m_resourceManager.createDefaults();

    el::StackedSizerView* stackedSizerView = new el::StackedSizerView(&m_context);
    m_context.getRoot()->addChild(stackedSizerView);

    el::ColorView* colorView1 = new el::ColorView(&m_context);
    stackedSizerView->addChild(colorView1);
    colorView1->setName("colorView1");
    colorView1->setColor(ca::Color{255, 0, 0, 255});
    colorView1->setExpand(el::View::ExpandBoth);

    el::TextView* textView = new el::TextView(&m_context, "Welg");
    stackedSizerView->addChild(textView);

    return true;
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color(0, 0, 127, 255));
    m_context.render(canvas);
  }

private:
  ca::ResourceManager m_resourceManager;
  el::Context m_context;
};

CANVAS_APP(App);
