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

#include "elastic/views/group_view.h"

namespace el {

// static
sf::IntRect GroupView::layoutControlInRect(View* view,
                                           const sf::IntRect& rect) {
  sf::Vector2i minSize{view->calculateMinSize()};
  sf::IntRect viewRect{rect.left, rect.top, minSize.x, minSize.y};

  const ExpandType expand = view->getExpand();

  // Apply the horizontal alignment and expand.
  if (expand == ExpandHorizontal || expand == ExpandBoth) {
    viewRect.width = rect.width;
  } else {
    AlignType horizontalAlign = view->getHorizontalAlign();
    if (horizontalAlign == AlignRight) {
      viewRect.left = rect.left + rect.width - viewRect.width;
    } else if (horizontalAlign == AlignCenter) {
      viewRect.left = rect.left + (rect.width / 2) - (viewRect.width / 2);
    }
  }

  // Apply the vertical alignment and expand.
  if (expand == ExpandVertical || expand == ExpandBoth) {
    viewRect.height = rect.height;
  } else {
    AlignType verticalAlign = view->getVerticalAlign();
    if (verticalAlign == AlignBottom) {
      viewRect.top = rect.top + rect.height - viewRect.height;
    } else if (verticalAlign == AlignCenter) {
      viewRect.top = rect.top + (rect.height / 2) - (viewRect.height / 2);
    }
  }

  return viewRect;
}

GroupView::GroupView(Context* context) : View(context) {
}

GroupView::~GroupView() {
  // Destroy all our children.
  for (auto& child : m_children) {
    delete child;
  }
}

void GroupView::addChild(View* view) {
  view->m_parent = this;
  m_children.push_back(view);
}

void GroupView::removeChild(View* view) {
  auto it = std::find(std::begin(m_children), std::end(m_children), view);
  if (it == std::end(m_children))
    return;
  view->m_parent = nullptr;
  m_children.erase(it);
}

View* GroupView::getViewAtPosition(const sf::Vector2i& pos) {
  View* foundView = nullptr;

  for (View* view : m_children) {
    View* result = view->getViewAtPosition(pos);
    if (result)
      foundView = result;
  }

  // If we found something deeper, return that.
  if (foundView) {
    return foundView;
  }

  if (!m_rect.contains(pos)) {
    return nullptr;
  }

  if (!handlesInput()) {
    return nullptr;
  }

  return this;
}

void GroupView::tick(float adjustment) {
  View::tick(adjustment);

  for (auto& child : m_children) {
    child->tick(adjustment);
  }
}

void GroupView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  View::draw(target, states);

  for (auto& child : m_children) {
    target.draw(*child, states);
  }
}

}  // namespace el
