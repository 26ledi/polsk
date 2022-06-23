#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

struct infoAboutFile
{
	int size;
	char name[100];
	int id;	
};

void addFile(struct infoAboutFile *file, int *memoryLeft, int *numberOfFile);
void deletFile(struct infoAboutFile *file, int *memoryLeft, int *numberOfFile);
void showTable(int size, struct infoAboutFile *file, int numberOfFile, int memoryLeft);
void defragment(int size, struct infoAboutFile *file, int *numberOfFile, int *memoryLeft);

void main()
{
	SetConsoleCP (1251); 
	SetConsoleOutputCP (1251);
	
	struct infoAboutFile files[1000];
	int sizeOfMemory, k = 1, memoryLeft, numberOfFile = 0;
	puts("Введите размер: ");
	scanf("%d", &sizeOfMemory);
	memoryLeft = sizeOfMemory;
	while(k != 0)
	{
		puts("1.Добавить файл");
		puts("2.Удалить файл");
		puts("3.таблица памяти");
		puts("4.дефрагментациа");
		puts("0.Выход");
		printf("ваш выбор: ");
		scanf("%d", &k);
		system("cls");
		switch(k)
		{
			case 1:
				addFile(&files, &memoryLeft, &numberOfFile);
				break;
			case 2:
				deletFile(&files, &memoryLeft, &numberOfFile);
				break;
			case 3:
				showTable(sizeOfMemory, &files, numberOfFile, memoryLeft);
				break;
			case 4:
				defragment(sizeOfMemory, &files, &numberOfFile, &memoryLeft);
				break;
			case 0:
				break;
			default:
				break; 
		}
	}
	fflush(stdin);
	getchar();	
}

void addFile(struct infoAboutFile *file, int *memoryLeft, int *numberOfFile)
{
	puts("Введите название файла : ");
	scanf("%s", &(file+(*numberOfFile))->name);
	puts("Введите размер файла: ");
	scanf("%d", &(file+(*numberOfFile))->size);
	if((file+(*numberOfFile))->size > *memoryLeft)
		puts("список файлов");
	else
	{
		(file+(*numberOfFile))->id = *numberOfFile + 1;
		*memoryLeft = *memoryLeft - (file+(*numberOfFile))->size;
    	*numberOfFile += 1;
	}
}

void deletFile(struct infoAboutFile *file, int *memoryLeft, int *numberOfFile)
{
	int i, k = 0; 
	char deletName[100];
	puts("Введите название файла: ");
	scanf("%s", &deletName);
	for(i = 0; i < *numberOfFile; i++)
	{
		if(strcmp(deletName, (file+i)->name) == 0)
		{
				*memoryLeft = *memoryLeft + (file+i)->size;
				(file+i)->id = 0;
				k = 1;
		}
	}
	if(k == 0)
		puts("");
}

void showTable(int size, struct infoAboutFile *file, int numberOfFile, int memoryLeft)
{
	int i, j, k = 1, fullMemoryLeft;
	fullMemoryLeft = memoryLeft;
	for(j = 0; j < numberOfFile; j++)
	{
		if((file+j)->id == 0)
		{
			for(i = 0; i < (file+j)->size; i++)
			{
				printf("%d", (file+j)->id);
				if(k % 50 == 0)
					printf("\n");
				k += 1;
				fullMemoryLeft -= 1;
			}
		}
		else
		{
			for(i = 0; i < (file+j)->size; i++)
			{
				printf("%d", (file+j)->id);
				if(k % 50 == 0)
					printf("\n");
				k += 1;
			}	
		}
    }
	for(i = 0; i < fullMemoryLeft; i++)
	{
		printf("%d", (file+j)->id);
		if(k % 50 == 0)
			printf("\n");
		k += 1;
	}
	printf("\n\n");
	printf("список файлов\n");
	for(i = 0; i < numberOfFile; i++)
	{
		if((file+i)->id != 0)
		{
			printf("name: %s\n", (file+i)->name);
			printf("size: %d\n", (file+i)->size);
			printf("id: %d\n\n", (file+i)->id);
		}  
	}
}

void defragment(int size, struct infoAboutFile *file, int *numberOfFile, int *memoryLeft)
{
	int i, j;
	i = 0; 
	while(i < *numberOfFile)
	{
		if((file+i)->id == 0)
		{
			j = i;
			
			while(j < *numberOfFile)
			{
				*(file+j) = *(file+j+1);
				j++;
			}
			*numberOfFile -= 1;
			i -= 1;
		}
		i +=1;
	}
}

