
#ifndef ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_
#define ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_

#include "elastic/Views/GroupView.h"

namespace el {

class StackedSizerView : public GroupView {
public:
  explicit StackedSizerView(Context* context);
  ~StackedSizerView() override;

  // Implement: GroupView
  ca::Size calculateMinSize() const override;
  void layout(const ca::Rect& rect) override;

private:
  DELETE_COPY_AND_MOVE(StackedSizerView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_
