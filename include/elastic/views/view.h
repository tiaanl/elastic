#pragma once

#include <canvas/windows/keyboard_event_receiver.h>
#include <canvas/windows/mouse_event_receiver.h>
#include <floats/mat4.h>
#include <floats/pos.h>
#include <floats/rect.h>
#include <floats/size.h>
#include <nucleus/macros.h>

#include "elastic/renderer/renderer.h"
#include "elastic/utils/margins.h"

namespace el {

class Context;
class GroupView;

enum class Alignment : U32 {
  Left,
  Top,
  Center,
  Right,
  Bottom,
};

enum class Expansion : U32 {
  None,
  Horizontal,
  Vertical,
  Both,
};

class View {
public:
  NU_DELETE_COPY_AND_MOVE(View);

  explicit View(Context* context);
  virtual ~View();

  // Return the parent of the view, if any.
  View* getParent() const {
    return m_parent;
  }

  // name
  nu::StringView getName() const {
    return m_name.view();
  }
  void setName(const nu::StringView& name);

  // minSize
  virtual const fl::Size& getMinSize() const {
    return m_minSize;
  }
  void setMinSize(const fl::Size& minSize);

  // margins
  auto margins() const -> const Margins& {
    return m_margins;
  }
  auto setMargins(const Margins& margins) -> void {
    m_margins = margins;
  }

  // horizontalAlign
  Alignment getHorizontalAlignment() const {
    return m_horizontalAlignment;
  }
  void setHorizontalAlignment(Alignment alignment);

  // verticalAlign
  Alignment getVerticalAlignment() const {
    return m_verticalAlignment;
  }
  void setVerticalAlignment(Alignment alignment);

  // expand
  Expansion getExpansion() const {
    return m_expansion;
  }
  void setExpansion(Expansion expansion);

  // proportion
  I32 getProportion() const {
    return m_proportion;
  }
  void setProportion(I32 proportion);

  // Virtual Interface

  // Get the view/child view at this position.
  virtual View* getViewAtPosition(const fl::Pos& pos) const;

  // Return true if you want to receive input events on this view.  If not,
  // events will be processed by this view's parents.
  virtual bool handlesInput() const {
    return false;
  }

  virtual void tick(F32 delta);
  virtual fl::Size calculateMinSize() const;
  virtual void layout(const fl::Rect& rect);

  // Raw input events from canvas.
  virtual void on_mouse_moved(const ca::MouseEvent& evt);
  virtual bool on_mouse_pressed(const ca::MouseEvent& evt);
  virtual void on_mouse_released(const ca::MouseEvent& evt);
  virtual void on_mouse_wheel(const ca::MouseWheelEvent& evt);

  virtual bool onMouseDragged(const ca::MouseEvent& evt);
  virtual void onMouseEnter(const ca::MouseEvent& evt);
  virtual void onMouseLeave(const ca::MouseEvent& evt);

  virtual void on_key_pressed(const ca::KeyEvent& evt);
  virtual void on_key_released(const ca::KeyEvent& evt);

  virtual void render(Renderer* renderer, const fl::Mat4& mat);

protected:
  friend class GroupView;

  // The context we belong to.
  Context* m_context;

  // The parent of this view.
  View* m_parent = nullptr;

  // The (optional) name of the control.
  nu::StaticString<64> m_name;

  // The rect where this view has been laid out to.
  fl::Rect m_rect;

  // The minimum size of the view.
  fl::Size m_minSize;

  // A margin around the view.
  Margins m_margins;

  // Horizontal/vertical align.
  Alignment m_horizontalAlignment = Alignment::Center;
  Alignment m_verticalAlignment = Alignment::Center;

  // Expand type of the view.
  Expansion m_expansion = Expansion::None;

  // The proportion of this view in relation to other views in the same GroupView.
  I32 m_proportion = 0;
};

}  // namespace el
