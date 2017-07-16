// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "elastic/views/context_view.h"

#include "elastic/context.h"

namespace el {

ContextView::ContextView(Context* context) : StackedSizerView(context) {
}

ContextView::~ContextView() {
}

bool ContextView::onMousePressed(const ca::MouseEvent& event) {
  // If m_mousePressedHandler is not null, we are currently processing a
  // pressed->drag->released session.  In that case we send the event to
  // m_mousePressedHandler.
  if (m_mousePressedHandler) {
    m_mousePressedHandler->onMousePressed(event);
    return true;
  }

  ca::Pos<I32> mousePos = event.pos;

  for (m_mousePressedHandler = getViewAtPosition(mousePos);
       m_mousePressedHandler && (m_mousePressedHandler != this);
       m_mousePressedHandler = m_mousePressedHandler->getParent()) {
    bool handled = m_mousePressedHandler->onMousePressed(event);

    // The view could have removed itself from the tree when handling
    // onMousePressed().  In this case, the removal notification will have reset
    // m_mousePressedHandler to null.  Detect this case and stop.
    // We don't return true here, because we don't want the context to forward
    // future events to us when there is no handler.
    if (!m_mousePressedHandler) {
      break;
    }

    // If the view handled the event, leave m_mousePressedHandler set and return
    // true, which will cause subsequent drag/release events to get forwarded to
    // that view.
    if (handled) {
      return true;
    }
  }

  // Reset m_mousePressedHandler to indicate that no processing is occurring.
  m_mousePressedHandler = nullptr;

  return false;
}

bool ContextView::onMouseDragged(const ca::MouseEvent& event) {
  if (m_mousePressedHandler) {
    return m_mousePressedHandler->onMouseDragged(event);
  }
  return false;
}

void ContextView::onMouseReleased(const ca::MouseEvent& event) {
  if (m_mousePressedHandler) {
    View* mousePressedHandler = m_mousePressedHandler;
    m_mousePressedHandler = nullptr;
    mousePressedHandler->onMouseReleased(event);
    // Don't touch mousePressedHandler any more.
  }
}

void ContextView::onMouseMoved(const ca::MouseEvent& event) {
  View* topMost = getViewAtPosition(event.pos);

  if (topMost && topMost != this) {
    // If we switched topMost controls, then we entered a new control.
    if (topMost != m_mouseMoveHandler) {
      // If we had a previous move handler, then we send it an exit event.
      if (m_mouseMoveHandler) {
        m_mouseMoveHandler->onMouseLeave(event);
      }

      // Set the new mouse move handler to what we have as top most now.
      m_mouseMoveHandler = topMost;

      // Send the new move handler an aneter event.
      m_mouseMoveHandler->onMouseEnter(event);
    }

    // Now send the move event.
    m_mouseMoveHandler->onMouseMoved(event);
  } else if (m_mouseMoveHandler) {
    m_mouseMoveHandler->onMouseLeave(event);
  }
}

bool ContextView::processMousePressed(const ca::MouseEvent& event, bool isDouble) {
  m_lastMouseEventWasMove = false;

  if (onMousePressed(event)) {
    m_isMouseDown = true;

    if (!m_hasCapture) {
      m_hasCapture = true;
    }

    return true;
  }

  return false;
}

void ContextView::processMouseDragged(const ca::MouseEvent& event) {
  m_lastMouseEventWasMove = false;

  onMouseDragged(event);
}

void ContextView::processMouseReleased(const ca::MouseEvent& event) {
  m_lastMouseEventWasMove = false;

  if (m_hasCapture) {
    m_hasCapture = false;
  }

  m_isMouseDown = false;

  onMouseReleased(event);
}

void ContextView::processMouseMoved(const ca::MouseEvent& event) {
  if (m_hasCapture && m_isMouseDown) {
    processMouseDragged(event);
  } else {
    if (m_lastMouseEventWasMove && (m_lastMouseMovePos == event.pos)) {
      return;
    }
    m_lastMouseMovePos = event.pos;
    m_lastMouseEventWasMove = true;
    onMouseMoved(event);
  }
}

void ContextView::processMouseWheel(const ca::MouseWheelEvent& event) {
  View* view = getViewAtPosition(event.pos);

  if (!view) {
    return;
  }

  view->onMouseWheel(event);
}

void ContextView::processKeyPressed(const ca::KeyEvent& event) {
  if (!m_context->getFocusView()) {
    return;
  }

  m_context->getFocusView()->onKeyPressed(event);
}

void ContextView::processKeyReleased(const ca::KeyEvent& event) {
  if (!m_context->getFocusView()) {
    return;
  }

  m_context->getFocusView()->onKeyReleased(event);
}

}  // namespace el
