// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-17
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
// ----------------------------------------------------
    /**      
     *       alReves() da la vuelta a un array
     *       @p:[T]
     *       
     *       @return p del reves */
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()

// ----------------------------------------------------
// ----------------------------------------------------
    /**      
     *       stringAUint8AlReves() da la vuelta a un array de string y lo convierte a Z
     *       @pString:[char] array al que dar la vuelta
     *       @pUint:[Z] array a devolver
     *       @tamMax:N tamaño maximo del array
     *       
     *       @return pUint del reves*/
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	// copio nombreServicio -> uuidServicio pero al revés
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} // for

	return pUint;
} // ()

// ----------------------------------------------------------
// ----------------------------------------------------------
class ServicioEnEmisora {

public:


  // --------------------------------------------------------
  // --------------------------------------------------------

  // .........................................................
  // .........................................................
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 
  // .........................................................
  // .........................................................
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	  // least signficant byte, el primero
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

	// 
	// 
	// 
	BLECharacteristic laCaracteristica;

  public:

	// .........................................................
	// .........................................................
    /**      
     *       Caracteristica() constructor
     *       @nombreCaracteristica_:[char] array con el nombre
     */
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	} // ()

	// .........................................................
	// .........................................................
    /**      
     *       Caracteristica() constructor con permisos
     *       @nombreCaracteristica_:[char] array con el nombre
     *       @props:N propiedades
     *       @permisoRead:BleSecurityMode
     *       @permisoWrite:BleSecurityMode
     */
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					BleSecurityMode permisoRead,
					BleSecurityMode permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	} // ()

  private:
	// .........................................................
	// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY 
	// .........................................................
    /**      
     *       asignarPropiedades() añade propiedades a la caracteristica
     *       @props:N propiedades
     */
	void asignarPropiedades ( uint8_t props ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");
	  (*this).laCaracteristica.setProperties( props );
	} // ()

	// .........................................................
	// BleSecurityMode::SECMODE_OPEN  , BleSecurityMode::SECMODE_NO_ACCESS
	// .........................................................
	void asignarPermisos( BleSecurityMode permisoRead, BleSecurityMode permisoWrite ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} // ()

	// .........................................................
	// .........................................................
    /**      
     *       asignarTamanyoDatos()
     *       @tam:N tamaño
     */
	void asignarTamanyoDatos( uint8_t tam ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
	  // (*this).laCaracteristica.setFixedLen( tam );
	  (*this).laCaracteristica.setMaxLen( tam );
	} // ()

  public:
	// .........................................................
	// .........................................................
    /**      
     *       asignarTamanyoDatos()
     *       @props:N propiedades
     *       @permisoRead:BleSecurityMode
     *       @permisoWrite:BleSecurityMode
     *       @tam:N tamaño
     */
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 BleSecurityMode permisoRead,
												 BleSecurityMode permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()
												 

	// .........................................................
	// .........................................................
    /**      
     *       escribirDatos() escribe el byte en forma de caracteres en la caracteristica y lo guarda en un array de N
     *       @str:[char]
     *       
     *       @return r:[N] */
	uint16_t escribirDatos( const char * str ) {
	  // Serial.print( " return (*this).laCaracteristica.write( str  = " );
	  // Serial.println( str );

	  uint16_t r = (*this).laCaracteristica.write( str );

	  // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

	  return r;
	} // ()

	// .........................................................
	// .........................................................
    /**      
     *       notificarDatos() apunta a un byte y en caso de que la informacion cambie lo notifica
     *       @str:[char]
     *       
     *       @return r:[N] byte que devuelve si cambia*/
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} //  ()

	// .........................................................
	// .........................................................
    /**      
     *       instalarCallbackCaracteristicaEscrita() comprueba que se escriba la caracteristica
     *       @cb:CallbackCaracteristicaEscrita callback
     */
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} // ()

	// .........................................................
	// .........................................................
    /**      
     *       activar() activa la caracteristica
     */
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} // ()

  }; // class Caracteristica
  
  // --------------------------------------------------------
  // --------------------------------------------------------
private:
  
  uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // .........................................................
  // .........................................................
    /**      
     *       ServicioEnEmisora() constructor
     *       @nombreServicio_:[char]
     */
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } // ()
  
  // .........................................................
  // .........................................................
    /**      
     *       escribeUUID() por pantalla
     */
  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } // ()

  // .........................................................
  // .........................................................
     /**      
     *       anyadirCaracteristica() añade la caracteristica al servicio
     *       @car:Caracteristica
     */
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } // ()

  // .........................................................
  // .........................................................
    /**      
     *       activarServicio()  inicializa el servicio
     */
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio

	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );

	for( auto pCar : (*this).lasCaracteristicas ) {
	  (*pCar).activar();
	} // for

  } // ()

  // .........................................................
  // .........................................................
  operator BLEService&() {
	// "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
	return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
