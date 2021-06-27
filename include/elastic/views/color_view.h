#pragma once

#include "elastic/Views/view.h"

namespace el {

class ColorView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(ColorView);

  explicit ColorView(Context* context, const ca::Color& color = ca::Color::white);
  ~ColorView() override;

  // color
  const ca::Color& getColor() const {
    return m_color;
  }
  void setColor(const ca::Color& color);

  // Override: View
  void layout(const fl::Rect& rect) override;
  void render(Renderer* renderer, const fl::Mat4& mat) override;

private:
  // The color of the view.
  ca::Color m_color;
};

}  // namespace el
