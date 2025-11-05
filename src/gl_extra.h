#pragma once

#include "log.h"

#include <cassert>

#include "types.h"

#ifndef NDEBUG
#define glCall(x) glClearError();\
                  x;\
                  assert(glCheckError());
#else
#define glCall(x) x;
#endif // NDEBUG

static const char* glGetErrorString(GLenum id) {
  switch (id)
  {
    case GL_INVALID_ENUM:                  return "INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                 return "INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:             return "INVALID_OPERATION"; break;
    case GL_STACK_OVERFLOW:                return "STACK_OVERFLOW"; break;
    case GL_STACK_UNDERFLOW:               return "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:                 return "OUT_OF_MEMORY"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION"; break;
  }

  return "UNKNOWN_ERROR";
}
static void glClearError() {
  while(glGetError() != GL_NO_ERROR);
}
static bool glCheckError() {
  bool no_error = true;

  while(GLenum error = glGetError()) {
    LOG_ERR("OpenGL: %s (%d)", glGetErrorString(error), error);
    no_error = false;
  }

  return no_error;
}
