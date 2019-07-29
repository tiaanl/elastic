
#include "elastic/Renderer/Font.h"
#include "canvas/Utils/Image.h"
#include "nucleus/Streams/Utils.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace el {

bool Font::load(ca::Renderer* renderer, nu::InputStream* inputStream, I32 size) {
  auto data = readEntireStream(inputStream);

  ca::Size imageSize{512, 512};
  auto image = ca::Image::createAlpha(imageSize, 0);

  stbtt_bakedchar bakedChars[96];
  stbtt_BakeFontBitmap(data.getData(), 0, static_cast<F32>(size), image.getData(), imageSize.width,
                       imageSize.height, 32, 96, bakedChars);

  for (auto i = 0; i < 96; ++i) {
    m_glyphData[i].rect = {bakedChars[i].x0, bakedChars[i].y0, bakedChars[i].x1, bakedChars[i].y1};
    m_glyphData[i].offset = {bakedChars[i].xoff, bakedChars[i].yoff};
    m_glyphData[i].xAdvance = bakedChars[i].xadvance;
  }

  m_texture = renderer->createTexture(image);
  if (!isValid(m_texture)) {
    LOG(Error) << "Could not create texture for font.";
    return false;
  }

  return true;
}

}  // namespace el
