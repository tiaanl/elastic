
#ifndef ELASTIC_VIEWS_COLOR_VIEW_H_
#define ELASTIC_VIEWS_COLOR_VIEW_H_

#include "canvas/Rendering/Geometry.h"
#include "canvas/Rendering/Program.h"
#include "elastic/Views/View.h"
#include "nucleus/Allocators/Allocated.h"

namespace el {

class ColorView : public View {
public:
  MOVE_DELETE(ColorView);
  COPY_DELETE(ColorView);

  explicit ColorView(Context* context);
  ColorView(Context* context, const ca::Color& color);
  virtual ~ColorView();

  // color
  const ca::Color& getColor() const {
    return m_color;
  }
  void setColor(const ca::Color& color);

  // Override: View
  void layout(const ca::Rect<I32>& rect) override;
  void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
  bool ensureShaders();
  bool updateRenderState();

  // The color of the view.
  ca::Color m_color;

  ca::ResourceRef<ca::Program> m_shaderProgram;

  GLuint m_vertexBufferObject = 0;
  GLuint m_vertexArrayObject = 0;
};

}  // namespace el

#endif  // ELASTIC_VIEWS_COLOR_VIEW_H_
