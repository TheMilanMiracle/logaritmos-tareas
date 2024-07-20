# TAREA 3 - Filtro de Bloom

## Espacio de trabajo y librerías

El directorio de trabajo con los archivos incluidos para la entrega de esta tarea se debería ver de la siguiente forma:

```
tarea_2
├── bloom
│   ├── bloom-filter.cpp
│   ├── bloom.h.h
│   ├── get_name_list.cpp
│   └── search.cpp
├── lib
│   ├── boost_1_85_0
│   │   ├──...
│   └── csv
│   │   ├── Film-Names.csv
│   │   └── Popular-Baby-Names-Final.csv
├── results
│   ├── n10m10k10.txt
│   ├── n10m11k5.txt
│   ├── n10m11k10.txt
│   ├── ...
├── main.cpp
├── makefile
└── README.md <
```

En la carpeta *results*, se encuentran los resultados con valores particulares de N, M y k que fueron obtenidos durante la experimentación y que se utilizaron para el análisis reportado en el informe entregado para esta tarea.

Dentro de la carpeta *bloom* se encuentran: la definición de la estructura utilizada para el filtro de bloom, junto con las funciones asociadas a su uso; la implementación de la función utilizada para obtener N nombres/películas y la implementación de una búsqueda líneal estilo **grep** de un string. Todos estos archivos serán necesarios (en la misma estructura de directorio descrita más arriba) para la compilación del programa para ejecutar la experimentación. También serán necesarias varias funcionalidades de la librería estándar de C++. Además dentro de la carpeta *lib* se encuentran otros recursos necesarios para el funcionamiento de este experimenta, los archivos en formato CSV para extraer los nombres y la librería Boost (versión 1.85.0 incluida con esta entrega), la cual proveé funcionalidades de hashing.

Dentro del archivo *main.cpp* se encuentra el código necesario para ejecutar el experimento descrito por el enunciado, donde este mide el tiempo que tarda la búsqueda de N elementos sin usar el filtro de Bloom y lo compara a la misma búsqueda ahora con el filtro. Para el caso de una búsqueda con filtro, también se contabilizan la cantidad de casos con falsos negativos, cantidad utilizada para calcular el error práctica del uso del filtro.

**Esta tarea fue desarrollada utilizando la versión 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04) del compilador g++ para C++**.

## Makefile

Entre los archivos entregados para esta tarea se encuentra un archivo *makefile* para simplificar la compilación del archivo *./main.cpp*. Para ejecutar un experimento parametrizado, se debe ejecutar el siguiente comando en la consola:

```
$ make run N="{int}" M="{int}" K="{int}"
```

Donde:
- **"N"** referente a la cantidad total de elementos que se buscarán en la lista de nombres en potencia de 2, es decir, N=10 indica que se utilizarán 2¹⁰ nombres para la búsqueda. El experimento se encarga de probar todos los valores pedidos de p, la proporción de palabras que efectivamente se deberían encontrarn en la búsqueda. 
- **"M"** referente a la cantidad de bits usaron en la tira de bits, también en potencia de 2, con la que funcionará el filtro de Bloom del experimento. 
- **"K"** referente a la cantidad de funciones de hash que serán generadas y usara el filtro de Bloom durante el experimento.

Luego de que el programa termine su ejecución los resultados del experimento se podrán encontrar en el archivo "results.txt".


#### Ejemplo de uso del comando make run:

##### - Experimento con 1024 nombres que usará un filtro de Bloom que con una tira de 2480 bits y 20 funciones de hashing
```
$ make run N="10" M="11" K="20"
```