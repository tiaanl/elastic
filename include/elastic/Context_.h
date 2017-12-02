
#ifndef ELASTIC_CONTEXT_H_
#define ELASTIC_CONTEXT_H_

#include <string>

#include "canvas/rendering/font.h"
#include "elastic/resources/resource_store.h"
#include "elastic/views/context_view.h"

namespace el {

class View;

class Context : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
  Context();
  virtual ~Context();

  // Get the root view of the context.
  ContextView* getRoot() { return &m_contextView; }

  // Get/set the view that will have the keyboard focus.
  View* getFocusView() const { return m_focusView; }
  void setFocusView(View* view);

  // Resources
  virtual ca::Font* getFont(const std::string& name) = 0;

  void onKeyPressed(const ca::KeyEvent& evt) override;
  void onKeyReleased(const ca::KeyEvent& evt) override;
  void onMouseMoved(const ca::MouseEvent& evt) override;
  bool onMousePressed(const ca::MouseEvent& evt) override;
  void onMouseReleased(const ca::MouseEvent& evt) override;
  void onMouseWheel(const ca::MouseWheelEvent& evt) override;

  void tick(float adjustment);
  void render(ca::Canvas* canvas);

protected:
  friend class View;

  // The root view of our hierarchy.
  mutable ContextView m_contextView;

  // The view that is currently the view with keyboard focus.
  View* m_focusView{nullptr};

private:
  DISALLOW_COPY_AND_ASSIGN(Context);
};

}  // namespace el

#endif  // ELASTIC_CONTEXT_H_