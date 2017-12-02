
#ifndef ELASTIC_VIEWS_GROUP_VIEW_H_
#define ELASTIC_VIEWS_GROUP_VIEW_H_

#include <vector>

#include "elastic/Views/View.h"
#include "nucleus/Memory/ScopedPtr.h"

namespace el {

class GroupView : public View {
public:
  static ca::Rect<I32> layoutControlInRect(View* view, const ca::Rect<I32>& rect);

  explicit GroupView(Context* context);
  virtual ~GroupView();

  void addChild(View* view);
  void removeChild(View* view);

  // Return a pointer to the view that is at the given coordinates.
  virtual View* getViewAtPosition(const ca::Pos<I32>& pos) const override;

  // Override: View
  virtual void tick(float adjustment) override;

  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

protected:
  // This view's child views.
  std::vector<View*> m_children;

private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(GroupView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_GROUP_VIEW_H_
