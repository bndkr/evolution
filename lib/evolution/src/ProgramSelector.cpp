#include "ProgramSelector.hpp"

namespace evolution
{
  ProgramSelector::ProgramSelector() { }

  ProgramSelector* ProgramSelector::getProgramSelector()
  {
    static ProgramSelector selector;
    return &selector;
  }

  Program* ProgramSelector::getProgram(const std::string& key)
  {
    if (m_programs.count(key))
    {
      return m_programs[key].get();
    }
    return nullptr;
  }

  void ProgramSelector::addProgram(const std::string& vertShader,
                                   const std::string& fragShader,
                                   const std::string& name)
  {
    m_programs[name] =
      std::make_unique<Program>(vertShader, fragShader);
  }

  bool ProgramSelector::isProgramValid(const std::string& key) const
  {
    // TODO: do some extra validation? is this necessary?
    return m_programs.count(key);
  }
  std::set<std::string> ProgramSelector::getAllValidProgramKeys() const
  {
    std::set<std::string> result;
    for (const auto& pair : m_programs)
    {
      result.insert(pair.first);
    }
    return result;
  }

  ProgramSelector* getProgramSelector()
  {
    return ProgramSelector::getProgramSelector();
  }
} // namespace evolution
