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

#ifndef ELASTIC_VIEWS_COLOR_VIEW_H_
#define ELASTIC_VIEWS_COLOR_VIEW_H_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "elastic/views/view.h"

namespace el {

class ColorView : public View {
public:
  explicit ColorView(Context* context);
  ColorView(Context* context, const sf::Color& color);
  virtual ~ColorView();

  // color
  const sf::Color& getColor() const { return m_color; }
  void setColor(const sf::Color& color);

  // Override: View
  virtual void layout(const sf::IntRect& rect) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  // The color of the view.
  sf::Color m_color;

  // The geometry used to render the view.
  sf::RectangleShape m_drawable;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ColorView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_COLOR_VIEW_H_
