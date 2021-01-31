
#include "elastic/Views/ButtonView.h"

#include "elastic/Context.h"

namespace el {

ButtonView::OnClickListener::~OnClickListener() = default;

ButtonView::ButtonView(Context* context, const nu::StringView& label, OnClickListener* listener)
  : View(context), m_label{label}, m_listener{listener} {}

ButtonView::~ButtonView() = default;

auto ButtonView::setFont(Font* font) -> void {
  m_font = font;
}

void ButtonView::setLabel(const nu::StringView& label) {
  m_label = label;
}

bool ButtonView::onMousePressed(const ca::MouseEvent& evt) {
  View::onMousePressed(evt);

  LOG(Info) << "onMousePressed";

  return true;
}

void ButtonView::onMouseReleased(const ca::MouseEvent& event) {
  View::onMouseReleased(event);

  LOG(Info) << "onMouseReleased";

  if (m_listener) {
    m_listener->onButtonClicked(this);
  }
}

fl::Size ButtonView::calculateMinSize() const {
  auto minSize = View::calculateMinSize();

  if (m_font && !m_label.empty()) {
    auto extent = m_font->calculateTextExtent(m_label.view());
    minSize = fl::maximum(minSize, extent);
  }

  return minSize;
}

void ButtonView::layout(const fl::Rect& rect) {
  View::layout(rect);
}

void ButtonView::render(Renderer* renderer, const fl::Mat4& mat) {
  View::render(renderer, mat);

  renderer->renderQuad(m_rect, ca::Color::red);

  if (m_font) {
    auto extent = m_font->calculateTextExtent(m_label.view());
    F32 x = static_cast<F32>(m_rect.size.width) / 2.0f - static_cast<F32>(extent.width) / 2.0f;
    F32 y = static_cast<F32>(m_rect.size.height) / 2.0f - static_cast<F32>(extent.height) / 2.0f;
    auto offset = fl::Pos{static_cast<I32>(std::round(x)), static_cast<I32>(std::round(y))};
    renderer->renderText(m_font, m_rect.pos + offset, m_label.view());
  }
}

}  // namespace el
