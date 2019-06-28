
#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

Context::Context() : m_contextView{this}, m_renderer{} {}

Context::~Context() = default;

void Context::setFocusView(View* view) {
  m_focusView = view;
}

void Context::onMouseMoved(const ca::MouseEvent& evt) {
  m_contextView.processMouseMoved(evt);
}

bool Context::onMousePressed(const ca::MouseEvent& evt) {
  return m_contextView.processMousePressed(evt, false);
}

void Context::onMouseReleased(const ca::MouseEvent& evt) {
  m_contextView.processMouseReleased(evt);
}

void Context::onMouseWheel(const ca::MouseWheelEvent& evt) {
  m_contextView.processMouseWheel(evt);
}

void Context::onKeyPressed(const ca::KeyEvent& evt) {
  m_contextView.processKeyPressed(evt);
}

void Context::onKeyReleased(const ca::KeyEvent& evt) {
  m_contextView.processKeyReleased(evt);
}

void Context::tick(float adjustment) {
  m_contextView.tick(adjustment);
}

void Context::render(ca::Renderer* renderer) {
  ca::Size<I32> size = {1600, 900};

  // Get the size of the render target in pixels for the UI to render.
  ca::Rect<I32> layoutRect{ca::Pos<I32>(0, 0), size};

#if 0
  F32 width = static_cast<F32>(layoutRect.size.width);
  F32 height = static_cast<F32>(layoutRect.size.height);

  ca::Mat4 ortho = ca::ortho(0.f, width, height, 0.f);
#endif  // 0

  m_contextView.layout(layoutRect);
  m_contextView.render(&m_renderer, ca::Mat4::identity);
}

}  // namespace el
