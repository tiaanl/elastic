
#ifndef ELASTIC_VIEWS_LABEL_VIEW_H_
#define ELASTIC_VIEWS_LABEL_VIEW_H_

#include "canvas/Primitives/Text.h"
#include "canvas/rendering/font.h"
#include "elastic/context.h"
#include "elastic/views/view.h"

namespace el {

class LabelView : public View {
public:
  LabelView(Context* context, std::string label);
  virtual ~LabelView();

  const std::string& getLabel() const { return m_label; }
  void setLabel(std::string label);

  // Override: View
  ca::Size<I32> calculateMinSize() const override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  // Update the render primitive.
  void updateTextInternal();

  std::string m_label;
  ca::Text m_text;

  nu::ScopedPtr<ca::Font> m_font;

  DISALLOW_IMPLICIT_CONSTRUCTORS(LabelView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_LABEL_VIEW_H_
