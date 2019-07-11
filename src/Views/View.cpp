
#include "elastic/Views/View.h"

#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

View::View(Context* context) : m_context(context) {}

View::~View() = default;

void View::setName(const nu::StringView& name) {
  m_name = name;
}

void View::setMinSize(const ca::Size& minSize) {
  m_minSize = minSize;
}

void View::setHorizontalAlignment(Alignment alignment) {
  m_horizontalAlignment = alignment;
}

void View::setVerticalAlignment(Alignment alignment) {
  m_verticalAlignment = alignment;
}

void View::setExpansion(Expansion expansion) {
  m_expansion = expansion;
}

void View::setProportion(I32 proportion) {
  m_proportion = proportion;
}

View* View::getViewAtPosition(const ca::Pos& pos) const {
  if (!handlesInput())
    return nullptr;

  return m_rect.contains(pos) ? const_cast<View*>(this) : nullptr;
}

void View::tick(F32 delta) {}

ca::Size View::calculateMinSize() const {
  return m_minSize;
}

void View::layout(const ca::Rect& rect) {
  m_rect = rect;
}

void View::onMouseMoved(const ca::MouseEvent& evt) {}

bool View::onMousePressed(const ca::MouseEvent& evt) {
  return false;
}

bool View::onMouseDragged(const ca::MouseEvent& evt) {
  return false;
}

void View::onMouseReleased(const ca::MouseEvent& evt) {}

void View::onMouseWheel(const ca::MouseWheelEvent& evt) {}

void View::onMouseEnter(const ca::MouseEvent& evt) {}

void View::onMouseLeave(const ca::MouseEvent& evt) {}

void View::onKeyPressed(const ca::KeyEvent& evt) {}

void View::onKeyReleased(const ca::KeyEvent& evt) {}

void View::render(Renderer* renderer, const ca::Mat4& mat) {}

}  // namespace el
