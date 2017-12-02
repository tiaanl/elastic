
#include "elastic/views/stacked_sizer_view.h"

#include <algorithm>

namespace el {

StackedSizerView::StackedSizerView(Context* context) : GroupView(context) {}

StackedSizerView::~StackedSizerView() {}

ca::Size<I32> StackedSizerView::calculateMinSize() const {
  ca::Size<I32> minSize = GroupView::calculateMinSize();

  for (auto& child : m_children) {
    ca::Size<I32> childSize = child->calculateMinSize();
    minSize.width = std::max(minSize.width, childSize.width);
    minSize.height = std::max(minSize.height, childSize.height);
  }

  return minSize;
}

void StackedSizerView::layout(const ca::Rect<I32>& rect) {
  GroupView::layout(rect);

  for (auto& child : m_children)
    child->layout(GroupView::layoutControlInRect(child, rect));
}

}  // namespace el
