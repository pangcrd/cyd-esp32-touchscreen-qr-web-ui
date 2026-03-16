#ifndef QR_WEBSERVER_H
#define QR_WEBSERVER_H

#include "ui.h"


#ifdef __cplusplus
extern "C" {
#endif

void qr_task(void *arg);
void init_server();
void run_server();

#ifdef __cplusplus
}
#endif

#endif