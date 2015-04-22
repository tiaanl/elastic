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

#include <string>

#include <nucleus/macros.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace el {

class Context;
class GroupView;

class View : public sf::Drawable {
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
  const sf::Vector2i& getMinSize() const { return m_minSize; }
  void setMinSize(const sf::Vector2i& minSize);

  // horizontalalign
  AlignType getHorizontalAlign() const { return m_horizontalAlign; }
  void setHorizontalAlign(AlignType align);

  // verticalalign
  AlignType getVerticalAlign() const { return m_verticalAlign; }
  void setVerticalAlign(AlignType align);

  // expand
  ExpandType getExpand() const { return m_expand; }
  void setExpand(ExpandType expand);

  // Virtual Interface

  // Get the view/child view at this position.
  virtual View* getViewAtPosition(const sf::Vector2i& pos);

  // Return true if you want to receive input events on this view.  If not,
  // events will be processed by this view's parents.
  virtual bool handlesInput() const { return false; }

  virtual void tick(float adjustment);
  virtual sf::Vector2i calculateMinSize() const;
  virtual void layout(const sf::IntRect& rect);

  // Events

  virtual bool onMousePressed(sf::Event& event);
  virtual bool onMouseDragged(sf::Event& event);
  virtual void onMouseMoved(sf::Event& event);
  virtual void onMouseReleased(sf::Event& event);
  virtual void onMouseWheel(sf::Event& event);
  virtual void onMouseEntered(sf::Event& event);
  virtual void onMouseExited(sf::Event& event);

  // Override: sf::Drawable
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

protected:
  friend class GroupView;

  // The context we belong to.
  Context* m_context;

  // The parent of this view.
  View* m_parent{nullptr};

  // The (optional) name of the control.
  std::string m_name;

  // The rect where this view has been layed out to.
  sf::IntRect m_rect;

  // The minimum size of the view.
  sf::Vector2i m_minSize;

  // Horizontal/vertical align.
  AlignType m_horizontalAlign;
  AlignType m_verticalAlign;

  // Expand type of the view.
  ExpandType m_expand;

private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(View);
};

}  // namespace el

#endif  // ELASTIC_VIEWS_VIEW_H_
