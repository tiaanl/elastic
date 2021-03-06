#pragma once

#include "elastic/Views/stacked_sizer_view.h"

namespace el {

class ContextView : public StackedSizerView {
public:
  NU_DELETE_COPY_AND_MOVE(ContextView);

  explicit ContextView(Context* context);
  ~ContextView() override;

  // Override: StackedSizerView
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  bool onMouseDragged(const ca::MouseEvent& evt) override;

private:
  friend class Context;

  // Initiate user input from the context.
  bool processMousePressed(const ca::MouseEvent& event, bool isDouble);
  void processMouseDragged(const ca::MouseEvent& event);
  void processMouseReleased(const ca::MouseEvent& event);
  void processMouseMoved(const ca::MouseEvent& event);
  void processMouseWheel(const ca::MouseWheelEvent& event);
  void processKeyPressed(const ca::KeyEvent& event);
  void processKeyReleased(const ca::KeyEvent& event);

  // Keeps track of whether the last mouse event was a move event.
  bool m_lastMouseEventWasMove = false;

  // Keeps track of whether we have the mouse captured or not.
  bool m_hasCapture = false;

  // Keeps track of whether the mouse is down or not.
  bool m_isMouseDown = false;

  // Keeps track of the last position we moved the mouse at.
  fl::Pos m_lastMouseMovePos;

  // The view that we last pressed on.
  View* m_mousePressedHandler = nullptr;

  // The view that we last moved on.
  View* m_mouseMoveHandler = nullptr;
};

}  // namespace el
