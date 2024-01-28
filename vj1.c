/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FILE_ERROR_OPEN -1
#define MALLOC_ERROR -2
#define SCANF_ERROR -3
#define MAX_SIZE 50
#define MAX_POINTS 20
#define MAX_LINE 1024

int readNoRows();

struct _Student;
typedef struct _Student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

int main() {
	int rows = 0;
	rows = readNoRows();

	if (rows > 0) {
		FILE* filePointer = NULL;
		filePointer = fopen("students.txt", "r");
		if (!filePointer) {
			printf("File not open!\n");
			return FILE_ERROR_OPEN;
		}

		Student* studentPointer = NULL;
		studentPointer = (Student*)malloc(rows * sizeof(Student));
		if (studentPointer == NULL) {
			printf("Malloc error!\n");
				return MALLOC_ERROR;
		}

		for (int i = 0; i < rows; i++) {
			if (fscanf(filePointer, " %s %s %lf ", studentPointer[i].name, studentPointer[i].surname, &studentPointer[i].points) != 3)
				return SCANF_ERROR;
		}

		for (int i = 0; i < rows; i++) {
			printf("%s %s %.2lf %.2lf \n", studentPointer[i].name, studentPointer[i].surname, studentPointer[i].points, studentPointer[i].points / MAX_POINTS * 100);
		}

		fclose(filePointer);
		free(studentPointer);
	}
	return EXIT_SUCCESS;
}

int readNoRows() {
	int counter = 0;
	char buffer[MAX_LINE] = { 0 };

	FILE* filePointer = NULL;
	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		printf("File not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}

	fclose(filePointer);
	return counter;
}
