#include "ProgramSelector.hpp"

namespace evolution
{
  ProgramSelector::ProgramSelector()
  {
    m_programs["default"] = std::make_unique<Program>();
  }

  Program* ProgramSelector::getProgram(std::string key)
  {
    if (m_programs.count(key))
    {
      return m_programs[key].get();
    }
    return nullptr;
  }
  void ProgramSelector::addProgram(const std::string& vertexShaderSrc,
                                   const std::string& fragmentShaderSrc,
                                   std::string* errMsg)
  {
  }
} // namespace evolution
