#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "wifi_config.h"

    // Declaraciones de funciones
    void wifi_task(void *pvParameters);
    void print_wifi_status(void);

#ifdef __cplusplus
}
#endif

#endif