
#include "elastic/Context.h"

namespace el {

Context::Context() : m_contextView{this}, m_renderer{} {}

Context::~Context() = default;

bool Context::initialize(ca::Renderer* renderer) {
#if BUILD(DEBUG)
  m_initializingRenderer = renderer;
#endif  // BUILD(DEBUG)

  if (!m_renderer.initialize(renderer)) {
    LOG(Error) << "Could not initialize elastic renderer.";
    return false;
  }

  return true;
}

void Context::resize(const fl::Size& size) {
  LOG(Info) << "Resizing context to (" << size.width << ", " << size.height << ")";
  m_renderer.resize(size);
}

void Context::setFocusView(View* view) {
  m_focusView = view;
}

void Context::tick(F32 adjustment) {
  m_contextView.tick(adjustment);
}

void Context::render(ca::Renderer* renderer) {
#if BUILD(DEBUG)
  DCHECK(renderer == m_initializingRenderer) << "Render with the same renderer you initialized "
                                                "with. Maybe you didn't initialize the context?";
#endif  // BUILD(DEBUG)

  fl::Size size = renderer->getSize();

  // Get the size of the render target in pixels for the UI to render.
  fl::Rect layoutRect{{0, 0}, size};

  m_contextView.layout(layoutRect);
  m_contextView.render(&m_renderer, fl::Mat4::identity);
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

}  // namespace el
