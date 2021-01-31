
#include "elastic/Views/LinearSizerView.h"

#include <algorithm>
#include <cmath>

namespace el {

LinearSizerView::LinearSizerView(Context* context, Orientation orientation)
  : GroupView(context), m_orientation(orientation) {}

LinearSizerView::~LinearSizerView() = default;

void LinearSizerView::setOrientation(Orientation orientation) {
  m_orientation = orientation;
}

fl::Size LinearSizerView::calculateMinSize() const {
  fl::Size minSize = GroupView::calculateMinSize();

  fl::Size contentSize;
  if (m_orientation == Orientation::Horizontal) {
    for (const auto& child : m_children) {
      fl::Size childMinSize = child->calculateMinSize();
      contentSize.width += childMinSize.width;
      contentSize.height = std::max(contentSize.height, childMinSize.height);
    }
  } else {
    for (const auto& child : m_children) {
      fl::Size childMinSize = child->calculateMinSize();
      contentSize.width = std::max(contentSize.width, childMinSize.width);
      contentSize.height += childMinSize.height;
    }
  }

  minSize.width = std::max(minSize.width, contentSize.width);
  minSize.height = std::max(minSize.height, contentSize.height);

  return minSize;
}

void LinearSizerView::layout(const fl::Rect& rect) {
  GroupView::layout(rect);

  if (m_orientation == Orientation::Horizontal)
    layoutHorizontal(rect);
  else
    layoutVertical(rect);
}

void LinearSizerView::layoutHorizontal(const fl::Rect& rect) {
  // Make place where we can store the size for each child.
  nu::DynamicArray<std::pair<I32, fl::Size>> sizes;
  sizes.resize(m_children.size(), std::make_pair(0, fl::Size{}));

  // The total width available to us.
  int32_t totalSize = rect.size.width;
  int32_t totalProportion = 0;
  for (size_t i = 0; i < m_children.size(); ++i) {
    sizes[i].first = m_children[i]->getProportion();
    sizes[i].second = m_children[i]->calculateMinSize();

    // Calculate the total number of proportions we need.
    totalProportion += m_children[i]->getProportion();

    // Adjust the space we have to divide between the views.
    totalSize -= sizes[i].second.width;
  }

  // Calculate the size we have per proportion for each view.
  float singleProportionSize = static_cast<float>(totalSize) / static_cast<float>(totalProportion);

  // Start with the entire area we have available.
  fl::Rect sectionRect(rect);
  for (size_t i = 0; i < m_children.size(); ++i) {
    // The height available is the minSize of the view + the amount we receive
    // from the total left over space.
    sectionRect.size.width =
        sizes[i].second.width +
        std::lround(singleProportionSize * static_cast<float>(m_children[i]->getProportion()));

    // Layout the child view.
    m_children[i]->layout(layoutControlInRect(m_children[i], sectionRect));

    // Adjust the top of the layout rect to where the next view will be layed
    // out.
    sectionRect.pos.x += sectionRect.size.width;
  }
}

void LinearSizerView::layoutVertical(const fl::Rect& rect) {
  // Make place where we can store the size for each child.
  nu::DynamicArray<std::pair<int32_t, fl::Size>> sizes;
  sizes.resize(m_children.size(), std::make_pair(0, fl::Size{}));

  // The total height available to us.
  int32_t totalSize = rect.size.height;
  int32_t totalProportion = 0;
  for (size_t i = 0; i < m_children.size(); ++i) {
    sizes[i].first = m_children[i]->getProportion();
    sizes[i].second = m_children[i]->calculateMinSize();

    // Calculate the total number of proportions we need.
    totalProportion += m_children[i]->getProportion();

    // Adjust the space we have to divide between the views.
    totalSize -= sizes[i].second.height;
  }

  // Calculate the size we have per proportion for each view.
  float singleProportionSize = static_cast<float>(totalSize) / static_cast<float>(totalProportion);

  // Start with the entire area we have available.
  fl::Rect sectionRect(rect);
  for (size_t i = 0; i < m_children.size(); ++i) {
    // The height available is the minSize of the view + the amount we receive
    // from the total left over space.
    sectionRect.size.height =
        sizes[i].second.height +
        std::lround(singleProportionSize * static_cast<float>(m_children[i]->getProportion()));

    // Layout the child view.
    m_children[i]->layout(layoutControlInRect(m_children[i], sectionRect));

    // Adjust the top of the layout rect to where the next view will be layed
    // out.
    sectionRect.pos.y += sectionRect.size.height;
  }
}

}  // namespace el
