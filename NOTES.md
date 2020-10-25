# File IO

## open()
open() öffnet das File pathname, ergibt Deskriptor fd:
    fd = open(pathname, flags, mode); // -1: error

Example usages:
    Existierende Datei zum Lesen öffnen:
        int fd = open("a.txt", O_RDONLY);

    Existierende oder neue Datei öffnen, zum Lesen und Schreiben,
    R+W für Owner, sonst keine Permissions:
        fd = open(f, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
        
    Datei öffnen, um etwas am Dateiende anzuhängen:
        fd = open(f, O_WRONLY|O_APPEND);

Open flags:
    O_RDONLY, O_WRONLY, O_RDWR
    O_CREAT, O_EXCL, O_TRUNC, O_APPEND, O_SYNC

Wenn O_EXCL zusammen mit O_CREAT verwendet wird, gibt es einen Fehler, falls das File schon existiert.
Prüfen und Erstellen geschieht dann in einem Schritt; bei Erfolg wurde das File garantiert "von uns" erstellt.
    int fd = open(pathname, O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);

Open modes:
    S_IRUSR, S_IWUSR, ...

    z.B. rw-rw-rw-:
        mode_t mode =   S_IRUSR | S_IWUSR |  S_IRGRP | S_IWGRP |  S_IROTH | S_IWOTH;

Errors:
    retval == -1 indicates error
    
    fd = open(pathname, flags, mode);
    if (fd == -1) { printf("%d\n", errno); }

## read()
read() liest r ≤ n bytes aus File fd in den Buffer buf:
    r = read(fd, buf, n); // r = 0: EOF, -1: error

Example usages:
    Lesen mit read() von stdin, geöffnet von der Shell:
        char buf[32]; r = read(STDIN_FILENO, buf, 32);
        if (r != -1) { printf("read: %s\n", buf); }

Errors:
    retval == -1 indicates error
    
    fd = read(pathname, flags, mode);
    if (fd == -1) { printf("%d\n", errno); }

## write()
write() schreibt w ≤ n bytes aus Buffer buf ins File fd:
    w = write(fd, buf, n); // w = -1: error

"O_APPEND" macht das Anfügen mit write() atomar:
    open(..., ...|O_APPEND); ...; write(...); // atomic

## lseek()

lseek() erlaubt, den offset zu setzen, gezählt ab from:
    off_t lseek(int fd, off_t offset, int from);

From:
    SEEK_SET, SEEK_CUR, SEEK_END

## ftruncate()

ftruncate() kürzt die Länge des Files auf length Bytes:
    int ftruncate(int fd, off_t length); // 0 or -1

## close()
close() schliesst das File fd:
    result = close(fd);

## Files vs. FDs

Der Kernel führt eine Tabelle mit fd pro Prozess (mit close-on-exec flag und File pointer), mit offenen Files im System (mit Status Flags, Access Modes und i-Note Pointers) & mit i-nodes im Filesystem (mit File Type, Permissions und Referenz zu Locks).

## fcntl()

fcntl() liest oder ändert Zugriff, Status offener Files.
    int flags = fcntl(fd, F_GETFL);     // Flags lesen
    if (flags & O_SYNC) { ... }         // Flags prüfen

    flags |= O_APPEND;                  // Flags modifizieren
    fcntl(fd, F_SETFL, flags);          // Flags schreiben

    int mode = flags & O_ACCMODE;       // Zugriff lesen
    if (mode == O_RDONLY) { ... }       // Zugriff prüfen

## dup()

## mkstemp()

## setvbuf() & fflush() & fsync()

### File IO Buffering
Bei regulären Files sind read/write() Calls gebuffert, der Kernel flushed seinen Buffer später auf die Disk.
Wenn nach write(), aber vor dem flushen ein read()kommt, retourniert der Kernel Bytes aus dem Buffer.
Damit sind read() und write() schnell genug, auch wenn der Zugriff auf die Disk relativ langsam ist.

### User-Space stdio Buffering
Die C Library I/O Funktionen fprintf(), fscanf(), ... nutzen Buffering, um System Calls zu reduzieren.
Die Buffergrösse kann im Voraus eingestellt werden:
    FILE *stream = stdout;  // or any other FILE

    *res = setvbuf(stream, buf, _IOFBF, BUF_SIZE);
    if (res != 0) { ... }   // non-zero (!) => error

    fprintf(stream, format, ...); // uses BUF_SIZE
    
Buffer mode kann xxx_IO{Line|Fully|Non}BF sein.

### Flushen von stdio Buffers
Die fflush() Funktion entleert den Buffer mit write():
    int fflush(FILE *stream); // 0 od. EOF, errno
    
Falls stream = NULL ist, werden alle Buffer in stdio "gespült", die zu Output Streams gehören.
Beim Flushen von Input Streams wird der gebufferte Input verworfen; Buffer bleibt leer bis wieder read().
Bei close() auf Streams wird fflush() aufgerufen.

### Flushen von Kernel Buffers
Der fsync() Call schreibt den File Buffer auf die Disk, bzw. erstellt den "file integrity completion" Zustand:
    int fsync(int fd); // 0 oder -1, errno

Denselben Effekt erreicht man mit dem O_SYNC Flag, welches nachfolgende write() Calls "synchron" macht:
    int fd = open(f, O_SYNC|...); // write does fsyncDer Call sync() flushed alle File Buffer im System.

### Buffering

User Buffer
    printf()    # stdio lib calls
stdio Buffer
    fflush()    # i/o system calls
Kernel Buffer
    fsync()     # kernel write
    
## Directories

Wie Files aber mit anderem File Type im inode Eintrag.

### mkdir()

Directory mit Pfad pathname erstellen, mit mkdir():
    int mkdir(const char *pathname, mode_t mode);

### rename()

File von Pfad old zu new umbenennen mit rename():
    int rename(const char *old, const char *new);

### remove()

Die remove() Funktion löscht ein File / Directory:
    int remove(const char *pathname);
    
remove() ruft entweder unlink() oder rmdir() auf:
    int rmdir(const char *pathname); // für Dir's
    int unlink(const char *pathname); // für Files
    
Falls kein anderer Prozess mehr das File offen hat, wird es gelöscht und der Speicherplatz freigegeben.
