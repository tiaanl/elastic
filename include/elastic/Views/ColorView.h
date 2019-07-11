
#ifndef ELASTIC_VIEWS_COLOR_VIEW_H_
#define ELASTIC_VIEWS_COLOR_VIEW_H_

#include "elastic/Views/View.h"

namespace el {

class ColorView : public View {
public:
  explicit ColorView(Context* context, const ca::Color& color = ca::Color::white);
  ~ColorView() override;

  // color
  const ca::Color& getColor() const {
    return m_color;
  }
  void setColor(const ca::Color& color);

  // Override: View
  void layout(const ca::Rect& rect) override;
  void render(Renderer* renderer, const ca::Mat4& mat) override;

private:
  DELETE_COPY_AND_MOVE(ColorView);

  // The color of the view.
  ca::Color m_color;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_COLOR_VIEW_H_
