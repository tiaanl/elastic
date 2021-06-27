#pragma once

#include "elastic/Views/group_view.h"

namespace el {

enum class Orientation : U32 {
  Horizontal,
  Vertical,
};

class LinearSizerView : public GroupView {
public:
  NU_DELETE_COPY_AND_MOVE(LinearSizerView);

  explicit LinearSizerView(Context* context, Orientation orientation = Orientation::Horizontal);
  ~LinearSizerView() override;

  // orientation
  Orientation getOrientation() const {
    return m_orientation;
  }
  void setOrientation(Orientation orientation);

  // Override: GroupView
  fl::Size calculateMinSize() const override;
  void layout(const fl::Rect& rect) override;

private:
  void layoutHorizontal(const fl::Rect& rect);
  void layoutVertical(const fl::Rect& rect);

  // The orientation of the sizer.
  Orientation m_orientation;
};

}  // namespace el
