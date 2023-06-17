#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "Buffers.hpp"
#include "ProgramSelector.hpp"
#include "Setup.hpp"
#include "Camera.hpp"
#include "ShaderEditor.hpp"
#include "MeshManager.hpp"
#include "MeshImporter.hpp"
#include "Texture.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
  void setupImgui(GLFWwindow* window)
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
  }
} // namespace

int main(int argc, char** argv)
{
  const uint32_t width = 1600;
  const uint32_t height = 900;

  auto window = evolution::setup(/*enable3D=*/true, width, height);
  setupImgui(window);

  evolution::ProgramSelector selector;
  evolution::UseProgramSelector(&selector);

  auto pDefaultProgram = selector.getProgram("default");
  if (!pDefaultProgram)
    throw std::runtime_error("unable to initialize default program");

  auto meshes = std::map<std::string, std::unique_ptr<evolution::Mesh>>();

  evolution::Texture myTexture("C:/Users/bende/OneDrive/Pictures/meme.png", 5, "myTexture");

  meshes["my cube"] =
    std::make_unique<evolution::Mesh>(evolution::createCubeMesh());

  meshes["my cube"]->useShader("default");

  meshes["my cube"]->movePostion(evolution::Float3{0.0f, 0.0f, -3.0f});

  meshes["teapot"] = std::make_unique<evolution::Mesh>(
    evolution::fromFile("C:/Users/bende/OneDrive/Desktop/meshes/teapot.stl"));
  meshes["teapot"]->setPosition(evolution::Float3{0.f, 0.f, -15.f});

  meshes["quad"] =
    std::make_unique<evolution::Mesh>(evolution::createTextureQuad());
  meshes["quad"]->setPosition(evolution::Float3{0.f, 0.f, -3.f});

  evolution::Camera camera(width, height);

  // Main loop
  // let's start off leaving the main loop client-side. this allows
  // the client more flexibility over events and state.
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin(
      "yep, it's me again.", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    static float color[4] = {0};
    if (ImGui::ColorPicker4("pick a color for the cube!", color))
    {
      pDefaultProgram->addUniform(color, 4, "un_color");
    }

    ImGui::End();

    ImGui::ShowDemoWindow();

    static bool shaderEditorOpen = true;
    showShaderEditor(&shaderEditorOpen, selector);

    static bool meshManagerOpen = true;
    showMeshManagerWindow(meshes, selector, meshManagerOpen);

    ImGui::Render();

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    glViewport(0, 0, displayWidth, displayHeight);
    camera.updateWindowSize(displayWidth, displayHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& mesh : meshes)
    {
      if (mesh.first != "quad")
        mesh.second->rotate(evolution::Float3{0.01f, 0.008f, 0.009f});
      mesh.second->draw(camera);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
