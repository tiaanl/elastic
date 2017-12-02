
#include "elastic/views/view.h"

#include "elastic/Context.h"

namespace el {

View::View(Context* context) : m_context(context) {}

View::~View() {}

void View::setName(const std::string& name) {
  m_name = name;
}

void View::setMinSize(const ca::Size<I32>& minSize) {
  m_minSize = minSize;
}

void View::setHorizontalAlign(AlignType align) {
  m_horizontalAlign = align;
}

void View::setVerticalAlign(AlignType align) {
  m_verticalAlign = align;
}

void View::setExpand(ExpandType expand) {
  m_expand = expand;
}

void View::setProportion(int32_t proportion) {
  m_proportion = proportion;
}

View* View::getViewAtPosition(const ca::Pos<I32>& pos) const {
  if (!handlesInput())
    return nullptr;

  return m_rect.contains(pos) ? const_cast<View*>(this) : nullptr;
}

void View::tick(float adjustment) {}

ca::Size<I32> View::calculateMinSize() const {
  return m_minSize;
}

void View::layout(const ca::Rect<I32>& rect) {
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

void View::render(ca::Canvas* canvas, const ca::Mat4& mat) {}

}  // namespace el
