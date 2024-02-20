#ifndef EVOLUTION_INPUT_HPP
#define EVOLUTION_INPUT_HPP

struct GLFWwindow;

namespace evolution
{
  class InputManager
  {
    public:
        InputManager(GLFWwindow* window);
    
        bool isKeyPressed(const int key) const;
        bool isKeyReleased(const int key) const;
        bool isKeyHeld(const int key) const;
    
        bool isMouseButtonPressed(const int button) const;
        bool isMouseButtonReleased(const int button) const;
        bool isMouseButtonHeld(const int button) const;
    
        void setKeyState(const int key, const bool state);
        void setMouseButtonState(const int button, const bool state);
  };
} // namespace evolution

#endif