
#include <gns/common/traits.h>

#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

//# define GNS_ARRA

GNS_C_LINKAGE_END

#ifdef __cplusplus

namespace gns::ref {

  template<typename T> struct ReflectorABI;

  template<typename T>
    struct ReflectorABI: Empty {
      //constexpr type = typeOf<T>;
    };

  template<>
    struct ReflectorABI<void> { // todos los tipos de tamaño desconocido
      //const Type& type;
    };


  template<Natural R>
    struct ExtentABI {
      Natural extent[R];
    };



  template<typename T, Natural R>
    struct ABI: ExtentABI<R>, ReflectorABI<T> {
      T* pointer;
    };



  template<typename T, Natural R>
    struct RankAttr: ABI<T,R> {
      operator Natural() {
        return R;
      }
    };


  template<typename T, Natural R>
    struct ExtentAttr: ABI<T,R> {

    };

  template<typename T, Natural R> struct LengthAttr;

  template<typename T, Natural R>
    struct LengthAttr: ABI<T,R> {
      using ABI<T,R>::extent;

      operator Natural() {
        return extent[0];
      }
      Natural operator = (Natural newLength) {
        // resize
      }
    };

  template<typename T>
    struct LengthAttr<T, 0>: ABI<T, 0> {

      operator Natural() {
        /*
          Usa el length GET/SET interface
          desde ABI::type -> length.get(this.pointer)
          para una estructura retorna el numero de elementos
          para un numero retorna el numero de bits

          esta conectado con la implementacion de el index []
        */
        return 0;
      }


      Natural operator = (Natural newLength) {

      }
    };


}

namespace gns {
  template<typename T, Natural R = 0> union Ref;


  template<typename T, Natural R>
    union Ref {
      ref::RankAttr<T, R> rank;
      ref::ExtentAttr<T, R> extent;
      ref::LengthAttr<T, R> length;

      // ref::C<T,R> c; // c interface

      Ref() : abi{ }
      {}

      template <typename U,
                typename = typeIf<U, ( isSame<T,U> && !isVoid<T> && R == 0 )>>
        Ref(U& value) : abi{ {},{}, &value }
        {}


#     define GNS_REF_CAST(U)
      // can be in the c interface
      // well know C conversions:
      // R == 1 && isSame<T, Byte> operator gnsBytes()

    private:
      ref::ABI<T,R> abi;
      //Ref()
    };

/*En function de los constructores, tenemos


*/
}
#endif
