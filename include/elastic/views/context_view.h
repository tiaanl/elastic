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

#ifndef ELASTIC_VIEWS_CONTEXT_VIEW_H_
#define ELASTIC_VIEWS_CONTEXT_VIEW_H_

#include "elastic/views/stacked_sizer_view.h"

namespace el {

class ContextView : public StackedSizerView {
public:
  explicit ContextView(Context* context);
  virtual ~ContextView();

  // Override: StackedSizerView
  virtual bool onMousePressed(sf::Event& event) override;
  virtual bool onMouseDragged(sf::Event& event) override;
  virtual void onMouseReleased(sf::Event& event) override;
  virtual void onMouseMoved(sf::Event& event) override;

private:
  friend class Context;

  // Initiate user input from the context.
  bool processMousePressed(sf::Event& event, bool isDouble);
  void processMouseDragged(sf::Event& event);
  void processMouseReleased(sf::Event& event);
  void processMouseMoved(sf::Event& event);
  void processMouseWheel(sf::Event& event);
  void processKeyPressed(sf::Event& event);
  void processKeyReleased(sf::Event& event);

  // Keeps track of whether the last mouse event was a move event.
  bool m_lastMouseEventWasMove{false};

  // Keeps track of whether we have the mouse captured or not.
  bool m_hasCapture{false};

  // Keeps track of whether the mouse is down or not.
  bool m_isMouseDown{false};

  // Keeps track of the last position we moved the mouse at.
  sf::Vector2i m_lastMouseMovePos;

  // The view that we last pressed on.
  View* m_mousePressedHandler{nullptr};

  // The view that we last moved on.
  View* m_mouseMoveHandler{nullptr};

  DISALLOW_IMPLICIT_CONSTRUCTORS(ContextView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_CONTEXT_VIEW_H_
