# Fiber mutex

struct gnsFiberMutex {
  Atomic<gnsFiber*> fiber;
};
