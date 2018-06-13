
#include "elastic/Views/ColorView.h"

#include <utility>

#include "canvas/Math/Transform.h"
#include "canvas/Rendering/Shader.h"
#include "elastic/Context.h"
#include "nucleus/Streams/WrappedMemoryInputStream.h"

#include "nucleus/MemoryDebug.h"

namespace el {

namespace {

const char* kVertexShaderSource =
    "#version 410\n"
    "\n"
    "layout(location = 0) in vec2 vertex_position;\n"
    "\n"
    "uniform mat4 uniform_mvp;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = uniform_mvp * vec4(vertex_position, 0.0, 1.0);\n"
    "}\n";

const char* kFragmentShaderSource =
    "#version 410\n"
    "\n"
    "uniform vec4 uniform_color;\n"
    "\n"
    "out vec4 fragment_color;\n"
    "\n"
    "void main() {\n"
    "  fragment_color = uniform_color;\n"
    "}\n";

}  // namespace

ColorView::ColorView(Context* context) : View(context) {}

ColorView::ColorView(Context* context, const ca::Color& color) : ColorView(context) {
  setColor(color);
}

ColorView::~ColorView() {
  if (m_vertexBufferObject) {
    glDeleteBuffers(1, &m_vertexBufferObject);
  }

  if (m_vertexArrayObject) {
    GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayObject));
  }
}

void ColorView::setColor(const ca::Color& color) {
  m_color = color;

  updateRenderState();
}

void ColorView::layout(const ca::Rect<I32>& rect) {
  View::layout(rect);
}

void ColorView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
  View::render(canvas, mat);

  ca::Mat4 view;
  view *= ca::translate(static_cast<F32>(m_rect.pos.x), static_cast<F32>(m_rect.pos.y), 0.f);
  view *= ca::scale(static_cast<F32>(m_rect.size.width), static_cast<F32>(m_rect.size.height), 1.f);

#if 1
  ca::Program::bind(m_shaderProgram.get());
  m_shaderProgram.get()->setUniform("uniform_color",
                                    ca::Vec4{static_cast<F32>(m_color.r) / 255.f, static_cast<F32>(m_color.g) / 255.f,
                                             static_cast<F32>(m_color.b) / 255.f, static_cast<F32>(m_color.a) / 255.f});
  m_shaderProgram.get()->setUniform("uniform_mvp", mat * view);

  GL_CHECK(glBindVertexArray(m_vertexArrayObject));
  GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
#else
  ca::Command* command =
      canvas->render(m_shaderProgram->getNativeHandle(), m_vertexArrayObject, GL_TRIANGLE_STRIP, 0, 4);
  command->addUniform("uniform_color",
                      ca::Vec4{static_cast<F32>(m_color.r) / 255.f, static_cast<F32>(m_color.g) / 255.f,
                               static_cast<F32>(m_color.b) / 255.f, static_cast<F32>(m_color.a) / 255.f});
  command->addUniform("uniform_mvp", mat * view);
#endif  // 0
}

bool ColorView::updateRenderState() {
  // Create the shader program if required.
  if (!m_shaderProgram) {
    m_shaderProgram = m_context->getResourceManager()->getOrCreateProgram("elastic_ColorView_program");
    if (!m_shaderProgram.get()->isLinked()) {
      // Create the vertex shader.
      nu::WrappedMemoryInputStream vertexStream{kVertexShaderSource, std::strlen(kVertexShaderSource)};
      ca::ResourceRef<ca::Shader> vertexShaderResource =
          m_context->getResourceManager()->getOrCreateShader("elastic_ColorView_vertexShader");
      if (!vertexShaderResource.get()->loadFromStream(ca::Shader::Vertex, &vertexStream)) {
        return false;
      }

      // Create the fragment shader.
      nu::WrappedMemoryInputStream fragmentStream{kFragmentShaderSource, std::strlen(kFragmentShaderSource)};
      ca::ResourceRef<ca::Shader> fragmentShaderResource =
          m_context->getResourceManager()->getOrCreateShader("elastic_ColorView_fragmentShader");
      if (!fragmentShaderResource.get()->loadFromStream(ca::Shader::Fragment, &fragmentStream)) {
        return false;
      }

      ca::Program program{vertexShaderResource, fragmentShaderResource};
      if (!program.link()) {
        return false;
      }

      m_shaderProgram = m_context->getResourceManager()->getOrCreateProgram("elastic_ColorView_program");
      m_shaderProgram->setVertexShader(vertexShaderResource);
      m_shaderProgram->setFragmentShader(fragmentShaderResource);
      if (!m_shaderProgram->link()) {
        return false;
      }
    }
  }

  // Create the vertex buffer object if required.
  if (!m_vertexBufferObject) {
    GL_CHECK(glGenBuffers(1, &m_vertexBufferObject));
  }

  // Create the vertex array object if required.
  if (!m_vertexArrayObject) {
    GL_CHECK(glGenVertexArrays(1, &m_vertexArrayObject));
  }

  // Bind the vertex array object.
  GL_CHECK(glBindVertexArray(m_vertexArrayObject));

  // clang-format off
  const F32 data[] = {
      0.f, 0.f,
      1.f, 0.f,
      0.f, 1.f,
      1.f, 1.f,
  };
  // clang-format on

  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));

  GL_CHECK(glEnableVertexAttribArray(0));
  GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

  return true;
}

}  // namespace el
