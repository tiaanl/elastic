#ifndef ELASTIC_RENDERER_RENDERER_H_
#define ELASTIC_RENDERER_RENDERER_H_

#include "canvas/Renderer/Renderer.h"

namespace el {

class Renderer {
public:
  Renderer();
  ~Renderer();

private:
  DELETE_COPY_AND_MOVE(Renderer);
};

}  // namespace el

#endif  // ELASTIC_RENDERER_RENDERER_H_
