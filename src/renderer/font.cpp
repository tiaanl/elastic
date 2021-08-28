#include "elastic/renderer/font.h"

#include <cmath>

#include "nucleus/streams/utils.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace el {

namespace {

void bake_font_bitmap(U8* data,
                      I32 offset,     // font location (use offset=0 for plain .ttf)
                      F32 font_size,  // height of font in pixels
                      U8* pixels, I32 pixel_width, I32 pixel_height,  // bitmap to be filled in
                      I32 first_char, I32 num_chars,                  // characters to bake
                      stbtt_bakedchar* char_data, I32* ascent, I32* descent  // outputs
) {
  I32 x, y, bottom_y, i;
  stbtt_fontinfo f;
  if (!stbtt_InitFont(&f, data, offset)) {
    return;
  }

  // background of 0 around pixels
  STBTT_memset(pixels, 0, pixel_width * pixel_height);
  x = y = 1;
  bottom_y = 1;

  F32 scale = stbtt_ScaleForPixelHeight(&f, font_size);

  stbtt_GetFontVMetrics(&f, ascent, descent, nullptr);
  *ascent = static_cast<I32>(std::round(static_cast<F32>(*ascent) * scale));
  *descent = static_cast<I32>(std::round(static_cast<F32>(*descent) * scale));

  for (i = 0; i < num_chars; ++i) {
    I32 advance, left_side_bearing, ax, ay, bx, by, glyph_width, glyph_height;

    I32 g = stbtt_FindGlyphIndex(&f, first_char + i);
    stbtt_GetGlyphHMetrics(&f, g, &advance, &left_side_bearing);
    stbtt_GetGlyphBitmapBox(&f, g, scale, scale, &ax, &ay, &bx, &by);
    glyph_width = bx - ax;
    glyph_height = by - ay;

    // advance to next row
    if (x + glyph_width + 1 >= pixel_width) {
      y = bottom_y, x = 1;
    }

    // check if it fits vertically AFTER potentially moving to next row
    if (y + glyph_height + 1 >= pixel_height) {
      return;
    }

    DCHECK(x + glyph_width < pixel_width);
    DCHECK(y + glyph_height < pixel_height);

    stbtt_MakeGlyphBitmap(&f, pixels + x + y * pixel_width, glyph_width, glyph_height, pixel_width,
                          scale, scale, g);

    char_data[i].x0 = (stbtt_int16)x;
    char_data[i].y0 = (stbtt_int16)y;
    char_data[i].x1 = (stbtt_int16)(x + glyph_width);
    char_data[i].y1 = (stbtt_int16)(y + glyph_height);
    char_data[i].xadvance = scale * static_cast<F32>(advance);
    char_data[i].xoff = (float)ax;
    char_data[i].yoff = (float)ay;
    x = x + glyph_width + 1;
    if (y + glyph_height + 1 > bottom_y)
      bottom_y = y + glyph_height + 1;
  }
}

}  // namespace

bool Font::load(nu::InputStream* stream, ca::Renderer* renderer, I32 size) {
  auto data = readEntireStream(stream);

  fl::Size image_size{1024, 1024};
  nu::DynamicArray<U8> image = nu::DynamicArray<U8>::withInitialSize(image_size.area(), 0);

  stbtt_bakedchar baked_chars[96];
  bake_font_bitmap(data.data(), 0, static_cast<F32>(size), image.data(), image_size.width,
                   image_size.height, 32, 96, baked_chars, &ascent_, &descent_);

  for (auto i = 0; i < 96; ++i) {
    glyphs_[i].rect = {baked_chars[i].x0, baked_chars[i].y0, baked_chars[i].x1 - baked_chars[i].x0,
                       baked_chars[i].y1 - baked_chars[i].y0};
    glyphs_[i].offset = {baked_chars[i].xoff, baked_chars[i].yoff};
    glyphs_[i].advance = baked_chars[i].xadvance;

#if 0
    LOG(Info) << "glyph " << i << ": subImage(" << m_glyphData[i].rect.pos.x << ", "
              << m_glyphData[i].rect.pos.y << ", " << m_glyphData[i].rect.size.width << ", "
              << m_glyphData[i].rect.size.height << "), offset(" << m_glyphData[i].offset.x << ", "
              << m_glyphData[i].offset.y << ")";
#endif  // 0
  }

  auto texture_id = renderer->create_texture(ca::TextureFormat::Alpha, image_size, image.data(),
                                             image.size(), false);
  if (!texture_id.is_valid()) {
    LOG(Error) << "Could not create texture for font.";
    return false;
  }

  image_ = Image{texture_id, image_size};

  return true;
}

fl::Size Font::calculate_text_extent(nu::StringView text) const {
  F32 width = 0.0f;
  for (StringLength i = 0; i < text.length(); ++i) {
    width += glyphs_[text[i] - 32].advance;
  }

  return {static_cast<I32>(std::round(width)), ascent_ - descent_};
}

}  // namespace el
