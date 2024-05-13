# TAREA 1 - M Tree

## Espacio de trabajo y librerías

El directorio de trabajo con los archivos incluidos para la entrega de esta tarea se deberían ver de la siguiente forma:

```
tarea_1
├── mtree
│   ├── ciaccia_patella.cpp
│   ├── generate_points.cpp
│   ├── mtree.cpp
│   ├── mtree.h
│   ├── search.cpp
│   └── sexton_swinbank.cpp
├── results_cp
│   ├── 10.txt
│   ├── 11.txt
│   ├── ...
├── results_ss
│   ├── 10.txt
│   ├── 11.txt
│   ├── ...
├── main.cpp
├── makefile
├── README.md <
└── results.txt
```

En las carpetas *results_cp* y *results_ss*, se encuentran algunos resultados de la experimentación obtenidos con anterioridad para el análisis reportado en el informe entregado para la tarea.

Dentro de la carpeta *mtree* se encuentran las definiciones de las estructuras utilizadas; las implementaciones de la búsqueda para M-Trees, los métodos de construcción descritos en el enunciado de la tarea y funciones que entregan distintas utilizades para la experimentación, como por ejemplo, la generación de *n* puntos random con posiciones entre 0 y 1 en el plano XY. Todos estos archivos serán necesarios (en la misma estructura de directorio descrita más arriba) para la compilación del programa para ejecutar la experimentación. Además serán necesarias varias funcionalidades de la librería estándas de C++.

Dentro del archivo *main.cpp* se encuentra el código necesario para ejecutar el experimento descrito por el enunciado, donde este mide aspectos como: tiempo de construcción de un árbol, tiempos de búsqueda, promedio de accesos a memoria simulados, entre otros.

## Makefile

Entre los archivos entregados para esta tarea se encuentra un archivo *makefile* para simplificar la compilación del archivo *./main.cpp*. Para ejecutar un experimento con determinados parámetros, basta con ejecutar el siguiente comando en la consola:

```
> make run method="{M}" test="{T}"
```

Donde *method* se refiere al método de construcción con el cual se realizará el experimento, con "{M}" pudiéndose reemplazar por "cp" o "ss", Ciaccia-Patella o Sexton-Swinbank respectivamente, y *test* refiriéndose a la candidad de puntos con la cual se construirá el M-Tree, pudiéndose reemplazar "{T}" por un valor entero que denotará la potencia de 2 que será la mencionada cantidad de puntos (se puede ingresar más de un número para realizar múltiples tests con distintos o iguales potencias de 2).

Luego de que el programa se termine de ejecutar los resultados del/los experimento(s) se podrán encontrar en el archivo "results.txt".


#### Ejemplos de uso del comando make run:

##### - Experimento con el método de construcción ciaccia-patella con 2¹⁰ puntos.
```
> make run method="cp" test="10"
```

##### - Experimento con el método de construcción sexton-swinbank con 2¹² puntos.
```
> make run method="ss" test="12"
```

##### - Experimento con el método de construcción ciaccia-patella con 2¹⁵, 2¹⁶ y 2¹⁷ puntos.
```
> make run method="cp" test="15 16 17"
```