# <img src="logo.svg" width="50" height="50"> Heimatforscher
**Heimatforscher** ist eine Datenbank zum zentralen Archivieren von historischen Dokumenten, Personen und Orten.  
Sie wird entwickelt für die _Heimatforscher Bad Bentheim_.

## Build
```
./server/build.sh
./client/build.sh
```
In dem `server`- und `client`-Verzeichnis befindet sich der jeweilige Build-Skript.  
- zum Bauen des Servers wird `g++` verwendet.
- zum Bauen des (Windows-)Clients wird `i686-w64-mingw32-g++` verwendet.

## Test
```
./build_and_run.sh
```
Mit diesem Skript können Server und Client getestet werden.  
Beide Instanzen werden erst gebaut und danach ausgeführt.  
Sollte ein Fehler auftreten, bricht der Skript ab.  
Hinweis: Der Server wird asynchron ausgeführt.

## Abhängigkeiten
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
