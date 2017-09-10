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

/*
GNS_CODE_C(
  extern gnsUnknowType gnsUnknowValue;
)
GNS_CODE_CXX(
  constexpr UnknowType unknowValue;
)
*/
//GNS_TYPEALIAS_DECLARE( UnknowType, struct { int _ [0]; } );
#define GNS_COMPAT_DECLARE(...)

GNS_TYPEALIAS_DECLARE( Empty, struct { int _ [0]; } );
GNS_TYPEALIAS_DECLARE( Bit, bool );
GNS_TYPEALIAS_DECLARE( Byte, uint8_t );
GNS_TYPEALIAS_DECLARE( Pointer, void* );

GNS_TYPEALIAS_DECLARE( Natural, uintptr_t );
GNS_TYPEALIAS_DECLARE( Natural8, uint8_t );
GNS_TYPEALIAS_DECLARE( Natural16, uint16_t );
GNS_TYPEALIAS_DECLARE( Natural32, uint32_t );
GNS_TYPEALIAS_DECLARE( Natural164, uint64_t );

GNS_TYPEALIAS_DECLARE( Integer, intptr_t );
GNS_TYPEALIAS_DECLARE( Integer8, int8_t );
GNS_TYPEALIAS_DECLARE( Integer16, int16_t );
GNS_TYPEALIAS_DECLARE( Integer32, int32_t );
GNS_TYPEALIAS_DECLARE( Integer164, int64_t );

GNS_TYPEALIAS_DECLARE( FloatPoint, double );
GNS_TYPEALIAS_DECLARE( FloatPoint32, float );
GNS_TYPEALIAS_DECLARE( FloatPoint64, double );

GNS_CODE_C(
  union gnsWord {
    gnsPointer asPointer;
    gnsNatural asNatural;
    gnsInteger asInteger;
    gnsFloatPoint asFloatPoint;
  };
)
GNS_CODE_CXX(
  union Word {
    GNS_COMPAT_CONSTRUCTOR(Word);

    Pointer asPointer;
    Natural asNatural;
    Integer asInteger;
    FloatPoint asFloatPoint;
  };
)


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

      operator Natural() const {
        return this->length;
      }

      Natural operator ++ () { return (*this) = this->length + 1; }
      Natural operator -- () { return (*this) = this->length - 1; }
      Natural operator += (Natural n) { return (*this) = this->length + n; }
      Natural operator -= (Natural n) { return (*this) = this->length - n; }

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
    };

  template<typename T>
    struct Array {
      union {
        ArrayABI<T> self;
        ArrayLengthAttr<T> length;
      };

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


#define GNS_ARRAY_DECLARE(ArrayTypeName, ElementTypeName, ...)                \
  GNS_CODE_C(                                                                 \
    struct gns ## ArrayTypeName {                                             \
      gnsNatural length;                                                      \
      GNS_SYMBOL_C(ElementTypeName) * data;                                   \
    };                                                                        \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    struct ArrayTypeName: Array<GNS_SYMBOL_CXX(ElementTypeName)> {            \
      GNS_DECLARE_C_COMPAT( ArrayTypeName );                                  \
      __VA_ARGS__                                                             \
    };                                                                        \
  )

GNS_ARRAY_DECLARE(Bytes, Byte);
GNS_ARRAY_DECLARE(Pointers, Pointer);
GNS_ARRAY_DECLARE(Integers, Integer);
GNS_ARRAY_DECLARE(Naturals, Natural);
GNS_ARRAY_DECLARE(FloatPoints, FloatPoint);

/*******************************************************************************
/     String
/******************************************************************************/
GNS_ARRAY_DECLARE(String, Byte,
  // String stuff
);
/*******************************************************************************
/     Object
/******************************************************************************/

/*******************************************************************************
/ # Cast
/******************************************************************************/

GNS_CODE_CXX(
  template<typename Interface, typename Target=Word>
    struct Object {
      GNS_STATIC_ASSERT( "Object target size must be word size",
        sizeof(Target) == sizeof(Word) );

      const Interface * interface;
      Target target;
    };
)


#define GNS_OBJECT_DECLARE(ObjectTypeName, InterfaceTypeName, TargetTypeName) \
  GNS_CODE_C(                                                                 \
    struct gns ## ObjectTypeName {                                            \
      const GNS_SYMBOL_C(InterfaceTypeName) * interface;                      \
      GNS_SYMBOL_C(TargetTypeName) target;                                    \
    };                                                                        \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    struct ObjectTypeName: Object<GNS_SYMBOL_CXX(InterfaceTypeName),          \
                                  GNS_SYMBOL_CXX(TargetTypeName)> {           \
      GNS_DECLARE_C_COMPAT(CastTypeName);                                     \
    };                                                                        \
  )


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
