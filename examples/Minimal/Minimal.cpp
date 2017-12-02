
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"
#include "elastic/context.h"
#include "elastic/views/ColorView.h"
#include "elastic/views/StackedSizerView.h"
#include "elastic/views/TextView.h"
#include "nucleus/files/file_path.h"
#include "nucleus/streams/file_input_stream.h"

class App : public ca::WindowDelegate, el::Context {
public:
  App() {}

  bool onWindowCreated() override {
    nu::FileInputStream fontStream{nu::FilePath{FILE_PATH_LITERAL("C:\\Windows\\Fonts\\arial.ttf")}};
    m_font.loadFromStream(&fontStream);

    el::StackedSizerView* stackedSizer = getRoot()->emplaceChild<el::StackedSizerView>(static_cast<el::Context*>(this));

    el::ColorView* colorView1 = stackedSizer->emplaceChild<el::ColorView>(static_cast<el::Context*>(this));
    colorView1->setName("colorView1");
    colorView1->setColor(ca::Color{255, 0, 0, 255});
    colorView1->setExpand(el::View::ExpandBoth);

    el::TextView* textView = stackedSizer->emplaceChild<el::TextView>(static_cast<el::Context*>(this), "Welg");

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
