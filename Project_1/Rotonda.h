#ifndef ROTONDA_H
#define ROTONDA_H

#include <mutex>
#include <vector>
#include "Buzon.h"

/**
 * @brief Clase que simula la rotonda
 * 
 */
class Rotonda {
  public:
    Rotonda(int calles, int lim, int carr);
    ~Rotonda();
    void iniciar();
    void crear_carro();
    void liberar_calle(int calle, int cant);
    double random_num(int tope);
    int calle_concurrida();

  private:
    bool ultimo;
    int cant_calles;
    int limite;
    int cant_act;
    int carros;
    std::vector<int> cant_carros;
    Buzon* buzon;
    std::mutex lock;
};

#endif  // ROTONDA_H
