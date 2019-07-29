#ifndef ELASTIC_VIEWS_IMAGE_VIEW_H_
#define ELASTIC_VIEWS_IMAGE_VIEW_H_

#include "canvas/Renderer/Types.h"
#include "elastic/Views/View.h"
#include "hive/Resource.h"
#include "hive/Resources/Texture.h"

namespace el {

class ImageView : public View {
public:
  explicit ImageView(Context* context,
                     const hi::Resource<hi::Texture>& texture = {nullptr, nullptr});
  ~ImageView() override;

  const hi::Resource<hi::Texture>& getTexture() const {
    return m_texture;
  }

  void setTexture(const hi::Resource<hi::Texture>& texture) {
    m_texture = texture;
  }

  ca::Size calculateMinSize() const override;
  void render(Renderer* renderer, const ca::Mat4& mat) override;

private:
  DELETE_COPY_AND_MOVE(ImageView);

  hi::Resource<hi::Texture> m_texture;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_IMAGE_VIEW_H_
