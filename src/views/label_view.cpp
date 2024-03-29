
#include "elastic/Views/label_view.h"

namespace el {

LabelView::LabelView(Context* context, nu::StringView label, Font* font)
  : View{context}, m_label{label}, m_font{font} {}

LabelView::~LabelView() = default;

void LabelView::setLabel(const nu::StringView& label) {
  m_label = label;
}

fl::Size LabelView::calculateMinSize() const {
  fl::Size minSize = View::calculateMinSize();

  auto textExtent = m_font->calculate_text_extent(m_label.view());

  minSize.width = std::max(minSize.width, textExtent.width);
  minSize.height = std::max(minSize.height, textExtent.height);

  return minSize;
}

void LabelView::render(Renderer* renderer, const fl::Mat4& mat) {
  View::render(renderer, mat);

  renderer->renderText(m_font, m_rect.pos, m_label.view());
}

}  // namespace el
