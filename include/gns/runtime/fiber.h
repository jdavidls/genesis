#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>

GNS_CODE_C(

  struct gnsFiber;
  struct gnsFiberTracker;
  struct gnsFiberContinuator;

  struct gnsFiberTracker {
    gnsFiberContinuator * continuator;
  };


  extern gnsFiber *gnsFiberGetCurrent();

  extern gnsFiberContinuator* gnsFiberAllocate();
  extern gnsFiberContinuator* gnsFiberSwap(gnsFiberContinuator*);

)

GNS_CODE_CXX(
# include<iostream>

  //using FiberCommand = gnsFiberCommand;


  struct FiberTracker: gnsFiberTracker {

    union {
      gnsFiberContinuator * continuator;

      struct  {
        gnsFiberContinuator * continuator;
        operator bool() {
          return continuator != nullptr;
        }
      } finished;
    };

    GNS_DECLARE_NON_COPYABLE(FiberTracker);

    FiberTracker():
      continuator( gnsFiberAllocate() )
    { }

    FiberTracker(gnsFiberContinuator*&& c):
      continuator(c)
    {
      c = nullptr;
    }

    ~FiberTracker() {
//      if( continuator )
//        gnsFiberUnwind(&continuator);
    }



    void swap() {
      continuator = gnsFiberSwap(continuator);
    }
  };

)
