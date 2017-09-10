# Value

Genesis es lo que realiza una metafuncion, las metafunciones hacen genesis de
un programa.

El acceso a un valor es  por referencia, siendo la referencia portadora de toda
la informacion descriptiva de ese valor.  

Propiedades de un valor

 - rank: natural
 - extent: natural[rank]

 - Layout: la estructura a bajo nivel de un valor

 - Mutability [constant|variable]
    La informacion contenida en un valor constante es conocida en su genesis.
    La informacion contenida en un valor variable es desconocida en su genesis.

 - Access [shared|owned variable]
    cuando un valor es compartido, el acceso mutativo debe ser atomico, o debe
    de hacerse uso de algun mecanismo de adquisicion del valor. La lectura es

 - locator: se encarga de allocation deallocation de un valor.
 - factory: constructor destructor.

 - frame [global|local] Exsiten dos marcos posibles para un valor,
    el marco local se refiere cuando un valor ha sido construido

Existen diferentes ciclos de vida para un valor, segun el uso frame


managerOf(value): constant


descriptorOf(value): descriptor
    retorna un descriptor del valor, esta funcion



rankOf(value): natural
    return the rank of value (number of dimensions)


extentOf(value): natural[]
    returns an array with the dimensional extent of value.
    if the input value is a zero rank value, the return is void array [].


isConstant isVariable
isShared isOwned
is


inference(value, naturalXY[]): value
inference(value, symbol[]): value




MEMORY:
    memory.local(type): value


EXECUTION FLOW:
    value = yield(value) -> async return to caller
