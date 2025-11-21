#pragma once

#include <stdexcept>

namespace ns
{
  template <typename T, size_t S>
  struct vec_t
  {
    T raw[S];

    /* Getters */
    T &operator[](size_t index)
    {
      if(index >= S) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }
    const T &operator[](size_t index) const
    {
      if(index >= S) throw std::out_of_range("Element index of a vector is out of range");
      return this->raw[index];
    }

  };

  template <typename T>
  struct vec_t<T, 2> 
  {
    union
    {
      T raw[2];
      struct
      {
        T x, y;
      };
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
  struct vec_t<T, 3> 
  {
    union
    {
      T raw[3];
      struct
      {
        T x, y, z;
      };
      struct
      {
        T r, g, b;
      };
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
  struct vec_t<T, 4> 
  {
    union
    {
      T raw[4];
      struct
      {
        T x, y, z, w;
      };
      struct
      {
        T r, g, b, a;
      };
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
  using vec2 = vec_t<float, 2>;
  using vec3 = vec_t<float, 3>;
  using vec4 = vec_t<float, 4>;

  using vec2i = vec_t<int, 2>;
  using vec3i = vec_t<int, 3>;
  using vec4i = vec_t<int, 4>;

  using vec2ui = vec_t<unsigned int, 2>;
  using vec3ui = vec_t<unsigned int, 3>;
  using vec4ui = vec_t<unsigned int, 4>;
} // namespace ns
