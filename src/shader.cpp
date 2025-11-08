#include "shader.h"

#define MAX_SHADER_ERROR_LEN 128

Shader::Shader(Shader::Type type) : _type(type), _state(Shader::State::Created), _program_id_attached_to(0)
{
  GLenum shader_type_gl;
  switch (_type)
  {
    case Shader::Type::Fragment:
    {
      shader_type_gl = GL_FRAGMENT_SHADER;
      break;
    }
    case Shader::Type::Vertex:
    {
      shader_type_gl = GL_VERTEX_SHADER;
      break;
    }
  }
  glCall(_id = glCreateShader(shader_type_gl));
}
Shader::Shader(Shader::Type type, const char *source_text) : Shader::Shader(type)
{
  glCall(glShaderSource(_id, 1, &source_text, NULL));
  _state = State::SourceLoaded;
}
Shader::~Shader()
{
  if (_program_id_attached_to)
  {
    glCall(glDetachShader(_program_id_attached_to, _id));
  }
  glCall(glDeleteShader(_id));
}
void Shader::set_source(const char *source_text)
{
  glCall(glShaderSource(_id, 1, &source_text, NULL));
  _state = Shader::State::SourceLoaded;
}
Shader::State Shader::get_state() const { return _state; }
GLuint Shader::get_id() const { return _id; }

bool Shader::compile()
{
  glCall(glCompileShader(_id));
  // Shader error checking
  int success;
  char shader_log[MAX_SHADER_ERROR_LEN] = {};
  glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(_id, MAX_SHADER_ERROR_LEN, 0, shader_log);
      LOG_ERR("%s shader compile error: %s", get_shader_type_char(_type), shader_log);
      _state = State::Error;
     return false;
  }
  _state = State::Compiled;

  return true;
}
void Shader::attach_to_program(const ShaderProgram &shader_program)
{
  _program_id_attached_to = shader_program.get_id();
}
void Shader::detach_from_program() { _program_id_attached_to = 0; }
ShaderProgram::ShaderProgram() : _state(State::Created)
{
  glCall(_id = glCreateProgram());
}
ShaderProgram::~ShaderProgram()
{
  glCall(glDeleteProgram(_id));
}
GLuint ShaderProgram::get_id() const { return _id; }
void ShaderProgram::attach_shader(Shader &shader)
{
  if (shader.get_state() != Shader::State::Compiled)
      return;
  glCall(glAttachShader(_id, shader.get_id()));
  shader.attach_to_program(*this);
}
void ShaderProgram::detach_shader(Shader &shader)
{
  if (shader.get_state() != Shader::State::Compiled)
      return;
  glCall(glDetachShader(_id, shader.get_id()));
  shader.detach_from_program();
}
bool ShaderProgram::link()
{
  glCall(glLinkProgram(_id));

  int success;
  char program_log[MAX_SHADER_ERROR_LEN] = {};

  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(_id, MAX_SHADER_ERROR_LEN, 0, program_log);
    LOG_ERR("Shader program compile error: %s", program_log);
    _state = State::Error;

    return false;
  }
  _state = State::Linked;

  return true;
}
void ShaderProgram::use()
{
  if (_state == State::Linked)
  {
    glCall(glUseProgram(_id));
  }
}