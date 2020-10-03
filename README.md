# System-Programmierung
## Hands-on zu Lektion 3
Für Slides und Code Beispiele, siehe [Lektion 3](../../../fhnw-syspr/blob/master/03/README.md)

> *Achtung: Arbeiten Sie nicht direkt auf diesem Repository.*<br/>
> *[Erstellen Sie eine persönliche Kopie, mit diesem GitHub Classroom Link](https://classroom.github.com/a/NP9Z70Ye).*

### a) TLPI Beispiele builden, 15'
* [TLPI](http://www.man7.org/tlpi/) Beispielcode Setup auf dem Raspberry Pi:<pre>
    $ cd ~
    $ wget http://man7.org/tlpi/code/download/tlpi-180725-book.tar.gz
    $ tar xfzmv tlpi-180725-book.tar.gz
    $ cd tlpi-book
    $ sudo apt-get install libcap-dev
    $ sudo apt-get install libacl1-dev
    $ make</pre>

### b) File I/O, 15'
* Schreiben Sie ein Programm *my_copy.c*, das eine beliebig grosse, existierende Datei source liest und in eine neue Datei dest kopiert, wie das *cp* Kommando:<pre>
    $ ./my_copy source dest</pre>
* Verwenden Sie bekannte File I/O System Calls. 

### c) File Append, 15'
* Schreiben Sie ein Programm *my_logger.c*, welches */proc/uptime* liest und den aktuellen Wert hinten an eine neue bzw. existierende Datei *my.log* anhängt.
* Nutzen Sie [lseek()](http://man7.org/linux/man-pages/man2/lseek.2.html) um das Ende der Datei zu finden.
* Nutzen Sie [sleep()](http://man7.org/linux/man-pages/man3/sleep.3.html) um in einer Schleife jede Sekunde einen neuen Wert an den Log anzuhängen.

### d) Dup (auf Papier), 10'
* Was steht im File *f*, nach jedem Aufruf von *write()*?<pre>
    int fd1 = open(f, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int fd2 = dup(fd1), fd3 = open(f, O_RDWR);
    write(fd1, "Ente,", 5);
    write(fd2, "Hund,", 5);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "Haus,", 5);
    write(fd3, "Pferd", 5);</pre>

### e) Buffering, 5'
* Kompilieren Sie das Programm [write_bytes](http://man7.org/tlpi/code/online/dist/filebuff/write_bytes.c.html) zuerst mit und dann ohne die Compiler Option *-DUSE_O_SYNC*.
* Messen Sie die Laufzeit (real, sys) der Binaries, je mit *num-bytes* = 100000 und *buf-size* = 1, 16, 256, 4096:<pre>
    $ time write_bytes my_file num-bytes buf-size</pre>
* Welchen Einfluss hat die Buffergrösse? Und *O_SYNC*?
* Wann/wozu ist Synchronisieren überhaupt nötig?
