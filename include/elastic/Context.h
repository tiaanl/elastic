
#ifndef ELASTIC_CONTEXT_H_
#define ELASTIC_CONTEXT_H_

#include "elastic/Renderer/Renderer.h"
#include "elastic/Views/ContextView.h"
#include "nucleus/Config.h"

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

  void resize(const ca::Size& size);

  // Get/set the view that will have the keyboard focus.
  View* getFocusView() const {
    return m_focusView;
  }
  void setFocusView(View* view);

  bool initialize(ca::Renderer* renderer);
  void tick(F32 delta);
  void render(ca::Renderer* renderer);

  // Override: ca::MouseEventHandlerInterface
  void onMouseMoved(const ca::MouseEvent& evt) override;
  bool onMousePressed(const ca::MouseEvent& evt) override;
  void onMouseReleased(const ca::MouseEvent& evt) override;
  void onMouseWheel(const ca::MouseWheelEvent& evt) override;

  // Override: ca::KeyboardEventHandlerInterface
  void onKeyPressed(const ca::KeyEvent& evt) override;
  void onKeyReleased(const ca::KeyEvent& evt) override;

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

#endif  // ELASTIC_CONTEXT_H_
