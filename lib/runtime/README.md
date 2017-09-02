# gns runtime

# Module
  Define una serie de

# Segments:
  Representan un conjunto de valores globales, variables o constantes,
  que tienen la capacidad de ser 'empujados' y 'traidos' en una pila propia
  para cada segmento.

# Globals:
  pueden tener un ámbito de proceso, de hilo, de tarea o de fiber, cada una es
  miembro de un segmento.


# Task:
  se utilizan las tareas para agrupar un conjunto de fibers, haciendo posible
  compartir variables entre diferentes fibers mediante el uso de task gobals.


# concurrenca global (Concurreny orchestrator):

  Las variables globales en ámbito de proceso y tarea son de naturaleza
  inmutable y volátil. Puede adquirirse exclusividad de lectura y modificación
  mediante el uso del sistema de concurrencia.

  synchronize(mySegment, READ)
    const Bytes& ()myVar;


  El orquestador de concurrencia, junto con los event loops...

  pueden ser process_global o task_global.
  SharedSegment;
  OwnSegment;

  SharedVariable a;
  SharedConstant b;


  // puede ser fiber_global o un thread_global, no necesitan concurrencia
  OwnVariable a;
  OwnConstant b;
