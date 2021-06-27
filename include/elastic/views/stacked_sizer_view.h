#pragma once

#include "elastic/Views/group_view.h"

namespace el {

class StackedSizerView : public GroupView {
public:
  NU_DELETE_COPY_AND_MOVE(StackedSizerView);

  explicit StackedSizerView(Context* context);
  ~StackedSizerView() override;

  // Implement: GroupView
  fl::Size calculateMinSize() const override;
  void layout(const fl::Rect& rect) override;
};

}  // namespace el
