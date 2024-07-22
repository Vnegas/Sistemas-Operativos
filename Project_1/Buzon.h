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

#include <sys/msg.h>
#include <sys/stat.h>

#define KEY 0xA12345	// Valor de la llave del recurso

#include <string>
struct message {
  long messageType;
  char data[800];
  char text[800];
};


class Buzon {
   public:
      Buzon();
      ~Buzon();
      int Enviar( const char *mensaje, long = 1 );
      int Enviar( const void *mensaje, int, long = 1 );
      int Recibir( const void *mensaje, int, long = 1 );	// len: space in mensaje

   private:
      int id;		// Identificador del buzon
};
