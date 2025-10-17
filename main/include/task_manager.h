#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

    // Declaraciones de tareas
    void wifi_task(void *pvParameters);
    void mdns_task(void *pvParameters);

    // Función para crear todas las tareas
    void create_all_tasks(void);

#ifdef __cplusplus
}
#endif

#endif