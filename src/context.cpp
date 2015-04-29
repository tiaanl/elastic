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

#include "elastic/context.h"

namespace el {

Context::Context() : m_contextView(this) {
}

Context::~Context() {
}

void Context::setFocusView(View* view) {
  m_focusView = view;
}

void Context::handleInput(sf::Event& event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed: {
      m_contextView.processMousePressed(event, false);
    } break;

    case sf::Event::MouseMoved: {
      m_contextView.processMouseMoved(event);
    } break;

    case sf::Event::MouseButtonReleased: {
      m_contextView.processMouseReleased(event);
    } break;

    case sf::Event::MouseWheelMoved: {
      m_contextView.processMouseWheel(event);
    } break;

    case sf::Event::KeyPressed: {
      m_contextView.processKeyPressed(event);
      break;
    }

    case sf::Event::KeyReleased: {
      m_contextView.processKeyReleased(event);
      break;
    }

    default:
      break;
  }
}

void Context::tick(float adjustment) {
  m_contextView.tick(adjustment);
}

void Context::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Get the size of the render target in pixels for the UI to render.
  sf::IntRect layoutRect{0, 0, static_cast<int>(target.getSize().x),
                         static_cast<int>(target.getSize().y)};

  m_contextView.layout(layoutRect);
  target.draw(m_contextView, states);
}

}  // namespace el
