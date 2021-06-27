
#include "elastic/Views/view.h"

#include "elastic/context.h"

namespace el {

View::View(Context* context) : m_context(context) {}

View::~View() = default;

void View::setName(const nu::StringView& name) {
  m_name = name;
}

void View::setMinSize(const fl::Size& minSize) {
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

View* View::getViewAtPosition(const fl::Pos& pos) const {
  if (!handlesInput())
    return nullptr;

  return m_rect.contains(pos) ? const_cast<View*>(this) : nullptr;
}

void View::tick(F32 NU_UNUSED(delta)) {}

fl::Size View::calculateMinSize() const {
  return m_minSize;
}

void View::layout(const fl::Rect& rect) {
  m_rect = rect;
}

void View::on_mouse_moved(const ca::MouseEvent& NU_UNUSED(evt)) {}

bool View::on_mouse_pressed(const ca::MouseEvent& NU_UNUSED(evt)) {
  return false;
}

bool View::onMouseDragged(const ca::MouseEvent& NU_UNUSED(evt)) {
  return false;
}

void View::on_mouse_released(const ca::MouseEvent& NU_UNUSED(evt)) {}

void View::on_mouse_wheel(const ca::MouseWheelEvent& NU_UNUSED(evt)) {}

void View::onMouseEnter(const ca::MouseEvent& NU_UNUSED(evt)) {}

void View::onMouseLeave(const ca::MouseEvent& NU_UNUSED(evt)) {}

void View::on_key_pressed(const ca::KeyEvent& NU_UNUSED(evt)) {}

void View::on_key_released(const ca::KeyEvent& NU_UNUSED(evt)) {}

void View::render(Renderer* NU_UNUSED(renderer), const fl::Mat4& NU_UNUSED(mat)) {}

}  // namespace el
