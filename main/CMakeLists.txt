cmake_minimum_required(VERSION 3.5)

set(COMPONENT_SRCS
    "src/main.cpp"
    "src/tasks/wifi_task.cpp"
    "src/tasks/mdns_task.cpp"
    "src/utils/helpers.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS
    "include"
)

idf_component_register(
    SRCS ${COMPONENT_SRCS}
    INCLUDE_DIRS ${COMPONENT_ADD_INCLUDEDIRS}
    REQUIRES 
        nvs_flash
        esp_netif
        esp_wifi
    PRIV_REQUIRES 
        mdns
)