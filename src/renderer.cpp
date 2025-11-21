#include "renderer.h"
#include "log.h"
#include "shader.h"
#include "texture.h"
#include "gl_extra.h"

#include "nsmath/mat.h"

#include <cmath>

bool Renderer::_is_system_initialized;
static u32 mat_loc;

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

    layout(location = 0) in vec3 pos;
    layout(location = 1) in vec2 in_tex_coord;

    out vec2 tex_coord;

    uniform mat4 rotate_mat;

    void main() {
      gl_Position = rotate_mat * vec4(pos, 1.0);
      tex_coord = in_tex_coord;
    }
  )";
  const char *fragment_shader_src = R"(
    #version 430 core

    in vec2 tex_coord;

    out vec4 frag_color;

    uniform sampler2D my_texture;

    void main() {
      frag_color = texture(my_texture, tex_coord);
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

  float points[] = {
    -0.5, 0.5, 0, 0, 1,
    0.5, 0.5, 0, 1, 1,
    0.5, -0.5, 0, 1, 0,
    -0.5, 0.5, 0, 0, 1,
    0.5, -0.5, 0, 1, 0,
    -0.5, -0.5, 0, 0, 0,
  };

  // VBO
  GLuint VBO;
  glCall(glGenBuffers(1, &VBO));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
  glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW));

  // VAO
  GLuint VAO;
  glCall(glGenVertexArrays(1, &VAO));
  glCall(glBindVertexArray(VAO));
  glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0)));
  glCall(glEnableVertexAttribArray(0));
  glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))));
  glCall(glEnableVertexAttribArray(1));
  
  auto texture = TextureLoader::load("test.jpg");

  glCall(mat_loc = glGetUniformLocation(prog.get_id(), "rotate_mat"));

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
  float tm = glfwGetTime();
  ns::mat4 rotate_mat = 
  {
    std::cos(tm), std::sin(tm), 0, 0,
    -std::sin(tm), std::cos(tm), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
  glCall(glUniformMatrix4fv(mat_loc, 1, GL_FALSE, rotate_mat.raw));
  glCall(glClear(GL_COLOR_BUFFER_BIT));
  glCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}
void Renderer::set_viewport(u32 width, u32 height)
{
  glCall(glViewport(0, 0, width, height));
}
