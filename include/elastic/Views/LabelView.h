
#ifndef ELASTIC_VIEWS_LABEL_VIEW_H_
#define ELASTIC_VIEWS_LABEL_VIEW_H_

#include "canvas/Primitives/Text.h"
#include "canvas/Rendering/Font.h"
#include "elastic/Context.h"
#include "elastic/Views/View.h"
#include "nucleus/Memory/ScopedPtr.h"

namespace el {

class LabelView : public View {
public:
  MOVE_DELETE(LabelView);
  COPY_DELETE(LabelView);

  LabelView(Context* context, nu::String label);
  virtual ~LabelView();

  const nu::String& getLabel() const {
    return m_label;
  }
  void setLabel(nu::String label);

  // Override: View
  ca::Size<I32> calculateMinSize() const override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  // Update the render primitive.
  void updateTextInternal();

  nu::String m_label;
  ca::Text m_text;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_LABEL_VIEW_H_
