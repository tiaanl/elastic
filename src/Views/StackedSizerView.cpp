
#include "elastic/Views/StackedSizerView.h"

#include <algorithm>

#include "nucleus/MemoryDebug.h"

namespace el {

StackedSizerView::StackedSizerView(Context* context) : GroupView(context) {}

StackedSizerView::~StackedSizerView() = default;

ca::Size StackedSizerView::calculateMinSize() const {
  ca::Size minSize = GroupView::calculateMinSize();

  for (auto& child : m_children) {
    ca::Size childSize = child->calculateMinSize();
    minSize.width = std::max(minSize.width, childSize.width);
    minSize.height = std::max(minSize.height, childSize.height);
  }

  return minSize;
}

void StackedSizerView::layout(const ca::Rect& rect) {
  GroupView::layout(rect);

  for (auto& child : m_children)
    child->layout(GroupView::layoutControlInRect(child, rect));
}

}  // namespace el
