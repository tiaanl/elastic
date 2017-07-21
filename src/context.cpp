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

#include "canvas/math/transform.h"

namespace el {

Context::Context() : m_contextView(this) {}

Context::~Context() {}

void Context::setFocusView(View* view) {
    m_focusView = view;
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

void Context::tick(float adjustment) {
    m_contextView.tick(adjustment);
}

void Context::render(ca::Canvas* canvas) {
    // Get the size of the render target in pixels for the UI to render.
    ca::Rect<I32> layoutRect{ca::Pos<I32>(0, 0), canvas->getSize()};

    F32 width = static_cast<F32>(layoutRect.size.width);
    F32 height = static_cast<F32>(layoutRect.size.height);

    ca::Mat4 ortho = ca::ortho(0.f, width, height, 0.f);

    m_contextView.layout(layoutRect);
    m_contextView.render(canvas, ortho);
}

}  // namespace el
