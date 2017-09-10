## Object Oriented Support

El acceso miembros de un objeto es implementado un mapa de membresia. Los
miembros de un objeto se pueden dividir en:
   - atributos: propiedades que se resuelven a traves a traves del layout
      con un inice y un tipo.
   - propiedades: getters, setters potencialmente metagenerados
   - metodos: es un getter que retorna un funcion binding.

Entendiendo que el sistema de tipado está parcialment desacoplado del layout
permaneciendo en un nivel mas abstracto, un mismo dato puede ser objeto de
varios interfaces. Es por ello que debemos de distringuir entre objeto y dato.


- Un dato puede ser objeto de varias inferencias simultaneamente.
- Un objeto siempre actúa como una referencia hacia un dato. El objeto es un
dato referencial separado del dato inferencial.

La estructura de un objeto es tambien un componente propio dentro del sistema
Se debe hablar de estructuras fluidas ya que su layout depede en gran medida
de la variabilidad de sus componentes.

un objeto puede entenderse como un tipo altamente dinamico materializado en
tiempo de compilacion y uilizado

El concepto mas abstracto de un objeto en genesies es el de Valor.


Object->release (TODOS LOS INTERFACES)
Object->reflector (TODOS LOS INTERFACES)

descriptorOf(object, Type) {
  const reflector = object->reflector;

  if( reflector.length < Type.Level)
    return nullptr;

}

for(const Object & reflector: hierarchyOf(obj) ) {
  // iterador por la jerarquia de prototipos..

}


La particularidad release (forgot)
los interfaces, de forma general, implementan la propiedad destroy.
