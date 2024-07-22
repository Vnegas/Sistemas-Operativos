/**
 *   C++ class to encapsulate Unix message passing intrinsic structures and system calls
 *
 *   UCR-ECCI
 *
 *   CI0122 Sistemas Operativos 2023-ii
 *
 *   Class interface
 *
 **/

#include <stdexcept>
#include <stdio.h>

#include <iostream>

#define LABEL_SIZE 64

#include "Buzon.h"


/**
  *  Class constructor
  *
 **/
Buzon::Buzon() {
  int st = -1;

  // Use msgget to create a new mailbox
  st = msgget( KEY, IPC_CREAT | 0600 );

  this->id = st;

  if ( -1 == st ) {
    throw std::runtime_error( "Buzon::Buzon( int )" );
  }

}


/**
  * Class destructor
  *
 **/
Buzon::~Buzon() {
  int st = -1;

  // Use msgctl to destroy mailbox
  msgctl(this->id, IPC_RMID, nullptr);

  if ( -1 == st ) {
    throw std::runtime_error( "Buzon::~Buzon( int )" );
  }

}


/**
  *  Send method
  *
  *  @param     const char * mensaje: arreglo de caracteres a enviar
  *
 **/
int Buzon::Enviar( const char * mensaje, long tipo ) {
  int st = -1;

  // Use msgsnd to send the message
  st = msgsnd(this->id, mensaje, sizeof(mensaje), 0);

  if ( -1 == st ) {
    throw std::runtime_error( "Buzon::Enviar( const char * )" );
  }

  return st;

}


/**
  *  Send method
  *
  *  @param     const void * mensaje: estructura con el mensaje a enviar
  *  @param	int cantidad: cantidad de bytes a enviar
  *
  *
 **/
int Buzon::Enviar( const void * mensaje, int cantidad, long tipo ) {
  int st = -1;

  // Use msgsnd to send the message
  st = msgsnd(this->id, mensaje, cantidad, 0);

  if ( -1 == st ) {
    throw std::runtime_error( "Buzon::Enviar( const void *, int, long )" );
  }

  return st;

}


/**
  *  Receive method
  *
  *  @param     const void * mensaje: estructura con el mensaje a enviar
  *  @param	int cantidad: cantidad de bytes a enviar
  *
  *
 **/
int Buzon::Recibir( void * mensaje, int cantidad, long tipo ) {
  int st = -1;

  // Use msgrcv to send the message
  st = msgrcv(this->id, mensaje, cantidad, tipo,0);
  
  if ( -1 == st ) {
    throw std::runtime_error( "Buzon::Recibir( void *, int, long )" );
  }

  return st;

}
