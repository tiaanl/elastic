#pragma once

#include "canvas/Renderer/types.h"
#include "elastic/Renderer/image.h"
#include "elastic/Views/view.h"

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

  fl::Size calculateMinSize() const override;
  void render(Renderer* renderer, const fl::Mat4& mat) override;

private:
  Image* m_image;
};

}  // namespace el
