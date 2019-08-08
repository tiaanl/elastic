
#include "elastic/Views/ButtonView.h"

#include "elastic/Context.h"

#include "nucleus/MemoryDebug.h"

namespace el {

ButtonView::OnClickListener::~OnClickListener() = default;

ButtonView::ButtonView(Context* context, const nu::StringView& label, OnClickListener* listener)
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

ButtonView::~ButtonView() = default;

void ButtonView::setLabel(const nu::StringView& label) {
  m_label = label;
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

void ButtonView::onMouseEnter(const ca::MouseEvent& UNUSED(event)) {
}

void ButtonView::onMouseLeave(const ca::MouseEvent& UNUSED(event)) {
}

ca::Size ButtonView::calculateMinSize() const {
  ca::Size result = View::calculateMinSize();

  return result;
}

void ButtonView::layout(const ca::Rect& rect) {
  View::layout(rect);
}

void ButtonView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);
}

}  // namespace el
