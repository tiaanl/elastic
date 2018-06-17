
#ifndef ELASTIC_VIEWS_TEXT_VIEW_H_
#define ELASTIC_VIEWS_TEXT_VIEW_H_

#include "canvas/Primitives/Text.h"
#include "canvas/Resources/Resource.h"
#include "elastic/Views/View.h"

namespace el {

class TextView : public View {
public:
  MOVE_DELETE(TextView);
  COPY_DELETE(TextView);

  explicit TextView(Context* context, const nu::String& label = nu::String{});
  ~TextView() override;

  // label
  const nu::String& getLabel() const {
    return m_label;
  }
  void setLabel(const nu::String& label);

  // font
  const ca::ResourceRef<ca::Font>& getFont() const {
    return m_font;
  }
  void setFont(const ca::ResourceRef<ca::Font>& font);

  // Override: View
  ca::Size<I32> calculateMinSize() const override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  // The label we render.
  nu::String m_label;

  // Hold a reference to the font we're using.
  ca::ResourceRef<ca::Font> m_font;

  // The shape we use to render the text.
  ca::Text m_text;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_TEXT_VIEW_H_
