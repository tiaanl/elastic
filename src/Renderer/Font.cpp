
#include "elastic/Renderer/Font.h"

#include <cmath>

#include "nucleus/Streams/Utils.h"
#include "silhouette/Image.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace el {

namespace {

void bakeFontBitmap(U8* data,
                    I32 offset,    // font location (use offset=0 for plain .ttf)
                    F32 fontSize,  // height of font in pixels
                    U8* pixels, I32 pixelWidth, I32 pixelHeight,          // bitmap to be filled in
                    I32 firstChar, I32 numChars,                          // characters to bake
                    stbtt_bakedchar* charData, I32* ascent, I32* descent  // outputs
) {
  I32 x, y, bottomY, i;
  stbtt_fontinfo f;
  if (!stbtt_InitFont(&f, data, offset)) {
    return;
  }

  // background of 0 around pixels
  STBTT_memset(pixels, 0, pixelWidth * pixelHeight);
  x = y = 1;
  bottomY = 1;

  F32 scale = stbtt_ScaleForPixelHeight(&f, fontSize);

  stbtt_GetFontVMetrics(&f, ascent, descent, 0);
  *ascent = static_cast<I32>(std::round(static_cast<F32>(*ascent) * scale));
  *descent = static_cast<I32>(std::round(static_cast<F32>(*descent) * scale));

  for (i = 0; i < numChars; ++i) {
    I32 advance, leftSideBearing, x0, y0, x1, y1, glyphWidth, glyphHeight;

    I32 g = stbtt_FindGlyphIndex(&f, firstChar + i);
    stbtt_GetGlyphHMetrics(&f, g, &advance, &leftSideBearing);
    stbtt_GetGlyphBitmapBox(&f, g, scale, scale, &x0, &y0, &x1, &y1);
    glyphWidth = x1 - x0;
    glyphHeight = y1 - y0;

    // advance to next row
    if (x + glyphWidth + 1 >= pixelWidth) {
      y = bottomY, x = 1;
    }

    // check if it fits vertically AFTER potentially moving to next row
    if (y + glyphHeight + 1 >= pixelHeight) {
      return;
    }

    DCHECK(x + glyphWidth < pixelWidth);
    DCHECK(y + glyphHeight < pixelHeight);

    stbtt_MakeGlyphBitmap(&f, pixels + x + y * pixelWidth, glyphWidth, glyphHeight, pixelWidth,
                          scale, scale, g);

    charData[i].x0 = (stbtt_int16)x;
    charData[i].y0 = (stbtt_int16)y;
    charData[i].x1 = (stbtt_int16)(x + glyphWidth);
    charData[i].y1 = (stbtt_int16)(y + glyphHeight);
    charData[i].xadvance = scale * advance;
    charData[i].xoff = (float)x0;
    charData[i].yoff = (float)y0;
    x = x + glyphWidth + 1;
    if (y + glyphHeight + 1 > bottomY)
      bottomY = y + glyphHeight + 1;
  }
}

}  // namespace

bool Font::load(nu::InputStream* inputStream, ca::Renderer* renderer, I32 size) {
  auto data = readEntireStream(inputStream);

  fl::Size imageSize{1024, 1024};
  auto image = si::Image::createAlpha(imageSize, 0);

  stbtt_bakedchar bakedChars[96];
  bakeFontBitmap(data.data(), 0, static_cast<F32>(size), const_cast<U8*>(image.data().data()),
                 imageSize.width, imageSize.height, 32, 96, bakedChars, &m_ascent, &m_descent);

  for (auto i = 0; i < 96; ++i) {
    m_glyphData[i].rect = {bakedChars[i].x0, bakedChars[i].y0, bakedChars[i].x1 - bakedChars[i].x0,
                           bakedChars[i].y1 - bakedChars[i].y0};
    m_glyphData[i].offset = {bakedChars[i].xoff, bakedChars[i].yoff};
    m_glyphData[i].xAdvance = bakedChars[i].xadvance;

#if 0
    LOG(Info) << "glyph " << i << ": subImage(" << m_glyphData[i].rect.pos.x << ", "
              << m_glyphData[i].rect.pos.y << ", " << m_glyphData[i].rect.size.width << ", "
              << m_glyphData[i].rect.size.height << "), offset(" << m_glyphData[i].offset.x << ", "
              << m_glyphData[i].offset.y << ")";
#endif  // 0
  }

  auto textureId = si::createTextureFromImage(renderer, image, false);
  if (!isValid(textureId)) {
    LOG(Error) << "Could not create texture for font.";
    return false;
  }

  m_image = Image{textureId, imageSize};

  return true;
}

fl::Size Font::calculateTextExtent(nu::StringView text) const {
  F32 width = 0.0f;
  for (StringLength i = 0; i < text.length(); ++i) {
    width += m_glyphData[text[i] - 32].xAdvance;
  }

  return {static_cast<I32>(std::round(width)), m_ascent - m_descent};
}

}  // namespace el
