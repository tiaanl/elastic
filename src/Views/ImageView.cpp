
#include "elastic/Views/ImageView.h"

namespace el {

ImageView::ImageView(Context* context, const hi::Resource<hi::Texture>& texture)
  : View{context}, m_texture{texture} {}

ImageView::~ImageView() = default;

ca::Size ImageView::calculateMinSize() const {
  ca::Size minSize = View::calculateMinSize();
  if (m_texture) {
    ca::Size textureSize = m_texture->getSize();

    minSize.width = std::max(minSize.width, textureSize.width);
    minSize.height = std::max(minSize.height, textureSize.height);
  }

  return minSize;
}

void ImageView::render(Renderer* renderer, const ca::Mat4& mat) {
  View::render(renderer, mat);

  if (m_texture) {
    renderer->renderQuad(m_rect, m_texture->getTextureId());
  }
}

}  // namespace el
