# Process Planner

Proyecto C++ en el que se implementa una simulación de un planificador de procesos CPU. Se implementan 4 algoritmos de planificación:
- First-Come, First Served (FCFS)
- Shortest Job First (SJF)
	- Cooperativo
	- Apropiativo
- Round Robin

## Entrada

El programa usará un archivo de texto de entrada (ubicado en /resources/processes_input.txt o pasado como parámetro) con los procesos que ejecutara la CPU, sus duraciones y momento en el que se creara cada proceso. También se indicará el algoritmo a usar.

### FCFS
```
fcfs
P1 3 0
P2 24 1
P3 4 2
```
### SJF 
(sjf_coop o sjf_apr)
```
sjf_coop
P1 7 0
P2 4 2
P3 1 4
P4 4 5
```
### Round Robin
```
rr 3
P1 7 0
P2 4 0
P3 1 0
P4 4 0
```

## Salida
La salida sera por terminal monstrando una linea por cada vez que se se empiece a ejecutar un proceso indicando cual y el segundo en el que empieza la ejecución. Ejemplo con Round Robin:
```
0 s  - P1
3 s  - P2
6 s  - P3
7 s  - P4
10 s  - P1
13 s  - P2
14 s  - P4
15 s  - P1
16 s  - END
```
