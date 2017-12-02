
#include "elastic/Views/TextView.h"

#include "canvas/math/transform.h"
#include "elastic/context.h"
#include "nucleus/algorithms/Utility.h"

#include "nucleus/MemoryDebug.h"

namespace el {

TextView::TextView(Context* context, const std::string& label) : View(context), m_label(label) {
  // Set up the text shape.
  ca::Font* font = context->getFont("default");

  // Set up the label.
  if (font) {
    m_text.setText(m_label);
    m_text.setFont(font);
    // m_shape.setColor(sf::Color{255, 255, 255});
    m_text.setTextSize(16);
  }
}

TextView::~TextView() {}

void TextView::setLabel(const std::string& label) {
  m_label = label;

  // Set the label on the shape.
  m_text.setText(m_label);
}

ca::Size<I32> TextView::calculateMinSize() const {
  ca::Size<I32> minSize = View::calculateMinSize();
  ca::Rect<I32> bounds = m_text.getBounds();

  minSize.width = nu::max(minSize.width, bounds.size.width);
  minSize.height = nu::max(minSize.height, bounds.size.height);

  return minSize;
}

void TextView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  ca::Mat4 vmat = mat * ca::translate(static_cast<F32>(m_rect.pos.x), static_cast<F32>(m_rect.pos.y), 0.f);

  m_text.render(canvas, vmat);
}

}  // namespace el
