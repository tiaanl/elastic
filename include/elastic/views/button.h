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

#ifndef ELASTIC_VIEWS_BUTTON_H_
#define ELASTIC_VIEWS_BUTTON_H_

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "elastic/views/view.h"

namespace el {

class Button : public View {
public:
  class OnClickListener {
  public:
    virtual ~OnClickListener();
    virtual void onButtonClicked(Button* sender) = 0;
  };

  Button(Context* context, const std::string& label = std::string{},
         OnClickListener* listener = nullptr);
  virtual ~Button() override;

  // label
  const std::string& getLabel() const { return m_label; }
  void setLabel(const std::string& label);

  // Override: View
  virtual bool handlesInput() const { return true; }
  virtual bool onMousePressed(sf::Event& event) override;
  virtual void onMouseReleased(sf::Event& event) override;
  virtual void onMouseEntered(sf::Event& event) override;
  virtual void onMouseExited(sf::Event& event) override;
  virtual sf::Vector2i calculateMinSize() const override;
  virtual void layout(const sf::IntRect& rect) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  // The label we print on the button.
  std::string m_label;

  // A listener that will receive events when the button is clicked.
  OnClickListener* m_listener;

  // The shape we use to render a background for the button.
  sf::RectangleShape m_backgroundShape;

  // The shape we use to render the label.
  sf::Text m_labelShape;

  DISALLOW_IMPLICIT_CONSTRUCTORS(Button);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_BUTTON_H_
