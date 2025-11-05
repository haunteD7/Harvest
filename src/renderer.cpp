#include "renderer.h"
#include "log.h"
#include "shader.h"
#include "gl_extra.h"

bool Renderer::_is_system_initialized;

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}

bool Renderer::system_start()
{
  if (!gladLoadGL())
  {
    LOG_ERR("GLAD initialization error");

    return false;
  }

  const char *vertex_shader_src = R"(
    #version 430 core

    void main() {
      vec2 points[6] = {
        vec2(-0.5, 0.5),
        vec2(0.5, 0.5),
        vec2(0.5, -0.5),

        vec2(-0.5, 0.5),
        vec2(0.5, -0.5),
        vec2(-0.5, -0.5),
      };

      gl_Position = vec4(points[gl_VertexID], 1.0, 1.0);
    }
  )";
  const char *fragment_shader_src = R"(
    #version 430 core

    layout (location = 0) out vec4 fragColor;

    void main() {
      fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
  )";

  ShaderProgram prog;
  {
    Shader fragment_shader(Shader::Type::Fragment, fragment_shader_src);
    Shader vertex_shader(Shader::Type::Vertex, vertex_shader_src);
    fragment_shader.compile();
    vertex_shader.compile();
    prog.attach_shader(fragment_shader);
    prog.attach_shader(vertex_shader);
    prog.link();
  }
  prog.use();

  // VAO
  GLuint VAO;
  glCall(glGenVertexArrays(1, &VAO));
  glCall(glBindVertexArray(VAO));

  return true;
}
void Renderer::system_stop()
{
  _is_system_initialized = false;
}

void Renderer::set_clear_color(const float r, const float g, const float b, const float a)
{
  glCall(glClearColor(r, g, b, a));
}
void Renderer::clear()
{
  glCall(glClear(GL_COLOR_BUFFER_BIT));
  glCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}
void Renderer::set_viewport(u32 width, u32 height)
{
  glCall(glViewport(0, 0, width, height));
}
