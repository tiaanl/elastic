
#include "elastic/Views/TextView.h"

#include "canvas/Math/Transform.h"
#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

TextView::TextView(Context* context, const nu::String& label)
  : View(context), m_label(label), m_text(context->getResourceManager()) {
  // Set up the text shape.
  auto font = context->getResourceManager()->getOrCreateFont("default");

  // Set up the label.
  if (font->isLoaded()) {
    m_text.setFont(font);
    m_text.setText(m_label);
  }
}

TextView::~TextView() {}

void TextView::setLabel(const nu::String& label) {
  m_label = label;

  // Set the label on the shape.
  m_text.setText(m_label);
}

void TextView::setFont(const ca::ResourceRef<ca::Font>& font) {
  m_font = font;
}

ca::Size<I32> TextView::calculateMinSize() const {
  ca::Size<I32> minSize = View::calculateMinSize();
  ca::Rect<I32> bounds = m_text.getBounds();

  minSize.width = std::max(minSize.width, bounds.size.width);
  minSize.height = std::max(minSize.height, bounds.size.height);

  return minSize;
}

void TextView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  ca::Mat4 vmat =
      mat * ca::translate(static_cast<F32>(m_rect.pos.x), static_cast<F32>(m_rect.pos.y), 0.f);

  m_text.render(canvas, vmat);
}

}  // namespace el
