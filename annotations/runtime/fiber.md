# Fibers

Abstrae el concepto de _transferencia de control_ entre dos fujos de
ejecucion diferentes. Proporciona la mecanica de bajo nivel subyacente en la
implementacion de todas las funcionalidades que requieran de _transferencia de
control_, como puede ser: Coroutines, async execution, generators, etc.

## analisis desde la posesión y la transferencia del _control de ejecucion_

Cuando un _fiber_ posee el control de ejecucion, y decide, en un momento
puntual, transferir ese control a otro _fiber_. Esa transferencia de control
implica tambien la transferencia de un dato que representa el estado de
ejecucion (**ESR**: _Execution State Representation_) del _fiber_ emisor,
hacia el fiber_ receptor.

El cometido del dato **ESR** es el de poder volver a transferir el control al
_fiber_ emisor, momento en el cual el dato perderá su validez. Una vez recibido,
un _**ESR**_ puede ser almacenado o transmitido, pero nunca duplicado. La
_posesion del control de ejecucion_, sobre el _fiber_ eyector, es determinada
por la posesion de su **ESR**.

Teniendo en cuenta lo anterior y apliando el foco a un marco general, podemos
visualizar un grafo dirigido donde los nodos (_fibers_) se conectan con otros
nodos en funcion del control de ejecucion sobre ellos. En un entorno
multithread, multiples _fibers_ pueden tener el control de ejecucion.

## Fibers auxiliares

Durante el proceso habitual del programa, ocurren diferentes situaciones en las
que debe de realizarse una transferencia de control hacia otros fibers. Como es
el caso de la espera a un evento, o la eyeccion por alguna excepcion. Para
estos casos existen fibers auxiliares cuyo control de ejecucion se encuentra a
nivel de _thread_ (el **ESR** es _thread local_).

Algunos mecanismos que puedel ser implementados utilizando fibers auxiliares:

  - *monitor*: stack unwinding, debugging, disassembly, profiling, etc.
    puede incluir varios fibers, algunos opcionales, algunos almacenados como
    fiber-locals (el fiber que hace debugging por ejemplo).
    - manejo de señales generadas a nivel de thread (error de acceso a memoria,
      error de punto flotante, etc),
    - manejo de ejecciones

  - *E/S asincrona*: para poder realizar en cualquier momento una transferencia
  de control al _orquestador asincrono_ asociado al _thread_.


## _Fiber Interfaces_

Es posible implementar un interface a través de un _fiber_ almacenando el ESR
como target de un object. Los procedimientos del interface podrán realizar
transferencias de control al fiber. Este método es entendido en genesis como
el uso mas correcto, donde todo el subsistema de fibers a bajo nivel queda
encapsultado en un sistema de alto nivel. Por lo que será el patron mas
habitual de uso de fibers.

Estos interfaces estarán pareados, donde un fiber será iterator, otro sera generator.

La unica particularidad, no poco importante, es que estos objetos núnca podran
ser copiados.

**un puntero adicional en el ESR, podria facilitar el acceso la implementacion del
interface a cierta informacion alojada en el server (getters y setters). De otra
forma esa informacion quedaría SIEMPRE oculta y para obtener un simple valor
habria que realizar dos transferencias de control.

Tambien necesario este hueco en el ESR para crear un protocolo de transferencia
de informacion. IFC**

## Inter Fiber Communication (IFC)

Pueden existir dos protocolos de IFC, uno basado en thread_locals y otro basado
en *ESR View pointer*, ambos mecanismos pueden ser utilizados a la vez.
