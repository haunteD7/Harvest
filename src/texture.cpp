#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(int width, int height, int channels) 
  : _width(width), _height(height), _channels(channels), _is_data_loaded(false)
{
  glCall(glGenTextures(1, &_id));
  glCall(glBindTexture(GL_TEXTURE_2D, _id));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void Texture::set_data(u8* data) {
  glCall(glBindTexture(GL_TEXTURE_2D, _id));
  glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)data));
  glCall(glGenerateMipmap(GL_TEXTURE_2D));

  _is_data_loaded = true;
}

void Texture::bind() {
  glCall(glBindTexture(GL_TEXTURE_2D, _id));
}

std::optional<Texture> TextureLoader::load(const char* path) {
  std::optional<Texture> result;

  int width, height, channels;

  stbi_set_flip_vertically_on_load(true);
  u8* image = stbi_load("test.jpg", &width, &height, &channels, 0);
  
  if(image) 
  {
    auto& texture = result.emplace(width, height, channels);
    texture.set_data(image);
  }
  else
  {
    LOG_ERR("Could not load texture (%s)", path);
  }

  stbi_image_free(image);

  return result;
}