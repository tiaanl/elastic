
#include "elastic/context.h"

namespace el {

Context::Context() : context_view_{this} {}

bool Context::initialize(ca::Renderer* renderer) {
#if BUILD(DEBUG)
  initializing_renderer_ = renderer;
#endif  // BUILD(DEBUG)

  if (!renderer_.initialize(renderer)) {
    LOG(Error) << "Could not initialize elastic renderer.";
    return false;
  }

  return true;
}

void Context::resize(const fl::Size& size) {
  LOG(Info) << "Resizing context to (" << size.width << ", " << size.height << ")";
  renderer_.resize(size);
}

void Context::set_focus_view(View* view) {
  focus_view_ = view;
}

void Context::tick(F32 adjustment) {
  context_view_.tick(adjustment);
}

void Context::render(ca::Renderer* renderer) {
#if BUILD(DEBUG)
  DCHECK(renderer == initializing_renderer_) << "Render with the same renderer you initialized "
                                                "with. Maybe you didn't initialize the context?";
#endif  // BUILD(DEBUG)

  fl::Size size = renderer->getSize();

  // Get the size of the render target in pixels for the UI to render.
  fl::Rect layoutRect{{0, 0}, size};

  context_view_.layout(layoutRect);
  context_view_.render(&renderer_, fl::Mat4::identity);
}

void Context::on_mouse_moved(const ca::MouseEvent& evt) {
  context_view_.processMouseMoved(evt);
}

bool Context::on_mouse_pressed(const ca::MouseEvent& evt) {
  context_view_.processMousePressed(evt, false);

  return false;
}

void Context::on_mouse_released(const ca::MouseEvent& evt) {
  context_view_.processMouseReleased(evt);
}

void Context::on_mouse_wheel(const ca::MouseWheelEvent& evt) {
  context_view_.processMouseWheel(evt);
}

void Context::on_key_pressed(const ca::KeyEvent& evt) {
  context_view_.processKeyPressed(evt);
}

void Context::on_key_released(const ca::KeyEvent& evt) {
  context_view_.processKeyReleased(evt);
}

}  // namespace el
