#pragma once

#include "types.h"

#include "gl_extra.h"

#include <optional>

class Texture 
{
public:
  Texture() = default;
  Texture(int width, int height, int channels);
  ~Texture() = default;

  void set_data(u8* data);
  void bind();

  int get_width() const { return _width; }
  int get_height() const { return _height; }
  bool is_data_loaded() const { return _is_data_loaded; }
private:
  int _width;
  int _height;
  int _channels;

  GLuint _id;

  bool _is_data_loaded;
};

class TextureLoader 
{
public:
  TextureLoader() = default;
  ~TextureLoader() = default;

  static std::optional<Texture> load(const char* path);
private:
};