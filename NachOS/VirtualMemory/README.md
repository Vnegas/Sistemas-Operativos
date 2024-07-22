# Entrega de NachOS VM

En este proyecto se desarrolló el sistema operativo NachOS, tomando como base las entregas anteriores. Creando la posibilidad de ejecutar los programas con memoria virtual.

La memoria virtual se implemento en la clase `addrspace`. Para lograr este objetivo, se empleó una clase denominada `Swap`, encargada de hacer el swap entre disco y memorio principal (RAM); en conjunto de la `tlb` que se encarga de mantener una cache de las últimas 4 páginas usadas por el programa.

> El `Swap` lleva un registro de las páginas que tiene ocupadas por medio de un `BitMap`, además de poseer un `OpenFile` que actua como disco para guardas las páginas. También, es el encargado de hacer los intercambios entre él y la Memoria Principal, para esto ocupa encontrar la página a sacar de RAM (por medio de FIFO) y hacer escrituras en memoria.

Para lograr el uso de la memoria virtual, se realizaron o se dividió en 5 casos posibles:

1. **La página ya está cargada en memoria**: Se actualiza la `tlb`.

1. **Hay un espacio libre en memoria, y la página NO está en Swap**: Se lee el ejecutable hacia memoria en el espacio encontrado libre. Se actualiza la `PageTable` y `tlb`

1. **Hay un espacio libre en memoria, y la página SI está en Swap**: Se lee desde el `Swap` hacia memoria en el espacio encontrado libre. Se actualiza la `PageTable` y `tlb`

1. **NO hay un espacio libre en memoria, y la página NO está en Swap**: Se encuentra página en memoria a sacar, se escribe esa página en `Swap` (sólo si esa página está `dirty`, si se ha modificado). Se lee desde el ejecutable hacia memoria en el espacio ahora libre. Se actualiza la `PageTable` y `tlb`

1. **NO hay un espacio libre en memoria, y la página NO está en Swap**: Se encuentra página en memoria a sacar, se escribe esa página en `Swap` (sólo si esa página está `dirty`, si se ha modificado). Se lee desde el `Swap` hacia memoria en el espacio ahora libre. Se actualiza la `PageTable` y `tlb`

## Ejecución

Para ejecutar o "correr" el programa se deben seguir los siguientes pasos:

1. Ubicarse en la carpeta de userprog
> `cd VirtualMemory/NachOS/NachOSx64/code/vm` 
2. Realizar el include de todas las dependencias que necesita el código
> `make depend`
3. Compilar el código
> `make`
4. Ejecutar las pruebas que desee
> `./nachos -x ../test/matmult5`

## Creditos

Sebastián Venegas Brenes - C18440