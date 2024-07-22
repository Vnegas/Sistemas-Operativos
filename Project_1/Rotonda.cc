#include <thread>
#include <iostream>
#include <random>
#include <string>
#include <sys/msg.h>
#include <sys/stat.h>

#include "Rotonda.h"

Rotonda::Rotonda(int calles, int lim, int carr) {
  this->cant_calles = calles;
  this->limite = lim; this->carros = carr;
  this->buzon = new Buzon();
  this->ultimo = false;
}

Rotonda::~Rotonda() {

}

void Rotonda::iniciar() {
  std::vector<std::thread> threads;
  for (int i = 0; i < carros; ++i) {
    if (i == carros) {
      this->ultimo = true;
    }
    std::thread th(&Rotonda::iniciar);
    threads.push_back(std::move(th));
  }

  for (std::thread & th : threads) {
    if (th.joinable())
      th.join();
  }
}

void Rotonda::crear_carro() {
  this->lock.lock();
    int calles = this->cant_calles;
    int actual = this->cant_act;
    int lim = this->limite;
    bool ult = this->ultimo;
  this->lock.unlock();

  int calle = (int) this->random_num(calles);
  this->buzon->Recibir("carro", 10, calle);
  printf("Llego un nuevo carro a la calle %d", calle + 1);
  ++actual;

  this->lock.lock();
    int cc = this->cant_carros[calle]; ++this->cant_carros[calle];
    ++this->cant_act;
  this->lock.unlock();

  if (ult) {
    for (int i = 0; i < calles; ++i) {
      this->lock.lock();
        int j = this->cant_carros[i];
      this->lock.unlock();
      this->liberar_calle(i, j);
    }
  } else {
    if (actual == lim) {
      int cual_calle = this->calle_concurrida();
      this->lock.lock();
        int j = this->cant_carros[cual_calle];
      this->lock.unlock();
      this->liberar_calle(cual_calle, j);
    }
  }
}

int Rotonda::calle_concurrida() {
  this->lock.lock();
    int x = this->cant_carros[0];
    for (int i = 1; i < this->cant_calles; ++i) {
      if (x < this->cant_carros[i]) {
        x = this->cant_carros[i];
      }
    }
  this->lock.unlock();
  return x;
}

void Rotonda::liberar_calle(int calle, int cant) {
  for (int i = 0; i < cant; ++i) {
    this->buzon->Enviar("1", 10, calle);
  }
  printf("Pasaron %d carros de la calle %d\n", cant, calle + 1);
}

double Rotonda::random_num(int tope) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, tope - 1);
  return dist(rng);
}
