
#include "elastic/Views/LabelView.h"

#include "nucleus/MemoryDebug.h"

namespace el {

LabelView::LabelView(Context* context, const nu::StringView& label)
  : View{context}, m_label{label} {
}

LabelView::~LabelView() = default;

void LabelView::setLabel(const nu::StringView& label) {
  m_label = label;
}

ca::Size<I32> LabelView::calculateMinSize() const {
  ca::Size<I32> minSize = View::calculateMinSize();

  return minSize;
}

void LabelView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);
}

}  // namespace el
