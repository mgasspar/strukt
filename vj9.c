/*Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define FILE_OPEN_ERROR -1
#define MALLOC_ERROR -2

struct node;
typedef struct node* Position;
typedef struct node {
	int data;
	Position left;
	Position right;
} Node;

Position insert(Position root, int x);
int replace(Position root);
int writeInorderToFile(Position root, int level, FILE* filePointer);
int deleteTree(Position root);

int main()
{
	srand(time(NULL));

	FILE* filePointer = NULL;
	filePointer = fopen("inorder.txt", "w");
	if (filePointer == NULL) {
		printf("File could not be opened.\n");
		return FILE_OPEN_ERROR;
	}

	int i = 0;
	Position root = NULL;
	for (i = 0; i < 10; i++) {
		root = insert(root, rand() % (91 - 10) + 10);
		if (root == NULL) {
			printf("Malloc error.\n");
			return MALLOC_ERROR;
		}
	}

	fprintf(filePointer, "Originalno stablo:\n");
	writeInorderToFile(root, 0, filePointer);
	replace(root);
	fprintf(filePointer, "\nStablo nakon replace():\n");
	writeInorderToFile(root, 0, filePointer);

	fclose(filePointer);
	deleteTree(root);

	return 0;
}

Position insert(Position root, int x)
{
	if (root == NULL) {

		root = (Position)malloc(sizeof(Node));
		if (root == NULL) return NULL;

		root->data = x;
		root->left = NULL;
		root->right = NULL;
	}

	else if (x < root->data) {
		root->left = insert(root->left, x);
	}
	else /* x >= root->data */ {
		root->right = insert(root->right, x);
	}

	return root;
}

int replace(Position root)
{
	if (root == NULL) return 0;

	int data = root->data;
	root->data = replace(root->left) + replace(root->right);

	return data + root->data;
}

int writeInorderToFile(Position root, int level, FILE* filePointer)
{
	int i = 0;

	if (root->left != NULL) writeInorderToFile(root->left, level + 1, filePointer);

	for (i; i < level; i++) fprintf(filePointer, "   ");
	fprintf(filePointer, "%d\n", root->data);

	if (root->right != NULL) writeInorderToFile(root->right, level + 1, filePointer);

	return 0;
}

int deleteTree(Position root) {

	if (root == NULL) return EXIT_SUCCESS;

	deleteTree(root->left);
	deleteTree(root->right);
	free(root);

	return EXIT_SUCCESS;
}
