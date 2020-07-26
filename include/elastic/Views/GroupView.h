
#ifndef ELASTIC_VIEWS_GROUP_VIEW_H_
#define ELASTIC_VIEWS_GROUP_VIEW_H_

#include "elastic/Views/View.h"
#include "nucleus/Containers/DynamicArray.h"

namespace el {

class GroupView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(GroupView);

  static ca::Rect layoutControlInRect(View* view, const ca::Rect& rect);

  explicit GroupView(Context* context);
  ~GroupView() override;

  void addChild(View* view);
  void removeChild(View* view);

  // Return a pointer to the view that is at the given coordinates.
  View* getViewAtPosition(const ca::Pos& pos) const override;

  // Override: View
  void tick(float delta) override;

  void render(Renderer* renderer, const ca::Mat4& mat) override;

protected:
  // This view's child views.
  nu::DynamicArray<View*> m_children;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_GROUP_VIEW_H_
