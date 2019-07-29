
#include "elastic/Views/ImageView.h"

namespace el {

ImageView::ImageView(Context* context, ca::TextureId texture) : View{context}, m_texture{texture} {}

ImageView::~ImageView() = default;

ca::Size ImageView::calculateMinSize() const {
  return View::calculateMinSize();
}

void ImageView::layout(const ca::Rect& rect) {
  View::layout(rect);
}

}  // namespace el
