#pragma once

#include "canvas/Renderer/renderer.h"
#include "canvas/Renderer/types.h"
#include "elastic/Renderer/image.h"
#include "floats/rect.h"
#include "floats/vec2.h"
#include "nucleus/Containers/static_array.h"
#include "nucleus/Streams/input_stream.h"
#include "nucleus/macros.h"

namespace el {

class Font {
public:
  NU_DELETE_COPY_AND_MOVE(Font);

  struct GlyphData {
    fl::Rect rect;
    fl::Vec2 offset{0.0f, 0.0f};
    F32 xAdvance = 0.0f;
  };

  Font() = default;
  ~Font() = default;

  // Load a TTF font from the given `inputStream` and return `true` if it was successful.
  bool load(nu::InputStream* inputStream, ca::Renderer* renderer, I32 size);

  const Image& getImage() const {
    return m_image;
  }

  I32 getAscent() const {
    return m_ascent;
  }

  I32 getDescent() const {
    return m_descent;
  }

  const GlyphData& glyph(Char ch) const {
    return m_glyphData[ch - 32];
  }

  fl::Size calculateTextExtent(nu::StringView text) const;

private:
  Image m_image;
  I32 m_ascent = 0;
  I32 m_descent = 0;
  nu::StaticArray<GlyphData, 96> m_glyphData;
};

}  // namespace el
