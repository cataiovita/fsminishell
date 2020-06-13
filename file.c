#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void createFS(Directory **root)
{	// Aloc memorie directorului principal.
	(*root) = (Directory *)calloc(1, sizeof(Directory));
	// Pointerul spre parinte e NULL.
	(*root)->parentDir = NULL;
	// Initializez nume director radacina.
	(*root)->name = "/";
	// Initializez listele de directoare si fisiere cu null.
	(*root)->headFile = NULL;
	(*root)->headDir = NULL;
}

// Creez functie adaugare nod la inceput intr-o lista de fisiere.
void addFileFront(Directory **current, char *name, char *data)
{
	fileNod *addFile;

	addFile = (fileNod *)calloc(1, sizeof(fileNod));
	addFile->file.name = NULL;
	addFile->file.data = NULL;

	if (addFile == NULL) {
		printf("Nu a putut fi alocata memoria.");
	}

	else {
		addFile->file.name = name;
		addFile->file.size = strlen(data);
		addFile->file.data = data;
		addFile->file.dir = (*current);
		addFile->next = (*current)->headFile;
		(*current)->headFile = addFile;
	}
}

// Creez functie adaugare nod la sfarsit intr-o lsita de fisiere.
void addFileBack(Directory **current, char *name, char *data)
{
	fileNod *temp, *addFile;

	temp = NULL;
	addFile = (fileNod *)calloc(1, sizeof(fileNod));
	addFile->file.name = NULL;
	addFile->file.data = NULL;

	if (addFile == NULL) {
		printf("Nu a putut fi alocata memoria.");
	}

	else {
		temp = (*current)->headFile;
		addFile->file.name = name;

		if (data)
			addFile->file.size = strlen(data);

		addFile->file.data = data;
		addFile->file.dir = (*current);
		// Parcurg lista pana la final sa gasesc ultimul element;
		while (temp->next != NULL)
			temp = temp->next;
		// Leg ultimul element al listei de noul nod creat.
		temp->next = addFile;
	}
}

// Creez functie adaugare nod director la inceput de lista.
void addDirFront(Directory **current, char *name)
{
	dirNod *addDir;

	addDir = (dirNod *)calloc(1, sizeof(dirNod));
	addDir->dir.name = NULL;

	if (addDir == NULL) {
		printf("Nu a putut fi alocata memoria.");
	}

	else {
		addDir->dir.name = name;
		addDir->dir.headFile = NULL;
		addDir->dir.headDir = NULL;
		addDir->dir.parentDir = *current;
		addDir->next = (*current)->headDir;
		(*current)->headDir = addDir;
	}
}

// Creez functie adaugare nod director la sfarsit de lista.
void addDirBack(Directory **current, char *name)
{
	dirNod *temp, *addDir;

	temp = NULL;
	addDir = (dirNod *)calloc(1, sizeof(dirNod));
	addDir->dir.name = NULL;

	if (addDir == NULL) {
		printf("Nu a putut fi alocata memoria.");
	}

	else {
		temp = (*current)->headDir;
		addDir->dir.name = name;
		addDir->dir.headFile = NULL;
		addDir->dir.headDir = NULL;
		addDir->dir.parentDir = (*current);
		// Parcurg lista pana la final sa gasesc ultimul element;
		while (temp->next != NULL)
			temp = temp->next;
		// Leg ultimul element al listei de noul nod creat.
		temp->next = addDir;
	}
}

// Inserare fisiere sortare (TOUCH)
void sortedInsertFile(Directory **current, char *name, char *data)
{
	fileNod *temp, *addFile;
	int count = 0;

	temp = NULL;
	temp = (*current)->headFile;
	// Daca lista e goala, inserez un element la inceput;
	if (temp == NULL) {
		addFileFront(current, name, data);
		count++;
	}

	else if (temp != NULL) {
		// Inserez la primul nod (caz in care e mai mic decat primu nod)
		if (strcmp(name, temp->file.name) < 0 && count < 1) {
			addFileFront(current, name, data);
			count++;
		}

		while (temp->next != NULL && count < 1) {
			// Compar stringul curent cu urmatorul si mut pozitia
			// daca e mai mare, ma duc spre dreapta;
			if (strcmp(name, temp->next->file.name) > 0) {
				temp = temp->next;
			}

			else if (strcmp(name, temp->next->file.name) < 0) {
				// Introduc addFile intre cele doua elemente;
				addFile = (fileNod *)calloc(1, sizeof(fileNod));

				if (addFile == NULL) {
					printf("Memoria nu a fost alocata.");
				}

				else {
					addFile->file.name = name;
					addFile->file.size = strlen(data);
					addFile->file.data = data;
					addFile->file.dir = (*current);
				}

				addFile->next = temp->next;
				temp->next = addFile;
				count++;
				break;
			}
		}

		// Inserez la sfarsit (daca e mai mare decat toate valorile).
		if (strcmp(name, temp->file.name) > 0 && count < 1)
			addFileBack(current, name, data);
	}
}

int cmpCond(dirNod *temp, char *name)
{
	if (strcmp(name, temp->next->dir.name) < 0)
		return 1;

	else if (strcmp(name, temp->next->dir.name) > 0)
		return 0;
}

void allocMem(dirNod **addDir)
{
	*addDir = (dirNod *)calloc(1, sizeof(dirNod));
}

void printError(void)
{
	printf("Memoria nu a fost alocata.");
}

void errorDir(char *name)
{
	printf("Cannot move to '%s': No such directory!\n", name);
}

void errorDir2(char *name)
{
	printf("Cannot remove '%s': No such directory!\n", name);
}

void errorFile(char *name)
{
	printf("Cannot remove '%s': No such file!\n", name);
}

// Inserare Directoare sortare (MKDIR)
void sortedInsertDir(Directory **current, char *name)
{
	dirNod *temp, *addDir;
	int count = 0;

	temp = (*current)->headDir;
	// Daca lista e goala, inserez un element la inceput;
	if (temp == NULL) {
		addDirFront(current, name);
		count++;
	}

	else if (temp != NULL) {
		// Inserez la primul nod (caz in care e mai mic decat primu nod)
		if (strcmp(name, temp->dir.name) < 0 && count < 1) {
			addDirFront(current, name);
			count++;
		}

		while (temp->next != NULL && count < 1) {
			// Compar stringul curent cu urmatorul si mut pozitia.
			// daca e mai mare, ma duc spre dreapta;
			if (name) {
				if (cmpCond(temp, name) == 0)
					temp = temp->next;

				else if (cmpCond(temp, name) == 1) {
				// Introduc addFile intre cele doua elemente.
					allocMem(&addDir);

					if (addDir == NULL)
						printError();

					else
						addDir->dir.name = name;

					addDir->next = temp->next;
					temp->next = addDir;
					count++;
					break;
				}
			}
		}

		// Inserez la sfarsit (daca e mai mare decat toate valorile).
		if (strcmp(name, temp->dir.name) > 0 && count < 1)
			addDirBack(current, name);
	}
}

// Printez lista de fisiere si directoare din directorul curent (LS).
void printFileDir(Directory **current)
{
	fileNod *tempFile;
	dirNod *tempDir;

	tempFile = (*current)->headFile;
	tempDir = (*current)->headDir;

	if (tempFile == NULL && tempDir == NULL)
		printf("\n");

	else {
		while (tempFile != NULL) {
			printf("%s ", tempFile->file.name);
			tempFile = tempFile->next;
		}

		while (tempDir != NULL) {
			printf("%s ", tempDir->dir.name);
			tempDir = tempDir->next;
		}

		printf("\n");
	}
}

// Functie de dezalocare a unui nod fisier.
void dissAllocFile(fileNod **delFile)
{
	free((*delFile)->file.name);
	free((*delFile)->file.data);
	free(*delFile);
}

// Functie de dezalocare a unui nod director.
void dissAllocDir(dirNod **delDir)
{
	free((*delDir)->dir.name);
	free(*delDir);
}

// Functie de adaugare a unui director pe o lista la inceput.
void pushFrontDir(dirNod **current, char *name)
{
	dirNod *addNode;

	addNode = (dirNod *)malloc(sizeof(dirNod));

	if (addNode == NULL)
		printf("Memoria nu a putut fi alocata.");

	else {
		addNode->dir.name = name;
		addNode->dir.headFile = NULL;
		addNode->dir.headDir = NULL;
		addNode->dir.parentDir = NULL;
		addNode->next = *current;
		(*current) = addNode;
	}
}

// Functie de adaugare a unui fisier pe o lsita la inceput.
void pushFront(fileNod **current, char *name)
{
	fileNod *addNode;

	if ((*current)->file.name == NULL)
		(*current)->file.name = name;

	else {
		addNode = (fileNod *)malloc(sizeof(fileNod));

		if (addNode == NULL)
			printf("Memoria nu a putut fi alocata.");

		else {
			addNode->file.name = name;
			addNode->file.data = NULL;
			addNode->file.size = strlen(name);
			addNode->next = *current;
			(*current) = addNode;
		}
	}
}

// Printare Working Directory (PWD).
void printWorkingDirectory1(Directory **current)
{
	Directory *temp;
	dirNod *saveList, **tempList;
	int count = 0;

	saveList = NULL;
	temp = *current;
	// Plec cu un pointer temporar la director
	while (temp != NULL) {
		// Adaug in lista temporara (saveList) fiecare string
		pushFrontDir(&saveList, temp->name);
		temp = temp->parentDir;
	}

	// Printez lista creata temporar
	while (saveList != NULL) {
		// Adaug cate un '/' necesar pt printare si count
		// reprezinta un flag pt ca / sa nu se printeze
		// daca primu director e root;
		if (saveList->dir.name != "/" && count > 1)
			printf("/");

		printf("%s", saveList->dir.name);
		saveList = saveList->next;
		count++;
	}
}

// Functie prin care schimb Directorul (CD).
void changeDirectory(Directory **current, char *name)
{
	dirNod *tempDir;
	Directory *temp;
	int width = 0;

	tempDir = (*current)->headDir;
	// Caut directorul cu numele necesar, folosindu-ma de un pointer
	if (tempDir == NULL)
		printf("Cannot move to '%s': No such directory!\n", name);

	else {
		// Compar stringul nodului temporar cu
		// numele primit ca argument din prompt;
		while (strcmp(tempDir->dir.name, name) != 0) {
			tempDir = tempDir->next;
			width++;

			if (tempDir == NULL) {
				errorDir(name);
				break;
			}
		}

		// Odata gasit, ma mut cu curent la directorul
		// nodului gasit;
		if (tempDir)
			*current = &tempDir->dir;
	}
}

// Functie de sterge fisier (rm);
void removeFile(Directory **current, char *name)
{
	fileNod *tempFile;
	fileNod *prevFile;

	tempFile = (*current)->headFile;
	// In caz ca lista e goala;
	if (tempFile == NULL)
		printf("Cannot remove '%s': No such file!\n", name);

	else {
		// Caut nodul de care am nevoie pt a-l sterge;
		while (strcmp(tempFile->file.name, name) != 0) {
			prevFile = tempFile;
			tempFile = tempFile->next;
			// Eroare:
			if (tempFile == NULL) {
				errorFile(name);
				break;
			}
		}
		// Daca nodul cautat e la capul listei, sterg recursiv;
		if (tempFile == (*current)->headFile && tempFile != NULL) {
			(*current)->headFile = (*current)->headFile->next;
			tempFile->next = NULL;
			dissAllocFile(&tempFile);
		}
		// Daca nodul cautat nu e la capul listei:
		else if (tempFile != NULL) {
			prevFile->next = tempFile->next;
			tempFile->next = NULL;
			dissAllocFile(&tempFile);
		}
	}
}

// Functie de traverse sa sterg directoare recursiv;
void travToRem(dirNod **current, fileNod **currentF, int i)
{
	dirNod *tDir, *prevDir;
	fileNod *tempFile, *prevFile, *fileGo;

	tDir = NULL;
	tempFile = NULL;

	if (*current) {
		tDir = (*current);
		// Traversez directoarele din directorul apelat;
		travToRem(&tDir->dir.headDir, &tDir->dir.headFile, 0);
		travToRem(&tDir->next, &tDir->dir.headFile, 0);
		// In fiecare director in parte, sterg fiecare lista
		// de fisiere;
		if (*currentF) {
			while ((*currentF)) {
				tempFile = *currentF;
				(*currentF) = (*currentF)->next;
				// Aplic functia de dezalocare,
				// ce contine dezalocarea stringurilor
				dissAllocFile(&tempFile);
			}
		}
		// Apoi sterg fiecare director in parte
		// Ma mut la urmatorul, pana cand tempDir devine NULL;
		if (*current) {
			if (tDir != NULL) {
				tDir = (*current);
				dissAllocDir(&tDir);
				i++;
			}
		}
	}
}

// TODO recursiv sterge tot sub-systemul din interior.
void removeDirectory(Directory **current, char *name)
{
	dirNod *tDir, *delNode;
	dirNod *prevDir;

	tDir = (*current)->headDir;

	if (tDir == NULL)
		printf("Cannot remove '%s': No such directory!\n", name);
	// Caut directorul de care am nevoie pt a-l sterge;
	else {
		while (strcmp(tDir->dir.name, name) != 0) {
			prevDir = tDir;
			tDir = tDir->next;

			if (tDir == NULL) {
				errorDir2(name);
				break;
			}
		}
		// Daca directorul este chiar capul listei:
		if (tDir == (*current)->headDir && tDir != NULL) {
			// Parcurg recursiv sa sterg tot continutul;
			travToRem(&tDir->dir.headDir, &tDir->dir.headFile, 0);
			(*current)->headDir = (*current)->headDir->next;
			tDir->next = NULL;
			dissAllocDir(&tDir);
		}
		// Altfel, daca directorul este prin lista
		// si e diferit de NULL;
		else if (tDir) {
			// Parcurg recursiv sa sterg tot continutul;
			travToRem(&tDir->dir.headDir, &tDir->dir.headFile, 0);
			prevDir->next = tDir->next;
			tDir->next = NULL;
			dissAllocDir(&tDir);
		}
	}
}

// traverseaza toate fisierele din subdirecctor;
void findTraverse(dirNod **current, fileNod **currentF, fileNod **saveFile,
		int p, int depth, int min, int max, char *subcon)
{
	dirNod *tempDir;
	fileNod *tFile;
	fileNod *findFiles;
	// Pointez cu un tempDir la directorul
	// curent;
	tempDir = (*current);

	// p reprezinta counterul pentru adancime
	if (tempDir && p <= depth) {
		if (tempDir->dir.parentDir->headFile) {
			tFile = tempDir->dir.parentDir->headFile;
			// Parcurg toata lista de fisiere
			// din fiecare director
			while (tFile) {
				if (tFile->file.size >= min
					&& tFile->file.size <= max
					&& strstr(tFile->file.data, subcon))
					pushFront(saveFile, tFile->file.name);

				tFile = tFile->next;
			}
		}
		// Aplic functia recursiv si ma mut la capul listei
		// directorului urmator (dir.headDir);
		// pana cand tempDir devine NULL;
		// De asemenea, cresc p-ul (adancimea);
		findTraverse(&tempDir->dir.headDir,
			&tempDir->dir.headFile,
				saveFile, p + 1, depth, min, max, subcon);
		if (tempDir->dir.headDir == NULL && p + 1 <= depth) {
			tFile = tempDir->dir.headFile;

			while (tFile) {
				if (tFile->file.size >= min
					&& tFile->file.size <= max
					&& strstr(tFile->file.data, subcon))
					pushFront(saveFile, tFile->file.name);

				tFile = tFile->next;
			}
		}
		// Ma mut apoi pe fiecare subdirector in parte
		// in latime de data aceasta, parcurgand la directorul
		// urmator din fiecare subdirector
		findTraverse(&tempDir->next,
				&tempDir->dir.headFile,
					saveFile, p, depth, min, max, subcon);
		p = 0;
	}
}


// Traversez recursiv directoarele pentru TREE print
void traverseThru(dirNod **current, fileNod **currentF, int countLev,
		int c, int p)
{
	dirNod *temp;
	fileNod *tempFile, *fileGo;
	int i;

	tempFile = *currentF;
	temp = *current;

	// Counter ce reprezinta diferenta de nivel
	// Whitespace-urile ce necesita printate;
	c = 0;

	if (temp) {
		while (tempFile != NULL && temp) {
			// Printez de fiecare data whitespace-uri
			// necesare pentru fiecare fisier;
			for (i = 0; i < countLev + c; i++)
				printf("    ");

			if (p == -1)
				printf("    ");
			// Printez apoi fisierele;
			printf("%s\n", tempFile->file.name);
			tempFile = tempFile->next;
		}
		// Aplic acelasi tratament pentru directoare;
		for (i = 0; i < countLev; i++)
			printf("    ");
		// Intai white space-uri, apoi nume;
		printf("%s\n", temp->dir.name);

		if (temp->dir.headDir) {
			countLev++;
			c++;
		}
		// Aplic apoi functiile recursiv, ma mut cu temp
		// la capul listei fiecarui subdirector
		// apoi la urmatorul din acea lista;
		traverseThru(&temp->dir.headDir, &temp->dir.headFile,
				countLev, c, p + 1);

		// Aplic un nou white space daca exista doar fisiere
		// intr-un director, la capatul acestuia;
		if (temp->dir.headDir == NULL && temp->dir.headFile)
			p = -1;

		traverseThru(&temp->next, &temp->dir.headFile,
				countLev - c, c, p);
	}
}

// Functia TREE propriu-zisa;
void realtreePrint(Directory **current)
{
	fileNod *tempFile;
	int i;

	// Fac printarile initiale din director
	// pentru fisierele;
	tempFile = (*current)->headFile;

	printf("%s\n", (*current)->name);

	if ((*current)->headDir == NULL) {
		while (tempFile != NULL) {
			for (i = 0; i < 1; i++)
				printf("    ");

				printf("%s\n", tempFile->file.name);
				tempFile = tempFile->next;
			}
	}

	// Apoi printez recursiv fiecare director cu
	// fiecare lista de fisiere din interiorul acestuia;
	traverseThru(&(*current)->headDir, &(*current)->headFile, 1, 0, 0);
}

// Functia CD .. prin care mut directorul;
void changeDirectoryBack(Directory **current)
{
	// Ma mut la directorul parinte al directorului curent.
	if ((*current)->parentDir != NULL)
		*current = (*current)->parentDir;
}

// Printez lista necesara find;
void printList(fileNod **current)
{
	if ((*current)) {
		printList(&(*current)->next);
		printf("%s ", (*current)->file.name);
	}
}

// Functie de reverse pt noduri (in caz de inserare front);
void reverse(fileNod **current)
{
	fileNod *prevNode, *curNode;
	// pointez cu prev la nodul 1;
	prevNode = *current;
	// current node trece la al doilea nod;
	curNode = (*current)->next;
	*current = (*current)->next;
	prevNode->next = NULL;

	while (*current != NULL) {
		*current = (*current)->next;
		curNode->next = prevNode;
		// pointez spre al doilea nod;
		prevNode = curNode;
		// mut indicii spre dreapta;
		curNode = *current;
	}
	// reasignez capul listei cu x cand ajunge la ultimul element, invers;
	*current = prevNode;
}

// Stergerea duplicatelor dintr-o lista;
void removeDuplicates(fileNod **current, fileNod **saveDat)
{
	fileNod *t1, *t2;
	int flag;
	// Adaug un prim element in lista (cel initial);
	t1 = (*current);
	pushFront(saveDat, t1->file.name);
	t2 = (*saveDat);
	t1 = t1->next;

	// Parcurg lista cea mare;
	while (t1) {
		// Imi iau un flag sa vad daca se repeta elementul;
		t2 = (*saveDat);
		flag = 0;
		// Parcurg fiecare element din lista mica
		// de fiecare data;
		while (t2) {
			if (strcmp(t1->file.name, t2->file.name) == 0)
				flag = 1;

			t2 = t2->next;
		}
		// Daca flagul ramane intact
		// adaug elementul in lista;
		if (flag == 0)
			pushFront(saveDat, t1->file.name);

		t1 = t1->next;
	}
}

// Prelucrez bufferul si sparg in stringuri;
void cutString(char *buffer, char **cmd, char **data, char **name,
		char **maxlen, char **minlen)
{
	char *p;
	// Primul string (comanda primita);
	p = strtok(buffer, " ");
	*cmd = strdup(p);
	p = strtok(NULL, " ");

	// Al doilea string spart, numele;
	if (p != NULL)
		*name = strdup(p);

	p = strtok(NULL, " ");
	// Al treilea string, data din interiorul file;
	if (p != NULL)
		*data = strdup(p);

	p = strtok(NULL, " ");

	// Al patrulea si al cincilea string, max si min lenght
	// necesar pentru comanda FIND;
	if (p != NULL)
		*minlen = strdup(p);

	p = strtok(NULL, " ");

	if (p != NULL)
		*maxlen = strdup(p);
}

// Sterg file-system si tot ce contine ultimul apel sizeof
// iteratie while (strdup-uri de la prelucrare buffer);
void deleteFS(Directory *root, char *saveb, char *cmd, char *name)
{
	free(saveb);
	free(cmd);
	free(name);
	free(root);
}
