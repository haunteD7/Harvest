#pragma once

#include "vec.h"

namespace ns
{
  template <typename T>
  struct mat2_t
  {
    union
    {
      vec2_t<T> raws[2];
      T raw[4];
    };
    
    vec2_t<T>& operator[](size_t row) 
    {
      if(row >= 2) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
    const vec2_t<T>& operator[](size_t row) const
    {
      if(row >= 2) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
  };
  template <typename T>
  struct mat3_t
  {
    union
    {
      vec3_t<T> raws[3];
      T raw[9];
    };
    
    vec3_t<T>& operator[](size_t row) 
    {
      if(row >= 3) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
    const vec3_t<T>& operator[](size_t row) const
    {
      if(row >= 3) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
  };    
  template <typename T>
  struct mat4_t
  {
    union
    {
      vec4_t<T> raws[4];
      T raw[16];
    };
    
    vec4_t<T>& operator[](size_t row) 
    {
      if(row >= 4) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
    const vec4_t<T>& operator[](size_t row) const
    {
      if(row >= 4) throw std::out_of_range("Row index is out of range");
      return raws[row];
    }
  };    

  using mat2 = mat2_t<float>;
  using mat3 = mat3_t<float>;
  using mat4 = mat4_t<float>;

  using mat2i = mat2_t<int>;
  using mat3i = mat3_t<int>;
  using mat4i = mat4_t<int>;

  using mat2ui = mat2_t<unsigned int>;
  using mat3ui = mat3_t<unsigned int>;
  using mat4ui = mat4_t<unsigned int>;
} // namespace ns
