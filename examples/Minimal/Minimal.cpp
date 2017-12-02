
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"
#include "elastic/context.h"
#include "elastic/views/ColorView.h"
#include "elastic/views/stacked_sizer_view.h"
#include "elastic/views/text_view.h"
#include "nucleus/files/file_path.h"
#include "nucleus/streams/file_input_stream.h"

class App : public ca::WindowDelegate, el::Context {
public:
  App() {}

  bool onWindowCreated() override {
    nu::FileInputStream fontStream{nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};
    m_font.loadFromStream(&fontStream);

    el::StackedSizerView* stackedSizer = new el::StackedSizerView{this};
    getRoot()->addChild(stackedSizer);

    el::ColorView* colorView1 = new el::ColorView(this);
    colorView1->setName("colorView1");
    colorView1->setColor(ca::Color{255, 0, 0, 255});
    colorView1->setExpand(el::View::ExpandBoth);
    stackedSizer->addChild(colorView1);

    el::TextView* textView = new el::TextView(this, "Welg");
    // textView->setMinSize(ca::Size<I32>{300, 200});
    stackedSizer->addChild(textView);

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
