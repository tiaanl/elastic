
#include "canvas/app.h"
#include "canvas/rendering/canvas.h"

class App : public ca::WindowDelegate {
public:
  void onPaint(ca::Canvas* canvas) override { canvas->clear(ca::Color(0, 0, 127, 255)); }
};

#if 0
class MyContext : public el::Context {
public:
  virtual sf::Font* getFont(const std::string& name) override {
    return nullptr;
  }
};

int main(int argc, char* argv[]) {
  sf::RenderWindow window{sf::VideoMode{800, 600}, "elastic - Minimal"};

  MyContext context;

  el::LinearSizerView* rootSizer = new el::LinearSizerView(&context);
  rootSizer->setName("rootSizer");
  rootSizer->setExpand(el::View::ExpandBoth);
  rootSizer->SetOrientation(el::LinearSizerView::OrientationHorizontal);
  context.getRoot()->addChild(rootSizer);

  el::ColorView* colorView1 = new el::ColorView(&context);
  colorView1->setName("colorView1");
  colorView1->setExpand(el::View::ExpandBoth);
  colorView1->setProportion(1);
  colorView1->setColor(sf::Color(50, 80, 110));
  rootSizer->addChild(colorView1);

  el::ColorView* colorView2 = new el::ColorView(&context);
  colorView2->setName("colorView2");
  colorView2->setExpand(el::View::ExpandBoth);
  colorView2->setProportion(1);
  colorView2->setColor(sf::Color(255, 0, 0));
  rootSizer->addChild(colorView2);

  while (window.isOpen()) {
    sf::Event event;
    if (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      }
    }

    window.clear(sf::Color{0, 0, 0, 0});
    window.draw(context);
    window.display();
  }

  return 0;
}
#endif  // 0

CANVAS_APP(App);
