#ifndef __FILE_H__
#define __FILE_H__

typedef struct Directory {
	// The name of the directory.
	char *name;
	struct fileNod *headFile;
	struct dirNod *headDir;
	struct Directory *parentDir;
} Directory;

typedef struct File {
    // The name of the files.
	char *name;
	// The size of the file.
	int size;
	// The content of the file.
	char *data;
	// The directory in which the file is located.
	Directory *dir;
} File;

// Structura listei de fisiere.
typedef struct fileNod {
	File file;
	struct fileNod *next;
} fileNod;

// Structura listei de directoare.
typedef struct dirNod {
	Directory dir;
	struct dirNod *next;
} dirNod;

#endif
