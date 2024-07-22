# Tarea Programada 1

## Rotonda de circunvalación

A una rotonda de la carretera de circunvalación van a desembocar N calles de doble sentido. Cada carro que llega a la rotonda está representado por un proceso. Cada Carro (C) tiene el siguiente comportamiento cuando llega al final de la cola en la calle C :

1. Registra su llegada al final de la cola de la calle C, lo que indica que hay un carro más en la cola; además incrementa la cantidad de carros totales que esperan pasar

2. Determina si la cantidad de carros que hay en todas las colas (ntotal) sobrepasa K carros, donde K representa una constante

3. Si hay menos de K carros, espera a que se le de paso colocándose al final de la cola (C) de la calle correspondiente; sino determina cuál es la calle con mayor número de carros en espera (nmax carros en la cola qmax) y los deja pasar, las demás colas siguen en espera, en caso de que dos o más calles cumplan la condición de tener el máximo, escogerá la primera que encuentró

4. Si mientras están pasando los nmax carros de la cola elegida, llegan nuevos carros a esa cola, éstos deberán esperar hasta la siguiente vez que se permita el tránsito por esa calle

5. Cuando el carro ha ingresado a la rotonda, podremos considerar que finaliza

6. No existe un proceso controlador que administra la rotonda, solo existen los procesos representativos para cada carro que quiere circular por la rotonda.

Se resolvió el problema utlizando hilos y paso de mensajes por medio de buzones.

# Creditos

Sebastián Venegas Brenes - C18440