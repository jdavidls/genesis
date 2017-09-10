#pragma once

#ifndef __cpluspus
# include <stdbool.h>
#endif

#include <stdint.h>

#ifdef __cplusplus
# include <iostream> // FOR ASSERT
# include <memory>
#endif

#include <gns/common/defines.h>
#include <gns/common/traits.h>

/*******************************************************************************
/ # C compatibility helper
/
/ Provides a
/******************************************************************************/
/*
#define GNS_COMPAT_DECLARE_CONSTRUCTOR(TypeName)  \
  template<typename Compat, typename = std::enable_if(::gns::CCompat<TypeName>::type, TypeName)>
    TypeName
*/

GNS_CODE_CXX(
  template<typename T> struct CCompat {
  };

  // TODO: trait for compat constructor..
  // template<typename C, typename = enable(isSame(C, CCompat<>::type))>
)

#define GNS_COMPAT_CHECK(TypeName)                                            \
  GNS_CODE_CXX(                                                               \
    GNS_STATIC_ASSERT(                                                        \
      "GNS C/C++ compatibility error, size of type " # TypeName " missmach",  \
      sizeof(GNS_SYMBOL_C(TypeName)) == sizeof(GNS_SYMBOL_CXX(TypeName))      \
    );                                                                        \
  )

#define GNS_COMPAT_DECLARE(TypeName)                                          \
  GNS_COMPAT_CHECK(TypeName)                                                  \
  GNS_CODE_CXX(                                                               \
    template<>                                                                \
      struct CCompat<GNS_SYMBOL_CXX(TypeName)> {                              \
        using type = GNS_SYMBOL_C(TypeName);                                  \
      };                                                                      \
  )

  // static auto cast(const GNS_SYMBOL_C(TypeName)) { return reinterpret_cast<GNS_SYMBOL_CXX(TypeName)>() }

#define GNS_TYPEALIAS_DECLARE(TypeName, ...)                                  \
  GNS_CODE_C(                                                                 \
    typedef __VA_ARGS__ gns ## TypeName;                                      \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    using TypeName = GNS_SYMBOL_C(TypeName);                                  \
  )                                                                           \

#define GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT(TypeName, ...)                   \
  GNS_TYPEALIAS_DECLARE(TypeName, __VA_ARGS__)                                \
  GNS_COMPAT_DECLARE(TypeName)

/*
GNS_CODE_C(
  extern gnsUnknowType gnsUnknowValue;
)
GNS_CODE_CXX(
  constexpr UnknowType unknowValue;
)
*/
//GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( UnknowType, struct { int _ [0]; } );

GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Empty, struct { int _ [0]; } );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Bit, bool );
GNS_TYPEALIAS_DECLARE( Byte, uint8_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Pointer, void* );

GNS_TYPEALIAS_DECLARE( Natural, uintptr_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Natural8, uint8_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Natural16, uint16_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Natural32, uint32_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Natural164, uint64_t );

GNS_TYPEALIAS_DECLARE( Integer, intptr_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Integer8, int8_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Integer16, int16_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Integer32, int32_t );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( Integer164, int64_t );

GNS_TYPEALIAS_DECLARE( FloatPoint, double );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( FloatPoint32, float );
GNS_TYPEALIAS_DECLARE_DECLARE_COMPAT( FloatPoint64, double );

/*******************************************************************************
/     Array
/******************************************************************************/

GNS_CODE_CXX(

template<typename T>
  struct ArrayABI: std::allocator<T> {
    static_assert( !isSame<T, void>, "Array<void> is not supported");

    using std::allocator<T>::allocate;
    using std::allocator<T>::deallocate;

    Natural length;
    T* data;

    ArrayABI():
    length(0),
    data(nullptr) {
    }

    ArrayABI(Natural length):
    length(length),
    data(allocate(length)) {
      std::uninitialized_value_construct_n(data, length);
    }

    ArrayABI(Natural length, const T* init):
    length(length),
    data(allocate(length)) {
      std::uninitialized_copy_n(init, length, data);
    }

    ~ArrayABI() {
      if( data )
      deallocate(data, length);
    }
  };

template<typename T>
  struct ArrayLengthAttr: private ArrayABI<T> {
    using ArrayABI<T>::allocate;
    using ArrayABI<T>::deallocate;

    operator Natural() {
      return this->length;
    }

    Natural operator = (const Natural length) {
      if( length != this->length ) {

        auto data = allocate(length);

        if( length > this->length )
          std::uninitialized_value_construct_n(
            std::uninitialized_copy_n(this->data, this->length, data),
            length - this->length);
        else
          std::destroy_n(
            std::uninitialized_copy_n(this->data, length, data),
            this->length - length);

        deallocate(this->data, this->length);

        this->length = length;
        this->data = data;
      }

      return length;
    }

    Natural operator ++() { return (*this) = this->length + 1; }
    Natural operator --() { return (*this) = this->length - 1; }

    Natural operator +=(Natural n) { return (*this) = this->length + n; }
    Natural operator -=(Natural n) { return (*this) = this->length - n; }

  };

template<typename T>
  union Array {
  private:
    ArrayABI<T> self;

  public:
    ArrayLengthAttr<T> length;

    Array():
      self() {
    }

    Array(Natural length, const T* init):
      self(length, init) {
    }

    template<Natural L>
      Array( const T (&init)[L] ):
        self(L, init) {
      }
/*
    template GNS_COMPAT_CONSTRUCTOR(CArray)
      Array( const CArray& c):
        self(c.length, c.data) {
      }
*/

    Array(const Array& init):
      self(init.self.length, init.self.data) {
    }

    // TODO: Compat constructor

    ~Array() {
      self.~ArrayABI();
    }

    operator bool () {
      return self.length > 0 && self.data;
    }

    T& operator [] (Integer idx) {
      if( idx >= 0 ) {
        GNS_ASSERT( idx < self.length );
        return self.data[idx];
      }
      else {
        idx = - idx;
        GNS_ASSERT( idx < self.length );
        return self.data[self.length - idx];
      }
    }

    Natural push(const T& value) {
      auto idx = self.length;

      ++length;
      self.data[idx] = value;
      return idx;
    }

  };
) // GNS_CODE_CXX


#define GNS_ARRAY_DECLARE(ArrayTypeName, ElementTypeName)                     \
  GNS_CODE_C(                                                                 \
    struct gns ## ArrayTypeName {                                             \
      gnsNatural length;                                                      \
      GNS_SYMBOL_C(ElementTypeName) * data;                                   \
    };                                                                        \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    using ArrayTypeName = Array<GNS_SYMBOL_CXX(ElementTypeName)>;             \
  )                                                                           \
  GNS_COMPAT_DECLARE(ArrayTypeName)

GNS_ARRAY_DECLARE(Bytes, Byte);
GNS_ARRAY_DECLARE(Pointers, Pointer);
GNS_ARRAY_DECLARE(Integers, Integer);
GNS_ARRAY_DECLARE(Naturals, Natural);
GNS_ARRAY_DECLARE(FloatPoints, FloatPoint);

/*******************************************************************************
/     String
/******************************************************************************/



/*******************************************************************************
/     MISC
/******************************************************************************/
GNS_CODE_CXX(

template<typename C, typename M>
  constexpr Natural offsetOf(M C::*member) {
    const C cls;
    return &(cls.*member) - &cls;
  }

template<typename T1, typename T2, typename T3>
  constexpr Natural offsetOf(T2 T1::*m1, T3 T2::*m2) {
    return offsetOf(m1) + offsetOf(m2);
  }
/*
template<typename T, T... values>
  struct Consts {

  };
*/
)
