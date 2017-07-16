// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "elastic/views/color_view.h"

#include <cstring>
#include <canvas/rendering/shader.h>

#include "nucleus/logging.h"
#include "nucleus/streams/wrapped_memory_input_stream.h"

namespace el {

namespace {

const char* kVertexShaderSource =
    "#version 420\n"
    "\n"
    "layout(location = 0) in vec3 vert_position;\n"
    "layout(location = 1) in vec2 vert_texCoord;\n"
    "layout(location = 2) in vec4 vert_color;\n"
    "\n"
    "uniform mat4 uni_mvp;\n"
    "\n"
    "out vec2 frag_texCoord;\n"
    "out vec4 frag_color;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = vec4(vert_position, 1.0) * uni_mvp;\n"
    "  frag_texCoord = vert_texCoord;\n"
    "  frag_color = vert_color;\n"
    "}\n";

const char* kFragmentShaderSource =
    "#version 420\n"
    "\n"
    "// We get the texture coordinates from the vertex shader.\n"
    "in vec2 frag_texCoord;\n"
    "in vec4 frag_color;\n"
    "\n"
    "// The bound texture.\n"
    "uniform sampler2D sampler;\n"
    "\n"
    "// The final color of the fragment.\n"
    "out vec4 final;\n"
    "\n"
    "void main() {\n"
    "  final = texture(sampler, frag_texCoord);\n"
    "}\n";

}  // namespace

ColorView::ColorView(Context* context)
  : View(context) {}

ColorView::ColorView(Context* context, const ca::Color& color) : ColorView(context) {
    setColor(color);
}

ColorView::~ColorView() {}

void ColorView::setColor(const ca::Color& color) {
    m_color = color;
    // m_drawable.setFillColor(color);
}

void ColorView::layout(const ca::Rect<I32>& rect) {
    View::layout(rect);

    LOG(Info) << m_name << " = (" << rect.pos.x << ", " << rect.pos.y << ") x (" << rect.size.width << ", "
              << rect.size.height << ")";

    // m_drawable.setPosition(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)));
    // m_drawable.setSize(sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height)));
}

void ColorView::render(ca::Canvas* canvas, const ca::Mat4& mat) {
    View::render(canvas, mat);

    m_geometry.render();
}

bool ColorView::loadShaders() {
    nu::WrappedMemoryInputStream vertexStream(kVertexShaderSource, std::strlen(kVertexShaderSource));
    ca::Shader vertexShader(ca::Shader::Vertex);
    if (!vertexShader.loadFromStream(&vertexStream)) {
        return false;
    }

    nu::WrappedMemoryInputStream fragmentStream(kVertexShaderSource, std::strlen(kFragmentShaderSource));
    ca::Shader fragmentShader(ca::Shader::Fragment);
    if (!fragmentShader.loadFromStream(&fragmentStream)) {
        return false;
    }

    m_program.setVertexShader(&vertexShader);
    m_program.setFragmentShader(&fragmentShader);
    m_program.link();

    m_geometry = ca::Geometry::createRectangle(ca::Rect<F32>{-50.0f, -50.0f, 100.0f, 100.0f}, ca::Color{255, 0, 0, 255});
    m_geometry.compileAndUpload();

    return false;
}

}  // namespace el
