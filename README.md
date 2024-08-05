# Heimatforscher
**Heimatforscher** (oder `forscher`) ist eine Datenbank zum zentralen Archivieren von historischen Dokumenten und Personen.
Der Zugriff und die Verwaltung der Datenbank ist per Webbrowser möglich.
Sie wird entwickelt für die _Heimatforscher Bad Bentheim_.

## Kompilieren
```
make [all]
```
Dieses Target kompiliert `forscher`. Das Programm wird in einem (neuen) Verzeichnis [build/](build) abgelegt.

## Testen
```
make test
```
Dieses Target kompiliert `forscher` und führt das Programm auf einer (neuen/leeren) Datenbank [build/test/](build/test) aus.

## Ausführen
```
./forscher /pfad/zur/datenbank/
```
Dieser Befehl führt `forscher` auf einer Datenbank aus oder erstellt diese neu.
Dies ist zugleich die einzige Syntax, mit der `forscher` aufgerufen werden kann.

## (externe) Bibliotheken
| Name | Pfad | Link |
| - | - | - |
| cpp-httplib | [lib/httplib/](lib/httplib) | [github.com/yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib)
