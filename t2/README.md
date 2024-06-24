# TAREA 2 - Dijkstra y análisis amortizado

## Espacio de trabajo y librerías

El directorio de trabajo con los archivos incluidos para la entrega de esta tarea se deberían ver de la siguiente forma:

```
tarea_2
├── graph
│   ├── dijsktra.cpp
│   ├── fibonacci_heap.cpp
│   ├── graph.cpp
│   ├── graph.h
│   └── heap.cpp
├── results_fheap
│   ├── v10e16.txt
│   ├── v10e17.txt
│   ├── ...
├── results_heap
│   ├── v10e16.txt
│   ├── v10e17.txt
│   ├── ...
├── main.cpp
├── makefile
└── README.md <
```

En las carpetas *results_fheap* y *results_heap*, se encuentran los resultados con valores particulares obtenidos durante la experimentación y que fueron utilizados para el análisis reportado en el informe entregado para esta tarea.

Dentro de la carpeta *graph* se encuentran las definiciones de las estructuras utilizadas; las implementaciones de Heap y Cola de Fibonnaci, sus respectivas implementaciones de Dijsktra y las funciones necesarias para crear y destruir grafo, deacuerdo con lo descrito en el enunciado. Todos estos archivos serán necesarios (en la misma estructura de directorio descrita más arriba) para la compilación del programa para ejecutar la experimentación. Además serán necesarias varias funcionalidades de la librería estándas de C++.

Dentro del archivo *main.cpp* se encuentra el código necesario para ejecutar el experimento descrito por el enunciado, donde este mide el tiempo que tarda Dijsktra, registrando cada iteración del experimento y el promedio de estos tiempos.

**Esta tarea fue desarrollada utilizando la versión 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04) del compilador g++ para C++**.

## Makefile

Entre los archivos entregados para esta tarea se encuentra un archivo *makefile* para simplificar la compilación del archivo *./main.cpp*. Para ejecutar un experimento con determinados parámetros, se debe ejecutar el siguiente comando en la consola:

```
$ make run structure="{H}" v="{V}" e="{E}" n="{N}"
```

Donde:
- **"structure"** se refiere a cuál estructura se usará como cola de prioridad durante el experimento con Dijsktra, con "{H}" pudiéndose reemplazar por "heap" o "fib", Heap o Cola de Fibonacci respectivamente. 
- **"v"** se refiere a la candidad de vértices con la cual se construirá cada grafo, pudiéndose reemplazar "{V}" por un valor entero que denotará la potencia de 2 que será la mencionada cantidad de vértices (se puede ingresar más de un número para realizar múltiples tests con distintos o iguales potencias de 2). 
- **"e"** se refiere a la cantidad de aristas con la que se contruirá el grafo, pudiéndose reemplazar "{E}" por un entero que denotará la potencia de dos que se utilizará para el dicho valor (tal como para **v**, también se pueden ingresar más de un valor), se probarán todas las *V* \**E* combinaciones.
- Finalmente, **n** se refiere a cuantos experimentos se realizarán por cada par v*e que define un grafo, por ejemplo, el experimento completo descrito por el enunciado se emula con n="50" (se recomienda un número menor para probar correctitud).

Luego de que el programa se termine de ejecutar los resultados del/los experimento(s) se podrán encontrar en el archivo "results.txt".


#### Ejemplos de uso del comando make run:

##### - 1 experimento con Heap usando un grafo de 2¹⁰ vértices y 2¹⁶ aristas. 
```
$ make run structure="heap" v="10" e="16" n="1"
```

##### - 5 experimentos con Colas de fibonacci para cada uno de los grafos descritos por los pares de vértices, aristas: {2¹⁰, 2¹⁶} y {2¹⁰, 2¹⁸}.
```
$ make run structure="fib" v="10" e="16 18" n="5"
```

##### - Recreación del experimento completo descrito en el enunciado.
```
$ make run structure="heap" v="10 14 16" e="16 17 18 19 20 21 22" n="50"
$ make run structure="fib" v="10 14 16" e="16 17 18 19 20 21 22" n="50"
```