# Sistemas Operativos y Redes

## Trabajo Práctico de hilos y semáforos

En la cocina de Hell’s Burgers compiten tres equipos de 
cocineros. 
La dificultad de la competencia es que la cocina no cuenta
con el equipamiento individual para cada equipo, sino que
algunos de ellos son compartidos. Por lo tanto es necesario una organizacion para
cumplir con el objetivo.

## Implementación:
La simulación se programo en lenguaje C con la utilización de hilos y semáforos. el objetivo, sumiluar un paralelismo y
una correcta organizacioón de los 3 equipos. 
<br>Se crearon 3 hilos, es decir uno por equipo, y cada hilo a su vez crea otro por cada acción. Estos mismos serán organizados por semáforos.
habra semáforos mutex que organicen la utilización de los recursos compartidos y semáforos particulares que organicen el paso a paso de cada
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
<br> 
<br> 
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
<br>
**HORNEAR()**{
<br>
&nbsp;&nbsp; *P(SEMAFOROCOMPARTIDO_HORNO)* //CHEQUEA QUE OTRO EQUIPO NO LO ESTE USANDO, EN ESE CASO LO DESCUENTA EN UNO PARA QUE OTRO EQUIPO NO ENTRE
  <br>
&nbsp;&nbsp; *V(SEMAFORO_PAN HORNEADO)*  //NECESARIO SABER ANTES DE ARMAR LA HAMBURGUESA //COMO NO DEPENDE OTRA ACCION SOLO SE EJECUTA Y HABILITA EL PASO QUE SIGUE
  <br>
&nbsp;&nbsp; *V(SEMAFOROCOMPARTIDO_HORNO*//SUMA UNO AL SEMAFORO, ES DECIR, LO HABILITA PARA QUE OTRO EQUIPO LO USE.
<br>
}
<br>
<br>
**CORTAR CEBOLLA AJO PEREJIL()**{
<br>
&nbsp;&nbsp; *V(SEMAFORO_MEZCLAR)*    //COMO NO DEPENDE OTRA ACCION SOLO SE EJECUTA Y HABILITA EL PASO QUE SIGUE
<br>
}
<br>
<br>
**CORTAR EXTRAS()**{
<br>
&nbsp;&nbsp; *V(SEMAFORO_EXTRAS CORTADOS)* //NECESARIO SABER ANTES DE ARMAR LA HAMBURGUESA //COMO NO DEPENDE OTRA ACCION SOLO SE EJECUTA Y HABILITA EL PASO QUE SIGUE
<br>
}
<br>
<br>
**MEZLCAR()**{
<br>
&nbsp; &nbsp;*P(SEMAFORO_MEZCLAR)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA HECHO
<br>
&nbsp; &nbsp;*V(SEMAFORO_SALAR)* // HABILITA LA ACCIÓN QUE SIGUE
<br>
}
<br>
<br>
**SALAR()**{
<br>
&nbsp;&nbsp; *P(SEMAFOROCOMPARTIDO_SAL)* //PREGUNTA QUE OTRO EQUIPO NO LO ESTE USANDO, EN ESE CASO LO DESCUENTA EN UNO PARA QUE OTRO EQUIPO NO ENTRE
<br>
&nbsp;&nbsp; *P(SEMAFORO_SALAR)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA HECHO
<br>
&nbsp;&nbsp; *V(SEMAFORO_ARMAR MEDALLON)* // HABILITA LA ACCIÓN QUE SIGUE
<br>
&nbsp;&nbsp; *V(SEMAFOROCOMPARTIDO_SAL)* //SUMA UNO AL SEMÁFORO, ES DECIR, LO HABILITA PARA QUE OTRO EQUIPO LO USE.
<br>
}
<br>
<br>
**ARMAR MEDALLON()**{
<br>
&nbsp;&nbsp;*P(SEMAFORO_ARMAR MEDALLON)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA ACTIVADO ESTE SEMÁFORO
<br>
&nbsp;&nbsp;*V(SEMAFORO_COCINAR)* // HABILITA LA ACCIÓN QUE SIGUE
<br>
}
<br>
<br>
**COCINAR()**{
<br>
&nbsp;&nbsp; *P(SEMAFOROCOMPARTIDO_PLANCHA)* //PREGUNTA QUE OTRO EQUIPO NO LO ESTE USANDO, EN ESE CASO LO DESCUENTA EN UNO PARA QUE OTRO EQUIPO NO ENTRE
<br>
&nbsp;&nbsp; *P(SEMAFORO_COCINAR)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA ACTIVADO ESTE SEMÁFORO
<br>
&nbsp;&nbsp;*V(SEMAFORO_ARMAR HAMBURGUESA)* // HABILITA LA ACCIÓN QUE SIGUE
<br>
&nbsp;&nbsp; *V(SEMAFOROCOMPARTIDO_PLANCHA)* //SUMA UNO AL SEMÁFORO, ES DECIR, LO HABILITA PARA QUE OTRO EQUIPO LO USE.
<br>
}
<br>
<br>
**ARMAR HAMBURGUESA()**{
<br>
&nbsp;&nbsp; *P(SEMAFORO_ARMAR HAMBURGUESA)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA ACTIVADO ESTE SEMÁFORO
<br>
&nbsp;&nbsp; *P(PAN HORNEADO)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA ACTIVADO ESTE SEMÁFORO
<br>
&nbsp;&nbsp; *P(EXTRAS CORTADOS)* // PREGUNTA QUE EL PASO ANTERIOR SE HAYA ACTIVADO ESTE SEMAFORO
<br>
}
<br>
### En la siguiente imágen se indican con flechas la secuencia que se lleva a cabo en el pseudocódigo
<br>
<img src = "SECUENCIA.png">
<br>

### Prueba de escritorio
<br>
<img src = "prueba de escritorio.png">

### Conclusión:
En sintesis la utilización de semaforos en conjunto de hilos se presta como una gran herramienta para el desarrollo de software. Si bien a primera vista no es una herramienta 
sencilla de utilizar pues, diversos inconvenientos se presentaron durante la relalización del trabajo. la realidad es que con una correcta busqueda de informacion las posibilidades de su aprendizaje y aprovechamiento son enormes. 


