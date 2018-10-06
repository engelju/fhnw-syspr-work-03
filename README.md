# System-Programmierung
## Hands-on zu Lektion 3
Für Slides und Code Beispiele, siehe [Lektion 3](../../../fhnw-syspr/blob/master/03/README.md)

> *Achtung: Arbeiten Sie nicht direkt auf diesem Repository.*<br/>
> *[Erstellen Sie eine persönliche Kopie, mit diesem GitHub Classroom Link](https://classroom.github.com/a/TODO).*

### a) TLPI Beispiele builden, 10'
* [TLPI](http://www.man7.org/tlpi/) Beispielcode Setup auf dem Raspberry Pi:<pre>
    $ cd ~
    $ wget http://man7.org/tlpi/code/download/tlpi-180725-book.tar.gz
    $ tar xfzmv tlpi-180725-book.tar.gz
    $ cd tlpi-book
    $ sudo apt-get install libcap-dev
    $ sudo apt-get install libacl1-dev
    $ make</pre>

### b) File I/O, 20'
* Schreiben Sie ein Programm *my_clone.c*, dass seinen eigenen Programmtext auf *stdout* ausgibt.
* Tipp: Verwenden Sie bekannte File I/O System Calls.
* _v2: Erweitern Sie das Programm, dass es auch nach dem Umbenennen des Binaries noch funktioniert, bzw. den ebenfalls umbenannten Code findet.

### c) File Append, 30'
* Schreiben Sie ein Programm *my_cpu_temp.c*, dass die CPU Temperatur in ein File *./temp.txt* schreibt.
* Hinweis für Raspberry Pi, Wert durch 1000 teilen:<pre>
    $ cat -v /sys/class/thermal/thermal_zone0/temp</pre>
* Erweitern Sie das Programm, dass es alle 3 Sekunden einen neuen Messwert anhängt, im [CSV](https://tools.ietf.org/html/rfc4180) Format.
* Hinweis: Die [sleep](http://man7.org/linux/man-pages/man3/sleep.3.html) Funktion ermöglicht Pausen.

### d) Atomic Append, 15'
* Führen Sie das Programm [atomic_append](http://man7.org/tlpi/code/online/dist/fileio/atomic_append.c.html) aus und vergleichen Sie die Grösse der erzeugten Dateien *f1*, *f2*:<pre>
$ ./atomic_append f1 1000000 & ./atomic_append f1 1000000
$ ./atomic_append f2 1000000 x & ./atomic_append f2 1000000 x</pre>
* Teilen Sie *atomic_append.c* in zwei Programme auf, *my_lseek.c* und *my_append.c*, ohne die Option 'x'.
* Wiederholen Sie den obigen Test mit ihrem Code.

### e) Dup (auf Papier), 15'
* Was steht im File *f*, nach jedem Aufruf von *write()*?<pre>
    int fd1 = open(f, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int fd2 = dup(fd1), fd3 = open(f, O_RDWR);
    write(fd1, "Ente,", 5);
    write(fd2, "Hund,", 5);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "Haus,", 5);
    write(fd3, "Pferd", 5);</pre>

### f) Buffering, 15'
* Kompilieren Sie das Programm [write_bytes](http://man7.org/tlpi/code/online/dist/filebuff/write_bytes.c.html) zuerst mit und dann ohne die Compiler Option *-DUSE_O_SYNC*.
* Messen Sie die Laufzeit (real, sys) der Binaries, je mit *num-bytes* = 100000 und *buf-size* = 1, 16, 256, 4096:<pre>
    $ time write_bytes my_file num-bytes buf-size</pre>
* Welchen Einfluss hat die Buffergrösse? Und *O_SYNC*?
* Wann/wozu ist Synchronisieren überhaupt nötig?

### Abgabe (optional)
* Lokale Änderungen [committen und pushen](#git).
* GitHub [Issue erstellen](../../issues/new) mit "Bitte um Review, @tamberg".
* Offene Fragen ausformulieren, was geht nicht, was haben Sie versucht.
* GitHub mailt mir (@tamberg) automatisch, ich versuche in weniger als 24h zu antworten :)

## Tools
### Git
Auf Ihrem Computer
* Zu Beginn jeder Lektion wird ein Hands-on Repository Link freigeschaltet
* Nachdem Sie das "Assessment" annehmen, bekommen Sie per Email ein Repository
* Die REPO_URL enthält Ihren GitHub Account USER_NAME und Ihre Klasse 3ia oder 3ib, z.B.<br/>
            https://github.com/fhnw-syspr-3ia/fhnw-syspr-work-03-tamberg

Auf dem Raspberry Pi
* Repository klonen<pre>
    $ cd ~
    $ git clone REPO_URL</pre>
* Neue Datei kreieren<pre>
    $ git add FILE</pre>
* Änderungen committen<pre>
    $ git commit FILE -m "Fixed all bugs"</pre>
* Änderungen hochladen<pre>
    $ git push</pre>

### Nano
Auf dem Raspberry Pi
* Neue oder bestehende Datei öffnen mit $ nano FILE
* Editieren (Achtung, nano hat kein Undo)
* Speichern mit `CRTL-X` `Y` `RETURN`

### SSH
Auf Ihrem Computer
* Terminal öffnen (Mac) oder `WINDOWS` `R` cmd `RETURN` (Windows)
* SSH Session starten mit<pre>
    $ ssh pi@raspberrypi.local</pre>

## Support
- [FHNW Syspr Slack](https://fhnw-syspr.slack.com/)
