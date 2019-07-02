#ifndef ELASTIC_RENDERER_RENDERER_H_
#define ELASTIC_RENDERER_RENDERER_H_

#include "canvas/Renderer/Renderer.h"
#include "canvas/Utils/Rect.h"
#include "canvas/Renderer/Renderer.h"

namespace el {

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool initialize(ca::Renderer* renderer);

  void renderQuad(const ca::Rect<I32>& rect);

private:
  DELETE_COPY_AND_MOVE(Renderer);

  ca::Renderer* m_renderer = nullptr;

  ca::ProgramId m_quadProgramId;
  ca::VertexBufferId m_quadVertexBufferId;
  ca::IndexBufferId m_quadIndexBufferId;
};

}  // namespace el

#endif  // ELASTIC_RENDERER_RENDERER_H_
