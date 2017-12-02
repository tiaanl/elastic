
#include "elastic/views/group_view.h"

#include <algorithm>

namespace el {

// static
ca::Rect<I32> GroupView::layoutControlInRect(View* view, const ca::Rect<I32>& rect) {
  ca::Size<I32> minSize = view->calculateMinSize();
  ca::Rect<I32> viewRect{rect.pos.x, rect.pos.y, minSize.width, minSize.height};

  const ExpandType expand = view->getExpand();

  // Apply the horizontal alignment and expand.
  if (expand == ExpandHorizontal || expand == ExpandBoth) {
    viewRect.size.width = rect.size.width;
  } else {
    AlignType horizontalAlign = view->getHorizontalAlign();
    if (horizontalAlign == AlignRight) {
      viewRect.pos.x = rect.pos.x + rect.size.width - viewRect.size.width;
    } else if (horizontalAlign == AlignCenter) {
      viewRect.pos.x = rect.pos.x + (rect.size.width / 2) - (viewRect.size.width / 2);
    }
  }

  // Apply the vertical alignment and expand.
  if (expand == ExpandVertical || expand == ExpandBoth) {
    viewRect.size.height = rect.size.height;
  } else {
    AlignType verticalAlign = view->getVerticalAlign();
    if (verticalAlign == AlignBottom) {
      viewRect.pos.y = rect.pos.y + rect.size.height - viewRect.size.height;
    } else if (verticalAlign == AlignCenter) {
      viewRect.pos.y = rect.pos.y + (rect.size.height / 2) - (viewRect.size.height / 2);
    }
  }

  return viewRect;
}

GroupView::GroupView(Context* context) : View(context) {}

GroupView::~GroupView() {}

void GroupView::addChild(View* view) {
  view->m_parent = this;
  m_children.emplace_back(view);
}

void GroupView::removeChild(View* view) {
  auto it = std::find(std::begin(m_children), std::end(m_children), view);
  if (it == std::end(m_children))
    return;
  view->m_parent = nullptr;
  m_children.erase(it);
}

View* GroupView::getViewAtPosition(const ca::Pos<I32>& pos) const {
  View* foundView = nullptr;

  for (const auto& view : m_children) {
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

  return const_cast<GroupView*>(this);
}

void GroupView::tick(float adjustment) {
  View::tick(adjustment);

  for (auto& child : m_children) {
    child->tick(adjustment);
  }
}

void GroupView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  for (auto& child : m_children) {
    child->render(canvas, mat);
  }
}

}  // namespace el
