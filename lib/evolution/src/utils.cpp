#include "TextureManager.hpp"
#include "ProgramSelector.hpp"
#include "utils.hpp"

#include <boost/filesystem.hpp>

#include <map>
#include <fstream>
#include <iostream>

namespace
{
  std::string readFile(const char* filename)
  {
    std::ifstream ifs(filename, std::ios::in);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
  }

} // namespace

namespace evolution
{
  void addTexturesFromDir(const std::string& dir)
  {
    for (const auto& item : boost::filesystem::directory_iterator(dir))
    {
      if (boost::filesystem::exists(item.path()) &&
          item.path().extension() == ".png")
      {
        getTextureManager()->addTexture(
          item.path().filename().string(), item.path().string());
      }
    }
  }

  void addProgramsFromDir(const std::string& dir)
  {
    std::map<std::string, std::pair<std::string, std::string>> detectedPrograms;
    for (const auto& item : boost::filesystem::directory_iterator(dir))
    {
      if (boost::filesystem::exists(item.path()) &&
          item.path().extension() == ".vert")
      {
        std::string shaderFilename = item.path().filename().string();
        // remove the extension from the filename to get the name of the shader
        size_t lastindex = shaderFilename.find_last_of(".");
        std::string shaderName = shaderFilename.substr(0, lastindex);

        if (detectedPrograms.count(shaderName))
        {
          detectedPrograms[shaderName].first =
            readFile(item.path().string().c_str());
        }
        else
        {
          detectedPrograms[shaderName] = {
            readFile(item.path().string().c_str()), std::string()};
        }
      }
      if (boost::filesystem::exists(item.path()) &&
          item.path().extension() == ".frag")
      {
        std::string shaderFilename = item.path().filename().string();
        // remove the extension from the filename to get the name of the shader
        size_t lastindex = shaderFilename.find_last_of(".");
        std::string shaderName = shaderFilename.substr(0, lastindex);
        if (detectedPrograms.count(shaderName))
        {
          detectedPrograms[shaderName].second =
            readFile(item.path().string().c_str());
        }
        else
        {
          detectedPrograms[shaderName] = {
            std::string(), readFile(item.path().string().c_str())};
        }
      }
    }
    for (const auto& item : detectedPrograms)
    {
      std::string name = item.first;
      std::string vertShader = item.second.first;
      std::string fragShader = item.second.second;
      if (!vertShader.empty() && !fragShader.empty())
      {
        if (getProgramSelector()->isProgramValid(name))
        {
          continue; // shader is already loaded
        }
        std::string errorMsg;
        getProgramSelector()->addProgram(
          vertShader, fragShader, name, &errorMsg);
        if (!errorMsg.empty())
        {
          std::cout << "Error compiling shader " << name << ": " << errorMsg
                    << std::endl;
        }
      }
    }
  }

} // namespace evolution
