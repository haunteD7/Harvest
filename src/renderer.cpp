#include "renderer.h"
#include "log.h"

#include "gl_extra.h"

bool Renderer::_is_system_initialized;

Renderer::Renderer() {

}
Renderer::~Renderer() {

}
bool Renderer::system_start() {
  if (!gladLoadGL()) {
    LOG_ERR("GLAD initialization error");

    return false;
  }

  const char* vertex_shader = R"(
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
  const char* fragment_shader = R"(
    #version 430 core

    layout (location = 0) out vec4 fragColor;

    void main() {
      fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
  )";

  GLuint vertex_shader_id;
  GLuint fragment_shader_id;
  glCall(vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
  glCall(fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
  glCall(glShaderSource(vertex_shader_id, 1, &vertex_shader, 0));
  glCall(glShaderSource(fragment_shader_id, 1, &fragment_shader, 0));

  glCall(glCompileShader(vertex_shader_id));
  glCall(glCompileShader(fragment_shader_id));

  // Vertex shader log
  {
    int success;
    char shader_log[1024] = {};

    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(vertex_shader_id, 1024, 0, shader_log);
      LOG_ERR("Vertex shader compile error: %s", shader_log);
    }
  }
  // Fragment shader log
  {
    int success;
    char shader_log[1024] = {};

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(fragment_shader_id, 1024, 0, shader_log);
      LOG_ERR("Fragment shader compile error: %s", shader_log);
    }
  }
  glCall(GLuint program_id = glCreateProgram());
  glCall(glAttachShader(program_id, vertex_shader_id));
  glCall(glAttachShader(program_id, fragment_shader_id));
  glCall(glLinkProgram(program_id));

  // Cleanup
  glDetachShader(program_id, vertex_shader_id);
  glDetachShader(program_id, fragment_shader_id);
  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  glCall(glUseProgram(program_id));
  // VAO
  GLuint VAO;
  glCall(glGenVertexArrays(1, &VAO));
  glCall(glBindVertexArray(VAO));


  return true;
}
void Renderer::system_stop() {
  _is_system_initialized = false;
}

void Renderer::set_clear_color(const float r, const float g, const float b, const float a) {
  glCall(glClearColor(r, g, b, a));
}
void Renderer::clear() {
  glCall(glClear(GL_COLOR_BUFFER_BIT));
  glCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}
void Renderer::set_viewport(u32 width, u32 height) {
  glCall(glViewport(0, 0, width, height));
}
