// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------

// ----------------------------------------------------------
// ----------------------------------------------------------
    /**      
     *       esperar() pausa el procesamiento
     *       @tiempo:N cuanto espera
     */
void esperar (long tiempo) {
  delay (tiempo);
}

// ----------------------------------------------------------
// ----------------------------------------------------------
class LED {
private:
  int numeroLED;
  bool encendido;
public:
  // .........................................................
  // .........................................................
    /**      
     *       LED() constructor
     *       @numero:N pin conectado al LED
     */
  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }
  

  // .........................................................
  // .........................................................
   /**      
    *       encender() enciende el LED
    */
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }

  // .........................................................
  // .........................................................
   /**      
    *       apagar() apaga el LED
    */
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  // .........................................................
  // .........................................................
   /**      
    *       alternar() si esta encendido apaga o viceversa
    */
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } // ()
  // .........................................................
  // .........................................................
   /**      
    *       brillar() el LED se enciende durante un periodo de tiempo
    *       @tiempo:N cuanto dura
    */
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
