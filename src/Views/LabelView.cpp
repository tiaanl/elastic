
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

ca::Size LabelView::calculateMinSize() const {
  ca::Size minSize = View::calculateMinSize();

  return minSize;
}

void LabelView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);
}

}  // namespace el
