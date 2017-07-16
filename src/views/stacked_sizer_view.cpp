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

#include "elastic/views/stacked_sizer_view.h"

#include <algorithm>

namespace el {

StackedSizerView::StackedSizerView(Context* context) : GroupView(context) {
}

StackedSizerView::~StackedSizerView() {
}

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
