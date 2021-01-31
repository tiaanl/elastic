#ifndef ELASTIC_RENDERER_IMAGE_H_
#define ELASTIC_RENDERER_IMAGE_H_

#include "canvas/Renderer/Types.h"
#include "floats/Size.h"
#include "nucleus/Macros.h"

namespace el {

class Image {
public:
  Image() = default;

  Image(ca::TextureId textureId, const fl::Size& size) : m_textureId{textureId}, m_size{size} {}

  const ca::TextureId& getTextureId() const {
    return m_textureId;
  }

  const fl::Size& getSize() const {
    return m_size;
  }

private:
  ca::TextureId m_textureId;
  fl::Size m_size;
};

}  // namespace el

#endif  // ELASTIC_RENDERER_IMAGE_H_
