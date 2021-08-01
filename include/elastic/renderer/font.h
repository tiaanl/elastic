#pragma once

#include <canvas/renderer/renderer.h>
#include <canvas/renderer/types.h>
#include <floats/rect.h>
#include <floats/vec2.h>
#include <nucleus/containers/static_array.h>
#include <nucleus/macros.h>
#include <nucleus/streams/input_stream.h>

#include "elastic/renderer/image.h"

namespace el {

class Font {
  NU_DELETE_COPY_AND_MOVE(Font);

public:
  struct Glyph {
    fl::Rect rect;
    fl::Vec2 offset{0.0f, 0.0f};
    F32 advance = 0.0f;
  };

  Font() = default;
  ~Font() = default;

  // Load a TTF font from the given `inputStream` and return `true` if it was successful.
  bool load(nu::InputStream* stream, ca::Renderer* renderer, I32 size);

  NU_NO_DISCARD const Image& image() const {
    return image_;
  }

  NU_NO_DISCARD I32 ascent() const {
    return ascent_;
  }

  NU_NO_DISCARD I32 descent() const {
    return descent_;
  }

  NU_NO_DISCARD const Glyph& glyph(Char ch) const {
    return glyphs_[ch - 32];
  }

  NU_NO_DISCARD fl::Size calculate_text_extent(nu::StringView text) const;

private:
  Image image_;
  I32 ascent_ = 0;
  I32 descent_ = 0;
  nu::StaticArray<Glyph, 96> glyphs_;
};

}  // namespace el
