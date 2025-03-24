# Sistemas Operativos
Repositorio destinado a proyectos alrededor de la creación y entendimiento de un sistema operativo

## NachOS
Se desarrolló/completo el sistema operativo NachOS en dos diferentes avances.
1. Se realizó el desarrolló de las syscalls o llamados a sistema por medio de uso de registros y manejo de memoria, más información en [NachOS Syscalls](NachOS/Syscalls/readme.md).
2. Se creó la posibilidad de ejecutar los programas con memoria virtual, por medio de memoria swap y una tlb, más información en [NachOS VM](NachOS/VirtualMemory/readme.md).

## Rotonda de circunvalación
Simulación de una rotonda. Se resuelve mediante hilos y buzones, , más información en [Rotonda](Project_1/readme.md)

## Filósofos comiendo
Solución del problema de los filósofos presente como ejercicio en NachOS. 
#### Problema de los filósofos:
> Cada filósofo tiene su propio plato en la mesa. Hay un tenedor entre cada plato. El plato servido se debe comerse con dos tenedores. Cada filósofo solo puede pensar y comer alternativamente. Además, un filósofo solo puede comer su espagueti cuando tiene un tenedor izquierdo y uno derecho. Por lo tanto, dos tenedores solo estarán disponibles cuando sus dos vecinos más cercanos estén pensando, no comiendo. Después de que un filósofo termine de comer, dejará ambos tenedores.

## Creditos
Sebastián Venegas Brenes

---

# Operating Systems
Repository for projects related to the creation and understanding of an operating system

## NachOS
The NachOS operating system was developed/completed in two different stages.
1. Syscalls were developed through the use of registers and memory management. More information is available in [NachOS Syscalls](NachOS/Syscalls/readme.md).
2. The ability to run programs in virtual memory was created, using swap memory and a tlb. More information is available in [NachOS VM](NachOS/VirtualMemory/readme.md).

## Roundabout
Simulation of a roundabout. It is solved through threads and mailboxes. More information can be found at [Rotonda](Project_1/readme.md)

## Philosophers Eating
Solution to the Philosophers Problem, presented as an exercise in NachOS.
#### Philosophers' Problem:
> Each philosopher has his own plate on the table. There is a fork between each plate. The served plate must be eaten with two forks. Each philosopher can only think and eat alternately. Furthermore, a philosopher can only eat his or her spaghetti when he has a left and a right fork. Therefore, two forks will only be available when his two nearest neighbors are thinking, not eating. After a philosopher finishes eating, he will put down both forks.

## Credits
Sebastián Venegas Brenes
