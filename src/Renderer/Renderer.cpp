
#include "elastic/Renderer/Renderer.h"
#include <nucleus/Streams/WrappedMemoryInputStream.h>

#include "canvas/Math/Vec2.h"
#include "nucleus/Logging.h"

namespace el {

namespace {

const I8* kQuadVertexShaderSource = R"source(
#version 330

layout(location = 0) in vec3 inPosition;

void main() {
  gl_Position = vec4(inPosition, 1.0);
}
)source";

const I8* kQuadFragmentShaderSource = R"source(
#version 330

out vec4 final;

void main() {
  final = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)source";

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

  nu::WrappedMemoryInputStream vertexShaderStream{
      kQuadVertexShaderSource, nu::StringView{kQuadVertexShaderSource}.getLength()};
  auto vertexShaderSource = ca::ShaderSource::from(&vertexShaderStream);

  nu::WrappedMemoryInputStream fragmentShaderStream{
      kQuadFragmentShaderSource, nu::StringView{kQuadFragmentShaderSource}.getLength()};
  auto fragmentShaderSource = ca::ShaderSource::from(&fragmentShaderStream);

  m_quadProgramId = renderer->createProgram(vertexShaderSource, fragmentShaderSource);
  if (!isValid(m_quadProgramId)) {
    LOG(Error) << "Could not create quad shader program.";
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

  return true;
}

void Renderer::renderQuad(const ca::Rect<I32>& rect) {
  if (m_renderer == nullptr) {
    DCHECK(m_renderer != nullptr) << "Renderer not initialized.";
    return;
  }

  ca::Command command{ca::CommandType::Draw};
  command.drawData.programId = m_quadProgramId;
  command.drawData.vertexBufferId = m_quadVertexBufferId;
  command.drawData.indexBufferId = m_quadIndexBufferId;
  command.drawData.textureId = ca::TextureId{};
  command.drawData.drawType = ca::DrawType::Triangles;
  command.drawData.numIndices = 6;

  m_renderer->pushCommand(command);
}

}  // namespace el
