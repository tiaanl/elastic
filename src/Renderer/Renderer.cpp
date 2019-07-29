
#include "elastic/Renderer/Renderer.h"

#include "canvas/Math/Transform.h"
#include "canvas/Math/Vec2.h"
#include "nucleus/Config.h"
#include "nucleus/Logging.h"
#include "nucleus/Streams/WrappedMemoryInputStream.h"

namespace el {

namespace {

const I8* kQuadVertexShaderSource = R"source(
#version 330

layout(location = 0) in vec2 inPosition;

uniform mat4 uTransform;

void main() {
  gl_Position = uTransform * vec4(inPosition, 0.0, 1.0);
}
)source";

const I8* kQuadColorFragmentShaderSource = R"source(
#version 330

uniform vec4 uColor;

out vec4 final;

void main() {
  final = uColor;
}
)source";

const I8* kQuadTextureFragmentShaderSource = R"source(
#version 330

out vec4 final;

void main() {
  final = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)source";

ca::ProgramId createProgram(ca::Renderer* renderer, const I8* vertexShaderSource,
                            const I8* fragmentShaderSource) {
  nu::WrappedMemoryInputStream vertexStream{vertexShaderSource,
                                            nu::StringView{vertexShaderSource}.getLength()};
  auto vss = ca::ShaderSource::from(&vertexStream);

  nu::WrappedMemoryInputStream fragmentStream{fragmentShaderSource,
                                              nu::StringView{fragmentShaderSource}.getLength()};
  auto fss = ca::ShaderSource::from(&fragmentStream);

  return renderer->createProgram(vss, fss);
}

ca::Vec2 kQuadVertices[] = {
    {0.0f, 0.0f},  //
    {0.0f, 1.0f},  //
    {1.0f, 1.0f},  //
    {1.0f, 0.0f},  //
};

U8 kQuadIndices[] = {
    0, 1, 2,  //
    2, 3, 0,  //
};

}  // namespace

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

bool Renderer::initialize(ca::Renderer* renderer) {
  m_renderer = renderer;

  m_size = renderer->getSize();

  m_quadColorProgramId =
      createProgram(renderer, kQuadVertexShaderSource, kQuadColorFragmentShaderSource);
  if (!isValid(m_quadColorProgramId)) {
    LOG(Error) << "Could not create quad color shader program.";
    return false;
  }

  m_quadTextureProgramId =
      createProgram(renderer, kQuadVertexShaderSource, kQuadTextureFragmentShaderSource);
  if (!isValid(m_quadTextureProgramId)) {
    LOG(Error) << "Could not create quad texture shader program.";
    return false;
  }

  ca::VertexDefinition definition;
  definition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two, "position");

  m_quadVertexBufferId =
      renderer->createVertexBuffer(definition, kQuadVertices, sizeof(kQuadVertices));
  if (!isValid(m_quadVertexBufferId)) {
    LOG(Error) << "Could not create quad vertex buffer.";
    return false;
  }

  m_quadIndexBufferId =
      renderer->createIndexBuffer(ca::ComponentType::Unsigned8, kQuadIndices, sizeof(kQuadIndices));
  if (!isValid(m_quadIndexBufferId)) {
    LOG(Error) << "Could not create quad index buffer.";
    return false;
  }

  m_quadTransformUniformId = renderer->createUniform("uTransform");
  if (!isValid(m_quadTransformUniformId)) {
    LOG(Error) << "Could not create quad transform uniform.";
    return false;
  }

  m_quadColorUniformId = renderer->createUniform("uColor");
  if (!isValid(m_quadColorUniformId)) {
    LOG(Error) << "Could not create quad color uniform.";
    return false;
  }

  m_projectionMatrix = ca::orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                                  static_cast<F32>(m_size.height), -1.0f, 1.0f);

  return true;
}

void Renderer::resize(const ca::Size& size) {
  m_size = size;

  m_projectionMatrix = ca::orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                                  static_cast<F32>(m_size.height), -1.0f, 1.0f);
}

void Renderer::renderQuad(const ca::Rect& rect, const ca::Color& color) {
#if BUILD(DEBUG)
  if (m_renderer == nullptr) {
    DCHECK(m_renderer != nullptr) << "Renderer not initialized.";
    return;
  }
#endif  // BUILD(DEBUG)

  ca::Mat4 translation =
      ca::translationMatrix({static_cast<F32>(rect.pos.x), static_cast<F32>(rect.pos.y), 0.0f});
  ca::Mat4 scale = ca::scaleMatrix(
      {static_cast<F32>(rect.size.width), static_cast<F32>(rect.size.height), 1.0f});

  ca::Mat4 view = translation * scale;

  ca::UniformBuffer uniforms;
  uniforms.set(m_quadTransformUniformId, m_projectionMatrix * view);
  uniforms.set(m_quadColorUniformId, color);

  m_renderer->draw(ca::DrawType::Triangles, 6, m_quadColorProgramId, m_quadVertexBufferId,
                   m_quadIndexBufferId, ca::TextureId{}, uniforms);
}

void Renderer::renderQuad(const ca::Rect& rect, ca::TextureId textureId) {
#if BUILD(DEBUG)
  if (m_renderer == nullptr) {
    DCHECK(m_renderer != nullptr) << "Renderer not initialized.";
    return;
  }
#endif  // BUILD(DEBUG)

  ca::Mat4 translation =
      ca::translationMatrix({static_cast<F32>(rect.pos.x), static_cast<F32>(rect.pos.y), 0.0f});
  ca::Mat4 scale = ca::scaleMatrix(
      {static_cast<F32>(rect.size.width), static_cast<F32>(rect.size.height), 1.0f});

  ca::Mat4 view = translation * scale;

  ca::UniformBuffer uniforms;
  uniforms.set(m_quadTransformUniformId, m_projectionMatrix * view);

  m_renderer->draw(ca::DrawType::Triangles, 6, m_quadTextureProgramId, m_quadVertexBufferId,
                   m_quadIndexBufferId, textureId, uniforms);
}

void Renderer::renderText(Font* font, const nu::StringView& text) {}

}  // namespace el
