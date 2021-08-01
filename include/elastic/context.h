#pragma once

#include <nucleus/config.h>

#include "elastic/renderer/renderer.h"
#include "elastic/views/context_view.h"

namespace el {

class View;

class Context : public ca::MouseEventReceiver, public ca::KeyboardEventReceiver {
  NU_DELETE_COPY_AND_MOVE(Context);

public:
  Context();

  // Get the root view of the context.
  ContextView* root_view() {
    return &context_view_;
  }

  // Resize the size of the render area.  Usually called when the window size changes.
  void resize(const fl::Size& size);

  // Get/set the view that will have the keyboard focus.
  NU_NO_DISCARD View* focus_view() const {
    return focus_view_;
  }
  void set_focus_view(View* view);

  bool initialize(ca::Renderer* renderer);
  void tick(F32 delta);
  void render(ca::Renderer* renderer);

  // Override: ca::MouseEventHandlerInterface
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;

  // Override: ca::KeyboardEventHandlerInterface
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;

protected:
  friend class View;

  // The root view of our hierarchy.
  ContextView context_view_;

  // The `Renderer` we are using to render all the views.
  Renderer renderer_;

  // The view that currently has keyboard focus.
  View* focus_view_ = nullptr;

#if BUILD(DEBUG)
  // In debug builds, we make sure that the `Renderer` we initialize with, is the one we render
  // with.
  ca::Renderer* initializing_renderer_ = nullptr;
#endif  // BUILD(DEBUG)
};

}  // namespace el
