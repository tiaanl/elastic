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

#include "elastic/views/text_view.h"

#include "elastic/context.h"

namespace el {

TextView::TextView(Context* context, const std::string& label) : View(context), m_label(label) {
    // Set up the text shape.
    // sf::Font* labelFont = context->getFont("default");

    // Set up the label.
    // if (labelFont) {
    //     m_shape.setString(m_label);
    //     m_shape.setFont(*labelFont);
    //     m_shape.setColor(sf::Color{255, 255, 255});
    //     m_shape.setCharacterSize(30);
    // }
}

TextView::~TextView() {}

void TextView::setLabel(const std::string& label) {
    m_label = label;

    // Set the label on the shape.
    // m_shape.setString(label);
}

ca::Size<I32> TextView::calculateMinSize() const {
    // ca::Rect<F32> bounds = m_shape.getLocalBounds();
    // return sf::Vector2i{static_cast<int>(std::ceil(bounds.width)), static_cast<int>(std::ceil(bounds.height))};

    return View::calculateMinSize();
}

void TextView::layout(const ca::Rect<I32>& rect) {
    // sf::FloatRect floatLabelSize = m_shape.getLocalBounds();

    // Move the shape to the correct position.
    // m_shape.setPosition(sf::Vector2f{static_cast<float>(rect.left) - floatLabelSize.left,
    // static_cast<float>(rect.top) - floatLabelSize.top});
}

void TextView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
    View::render(canvas, mat);

    // target.draw(m_shape, states);
}

}  // namespace el
