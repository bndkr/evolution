#ifndef EVOLUTION_PROGRAM_SELECTOR_HPP
#define EVOLUTION_PROGRAM_SELECTOR_HPP

#include "Shader.hpp"

#include <map>
#include <memory>
#include <set>
#include <string>

namespace evolution
{
  class ProgramSelector
  {
  public:
    ProgramSelector();

    Program* getProgram(const std::string& key);

    void addProgram(const std::string& name);

    bool isProgramValid(const std::string& key) const;

    std::set<std::string> getAllValidProgramKeys() const;

  private:
    std::map<std::string, std::unique_ptr<Program>> m_programs;
  };

  extern ProgramSelector* pProgramSelector;

  void UseProgramSelector(ProgramSelector* pSelector);
} // namespace evolution
#endif