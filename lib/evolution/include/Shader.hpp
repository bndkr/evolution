#ifndef EVOLUTION_SHADER_HPP
#define EVOLUTION_SHADER_HPP

#include <string>
#include <vector>

namespace evolution
{
  class Program
  {
  public:
    Program(const std::string& vertexShaderSrc,
            const std::string& fragmentShaderSrc,
            std::string* errMsg = nullptr);

    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&& other);

    Program& operator=(Program&& other);

    std::string& getVertexShaderSrc();
    std::string& getFragmentShaderSrc();

    void bind();
    void unbind();

    void recompileFragShader(const std::string& fragmentShaderSrc,
                             std::string* errMsg = nullptr);
    void recompileVertexShader(const std::string& vertexShaderSrc,
                               std::string* errMsg = nullptr);

    void recompileProgram(const std::string& fragmentShaderSrc,
                          const std::string& vertexShaderSrc,
                          std::string* errMsg);

    void recompileProgram(std::string* errMsg);

    void addUniform(const float* vals, size_t num, std::string name);
    void addUniform(const uint32_t* vals, size_t num, std::string name);
    void addUniform(const int32_t* vals, size_t num, std::string name);

  private:
    uint32_t m_programID = 0;
    std::string m_vertexSrc;
    std::string m_fragSrc;

    void release();
  };
} // namespace evolution

#endif