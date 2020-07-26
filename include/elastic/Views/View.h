#ifndef ELASTIC_VIEWS_VIEW_H_
#define ELASTIC_VIEWS_VIEW_H_

#include "canvas/Math/Mat4.h"
#include "canvas/Utils/Pos.h"
#include "canvas/Utils/Rect.h"
#include "canvas/Utils/Size.h"
#include "canvas/Windows/KeyboardEventHandlerInterface.h"
#include "canvas/Windows/MouseEventHandlerInterface.h"
#include "elastic/Renderer/Renderer.h"
#include "elastic/Utils/Margins.h"
#include "nucleus/Macros.h"

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

class View : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
  NU_DELETE_COPY_AND_MOVE(View);

  explicit View(Context* context);
  virtual ~View();

  // Return the parent of the view, if any.
  View* getParent() const {
    return m_parent;
  }

  // name
  const nu::StringView& getName() const {
    return m_name;
  }
  void setName(const nu::StringView& name);

  // minSize
  virtual const ca::Size& getMinSize() const {
    return m_minSize;
  }
  void setMinSize(const ca::Size& minSize);

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
  virtual View* getViewAtPosition(const ca::Pos& pos) const;

  // Return true if you want to receive input events on this view.  If not,
  // events will be processed by this view's parents.
  virtual bool handlesInput() const {
    return false;
  }

  virtual void tick(F32 delta);
  virtual ca::Size calculateMinSize() const;
  virtual void layout(const ca::Rect& rect);

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

  virtual void render(Renderer* renderer, const ca::Mat4& mat);

protected:
  friend class GroupView;

  // The context we belong to.
  Context* m_context;

  // The parent of this view.
  View* m_parent = nullptr;

  // The (optional) name of the control.
  nu::StaticString<64> m_name;

  // The rect where this view has been laid out to.
  ca::Rect m_rect;

  // The minimum size of the view.
  ca::Size m_minSize;

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

#endif  // ELASTIC_VIEWS_VIEW_H_
