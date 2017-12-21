
#include "elastic/Context.h"

#include "canvas/Math/Transform.h"

#include "nucleus/MemoryDebug.h"

namespace el {

Context::Context(nu::Allocator* allocator) : m_allocator(allocator), m_contextView(this) {}

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

void Context::render(ca::Canvas* canvas) {
  // Get the size of the render target in pixels for the UI to render.
  ca::Rect<I32> layoutRect{ca::Pos<I32>(0, 0), canvas->getSize()};

  F32 width = static_cast<F32>(layoutRect.size.width);
  F32 height = static_cast<F32>(layoutRect.size.height);

  ca::Mat4 ortho = ca::ortho(0.f, width, height, 0.f);

  m_contextView.layout(layoutRect);
  m_contextView.render(canvas, ortho);
}

}  // namespace el
