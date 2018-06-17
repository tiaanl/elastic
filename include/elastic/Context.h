
#ifndef ELASTIC_CONTEXT_H_
#define ELASTIC_CONTEXT_H_

#include <string>

#include "canvas/Rendering/Font.h"
#include "canvas/Resources/ResourceManager.h"
#include "elastic/Views/ContextView.h"
#include "nucleus/Allocators/Allocator.h"

namespace el {

class View;

class Context : public ca::MouseEventHandlerInterface, public ca::KeyboardEventHandlerInterface {
public:
  COPY_DELETE(Context);
  MOVE_DELETE(Context);

  explicit Context(ca::ResourceManager* resourceManager);
  virtual ~Context() = default;

  ca::ResourceManager* getResourceManager() { return m_resourceManager; }

  // Get the root view of the context.
  ContextView* getRoot() { return &m_contextView; }

  // Get/set the view that will have the keyboard focus.
  View* getFocusView() const { return m_focusView; }
  void setFocusView(View* view);

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

  ca::ResourceManager* m_resourceManager;

  // The root view of our hierarchy.
  mutable ContextView m_contextView;

  // The view that is currently the view with keyboard focus.
  View* m_focusView = nullptr;
};

}  // namespace el

#endif  // ELASTIC_CONTEXT_H_
