#include <thread>
#include <iostream>
#include <string>
#include <sys/msg.h>
#include <sys/stat.h>

#include "Rotonda.h"

int main(int argc, char* argv[]) {
  if (argc == 4) {
    int cant_calles = atoi(argv[2]); int limite = atoi(argv[3]);
    int carros = atoi(argv[4]);
    Rotonda rotonda = new Rotonda(cant_calles, limite, carros);
    rotonda.iniciar();
  } else {
    std::cerr << "Not enough arguments"
  }
}
