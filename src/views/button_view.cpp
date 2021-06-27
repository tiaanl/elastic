
#include "elastic/Views/button_view.h"

#include "elastic/context.h"

namespace el {

class LambdaListener : public ButtonView::OnClickListener {
public:
  explicit LambdaListener(nu::Function<void(ButtonView*)> listener)
    : listener_{std::move(listener)} {}

  void onButtonClicked(ButtonView* sender) override {
    listener_(sender);
  }

private:
  nu::Function<void(ButtonView*)> listener_;
};

ButtonView::OnClickListener::~OnClickListener() = default;

ButtonView::ButtonView(Context* context, nu::StringView label, OnClickListener* listener)
  : View(context), m_label{label}, m_listener{listener} {}

ButtonView::ButtonView(Context* context, nu::StringView label,
                       nu::Function<void(ButtonView*)> listener)
  : View{context}, m_label{label}, m_listener{new LambdaListener{std::move(listener)}} {}

ButtonView::~ButtonView() = default;

auto ButtonView::setFont(Font* font) -> void {
  m_font = font;
}

void ButtonView::background(Image background) {
  background_ = std::move(background);
}

void ButtonView::setLabel(const nu::StringView& label) {
  m_label = label;
}

bool ButtonView::on_mouse_pressed(const ca::MouseEvent& evt) {
  View::on_mouse_pressed(evt);

  return true;
}

void ButtonView::on_mouse_released(const ca::MouseEvent& event) {
  View::on_mouse_released(event);

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

  if (background_.getSize().area() > 0) {
    // renderer->renderQuad(m_rect, ca::Color::red);
    renderer->renderQuad(m_rect, background_);
  }

  if (m_font) {
    auto extent = m_font->calculateTextExtent(m_label.view());
    F32 x = static_cast<F32>(m_rect.size.width) / 2.0f - static_cast<F32>(extent.width) / 2.0f;
    F32 y = static_cast<F32>(m_rect.size.height) / 2.0f - static_cast<F32>(extent.height) / 2.0f;
    auto offset = fl::Pos{static_cast<I32>(std::round(x)), static_cast<I32>(std::round(y))};
    renderer->renderText(m_font, m_rect.pos + offset, m_label.view());
  }
}

}  // namespace el
