
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"
#include "elastic/Context.h"
#include "elastic/Views/ColorView.h"
#include "elastic/Views/TextView.h"
#include "nucleus/files/file_path.h"
#include "nucleus/streams/file_input_stream.h"

class App : public ca::WindowDelegate, el::Context {
public:
  App() {}

  bool onWindowCreated() override {
#if OS(WIN32)
    nu::FileInputStream fontStream{nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};
#elif OS(MACOSX)
      nu::FileInputStream fontStream{nu::FilePath{FILE_PATH_LITERAL("/Library/Fonts/Arial.ttf")}};
#endif

    m_font.loadFromStream(&fontStream);

    el::StackedSizerView* stackedSizerView = new el::StackedSizerView(this);
    getRoot()->addChild(stackedSizerView);

    el::ColorView* colorView1 = new el::ColorView(this);
    colorView1->setName("colorView1");
    colorView1->setColor(ca::Color{255, 0, 0, 255});
    colorView1->setExpand(el::View::ExpandBoth);

    el::TextView* textView = new el::TextView(this, "Welg");
    stackedSizerView->addChild(textView);

    return true;
  }

  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color(0, 0, 127, 255));
    render(canvas);
  }

  ca::Font* getFont(const std::string& name) override { return &m_font; }

private:
  ca::Font m_font;
};

CANVAS_APP(App);
