
#ifndef ELASTIC_VIEWS_TEXT_VIEW_H_
#define ELASTIC_VIEWS_TEXT_VIEW_H_

#include "canvas/Primitives/Text.h"
#include "elastic/views/view.h"

namespace el {

class TextView : public View {
public:
  explicit TextView(Context* context, const std::string& label = std::string{});
  ~TextView() override;

  // label
  const std::string& getLabel() const { return m_label; }
  void setLabel(const std::string& label);

  // Override: View
  ca::Size<I32> calculateMinSize() const override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  // The label we render.
  std::string m_label;

  // The shape we use to render the text.
  ca::Text m_text;

  DISALLOW_IMPLICIT_CONSTRUCTORS(TextView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_TEXT_VIEW_H_
