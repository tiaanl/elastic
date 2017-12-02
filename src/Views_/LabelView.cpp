
#include "elastic/views/LabelView.h"

#include <algorithm>

#include "canvas/math/transform.h"
#include "nucleus/streams/file_input_stream.h"

namespace el {

LabelView::LabelView(Context* context, std::string label)
  : View(context), m_label(label), m_font(nu::MakeScopedPtr<ca::Font>()) {
  m_text.setFont(context->getFont("default"));

  updateTextInternal();
}

LabelView::~LabelView() {}

void LabelView::setLabel(std::string label) {
  m_label = label;

  updateTextInternal();
}

ca::Size<I32> LabelView::calculateMinSize() const {
  ca::Size<I32> minSize = View::calculateMinSize();

  ca::Rect<I32> bounds = m_text.getBounds();

  minSize.width = std::max(minSize.width, bounds.size.width);
  minSize.height = std::max(minSize.height, bounds.size.height);

  return minSize;
}

void LabelView::updateTextInternal() {
  m_text.setText(m_label);
}

void LabelView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  auto bounds = m_text.getBounds();

  ca::Mat4 view;
  view *=
      ca::translate(static_cast<F32>(m_rect.pos.x - bounds.pos.x), static_cast<F32>(m_rect.pos.y - bounds.pos.y), 0.f);

  m_text.render(canvas, mat * view);
}

}  // namespace el
