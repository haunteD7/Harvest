#pragma once

#include "vec.h"

namespace ns
{
  template <typename T, size_t S>
  struct mat_t
  {
    union
    {
      vec_t<T, S> rows[S];
      T raw[S * S];
    };

    vec_t<T, S>& operator[](size_t row) 
    {
      if(row >= S) throw std::out_of_range("Row index is out of range");
      return rows[row];
    }
    const vec_t<T, S>& operator[](size_t row) const
    {
      if(row >= S) throw std::out_of_range("Row index is out of range");
      return rows[row];
    }
  };

  using mat2 = mat_t<float, 2>;
  using mat3 = mat_t<float, 3>;
  using mat4 = mat_t<float, 4>;

  using mat2i = mat_t<int, 2>;
  using mat3i = mat_t<int, 3>;
  using mat4i = mat_t<int, 4>;

  using mat2ui = mat_t<unsigned int, 2>;
  using mat3ui = mat_t<unsigned int, 3>;
  using mat4ui = mat_t<unsigned int, 4>;
} // namespace ns
