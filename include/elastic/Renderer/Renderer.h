#ifndef ELASTIC_RENDERER_RENDERER_H_
#define ELASTIC_RENDERER_RENDERER_H_

#include "canvas/Renderer/Renderer.h"
#include "canvas/Utils/Rect.h"
#include "elastic/Renderer/Font.h"
#include "elastic/Renderer/Image.h"

namespace el {

class Renderer {
public:
  NU_DELETE_COPY_AND_MOVE(Renderer);

  Renderer();
  ~Renderer();

  bool initialize(ca::Renderer* renderer);
  void resize(const ca::Size& size);

  void renderQuad(const ca::Rect& rect, const ca::Color& color);
  void renderQuad(const ca::Rect& rect, const Image& image);
  void renderQuad(const ca::Rect& rect, const Image& image, const ca::Rect& subImage);
  void renderText(Font* font, const ca::Pos& position, const nu::StringView& text);

private:
  void renderTexturedQuad(const ca::Rect& rect, const Image& image, const ca::Rect& subImage,
                          ca::ProgramId programId);

  ca::Renderer* m_renderer = nullptr;

  ca::Size m_size;
  ca::Mat4 m_projectionMatrix = ca::Mat4::identity;

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

#endif  // ELASTIC_RENDERER_RENDERER_H_
