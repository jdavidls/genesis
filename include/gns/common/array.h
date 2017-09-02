#pragma once
#include <memory>
#include <gns/common/basics.h>
#include <gns/common/traits.h>

#ifdef __cplusplus
namespace gns {

  template<typename T>
    struct ArrayABI: std::allocator<T> {
      static_assert( !isSame<T, void>, "Array<void> is not supported");

      Natural length;
      T* data;
    };

  template<typename T>
    struct ArrayLengthAttr: private ArrayABI<T> {

      operator Natural() {
        return this->length;
      }

      Natural operator = (const Natural length) {
        if( length != this->length ) {

          auto data = ArrayABI<T>::allocate(length);

          if( length > this->length )
            std::uninitialized_value_construct_n(
              std::uninitialized_copy_n(this->data, this->length, data),
              length - this->length);
          else
            std::destroy_n(
              std::uninitialized_copy_n(this->data, length, data),
              this->length - length);

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
    struct ArrayCastAttr: ArrayABI<T> {
    };

  template<>
    struct ArrayCastAttr<Byte>: ArrayABI<Byte> {
      operator gnsBytes () {
        return { this->length, this->data };
      }
    };

  template<typename T>
    union Array {
      ArrayLengthAttr<T> length;
      ArrayCastAttr<T> c;

      Array(): self{ 0, nullptr }
      {};
/*
      Array(Natural length, const T* data):
        self{ length, ArrayABI<T>::dup(data, length) } {
      }
      */
      Array(Natural length, const T* data) {
        self.length = length;
        self.data = self.allocate(length);

        std::uninitialized_copy_n(data, length, self.data);
      }


      template<Natural L>
        Array( const T (&data)[L] ):
          Array(L, data) {
        }

      operator bool () {
        return self.length > 0 && self.data;
      }

      ~Array() {
        if( self.data )
          self.deallocate(self.data, self.length);
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
    private:
      ArrayABI<T> self;
    };

}
#endif
