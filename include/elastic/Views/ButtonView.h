
#ifndef ELASTIC_VIEWS_BUTTON_VIEW_H_
#define ELASTIC_VIEWS_BUTTON_VIEW_H_

#include <string>

#include "elastic/Views/View.h"

namespace el {

class ButtonView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(ButtonView);

  class OnClickListener {
  public:
    virtual ~OnClickListener();
    virtual void onButtonClicked(ButtonView* sender) = 0;
  };

  explicit ButtonView(Context* context, const nu::StringView& label = nu::StringView{},
                      OnClickListener* listener = nullptr);
  ~ButtonView() override;

  // font
  auto font() const -> Font* {
    return m_font;
  }
  auto setFont(Font* font) -> void;

  // label
  nu::StringView getLabel() const {
    return m_label.view();
  }
  void setLabel(const nu::StringView& label);

  // Override: View
  bool handlesInput() const override {
    return true;
  }
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  fl::Size calculateMinSize() const override;
  void layout(const fl::Rect& rect) override;
  void render(Renderer* renderer, const fl::Mat4& mat) override;

private:
  // The label we print on the button.
  nu::StaticString<128> m_label;

  Font* m_font = nullptr;

  // A listener that will receive events when the button is clicked.
  OnClickListener* m_listener = nullptr;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_BUTTON_VIEW_H_
