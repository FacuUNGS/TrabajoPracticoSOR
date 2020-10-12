# Sistemas Operativos y Redes

## Trabajo Práctico de hilos y semáforos

En la cocina de Hell’s Burgers compiten tres equipos de 
cocineros. 
La dificultad de la competencia es que la cocina no cuenta
con el equipamiento individual para cada equipo, sino que
algunos de ellos son compartidos. Por lo tanto es necesario una organizacion para
cumplir con el objetivo.

## Implementacion:
La simulación se programo en lenguaje C con la utilizacion de hilos y semaforos. el objetivo, sumiluar un paralelismo y
una correcta organizacion de los 3 equipos. 
<br>Se crearon 3 hilos, es decir uno por equipo, y cada hilo a su vez crea otro por cada accion. Estos mismos seran organizados por semaforos.
habra semaforos mutex que organicen la utilizacion de los recursos compartidos y semaforos particulares que organicen el paso a paso de cada
equipo en particular.

## Explicación en pseudocódigo:



main{
  <br>
  &nbsp; HILO EQUIPO 1(EJECUTAR RECETA);
  <br>
  &nbsp; HILO EQUIPO 2(EJECUTAR RECETA);     &nbsp; &nbsp;  //TODO LOS HILOS EJECUTAN LA MISMA FUNCION.
  <br>
  &nbsp; HILO EQUIPO 2(EJECUTAR RECETA);
  <br>
  <br>
  //SEMAFOROS COMPARTIDOS:
  <br>
 &nbsp;   SEMAFOROCOMPARTIDO_SAL 1
  <br>
 &nbsp;   SEMAFOROCOMPARTIDO_PLANCHA 1
  <br>
 &nbsp;  SEMAFOROCOMPARTIDO_HORNO 1
  <br>
  
  
  
}

*EJECUTAR RECETA*{
    <br>
    &nbsp; HILO (HORNEAR);
    <br>
    &nbsp; HILO (CORTAR CEBOLLA AJO PEREJIL);
    <br>
    &nbsp; HILO (CORTAR EXTRAS);
    <br>
    &nbsp; HILO (MEZCLAR)
    <br>
    &nbsp; HILO (SALAR)
    <br>
    &nbsp; HILO(ARMAR MEDALLON);
    <br>
    &nbsp;  HILO (COCINAR);
    <br>
    &nbsp; HILO (ARMAR HAMBURGUESA);
    <br>
    <br>
    //SEMAFOROS PARTICULARES POR EQUIPO COMIENZAN TODOS APAGADOS
    <br>
   &nbsp; SEMAFORO_MEZCLAR 0
    <br>
   &nbsp; SEMAFORO_SALAR 0
    <br>
   &nbsp; SEMAFORO_ARMAR MEDALLON 0
    <br>
   &nbsp; SEMAFORO_COCINAR 0
    <br>
   &nbsp; SEMAFORO_ARMAR HAMBURGUESA 0
    <br>
   &nbsp; SEMAFORO_EXTRAS CORTADOS 0
    <br>
  &nbsp;  SEMAFORO_PAN HORNEADO 0
    <br>
}
<br>

HORNEAR(){
<br>
  P(SEMAFOROCOMPARTIDO_HORNO)
  <br>
  V(SEMAFORO_PAN HORNEADO)  //NECESARIO SABER ANTES DE ARMAR LA HAMBURGUESA
  <br>
  V(SEMAFOROCOMPARTIDO_HORNO
<br>
}
<br>
CORTAR CEBOLLA AJO PEREJIL(){
<br>
  V(SEMAFORO_MEZCLAR)
<br>
}
<br>
CORTAR EXTRAS(){
<br>
  V(SEMAFORO_EXTRAS CORTADOS) //NECESARIO SABER ANTES DE ARMAR LA HAMBURGUESA
<br>
}
<br>
MEZLCAR(){
<br>
  V(SEMAFORO_SALAR)
<br>
}
<br>
SALAR(){
<br>
  P(SEMAFOROCOMPARTIDO_SAL)
<br>
  V(SEMAFORO_ARMAR MEDALLON)
<br>
  V(SEMAFOROCOMPARTIDO_SAL)
}
<br>
ARMAR MEDALLON(){
  V(SEMAFORO_COCINAR)
<br>
}
<br>
COCINAR(){
<br>
  P(SEMAFOROCOMPARTIDO_PLANCHA)
  <br>
  V(SEMAFORO_ARMAR HAMBURGUESA)
  <br>
  V(SEMAFOROCOMPARTIDO_PLANCHA)
<br>
}
<br>
ARMAR HAMBURGUESA(){
<br>
  P(SEMAFORO_ARMAR HAMBURGUESA)
<br>
  P(PAN HORNEADO)
<br>
  P(EXTRAS CORTADOS)
<br>
}
<br>
