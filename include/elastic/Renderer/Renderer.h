#ifndef ELASTIC_RENDERER_RENDERER_H_
#define ELASTIC_RENDERER_RENDERER_H_

#include "canvas/Renderer/Renderer.h"
#include "canvas/Utils/Rect.h"
#include "elastic/Renderer/Font.h"

namespace el {

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool initialize(ca::Renderer* renderer);
  void resize(const ca::Size& size);

  void renderQuad(const ca::Rect& rect, const ca::Color& color);
  void renderQuad(const ca::Rect& rect, ca::TextureId textureId);
  void renderText(Font* font, const nu::StringView& text);

private:
  DELETE_COPY_AND_MOVE(Renderer);

  ca::Renderer* m_renderer = nullptr;

  ca::Size m_size;
  ca::Mat4 m_projectionMatrix = ca::Mat4::identity;

  ca::ProgramId m_quadColorProgramId;
  ca::ProgramId m_quadTextureProgramId;
  ca::VertexBufferId m_quadVertexBufferId;
  ca::IndexBufferId m_quadIndexBufferId;

  ca::UniformId m_quadTransformUniformId;
  ca::UniformId m_quadColorUniformId;
};

}  // namespace el

#endif  // ELASTIC_RENDERER_RENDERER_H_
