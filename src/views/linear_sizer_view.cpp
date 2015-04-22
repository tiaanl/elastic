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
  float sectionSize =
      static_cast<float>(rect.width) / static_cast<float>(m_children.size());

  sf::IntRect sectionRect(rect);
  sectionRect.width = std::lround(sectionSize);

  int section = 0;
  for (const auto& child : m_children) {
    sectionRect.left =
        rect.left + std::lround(sectionSize * static_cast<float>(section));
    child->layout(layoutControlInRect(child, sectionRect));
    ++section;
  }
}

void LinearSizerView::layoutVertical(const sf::IntRect& rect) {
  float sectionSize =
      static_cast<float>(rect.height) / static_cast<float>(m_children.size());

  sf::IntRect sectionRect(rect);
  sectionRect.height = std::lround(sectionSize);

  int section = 0;
  for (const auto& child : m_children) {
    sectionRect.top =
        rect.top + std::lround(sectionSize * static_cast<float>(section));
    child->layout(layoutControlInRect(child, sectionRect));
    ++section;
  }
}

}  // namespace el
