/*
Scheduler se divide en varios subsistemas:

- event-loop (base)
- timer (cola de eventos programados en el tiempo)
- io (espera para operaciones de entrada y salida asincrona)

- sync (operaciones en paralelo al event loop para fs)


la estructura del Evento esta compartida entre estos subsistemas
de forma que todo evento puede tener un timeout, io etc, almacenandose
la misma estancia los diferentes contenedores.

 Invokation protocols:
  FFI
  Delegate (function + context)
  Fiber continue
*/
#include <gns/sync/queue.h>

using namespace gns;

#include <queue>
#include <mutex>
#include <chrono>

struct gnsSchedulerEvent {

};


struct SchedulerEvent: gnsSchedulerEvent {

};

// scheduler es una TaskGlobal
struct gnsScheduler {
  // scheduler public abi
};

struct Scheduler: gnsScheduler {
  SyncQueue<SchedulerEvent> eventQueue;

// currentTick // now


};
/*
void gnsSchedulerConstructor(Scheduler& scheduler) {

}

void gnsSchedulerDestructor(gnsScheduler* scheduler) {

}
*/

/*

Pueden existir varias colas asociadas a grupos de threads (task's)
las colas estan disociadas del epoll,

*/

void gnsSchedulerMainLoop(Scheduler & scheduler) {

  // add the fiber to the scheduler worker lists (and guard + mutex)
  // SchedulerWorker worker(currentFiber);


  for(;;) {
    // accept a event
    //auto event = scheduler.eventQueue.pop();

    // dispatch event





  }
  // remove the thread from the scheduler
}

void gnsIOSignal() {
  // ... put all fd waiters in the event queue, remove timeouts from timer
}

void gnsSchedTimerHandler(Scheduler& scheduler) {
  auto now = std::chrono::steady_clock::now();

  //currentTick = now;

  // esta funcion es registrada para ser llamada cada X tiempo
  // se encarga de sacar elementos de la cola de scheduleds events
  // e introducirlos en la cola de dispatch

  // algunos de estos eventos pueden cencelar otros eventos
  // de forma colateral (timeout of )

}



void gnsSchedIOCosntructor(/*gnsSchedIO* */) {
  // epoll_init
  // fcntl -> establecer el sigio
  //
}

void gnsSchedIODestructor() {

}

// epoll + sigio + fdsignal
/*
void gnsSchedIOHandler(int sig, siginfo_t* sinfo, void* value) {
  // recibe un signal de entrada y salida, daba
}
*/
