class Temperatura{
  private:
    int valorTemperatura;
    int contador;
    long tiempoEspera;
  public:
    Temperatura( int valorTemperatura, int contador, long tiempoEspera){
      (*this).valorTemperatura=valorTemperatura;
      (*this).contador=contador;
      (*this).tiempoEspera=tiempoEspera;
    }
}
