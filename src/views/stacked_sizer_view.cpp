
#include "elastic/Views/stacked_sizer_view.h"

#include <algorithm>

namespace el {

StackedSizerView::StackedSizerView(Context* context) : GroupView(context) {}

StackedSizerView::~StackedSizerView() = default;

fl::Size StackedSizerView::calculateMinSize() const {
  fl::Size minSize = GroupView::calculateMinSize();

  for (auto& child : m_children) {
    fl::Size childSize = child->calculateMinSize();
    minSize.width = std::max(minSize.width, childSize.width);
    minSize.height = std::max(minSize.height, childSize.height);
  }

  return minSize;
}

void StackedSizerView::layout(const fl::Rect& rect) {
  GroupView::layout(rect);

  for (auto& child : m_children)
    child->layout(GroupView::layoutControlInRect(child, rect));
}

}  // namespace el
