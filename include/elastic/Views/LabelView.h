
#ifndef ELASTIC_VIEWS_LABEL_VIEW_H_
#define ELASTIC_VIEWS_LABEL_VIEW_H_

#include "elastic/Context.h"
#include "elastic/Renderer/Font.h"
#include "elastic/Views/View.h"

namespace el {

class LabelView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(LabelView);

  LabelView(Context* context, const nu::StringView& label, Font* font);
  ~LabelView() override;

  const nu::StringView& getLabel() const {
    return m_label;
  }
  void setLabel(const nu::StringView& label);

  // Override: View
  ca::Size calculateMinSize() const override;
  void render(Renderer* canvas, const ca::Mat4& mat) override;

private:
  nu::StaticString<128> m_label;

  Font* m_font;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_LABEL_VIEW_H_
