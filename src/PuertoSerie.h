
// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // .........................................................
    /**      
     *       PuertoSerie() constructor
     *       @baudios:N frecuencia del puerto
     */
  PuertoSerie (long baudios) {
	Serial.begin( baudios );
	// mejor no poner esto aquí: while ( !Serial ) delay(10);   
  } // ()
  // .........................................................
  // .........................................................
    /**      
     *       esperarDisponible() comprueba si el puerto puede enviar
     */
  void esperarDisponible() {

	while ( !Serial ) {
	  delay(10);   
	}

  } // ()
  // .........................................................
  // .........................................................
    /**      
     *       escribir() muestra por pantalla
     *       @mensaje:T mensaje a escribir
     */
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
