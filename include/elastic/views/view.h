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

#ifndef ELASTIC_VIEWS_VIEW_H_
#define ELASTIC_VIEWS_VIEW_H_

#include <cstdint>
#include <string>

#include "canvas/math/mat4.h"
#include "canvas/rendering/canvas.h"
#include "canvas/utils/pos.h"
#include "canvas/utils/rect.h"
#include "canvas/utils/size.h"
#include "canvas/windows/KeyboardEventHandlerInterface.h"
#include "canvas/windows/MouseEventHandlerInterface.h"
#include "nucleus/macros.h"

namespace el {

class Context;
class GroupView;

class View : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
    enum AlignType {
        AlignLeft,
        AlignTop,
        AlignCenter,
        AlignRight,
        AlignBottom,
    };

    enum ExpandType {
        ExpandNone,
        ExpandHorizontal,
        ExpandVertical,
        ExpandBoth,
    };

    explicit View(Context* context);
    virtual ~View();

    // Return the parent of the view, if any.
    View* getParent() const { return m_parent; }

    // name
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name);

    // minsize
    const ca::Size<I32>& getMinSize() const { return m_minSize; }
    void setMinSize(const ca::Size<I32>& minSize);

    // horizontalalign
    AlignType getHorizontalAlign() const { return m_horizontalAlign; }
    void setHorizontalAlign(AlignType align);

    // verticalalign
    AlignType getVerticalAlign() const { return m_verticalAlign; }
    void setVerticalAlign(AlignType align);

    // expand
    ExpandType getExpand() const { return m_expand; }
    void setExpand(ExpandType expand);

    // proportion
    int32_t getProportion() const { return m_proportion; }
    void setProportion(int32_t proportion);

    // Virtual Interface

    // Get the view/child view at this position.
    virtual View* getViewAtPosition(const ca::Pos<I32>& pos) const;

    // Return true if you want to receive input events on this view.  If not,
    // events will be processed by this view's parents.
    virtual bool handlesInput() const { return false; }

    virtual void tick(float adjustment);
    virtual ca::Size<I32> calculateMinSize() const;
    virtual void layout(const ca::Rect<I32>& rect);

    // Events

    void onMouseMoved(const ca::MouseEvent& evt) override;
    bool onMousePressed(const ca::MouseEvent& evt) override;
    void onMouseReleased(const ca::MouseEvent& evt) override;
    void onMouseWheel(const ca::MouseWheelEvent& evt) override;

    virtual bool onMouseDragged(const ca::MouseEvent& evt);
    virtual void onMouseEnter(const ca::MouseEvent& evt);
    virtual void onMouseLeave(const ca::MouseEvent& evt);

    void onKeyPressed(const ca::KeyEvent& evt) override;
    void onKeyReleased(const ca::KeyEvent& evt) override;

    virtual void render(ca::Canvas* canvas, const ca::Mat4& mat);

protected:
    friend class GroupView;

    // The context we belong to.
    Context* m_context;

    // The parent of this view.
    View* m_parent{nullptr};

    // The (optional) name of the control.
    std::string m_name;

    // The rect where this view has been layed out to.
    ca::Rect<I32> m_rect;

    // The minimum size of the view.
    ca::Size<I32> m_minSize;

    // Horizontal/vertical align.
    AlignType m_horizontalAlign{AlignCenter};
    AlignType m_verticalAlign{AlignCenter};

    // Expand type of the view.
    ExpandType m_expand{ExpandNone};

    // The proportion of this view in relation to other views in the same
    // GroupView.
    int32_t m_proportion{0};

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(View);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_VIEW_H_
