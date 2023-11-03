#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person * Position;

struct Person{
    char name[10];
    char surname[10];
    int Yob;
    Position Next;
};

void Insert(Position P){

    Position temp;

	temp = (Position)malloc(sizeof(struct Person));
	printf("Unesite podatke o osobi:\n");
	scanf( " %s %s %d", temp->name, temp->surname, &temp->Yob);

	temp->Next = P->Next;
	P->Next = temp;
}

void Print(Position P){
    if(P == NULL)
		printf("Lista je prazna!\n");
	else
	{
		printf("Lista:\n");
		while(P!=NULL)
		{
			printf("\t%s %s %d\n", P->name, P->surname, P->Yob);
			P=P->Next;
		}
	}
}

Position FindLast(Position P){
    while(NULL != P->Next)
		P = P->Next;
	return P;
}

Position Find(Position P){
    char sur[10];


	printf("Unesi prezime osobe:\n");
	scanf(" %s", sur);

	while(P != NULL && strcmpi(P->surname, sur)!= 0)
		P = P->Next;

	return P;
}

Position FindPrev(Position P){
    char sur[10];

	if(NULL == P->Next)
		P = NULL;
	else
	{
		printf("Unesi prezime osobe:\n");
		scanf(" %s", sur);


		while(strcmpi(P->Next->surname, sur)!= 0 && P->Next->Next != NULL)
			P = P->Next;

		if(strcmpi(P->Next->surname, sur)!= 0)
			P = NULL;
	}
	
	return P;
}

void Delete(Position P){
    Position prev;

	prev = FindPrev(P);

	if (prev !=NULL)
	{
		P = prev->Next;
		prev->Next = P->Next;
		printf("Osoba %s %s %d je obrisana!\n", P->name, P->surname, P->Yob);
		free(P);
	}
	else
		printf("Osoba nije pronadena!\n");
}

void ReadFromFile(Position P){
    FILE *File;
	char FileName[10];
	Position temp;

	printf("Unesi ime datoteke:\n");
	scanf(" %s", FileName);

	File = fopen(FileName, "r");
	
	if (File == NULL)
		printf("Ne postoji datoteke s tim imenom\n");
	else
	{
		while(feof(File)==0)
		{
			temp = (Position)malloc(sizeof(struct Person));
			
			fscanf(File, " %s %s %d", temp->name, temp->surname, &temp->Yob);

			temp->Next = P->Next;
			P->Next= temp;
			P = temp;
		}

		fclose(File);
	}
}

void WriteToFile(Position P){
    FILE *File;
	char FileName[10];

	printf("Unesi ime datoteke za spremanje liste:\n");
	scanf(" %s", FileName);

	File = fopen(FileName, "w");
	
	if (File == NULL)
		printf("Datoteka se ne moze otvoriti\n");
	else
	{
		while(P!=NULL)
		{
			fprintf(File, "\n %s %s %d", P->name, P->surname, P->Yob);
			P = P->Next;
		}

		fclose(File);
	}
}

void main(){
    struct Person head, *q;
    char choice = 0;

    head.Next = NULL;

    while(choice != 'K' && choice != 'k'){
        printf("Unesite znak:\nA - unos elementa na pocetak\nB - ispis liste\nC - unos elementa na kraj\nD - trazenje elementa po prezimenu\nE - brisanje elementa\nF - dodavanje iza elementa\nG - dodavanje ispred elementa\nH - upis u datoteku\nI - citanje iz datoteke\nK - kraj\n\n");
		
        scanf(" %c", &choice);

        switch (choice){
            case 'A':
            case 'a':
                Insert(&head);
			    break;
            case 'B':
            case 'b':
                Print(head.Next);
                break;
            case 'C':
            case 'c':
                q = FindLast(&head);
                Insert(q);
                break;
            case 'D':
            case 'd':
                q = Find(head.Next);
                if(q == NULL)
				    printf("Osoba nije pronadena!\n");
                else
				    printf("Trazena soba:\n\t %s %s, %d\n", q->name, q->surname, q->Yob);
                break;
            case 'E':
            case 'e':
                Delete(&head);
                break;
            case 'F':
            case 'f':
                q = Find(head.Next);
                if(q == NULL)
				    printf("Osoba nije pronadena!\n");
			    else
				    Insert(q);
                break;
            case 'G':
            case 'g':
                q = FindPrev(&head);
			    if(q == NULL)
				    printf("Osoba nije pronadena!\n");
			    else
				    Insert(q);
                break;
            case 'H':
            case 'h':
                WriteToFile(head.Next);
                break;
            case 'I':
            case 'i':
                ReadFromFile(&head);
                break;
            case 'K':
            case 'k':
                printf("Kraj programa!\n");
			    break;
		    default:
			    printf("Greska u unosu!\n");
        }
    }
}