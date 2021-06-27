#pragma once

#include "canvas/Renderer/types.h"
#include "floats/size.h"
#include "nucleus/macros.h"

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
