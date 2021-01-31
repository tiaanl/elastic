
#include "elastic/Views/ColorView.h"

#include "elastic/Context.h"

namespace el {

ColorView::ColorView(Context* context, const ca::Color& color) : View{context}, m_color{color} {}

ColorView::~ColorView() = default;

void ColorView::setColor(const ca::Color& color) {
  m_color = color;
}

void ColorView::layout(const fl::Rect& rect) {
  View::layout(rect);
}

void ColorView::render(Renderer* renderer, const fl::Mat4& mat) {
  View::render(renderer, mat);

  renderer->renderQuad(m_rect, m_color);
}

}  // namespace el
