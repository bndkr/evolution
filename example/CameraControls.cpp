#include "CameraControls.hpp"

#include <imgui/imgui.h>

void showCameraControlWindow(bool* open, evolution::Camera& camera)
{
  ImGui::Begin("Camera Controls", open, ImGuiWindowFlags_AlwaysAutoResize);

  auto& position = camera.getPositionInfo();
  ImGui::SliderFloat3("Position", &position.position.x, -10.f, 10.f);
  ImGui::SliderFloat3("Rotation", &position.rotation.x, -3.14f, 3.14f);
  ImGui::End();
}