
#include "elastic/Views/GroupView.h"

#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

// static
ca::Rect<I32> GroupView::layoutControlInRect(View* view, const ca::Rect<I32>& rect) {
  ca::Size<I32> minSize = view->calculateMinSize();
  ca::Rect<I32> viewRect{rect.pos.x, rect.pos.y, minSize.width, minSize.height};

  const Expansion expand = view->getExpansion();

  // Apply the horizontal alignment and expand.
  if (expand == Expansion::Horizontal || expand == Expansion::Both) {
    viewRect.size.width = rect.size.width;
  } else {
    const Alignment horizontalAlignment = view->getHorizontalAlignment();
    if (horizontalAlignment == Alignment::Right) {
      viewRect.pos.x = rect.pos.x + rect.size.width - viewRect.size.width;
    } else if (horizontalAlignment == Alignment::Center) {
      viewRect.pos.x = rect.pos.x + (rect.size.width / 2) - (viewRect.size.width / 2);
    }
  }

  // Apply the vertical alignment and expand.
  if (expand == Expansion::Vertical || expand == Expansion::Both) {
    viewRect.size.height = rect.size.height;
  } else {
    Alignment verticalAlignment = view->getVerticalAlignment();
    if (verticalAlignment == Alignment::Bottom) {
      viewRect.pos.y = rect.pos.y + rect.size.height - viewRect.size.height;
    } else if (verticalAlignment == Alignment::Center) {
      viewRect.pos.y = rect.pos.y + (rect.size.height / 2) - (viewRect.size.height / 2);
    }
  }

  return viewRect;
}

GroupView::GroupView(Context* context) : View(context) {}

GroupView::~GroupView() = default;

void GroupView::addChild(View* view) {
  view->m_parent = this;
  m_children.emplaceBack(view);
}

void GroupView::removeChild(View* view) {
  auto it = std::find(std::begin(m_children), std::end(m_children), view);
  if (it == std::end(m_children))
    return;
  view->m_parent = nullptr;
  m_children.remove(it);
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

void GroupView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);

  for (auto& child : m_children) {
    child->render(renderer, mat);
  }
}

}  // namespace el
