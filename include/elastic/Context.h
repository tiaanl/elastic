
#ifndef ELASTIC_CONTEXT_H_
#define ELASTIC_CONTEXT_H_

#include "elastic/Renderer/Renderer.h"
#include "elastic/Views/ContextView.h"

namespace el {

class View;

class Context : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
  Context();
  ~Context();

  // Get the root view of the context.
  ContextView* getRootView() {
    return &m_contextView;
  }

  // Get/set the view that will have the keyboard focus.
  View* getFocusView() const {
    return m_focusView;
  }
  void setFocusView(View* view);

  void onKeyPressed(const ca::KeyEvent& evt) override;
  void onKeyReleased(const ca::KeyEvent& evt) override;
  void onMouseMoved(const ca::MouseEvent& evt) override;
  bool onMousePressed(const ca::MouseEvent& evt) override;
  void onMouseReleased(const ca::MouseEvent& evt) override;
  void onMouseWheel(const ca::MouseWheelEvent& evt) override;

  void tick(float delta);
  void render(ca::Renderer* renderer);

protected:
  DELETE_COPY_AND_MOVE(Context);

  friend class View;

  // The root view of our hierarchy.
  ContextView m_contextView;

  // The elastic renderer we use to render all the views.
  Renderer m_renderer;

  // The view that currently has keyboard focus.
  View* m_focusView = nullptr;
};

}  // namespace el

#endif  // ELASTIC_CONTEXT_H_
