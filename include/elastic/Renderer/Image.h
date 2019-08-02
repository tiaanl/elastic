#ifndef ELASTIC_RENDERER_IMAGE_H_
#define ELASTIC_RENDERER_IMAGE_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Macros.h"

namespace el {

class Image {
public:
  Image() = default;

  Image(ca::TextureId textureId, const ca::Size& size) : m_textureId{textureId}, m_size{size} {}

  const ca::TextureId& getTextureId() const {
    return m_textureId;
  }

  const ca::Size& getSize() const {
    return m_size;
  }

private:
  ca::TextureId m_textureId;
  ca::Size m_size;
};

}  // namespace el

#endif  // ELASTIC_RENDERER_IMAGE_H_
