#ifndef ELASTIC_VIEWS_IMAGE_VIEW_H_
#define ELASTIC_VIEWS_IMAGE_VIEW_H_

#include "canvas/Renderer/Types.h"
#include "elastic/Renderer/Image.h"
#include "elastic/Views/View.h"

namespace el {

class ImageView : public View {
public:
  NU_DELETE_COPY_AND_MOVE(ImageView);

  explicit ImageView(Context* context, Image* image = nullptr);
  ~ImageView() override;

  Image* getImage() const {
    return m_image;
  }

  void setImage(Image* image) {
    m_image = image;
  }

  ca::Size calculateMinSize() const override;
  void render(Renderer* renderer, const ca::Mat4& mat) override;

private:
  Image* m_image;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_IMAGE_VIEW_H_
