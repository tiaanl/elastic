// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "elastic/views/linear_sizer_view.h"

#include <cmath>
#include <algorithm>

namespace el {

LinearSizerView::LinearSizerView(Context* context)
  : GroupView(context), m_orientation(OrientationHorizontal) {
}

LinearSizerView::LinearSizerView(Context* context, OrientationType orientation)
  : GroupView(context), m_orientation(orientation) {
}

LinearSizerView::~LinearSizerView() {
}

void LinearSizerView::SetOrientation(OrientationType orientation) {
  m_orientation = orientation;
}

sf::Vector2i LinearSizerView::calculateMinSize() const {
  sf::Vector2i minSize(GroupView::calculateMinSize());

  sf::Vector2i contentSize;
  if (m_orientation == OrientationHorizontal) {
    for (const auto& child : m_children) {
      sf::Vector2i childMinSize{child->calculateMinSize()};
      contentSize.x += childMinSize.x;
      contentSize.y = std::max(contentSize.y, childMinSize.y);
    }
  } else {
    for (const auto& child : m_children) {
      sf::Vector2i childMinSize{child->calculateMinSize()};
      contentSize.x = std::max(contentSize.x, childMinSize.x);
      contentSize.y += childMinSize.y;
    }
  }

  minSize.x = std::max(minSize.x, contentSize.x);
  minSize.y = std::max(minSize.y, contentSize.y);

  return minSize;
}

void LinearSizerView::layout(const sf::IntRect& rect) {
  GroupView::layout(rect);

  if (m_orientation == OrientationHorizontal)
    layoutHorizontal(rect);
  else
    layoutVertical(rect);
}

void LinearSizerView::layoutHorizontal(const sf::IntRect& rect) {
  // Make place where we can store the size for each child.
  std::vector<std::pair<int32_t, sf::Vector2i>> sizes;
  sizes.resize(m_children.size(), std::make_pair(0, sf::Vector2i{}));

  // The total width available to us.
  int32_t totalSize = rect.width;
  int32_t totalProportion = 0;
  for (size_t i = 0; i < m_children.size(); ++i) {
    sizes[i].first = m_children[i]->getProportion();
    sizes[i].second = m_children[i]->calculateMinSize();

    // Calculate the total number of proportions we need.
    totalProportion += m_children[i]->getProportion();

    // Adjust the space we have to divide between the views.
    totalSize -= sizes[i].second.x;
  }

  // Calculate the size we have per proportion for each view.
  float singleProportionSize =
      static_cast<float>(totalSize) / static_cast<float>(totalProportion);

  // Start with the entire area we have available.
  sf::IntRect sectionRect(rect);
  for (size_t i = 0; i < m_children.size(); ++i) {
    // The height available is the minSize of the view + the amount we receive
    // from the total left over space.
    sectionRect.width =
        sizes[i].second.x +
        std::lround(singleProportionSize *
                    static_cast<float>(m_children[i]->getProportion()));

    // Layout the child view.
    m_children[i]->layout(layoutControlInRect(m_children[i], sectionRect));

    // Adjust the top of the layout rect to where the next view will be layed
    // out.
    sectionRect.left += sectionRect.width;
  }
}

void LinearSizerView::layoutVertical(const sf::IntRect& rect) {
  // Make place where we can store the size for each child.
  std::vector<std::pair<int32_t, sf::Vector2i>> sizes;
  sizes.resize(m_children.size(), std::make_pair(0, sf::Vector2i{}));

  // The total height available to us.
  int32_t totalSize = rect.height;
  int32_t totalProportion = 0;
  for (size_t i = 0; i < m_children.size(); ++i) {
    sizes[i].first = m_children[i]->getProportion();
    sizes[i].second = m_children[i]->calculateMinSize();

    // Calculate the total number of proportions we need.
    totalProportion += m_children[i]->getProportion();

    // Adjust the space we have to divide between the views.
    totalSize -= sizes[i].second.y;
  }

  // Calculate the size we have per proportion for each view.
  float singleProportionSize =
      static_cast<float>(totalSize) / static_cast<float>(totalProportion);

  // Start with the entire area we have available.
  sf::IntRect sectionRect(rect);
  for (size_t i = 0; i < m_children.size(); ++i) {
    // The height available is the minSize of the view + the amount we receive
    // from the total left over space.
    sectionRect.height =
        sizes[i].second.y +
        std::lround(singleProportionSize *
                    static_cast<float>(m_children[i]->getProportion()));

    // Layout the child view.
    m_children[i]->layout(layoutControlInRect(m_children[i], sectionRect));

    // Adjust the top of the layout rect to where the next view will be layed
    // out.
    sectionRect.top += sectionRect.height;
  }
}

}  // namespace el
