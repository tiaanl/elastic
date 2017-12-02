
#ifndef ELASTIC_VIEWS_BUTTON_VIEW_H_
#define ELASTIC_VIEWS_BUTTON_VIEW_H_

#include <string>

#include "elastic/Views/View.h"

namespace el {

class ButtonView : public View {
public:
  class OnClickListener {
  public:
    virtual ~OnClickListener();
    virtual void onButtonClicked(ButtonView* sender) = 0;
  };

  ButtonView(Context* context, const std::string& label = std::string{}, OnClickListener* listener = nullptr);
  virtual ~ButtonView() override;

  // label
  const std::string& getLabel() const { return m_label; }
  void setLabel(const std::string& label);

  // Override: View
  bool handlesInput() const override { return true; }

  bool onMousePressed(const ca::MouseEvent& evt) override;
  void onMouseReleased(const ca::MouseEvent& evt) override;
  void onMouseEnter(const ca::MouseEvent& evt) override;
  void onMouseLeave(const ca::MouseEvent& evt) override;

  ca::Size<I32> calculateMinSize() const override;
  void layout(const ca::Rect<I32>& rect) override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  // The label we print on the button.
  std::string m_label;

  // A listener that will receive events when the button is clicked.
  OnClickListener* m_listener;

  // The shape we use to render a background for the button.
  // sf::RectangleShape m_backgroundShape;

  // The shape we use to render the label.
  // sf::Text m_labelShape;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ButtonView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_BUTTON_VIEW_H_
