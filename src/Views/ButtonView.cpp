
#include "elastic/Views/ButtonView.h"

#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

ButtonView::OnClickListener::~OnClickListener() {}

ButtonView::ButtonView(Context* context, const std::string& label, OnClickListener* listener)
  : View(context), m_label(label), m_listener(listener) {
  // sf::Font* buttonFont = context->getFont("default");

  // Set up the background shape.
  // m_backgroundShape.setFillColor(sf::Color{255, 255, 255, 127});
  // m_backgroundShape.setOutlineColor(sf::Color{127, 255, 127});
  // m_backgroundShape.setOutlineThickness(1);

  // Set up the label.
  // if (buttonFont) {
  //   m_labelShape.setString(m_label);
  //   m_labelShape.setFont(*buttonFont);
  //   m_labelShape.setColor(sf::Color{127, 255, 127});
  //   m_labelShape.setCharacterSize(25);
  // }
}

ButtonView::~ButtonView() {}

void ButtonView::setLabel(const std::string& label) {
  m_label = label;
  // m_labelShape.setString(label);
}

bool ButtonView::onMousePressed(const ca::MouseEvent& evt) {
  View::onMousePressed(evt);
  return true;
}

void ButtonView::onMouseReleased(const ca::MouseEvent& event) {
  View::onMouseReleased(event);

  if (m_listener) {
    m_listener->onButtonClicked(this);
  }
}

void ButtonView::onMouseEnter(const ca::MouseEvent& event) {
  // m_backgroundShape.setFillColor(sf::Color{255, 255, 255, 191});
}

void ButtonView::onMouseLeave(const ca::MouseEvent& event) {
  // m_backgroundShape.setFillColor(sf::Color{255, 255, 255, 127});
}

ca::Size<I32> ButtonView::calculateMinSize() const {
  ca::Size<I32> result = View::calculateMinSize();

  // Calculate the size of the label.
  // sf::FloatRect floatLabelSize{m_labelShape.getLocalBounds()};

  // sf::Vector2i labelSize{static_cast<int>(std::ceil(floatLabelSize.width)),
  //                        static_cast<int>(std::ceil(floatLabelSize.height))};

  // Add a border around the label.
  // labelSize.x += 20;
  // labelSize.y += 20;

  // result.x = std::max(result.x, labelSize.x);
  // result.y = std::max(result.y, labelSize.y);

  return result;
}

void ButtonView::layout(const ca::Rect<I32>& rect) {
  View::layout(rect);

  // Move the background shape into position.
  // m_backgroundShape.setPosition(sf::Vector2f{static_cast<float>(rect.left), static_cast<float>(rect.top)});
  // m_backgroundShape.setSize(sf::Vector2f{static_cast<float>(rect.width), static_cast<float>(rect.height)});

  // sf::FloatRect floatLabelSize{m_labelShape.getLocalBounds()};

  // Move the shape to the correct position.
  // m_labelShape.setPosition(sf::Vector2f{static_cast<float>(rect.left + 10) - floatLabelSize.left,
  //                                       static_cast<float>(rect.top + 10) - floatLabelSize.top});
}

void ButtonView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  // target.draw(m_backgroundShape);
  // target.draw(m_labelShape);
}

}  // namespace el
