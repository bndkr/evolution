#ifndef EVOLUTION_INPUT_HPP
#define EVOLUTION_INPUT_HPP

#include <set>
#include <utility>

struct GLFWwindow;

namespace evolution
{
  class InputManager
  {
  public:
    InputManager(GLFWwindow* window);

    bool isKeyPressed(const int key) const;

    bool isMouseButtonPressed(const int button) const;

    std::pair<double, double> getMousePosition() const;

    void setKeyPressed(const int key);
    void setKeyReleased(const int key);

    void setMouseButtonPressed(const int button);
    void setMouseButtonReleased(const int button);

  private:

    std::set<int> m_pressedKeys;
    std::set<int> m_pressedMouseButtons;
    GLFWwindow* m_window;
  };
} // namespace evolution

#endif