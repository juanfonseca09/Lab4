Observación sobre la comparación con salida.txt:

Al ejecutar:

./main < entrada.txt > salida_grupo.txt
diff -u salida.txt salida_grupo.txt

la única diferencia obtenida corresponde a la línea de listado de vehículos del conductor.

En salida.txt figura:
Matricula: qtr1515, Modelo: Ninja, Capacidad: 1

Pero según la corrección docente, listarVehiculosConductor debe mostrar matrícula, marca y capacidad. Por eso nuestra salida muestra:
Matricula: qtr1515, Marca: Kawasaki, Capacidad: 1

Se mantiene esta salida porque coincide con la corrección indicada.