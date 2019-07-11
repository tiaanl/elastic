
#ifndef ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_
#define ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_

#include "elastic/Views/GroupView.h"

namespace el {

enum class Orientation : U32 {
  Horizontal,
  Vertical,
};

class LinearSizerView : public GroupView {
public:
  explicit LinearSizerView(Context* context, Orientation orientation = Orientation::Horizontal);
  ~LinearSizerView() override;

  // orientation
  Orientation getOrientation() const {
    return m_orientation;
  }
  void setOrientation(Orientation orientation);

  // Override: GroupView
  ca::Size calculateMinSize() const override;
  void layout(const ca::Rect& rect) override;

private:
  DELETE_COPY_AND_MOVE(LinearSizerView);

  void layoutHorizontal(const ca::Rect& rect);
  void layoutVertical(const ca::Rect& rect);

  // The orientation of the sizer.
  Orientation m_orientation;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_LINEAR_SIZER_VIEW_H_
