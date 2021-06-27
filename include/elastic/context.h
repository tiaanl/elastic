#pragma once

#include "elastic/Renderer/renderer.h"
#include "elastic/Views/context_view.h"
#include "nucleus/config.h"

namespace el {

class View;

class Context : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
  NU_DELETE_COPY_AND_MOVE(Context);

  Context();
  ~Context();

  // Get the root view of the context.
  ContextView* getRootView() {
    return &m_contextView;
  }

  void resize(const fl::Size& size);

  // Get/set the view that will have the keyboard focus.
  View* getFocusView() const {
    return m_focusView;
  }
  void setFocusView(View* view);

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
  ContextView m_contextView;

  // The `Renderer` we use to render all the views.
  Renderer m_renderer;

  // The view that currently has keyboard focus.
  View* m_focusView = nullptr;

#if BUILD(DEBUG)
  // In debug builds, we make sure that the `Renderer` we initialize with, is the one we render
  // with.
  ca::Renderer* m_initializingRenderer = nullptr;
#endif  // BUILD(DEBUG)
};

}  // namespace el
