#pragma once

#include "elastic/Renderer/font.h"
#include "elastic/Views/view.h"
#include "elastic/context.h"

namespace el {

class LabelView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(LabelView);

  LabelView(Context* context, nu::StringView label, Font* font);
  ~LabelView() override;

  nu::StringView getLabel() const {
    return m_label.view();
  }
  void setLabel(const nu::StringView& label);

  // Override: View
  fl::Size calculateMinSize() const override;
  void render(Renderer* canvas, const fl::Mat4& mat) override;

private:
  nu::StaticString<128> m_label;

  Font* m_font;
};

}  // namespace el
