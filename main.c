#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "file.c"

int main(void)
{
	Directory *root;
	Directory *current;
	char buffer[100];
	char *name, *cmd, *data, *maxlen, *minlen, *savebuffer;
	int max, min, depth;
	fileNod *saveFile, *saveDat;

	root = NULL;
	saveDat = NULL;

	while (1) {
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		// Salvezi buffer intr-unul temporar;
		savebuffer = strdup(buffer);
		// FUNCTIE DE PRELUCRARE savebuffer;
		cutString(savebuffer, &cmd, &data, &name, &maxlen, &minlen);
		// FUNCTIA CREATEFS
		if (strcmp(cmd, "create") == 0 && strcmp(name, "fs") == 0) {
			createFS(&root);
			current = root;
			free(name);
		}
		// FUNCTIA DELETEFS
		else if (strcmp(buffer, "delete fs") == 0) {
			deleteFS(root, savebuffer, cmd, name);
			break;
		}
		// FUNCTIA TOUCH;
		else if (strcmp(cmd, "touch") == 0)
			sortedInsertFile(&current, name, data);
		// FUNCTIA MKDIR;
		else if (strcmp(cmd, "mkdir") == 0)
			sortedInsertDir(&current, name);
		// FUNCTIA LS;
		else if (strcmp(cmd, "ls") == 0)
			printFileDir(&current);
		// FUNCTIA PWD;
		else if (strcmp(cmd, "pwd") == 0) {
			printWorkingDirectory1(&current);
			printf("\n");
		}
		// FUNCTIA CD;
		else if (strcmp(cmd, "cd") == 0 && strcmp(name, "..") != 0) {
			changeDirectory(&current, name);
			free(name);
		}
		// FUNCTIA CD BACK(..);
		else if (strcmp(cmd, "cd") == 0 && strcmp(name, "..") == 0) {
			changeDirectoryBack(&current);
			free(name);
		}
		// FUNCTIA RM FILE;
		else if (strcmp(cmd, "rm") == 0) {
			removeFile(&current, name);
			free(name);
		}
		// FUNCTIA RMDIR;
		else if (strcmp(cmd, "rmdir") == 0) {
			removeDirectory(&current, name);
			free(name);
		}
		// FUNCTIA TREE;
		else if (strcmp(cmd, "tree") == 0)
			realtreePrint(&current);

		// FUNCTIA FIND;
		else if (strcmp(cmd, "find") == 0) {
			// Convertesc din char in int pt comparatie adancime;
			depth = atoi(name);
			min = atoi(data);
			max = atoi(minlen);
			// Aloc memorie listelor temporare;
			saveFile = (fileNod *)malloc(sizeof(fileNod));
			saveDat = (fileNod *)malloc(sizeof(fileNod));
			findTraverse(&current->headDir, &current->headFile,
				&saveFile, 0, depth, min, max, maxlen);
			reverse(&saveFile);
			removeDuplicates(&saveFile, &saveDat);
			printList(&saveDat);
			printf("\n");
		}

		// ELIBEREZ DE FIECARE DATA CMD SI SAVEBUFFER
		// ALOCATE LA FIECARE COMANDA DATA;
		free(cmd);
		free(savebuffer);
	}

	return 0;
}
