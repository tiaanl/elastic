
#ifndef ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_
#define ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_

#include "elastic/Views/GroupView.h"

namespace el {

class LinearSizerView : public GroupView {
public:
  enum OrientationType {
    OrientationHorizontal,
    OrientationVertical,
  };

  explicit LinearSizerView(Context* context);
  LinearSizerView(Context* context, OrientationType orientation);
  virtual ~LinearSizerView();

  // orientation
  OrientationType GetOrientation() const { return m_orientation; }
  void SetOrientation(OrientationType orientation);

  // Override: GroupView
  virtual ca::Size<I32> calculateMinSize() const override;
  virtual void layout(const ca::Rect<I32>& rect) override;

private:
  void layoutHorizontal(const ca::Rect<I32>& rect);
  void layoutVertical(const ca::Rect<I32>& rect);

  // The orientaion of the sizer.
  OrientationType m_orientation;

  DISALLOW_IMPLICIT_CONSTRUCTORS(LinearSizerView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_
