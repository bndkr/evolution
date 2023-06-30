#ifndef EVOLUTION_PROGRAM_SELECTOR_HPP
#define EVOLUTION_PROGRAM_SELECTOR_HPP

#include "Shader.hpp"

#include <map>
#include <memory>
#include <set>
#include <string>

namespace evolution
{
  // singleton class to hold a collection of programs (GLSL shaders)
  class ProgramSelector
  {
  public:
    static ProgramSelector* getProgramSelector();

    ~ProgramSelector() { }

    // rule of three
    ProgramSelector(const ProgramSelector&) = delete;
    ProgramSelector& operator=(const ProgramSelector&) = delete;

    Program* getProgram(const std::string& key);

    void addProgram(const std::string& vertShader,
                    const std::string& fragShader,
                    const std::string& name);

    bool isProgramValid(const std::string& key) const;

    std::set<std::string> getAllValidProgramKeys() const;

  private:
    std::map<std::string, std::unique_ptr<Program>> m_programs;
    ProgramSelector();
  };

  ProgramSelector* getProgramSelector();
} // namespace evolution
#endif