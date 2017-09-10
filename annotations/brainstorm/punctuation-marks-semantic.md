# The Semantic of punctuation marks

Utilizamos la idea de semantica en relacion a los signos de puntuacion con la
intencion de crear patrones ideograficos facilmente recordables.

- La identacion, da a entender una idea de bloque

- *`a: b`* el _colon_ (:) como signo de vinculacion constante, lo que está
  a la izquierda de la marca de puntuacion tiene un fuerte enlace con lo que
  se encuentra a la derecha.

- *` => `* Fat arrow, promocion de un dato a otro, una transformacion.


  b = a => Natural

# declaracion de bloque
```

symbol: statement
  code

\ Sustituyendo statement por una sentencia de creacion de prototipos:

suma: (a: Natural, b: Natural) => Natural
  <- a + b


\ el tipo de valor de retorno puede ser omitido
suma: (a: Natural, b: Natural) =>
  <- a + b

\ el bloque puede ser omitido

suma: (a: Natural, b: Natural) => a + b

\ el tipado puede ser omitido

suma: (a, b) => a + b


ref: (rank:Natural) =>
  <=

funcionQueRetornaUnObjeto: =>
    Esta funcion tiene una documentacion miu interesante con la idea de
    cotejarla junto con los

  > input: Natural
      Un parametro de esta funcion

  < alpha: Natural = 7
      un valor de retorno como objeto

  < beta: Natural = undefined
      un segundo valor de retorno

  v = 7

...
    Este es el finalizador de la funcion, es opcional, queda asegurada la
    ejecucion del finalizador justo al final del ciclo de vida del valor
    retornado.

  out < 'finalizador'




  alpha = beta = 9
