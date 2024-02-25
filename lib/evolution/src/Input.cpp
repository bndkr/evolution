#include "Input.hpp"
#include <unordered_map>
#include <GLFW/glfw3.h>

namespace evolution
{
  InputManager::InputManager(GLFWwindow* window)
  {
    glfwSetKeyCallback(
      window,
      [](GLFWwindow* window, int key, int scancode, int action, int mods)
      {
        InputManager* manager =
          static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
          manager->setKeyPressed(key);
        }
        else if (action == GLFW_RELEASE)
        {
          manager->setKeyReleased(key);
        }
      });

    glfwSetMouseButtonCallback(
      window,
      [](GLFWwindow* window, int button, int action, int mods)
      {
        InputManager* manager =
          static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
          manager->setMouseButtonPressed(button);
        }
        else if (action == GLFW_RELEASE)
        {
          manager->setMouseButtonReleased(button);
        }
      });

    glfwSetWindowUserPointer(window, this);
  }

  bool InputManager::isKeyPressed(const int key) const
  {
    return m_pressedKeys.count(key);
  }

  bool InputManager::isMouseButtonPressed(const int button) const
  {
    return m_pressedMouseButtons.count(button);
  }

  std::pair<double, double> InputManager::getMousePosition() const
  {
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    return {xpos, ypos};
  }
  void InputManager::setKeyPressed(const int key)
  {
    if (m_pressedKeys.count(key) == 0)
    m_pressedKeys.insert(key);
  }
  void InputManager::setKeyReleased(const int key)
  {
    if (m_pressedKeys.count(key) > 0)
      m_pressedKeys.erase(key);
  }
  void InputManager::setMouseButtonPressed(const int button)
  {
    if (m_pressedMouseButtons.count(button) == 0)
      m_pressedMouseButtons.insert(button);
  }
  void InputManager::setMouseButtonReleased(const int button)
  {
    if (m_pressedMouseButtons.count(button) > 0)
      m_pressedMouseButtons.erase(button);
  }
} // namespace evolution
