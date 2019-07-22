#ifndef ELASTIC_VIEWS_IMAGE_VIEW_H_
#define ELASTIC_VIEWS_IMAGE_VIEW_H_

#include "elastic/Views/View.h"

namespace el {

class ImageView : public View {
public:
  explicit ImageView(Context* context);
  ~ImageView() override;

private:
  DELETE_COPY_AND_MOVE(ImageView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_IMAGE_VIEW_H_
