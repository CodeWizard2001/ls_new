#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stddef.h>

// Struktur für einen einzelnen Datei-Knoten
typedef struct FileNode {
    char name[256];            // Name der Datei
    struct stat file_stat;     // Metadaten der Datei
    struct FileNode *next;     // Zeiger auf den nächsten Knoten
} FileNode;

// Struktur für die dynamische Datei-Liste
typedef struct FileList {
    FileNode *head;            // Kopf der Liste
    FileNode *tail;            // Ende der Liste
    size_t count;              // Anzahl der Dateien in der Liste
} FileList;

// Funktion, um eine neue Datei-Liste zu erstellen
FileList *create_file_list(void);

// Funktion, um eine Datei zur Liste hinzuzufügen
void add_file_to_list(FileList *list, const char *name, const struct stat *file_stat);

// Funktion, um die Datei-Liste und ihre Knoten freizugeben
void destroy_file_list(FileList *list);

// Funktion, um ein Verzeichnis nach Dateitypen zu filtern
int wildcard_match(const char *str, const char *pattern);

// Funktion, um ein Verzeichnis zu traversieren und Dateien in die Liste einzutragen
int traverse_directory(const char *path, int show_hidden, FileList *list);
// Funktion, um ein Verzeichnis rekursiv zu traversieren (inkl. Unterverzeichnisse)
int traverse_directory_recursive(const char *path, int show_hidden, FileList *list);
void sort_file_list_by_size(FileList *list);
void sort_file_list_alphabetically(FileList *list);//noch nicht implementirert

// Funktion, um ein Verzeichnis nach Zeit zu sortieren. (Neueste Zuerst)
void sort_file_list_by_time(FileList *list);

// Funktion, um ein Verzeichnis nach Extension zu sortieren
void sort_file_list_by_extension(FileList *list);

// Funktion, um die Datei-Liste zu reversieren
void reverse_file_list(FileList *list);

#endif // FILESYSTEM_H