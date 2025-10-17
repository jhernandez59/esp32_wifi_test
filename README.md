# ESP32 WiFi Test con mDNS

Proyecto de prueba para conexión WiFi y servicio mDNS en ESP32.

## Características
- Conexión WiFi automática
- Servicio mDNS para descubrimiento en red
- Estructura modular con tareas FreeRTOS

## Estructura
esp32_wifi_test/
├── .gitignore
├── .gitattributes
├── README.md
├── CMakeLists.txt
├── main/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── tasks/
│   │   │   ├── wifi_task.cpp
│   │   │   └── mdns_task.cpp
│   │   └── utils/
│   │       └── helpers.cpp
│   ├── include/
│   │   ├── task_manager.h
│   │   └── wifi_manager.h
│   └── CMakeLists.txt
└── managed_components/ (se crea automáticamente)


## Configuración
1. Edita `include/wifi_manager.h` con tus credenciales WiFi
2. Compila: `idf.py build`
3. Flash: `idf.py -p /dev/ttyUSB0 flash monitor`

## Uso
- Accede via: `http://esp32-test.local`
- Servicios mDNS: `avahi-browse -at`