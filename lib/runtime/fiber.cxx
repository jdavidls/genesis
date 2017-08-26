#include <dlfcn.h>
#include <link.h>

#include <gns/common/basics.h>

struct gnsFiber {

};

GNS_THREAD_LOCAL gnsFiber* gnsCurrentFiber;



void gnsFiberStartup() {

}

void gnsFiberShutdown() {

}
/*
void gnsContinueFiber() {

}
*/
