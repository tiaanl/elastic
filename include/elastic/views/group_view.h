#pragma once

#include "elastic/Views/view.h"
#include "nucleus/Containers/dynamic_array.h"

namespace el {

class GroupView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(GroupView);

  static fl::Rect layoutControlInRect(View* view, const fl::Rect& rect);

  explicit GroupView(Context* context);
  ~GroupView() override;

  void addChild(View* view);
  void removeChild(View* view);

  // Return a pointer to the view that is at the given coordinates.
  View* getViewAtPosition(const fl::Pos& pos) const override;

  // Override: View
  void tick(float delta) override;

  void render(Renderer* renderer, const fl::Mat4& mat) override;

protected:
  // This view's child views.
  nu::DynamicArray<View*> m_children;
};

}  // namespace el
