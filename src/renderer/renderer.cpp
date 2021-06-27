
#include "elastic/Renderer/renderer.h"

#include "floats/transform.h"
#include "nucleus/Streams/array_input_stream.h"

namespace el {

namespace {

const char* kQuadVertexShaderSource = R"source(
#version 330

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoords;

out vec2 texCoords;

uniform mat4 uTransform;
uniform mat4 uTexCoordsTransform;

void main() {
  texCoords = (uTexCoordsTransform * vec4(inTexCoords, 0.0, 1.0)).xy;
  gl_Position = uTransform * vec4(inPosition, 0.0, 1.0);
}
)source";

const char* kQuadColorFragmentShaderSource = R"source(
#version 330

uniform vec4 uColor;

out vec4 final;

void main() {
  final = uColor;
}
)source";

const char* kQuadTextureFragmentShaderSource = R"source(
#version 330

in vec2 texCoords;

out vec4 final;

uniform sampler2D uTexture;

void main() {
  final = texture(uTexture, texCoords);
}
)source";

const char* kQuadFontFragmentShaderSource = R"source(
#version 330

in vec2 texCoords;

out vec4 final;

uniform sampler2D uTexture;

void main() {
   float alpha = texture(uTexture, texCoords).r;
   final = vec4(1.0f, 1.0f, 1.0f, alpha);
}
)source";

ca::ProgramId createProgram(ca::Renderer* renderer, nu::StringView vertexShaderSource,
                            nu::StringView fragmentShaderSource) {
  nu::ArrayInputStream vertexStream{nu::ArrayView<U8>{
      reinterpret_cast<const U8*>(vertexShaderSource.data()), vertexShaderSource.length()}};
  auto vss = ca::ShaderSource::from(&vertexStream);

  nu::ArrayInputStream fragmentStream{nu::ArrayView<U8>{
      reinterpret_cast<const U8*>(fragmentShaderSource.data()), fragmentShaderSource.length()}};
  auto fss = ca::ShaderSource::from(&fragmentStream);

  return renderer->createProgram(vss, fss);
}

struct QuadVertex {
  fl::Vec2 position;
  fl::Vec2 texCoords;
} kQuadVertices[] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}},  //
    {{0.0f, 1.0f}, {0.0f, 1.0f}},  //
    {{1.0f, 1.0f}, {1.0f, 1.0f}},  //
    {{1.0f, 0.0f}, {1.0f, 0.0f}},  //
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

  m_quadFontProgramId =
      createProgram(renderer, kQuadVertexShaderSource, kQuadFontFragmentShaderSource);
  if (!isValid(m_quadTextureProgramId)) {
    LOG(Error) << "Could not create quad FONT shader program.";
    return false;
  }

  ca::VertexDefinition definition;
  definition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  definition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);

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

  m_quadTexCoordsTransformUniformId = renderer->createUniform("uTexCoordsTransform");
  if (!isValid(m_quadTexCoordsTransformUniformId)) {
    LOG(Error) << "Could not create quad tex coords transform uniform.";
    return false;
  }

  m_quadColorUniformId = renderer->createUniform("uColor");
  if (!isValid(m_quadColorUniformId)) {
    LOG(Error) << "Could not create quad color uniform.";
    return false;
  }

  m_projectionMatrix = fl::orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                                  static_cast<F32>(m_size.height), -1.0f, 1.0f);

  return true;
}

void Renderer::resize(const fl::Size& size) {
  m_size = size;

  m_projectionMatrix = fl::orthographicProjection(0.0f, static_cast<F32>(m_size.width), 0.0f,
                                                  static_cast<F32>(m_size.height), -1.0f, 1.0f);
}

void Renderer::renderQuad(const fl::Rect& rect, const ca::Color& color) {
#if BUILD(DEBUG)
  if (m_renderer == nullptr) {
    DCHECK(m_renderer != nullptr) << "Renderer not initialized.";
    return;
  }
#endif  // BUILD(DEBUG)

  fl::Mat4 translation =
      fl::translationMatrix({static_cast<F32>(rect.pos.x), static_cast<F32>(rect.pos.y), 0.0f});
  fl::Mat4 scale = fl::scaleMatrix(
      {static_cast<F32>(rect.size.width), static_cast<F32>(rect.size.height), 1.0f});

  fl::Mat4 view = translation * scale;

  ca::UniformBuffer uniforms;
  uniforms.set(m_quadTransformUniformId, m_projectionMatrix * view);
  // uniforms.set(m_quadTexCoordsTransformUniformId, fl::Mat4::identity);
  uniforms.set(m_quadColorUniformId, color);

  m_renderer->state().depth_test(false);
  m_renderer->state().cull_face(false);

  m_renderer->draw(ca::DrawType::Triangles, 6, m_quadColorProgramId, m_quadVertexBufferId,
                   m_quadIndexBufferId, ca::TextureId{}, uniforms);
}

void Renderer::renderQuad(const fl::Rect& rect, const Image& image) {
  if (!image.getTextureId().isValid()) {
    LOG(Warning) << "Rendering invalid image.";
    return;
  }
  renderTexturedQuad(rect, image, {{0, 0}, image.getSize()}, m_quadTextureProgramId);
}

void Renderer::renderQuad(const fl::Rect& rect, const Image& image, const fl::Rect& subImage) {
  renderTexturedQuad(rect, image, subImage, m_quadTextureProgramId);
}

void Renderer::renderText(Font* font, const fl::Pos& position, const nu::StringView& text) {
  const Image& image = font->getImage();
  fl::Vec2 currentPosition{static_cast<F32>(position.x), static_cast<F32>(position.y)};
  for (StringLength i = 0; i < text.length(); ++i) {
    Char ch = text[i];
    auto& glyph = font->glyph(ch);

    fl::Rect rect{(I32)std::round(currentPosition.x + glyph.offset.x),
                  (I32)std::round(currentPosition.y + font->getAscent() + glyph.offset.y),
                  glyph.rect.size.width, glyph.rect.size.height};

#if 0
    LOG(Info) << "glyph " << ch << ": rect(" << rect.pos.x << ", " << rect.pos.y << ", "
              << rect.size.width << ", " << rect.size.height << "), glyph.rect(" << glyph.rect.pos.x
              << ", " << glyph.rect.pos.y << ", " << glyph.rect.size.width << ", "
              << glyph.rect.size.height << "), offset(" << glyph.offset.x << ", " << glyph.offset.y
              << ")";
#endif  // 0

    // renderQuad(rect, image, glyph.rect);
    renderTexturedQuad(rect, image, glyph.rect, m_quadFontProgramId);

    currentPosition.x += glyph.xAdvance;
  }
}

void Renderer::renderTexturedQuad(const fl::Rect& rect, const Image& image,
                                  const fl::Rect& subImage, ca::ProgramId programId) {
#if BUILD(DEBUG)
  if (m_renderer == nullptr) {
    DCHECK(m_renderer != nullptr) << "Renderer not initialized.";
    return;
  }
#endif  // BUILD(DEBUG)

  fl::Mat4 translation =
      fl::translationMatrix({static_cast<F32>(rect.pos.x), static_cast<F32>(rect.pos.y), 0.0f});
  fl::Mat4 scale = fl::scaleMatrix(
      {static_cast<F32>(rect.size.width), static_cast<F32>(rect.size.height), 1.0f});

  fl::Mat4 view = translation * scale;

  // TRS
  fl::Vec2 imageSize{static_cast<F32>(image.getSize().width),
                     static_cast<F32>(image.getSize().height)};
  fl::Mat4 texCoordsTransform =
      fl::translationMatrix({static_cast<F32>(subImage.pos.x) / imageSize.x,
                             static_cast<F32>(subImage.pos.y) / imageSize.y, 0.0f}) *
      fl::scaleMatrix({static_cast<F32>(subImage.size.width) / imageSize.x,
                       static_cast<F32>(subImage.size.height) / imageSize.y, 0.0f});

  ca::UniformBuffer uniforms;
  uniforms.set(m_quadTransformUniformId, m_projectionMatrix * view);
  uniforms.set(m_quadTexCoordsTransformUniformId, texCoordsTransform);

#if 0
  LOG(Info) << "Rendering quad at (" << rect.pos.x << ", " << rect.pos.y << ", " << rect.size.width
            << ", " << rect.size.height << ")";
#endif  // 0

  m_renderer->state().depth_test(false);
  m_renderer->state().cull_face(false);

  m_renderer->draw(ca::DrawType::Triangles, 6, programId, m_quadVertexBufferId, m_quadIndexBufferId,
                   image.getTextureId(), uniforms);
}

}  // namespace el
