#ifndef ELASTIC_VIEWS_IMAGE_VIEW_H_
#define ELASTIC_VIEWS_IMAGE_VIEW_H_

#include "canvas/Renderer/Types.h"
#include "elastic/Views/View.h"

namespace el {

class ImageView : public View {
public:
  explicit ImageView(Context* context, ca::TextureId texture = {});
  ~ImageView() override;

  ca::TextureId getTexture() const {
    return m_texture;
  }

  void setTexture(ca::TextureId texture) {
    m_texture = texture;
  }

  ca::Size calculateMinSize() const override;
  void layout(const ca::Rect& rect) override;

private:
  DELETE_COPY_AND_MOVE(ImageView);

  ca::TextureId m_texture;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_IMAGE_VIEW_H_
