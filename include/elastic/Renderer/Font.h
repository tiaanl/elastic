
#ifndef ELASTIC_RENDERER_FONT_H_
#define ELASTIC_RENDERER_FONT_H_

#include "canvas/Math/Vec2.h"
#include "canvas/Renderer/Renderer.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Rect.h"
#include "nucleus/Containers/Array.h"
#include "nucleus/Macros.h"
#include "nucleus/Streams/InputStream.h"

namespace el {

class Font {
public:
  Font() = default;
  ~Font() = default;

  // Load a TTF font from the given `inputStream` and return `true` if it was successful.
  bool load(ca::Renderer* renderer, nu::InputStream* inputStream, I32 size);

private:
  DELETE_COPY_AND_MOVE(Font);

  struct GlyphData {
    ca::Rect rect;
    ca::Vec2 offset{0.0f, 0.0f};
    F32 xAdvance;
  };

  nu::Array<GlyphData, 96> m_glyphData;
  ca::TextureId m_texture;
};

}  // namespace el

#endif  // ELASTIC_RENDERER_FONT_H_
