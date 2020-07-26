
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
  const nu::StringView& getLabel() const {
    return m_label;
  }
  void setLabel(const nu::StringView& label);

  // Override: View
  bool handlesInput() const override {
    return true;
  }
  bool onMousePressed(const ca::MouseEvent& evt) override;
  void onMouseReleased(const ca::MouseEvent& evt) override;
  ca::Size calculateMinSize() const override;
  void layout(const ca::Rect& rect) override;
  void render(Renderer* renderer, const ca::Mat4& mat) override;

private:
  // The label we print on the button.
  nu::StaticString<128> m_label;

  Font* m_font = nullptr;

  // A listener that will receive events when the button is clicked.
  OnClickListener* m_listener = nullptr;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_BUTTON_VIEW_H_
