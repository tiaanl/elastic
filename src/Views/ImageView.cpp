
#include "elastic/Views/ImageView.h"

namespace el {

ImageView::ImageView(Context* context, Image* image) : View{context}, m_image{image} {}

ImageView::~ImageView() = default;

fl::Size ImageView::calculateMinSize() const {
  fl::Size minSize = View::calculateMinSize();

  if (m_image) {
    fl::Size textureSize = m_image->getSize();

    minSize.width = std::max(minSize.width, textureSize.width);
    minSize.height = std::max(minSize.height, textureSize.height);
  }

  return minSize;
}

void ImageView::render(Renderer* renderer, const fl::Mat4& mat) {
  View::render(renderer, mat);

  if (m_image) {
    renderer->renderQuad(m_rect, *m_image);
  }
}

}  // namespace el
