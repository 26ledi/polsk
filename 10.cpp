#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <windows.h>
char bufRus[256];
char* Rus(const char* text)
{
	CharToOem(text, bufRus);
	return bufRus;
}
using namespace std;

void add_proc(string *processes, string *Vprocesses, int *numbers, int *Vnumbers, char* memory[], char* Vmemory[], int *Idx, int &min, int col_pages, int &j, int &k, int &size, int page_size, int &free_pages)
{
    string m;
    printf(Rus("Введите имя процесса: "));
    fflush(stdin);
    getline(cin, m);
    int i,n,h;
    printf(Rus("Введите количество байт, нужных процессу: "));
    scanf("%d", &n);
    
    int pages = n / page_size; // Количество страниц для процесса
    if(n % page_size != 0)
    	pages++;
	
	if(size >= n)
	{
		i = 0;
		while(n != 0)
	    {
	    	if(processes[i] == "" && numbers[i] == 0)
	    	{
	            if(free_pages > 0) //Уменьшение количества свободных страниц на 1
	    	        free_pages--;
	    		processes[i] = m;
	    		if(pages > 1)
	    		{
	    			numbers[i] = page_size;
	    			memory[i] = (char*) malloc (page_size);
	    			size = size - page_size;
	    			n = n - page_size;
	    			Idx[i] = j+1;
	    			j++;
	    		}
	    		else
	    		{
	    			numbers[i] = n;
	    			size = size - page_size;
	    			memory[i] = (char*) malloc (n);
	    			n = 0;
	    			Idx[i] = j+1;
	    			j++;
	    			
	    			min = Idx[0];
	    			for(h=0;h<col_pages;h++)
	    				if(min > Idx[h] && Idx[h]>0) min = Idx[h];
	    			//printf("\n min = %d\n", min);
	    			printf(Rus("\nПроцесс успешно добавлен в память."));
	    			return;
	    		}
	    		pages--;
			}
			i++;
	    }
	}
	else
	{
		i = 0;
		while(n != 0)
	    {
	    	if(processes[i] == "" && numbers[i] == 0)
	    	{
	    		if(free_pages > 0) //Уменьшение количесвта свободных страниц на 1
	    	        free_pages--;
	    		processes[i] = m;
	    		if(pages > 1)
	    		{
	    			numbers[i] = page_size;
	    			memory[i] = (char*) malloc (page_size);
	    			size = size - page_size;
	    			n = n - page_size;
	    			Idx[i] = j+1;
	    			j++;
	    		}
	    		pages--;
	    	}
	    	else if(processes[i] != "" && numbers[i] != 0  && size == 0) //Уже size = 0!!!!!!!!
	    	{
	    		if(Idx[i] != -1 && Idx[i] == min) // ЗАМЕЩЕНИЕ 
	    		{
	    			for(int g=0; g<k+1; g++)
	    			{
	    				if(Vprocesses[g] == "" && Vnumbers[g] == 0)
	    				{
	    					Vprocesses[g] = processes[i];
		    				Vnumbers[g] = numbers[i];
		    				Vmemory[g] = memory[i];
						}
					}
		    		k++;
		    		processes[i] = m;
		    		if(pages > 1)
		    		{
		    			numbers[i] = page_size;
		    			memory[i] = (char*) malloc (page_size);
		    			n = n - page_size;
		    			Idx[i] = -1;
		    		}
		    		else
		    		{
		    			numbers[i] = n;
		    			memory[i] = (char*) malloc (n);
		    			n = 0;
		    			Idx[i] = -1;
		    			printf(Rus("\nПроцесс успешно добавлен в память с замещением на диск старого."));
		    			//return;
		    		}
		    		min = Idx[0];
	    			for(h=0;h<col_pages;h++)
	    				if(min > Idx[h] && Idx[h]>0) min = Idx[h];
		    		
		    		pages--;
				}
			}
			i++;
			if(i>col_pages-1) i = 0;
	    }
	}
}

void delete_process(char* memory[], char* Vmemory[], string *processes, string *Vprocesses, int *numbers, int *Vnumbers, int *Idx, int &j, int col_pages, int k, int &size, int page_size, int &free_pages)
{
    string m;
    printf(Rus("Введите имя процесса, который хотите удалить: "));
    fflush(stdin);
    getline(cin, m);
    
    int i,d=0,q=0;
    
    for(i = 0; i < col_pages; i++)
    {
        if(processes[i] == m && numbers[i] != 0)
        {
            processes[i] = "";
            numbers[i] = 0;
            free(memory[i]);
            free_pages++;
            size = size + page_size;
            Idx[i] = 0;
            d++; 
        }
	}
	for(i = 0; i < k; i++)
    {
        if(Vprocesses[i] == m && Vnumbers[i] != 0)
        {
        	Vprocesses[i] = "";
            Vnumbers[i] = 0;
            free(Vmemory[i]);
		}
	}
    if(d == 0)
		printf(Rus("\nНазвание не действительно!"));
	else
    	printf(Rus("\nПамять освобождена по названию процесса."));
}

void menu()
{
	puts(Rus("\n1. Информация"));
    puts(Rus("2. Добавить процесс"));
    puts(Rus("3. Удалить по названию"));
    puts(Rus("4. Таблица страниц"));
    puts(Rus("5. Выход из программы"));
    printf(Rus("\nВыберите пункт меню: "));
}

void table(int col_pages, string *processes, int *numbers) //Вывод таблицы
{
	int i;
	//Шапка
	const char *S;
	printf("%c", 218);
	for(i=0;i<16;i++) printf("%c", 196);  printf("%c", 194); for(i=0;i<19;i++) printf("%c", 196);  printf("%c", 194);
	for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 191);
	printf(Rus("%c Номер страницы %c Название процесса %c Количество занятых байт %c\n"), 179,179,179,179);
	for(int j=0; j<col_pages; j++)
	{
		if(j!=col_pages-1)
		{
			printf("%c", 195); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 197);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 197); for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c%8d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
		}
		else
		{
			printf("%c", 195); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 197);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 197); for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c       %d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
			
			printf("%c", 192); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 193);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 193); for(i=0;i<25;i++) printf("%c", 196); printf("%c", 217);
		}
	}
}

int main()
{
	int size = 0; //Размер общей памяти
    int col_pages = 0; //Количество страниц
    int page_size = 0; // Размер одной страницы
    int free_pages = 0; //Количество свободных страниц
    int j = 0, k1 = 0, min;
    
    printf(Rus("Введите объём памяти в байтах: "));
    //cout << "Input size of memory (bites): ";
    while(size <= 0)
    	scanf("%d",&size);
    printf(Rus("Введите количество страниц: "));
    while(col_pages <= 0)
    	scanf("%d",&col_pages); //Количество страниц
    
    page_size = size / col_pages; // Размер одной страницы
    free_pages = col_pages;
    
    int size1 = size;
    int Idx[col_pages];
    min = Idx[0];
    
    string processes[col_pages]; //Массив имен процессов
    string Vprocesses[col_pages];
    
    int numbers[col_pages]; //Массив количества байтов процессов
    int Vnumbers[col_pages];
    
    for(int i = 0; i < col_pages; i++)
	{
		processes[i] = "";
		Vprocesses[i] = "";
		numbers[i] = 0;
		Vnumbers[i] = 0;
	}
    
    char* memory[col_pages]; //Массив памяти для процесса
    char* Vmemory[col_pages];
    
    int k;
    while(true)
    {
        menu();
        scanf("%d",&k);
        system("cls");
        switch(k)
    	{
		case 1:
			printf(Rus("Информация:\n"));
			printf(Rus("Объём памяти (в байтах): %d\n"),size);
			printf(Rus("Объём свободной памяти (в байтах): %d\n"),size1);
			printf(Rus("Размер страницы (в байтах): %d\n"), page_size);
			printf(Rus("Число страниц: %d\n"), col_pages);
			printf(Rus("Число свободных страниц: %d\n"), free_pages);
			break;
		case 2:
			add_proc(processes, Vprocesses, numbers, Vnumbers, memory, Vmemory, Idx, min, col_pages, j, k1, size1, page_size, free_pages);
			break;
		case 3:
			delete_process(memory, Vmemory, processes, Vprocesses, numbers, Vnumbers, Idx, j, col_pages, k1, size1, page_size, free_pages);
			break;
		case 4:
			printf(Rus("\n Оперативная память устройства\n"));
			table(col_pages, processes, numbers);
			//table(col_pages, processes, Idx);
			printf(Rus("\n\n Внешнаяя(дисковая) память устройства\n"));
			table(k1, Vprocesses, Vnumbers);
			break;
		case 5:
			exit(0);
			break;
		default:
			puts(Rus("Выбран неправильный пункт меню!"));
	   }
	   printf("\n");
    }
    return 0;
}

