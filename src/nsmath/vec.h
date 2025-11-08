#pragma once

#include <stdexcept>

namespace ns
{
  template <typename T>
  struct vec2_t
  {
    /* Data */
    union
    {
      struct
      {
        T x, y;
      };
      T raw[2];
    };
    /* Getters */
    T &operator[](size_t index)
    {
      if(index >= 2) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
    const T &operator[](size_t index) const
    {
      if(index >= 2) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
  };
  template <typename T>
  struct vec3_t
  {
    /* Data */
    union
    {
      struct
      {
        T x, y, z;
      };
      struct
      {
        T r, g, b;
      };
      T raw[3];
    };
    /* Getters */
    T &operator[](size_t index)
    {
      if(index >= 3) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
    const T &operator[](size_t index) const
    {
      if(index >= 3) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
  };
  template <typename T>
  struct vec4_t
  {
    /* Data */
    union
    {
      struct
      {
        T x, y, z, w;
      };
      struct
      {
        T r, g, b, a;
      };
      T raw[4];
    };
    /* Getters */
    T &operator[](size_t index)
    {
      if(index >= 4) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
    const T &operator[](size_t index) const
    {
      if(index >= 4) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
  };

  using vec2 = vec2_t<float>;
  using vec3 = vec3_t<float>;
  using vec4 = vec4_t<float>;

  using vec2i = vec2_t<int>;
  using vec3i = vec3_t<int>;
  using vec4i = vec4_t<int>;

  using vec2ui = vec2_t<unsigned int>;
  using vec3ui = vec3_t<unsigned int>;
  using vec4ui = vec4_t<unsigned int>;
} // namespace ns
