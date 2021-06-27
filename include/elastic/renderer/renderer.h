#pragma once

#include "canvas/Renderer/renderer.h"
#include "elastic/Renderer/font.h"
#include "elastic/Renderer/image.h"
#include "floats/rect.h"

namespace el {

class Renderer {
public:
  NU_DELETE_COPY_AND_MOVE(Renderer);

  Renderer();
  ~Renderer();

  bool initialize(ca::Renderer* renderer);
  void resize(const fl::Size& size);

  void renderQuad(const fl::Rect& rect, const ca::Color& color);
  void renderQuad(const fl::Rect& rect, const Image& image);
  void renderQuad(const fl::Rect& rect, const Image& image, const fl::Rect& subImage);
  void renderText(Font* font, const fl::Pos& position, const nu::StringView& text);

private:
  void renderTexturedQuad(const fl::Rect& fl, const Image& image, const fl::Rect& subImage,
                          ca::ProgramId programId);

  ca::Renderer* m_renderer = nullptr;

  fl::Size m_size;
  fl::Mat4 m_projectionMatrix = fl::Mat4::identity;

  ca::ProgramId m_quadColorProgramId;
  ca::ProgramId m_quadTextureProgramId;
  ca::ProgramId m_quadFontProgramId;
  ca::VertexBufferId m_quadVertexBufferId;
  ca::IndexBufferId m_quadIndexBufferId;

  ca::UniformId m_quadTransformUniformId;
  ca::UniformId m_quadTexCoordsTransformUniformId;
  ca::UniformId m_quadColorUniformId;
};

}  // namespace el
