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

#include "elastic/views/color_view.h"

#include "nucleus/logging.h"

namespace el {

ColorView::ColorView(Context* context) : View(context) {
}

ColorView::ColorView(Context* context, const sf::Color& color) : View(context) {
  setColor(color);
}

ColorView::~ColorView() {
}

void ColorView::setColor(const sf::Color& color) {
  m_color = color;
  m_drawable.setFillColor(color);
}

void ColorView::layout(const sf::IntRect& rect) {
  View::layout(rect);

  LOG(Info) << m_name << " = (" << rect.left << ", " << rect.top << ") x (" << rect.width << ", " << rect.height << ")";

  m_drawable.setPosition(sf::Vector2f(static_cast<float>(rect.left),
                                      static_cast<float>(rect.top)));
  m_drawable.setSize(sf::Vector2f(static_cast<float>(rect.width),
                                  static_cast<float>(rect.height)));
}

void ColorView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_drawable, states);
}

}  // namespace el
