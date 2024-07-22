# Entrega de NachOS

En este proyecto se desarrolló el sistema operativo NachOS, creando sus llamados a sistema en el archivo `exception.cc` :

* Create
* Open
* Read
* Write
* Close
* Yield
* Exec
* Exit
* Fork
* Join
* Socket
* Connect

Cada llamado a sistema (`syscalls`) se emplea leyendo registros 4, 5 y 6 (donde se ubican los parámetros de la función) y se utilizan los syscalls de Unix. Para terminar, se devuelve (`return`) en el registro 2.

Además se implementó la clase `addrspace` para poder ejecutar varios programas de usuario simultanéamente, para ello se utiliza un objeto de la clase `BitMap`, con el objetivo de tener un control de cuales páginas están en uso y a que lugar de la memoria (página física) está asociada la página virtual. La asociación página virtual-página física, se realiza por medio del `BitMap` el cual guarda los bits ocupados (espacios físicos ya en uso) y encuentra el siguiente espacio desocupado para utilizar.

Para lograr todo esto, se creó un semáforo para control de concurrencia de consola; además de tablas de archivos abiertos. Esto se declara y crea en los archivos `system.h` y `system.cc` en la carpeta `/threads`

## Ejecución

Para ejecutar o "correr" el programa se deben seguir los siguientes pasos:

1. Ubicarse en la carpeta de userprog
> `cd NachOS/NachOSx64/code/userprog` 
2. Realizar el include de todas las dependencias que necesita el código
> `make depend`
3. Compilar el código
> `make`
4. Ejecutar las pruebas que desee
> `./nachos -x ../test/copy`

## Creditos

Sebastián Venegas Brenes - C18440