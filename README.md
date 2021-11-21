Game "Akinator"

=================

Game for guessing objects by asking questions (object's characteristics) and adding new objects with its characteristic for making difference between expected and real. 
Database is graph, there is two types of node are characteristic and object on the end of tree

Game has few modes:
------------------

Play mode:
------------------

This mode is main, in this mode you play with akinator, programm is trying guessing envisioned object in cause of mismatch adding new difference characteristics between guessing and expected.
In the end a three file will be created:
1) "save.database" with current tree
2) "graph.dot" for saving database in graphviz format.
3) "graph.png" with "graph.dot" database graph.


Find mode:
------------------

This mode find object in databse, get path of characteristics.
In the end a two file will be created:
1) "graph.dot" for saving database with highlighted object path in graphviz format.
2) "graph.png" with visualisation "graph.dot" with object path.


Compare mode:
------------------

This mode compare two objects by their characteristics after getting their paths of characteristics, mode finds common parts.
In the end a two file will be created:
1) "graph.dot" for saving database with highlighted with two colors objects' paths and  with one color common characteritics of objects' in graphviz format.
2) "graph.png" with visualisation "graph.dot" with object path.
