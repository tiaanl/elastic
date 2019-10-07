#ifndef ELASTIC_UTILS_MARGINS_H_
#define ELASTIC_UTILS_MARGINS_H_

#include "nucleus/Types.h"

namespace el {

class Margins {
public:
  Margins() = default;

  explicit Margins(I32 all) : m_top{all}, m_right{all}, m_bottom{all}, m_left{all} {}

  Margins(I32 vertical, I32 horizontal)
    : m_top{vertical}, m_right{horizontal}, m_bottom{vertical}, m_left{horizontal} {}

  Margins(I32 top, I32 right, I32 bottom, I32 left)
    : m_top{top}, m_right{right}, m_bottom{bottom}, m_left{left} {}

  auto top() const -> I32 {
    return m_top;
  }

  auto right() const -> I32 {
    return m_right;
  }

  auto bottom() const -> I32 {
    return m_bottom;
  }

  auto left() const -> I32 {
    return m_left;
  }

private:
  I32 m_top = 0;
  I32 m_right = 0;
  I32 m_bottom = 0;
  I32 m_left = 0;
};

}  // namespace el

#endif  // ELASTIC_UTILS_MARGINS_H_
