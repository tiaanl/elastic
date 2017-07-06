// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "elastic/context.h"
#include "elastic/views/color_view.h"
#include "elastic/views/linear_sizer_view.h"

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
