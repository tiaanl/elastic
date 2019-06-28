
#include "elastic/Views/ColorView.h"

#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

ColorView::ColorView(Context* context, const ca::Color& color) : View{context}, m_color{color} {}

ColorView::~ColorView() = default;

void ColorView::setColor(const ca::Color& color) {
  m_color = color;
}

void ColorView::layout(const ca::Rect<I32>& rect) {
  View::layout(rect);
}

void ColorView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);
}

}  // namespace el
