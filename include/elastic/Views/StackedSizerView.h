
#ifndef ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_
#define ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_

#include "elastic/views/group_view.h"

namespace el {

class StackedSizerView : public GroupView {
public:
  explicit StackedSizerView(Context* context);
  virtual ~StackedSizerView();

  // Implement: GroupView
  virtual ca::Size<I32> calculateMinSize() const override;
  virtual void layout(const ca::Rect<I32>& rect) override;

private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(StackedSizerView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_STACKED_SIZER_VIEW_H_
