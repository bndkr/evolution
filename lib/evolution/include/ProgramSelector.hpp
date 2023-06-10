#ifndef EVOLUTION_PROGRAM_SELECTOR_HPP
#define EVOLUTION_PROGRAM_SELECTOR_HPP

#include "Shader.hpp"

#include <map>
#include <memory>
#include <string>

namespace evolution
{
  class ProgramSelector
  {
  public:
    ProgramSelector();

    Program* getProgram(std::string key);

    void addProgram(const std::string& vertexShaderSrc,
                    const std::string& fragmentShaderSrc,
                    std::string* errMsg);

  private:
    std::map<std::string, std::unique_ptr<Program>> m_programs;
  };
} // namespace evolution
#endif