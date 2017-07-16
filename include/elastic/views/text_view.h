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

#ifndef ELASTIC_VIEWS_TEXT_VIEW_H_
#define ELASTIC_VIEWS_TEXT_VIEW_H_

#include "elastic/views/view.h"

namespace el {

class TextView : public View {
public:
    explicit TextView(Context* context, const std::string& label = std::string{});
    ~TextView() override;

    // label
    const std::string& getLabel() const { return m_label; }
    void setLabel(const std::string& label);

    // Override: View
    ca::Size<I32> calculateMinSize() const override;
    void layout(const ca::Rect<I32>& rect) override;
    void render(ca::Canvas* canvas, const ca::Mat4& mat) override;

private:
    // The label we render.
    std::string m_label;

    // The shape we use to render the text.
    // sf::Text m_shape;

    DISALLOW_IMPLICIT_CONSTRUCTORS(TextView);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_TEXT_VIEW_H_
