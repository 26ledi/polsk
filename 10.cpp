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
    printf(Rus("������� ��� ��������: "));
    fflush(stdin);
    getline(cin, m);
    int i,n,h;
    printf(Rus("������� ���������� ����, ������ ��������: "));
    scanf("%d", &n);
    
    int pages = n / page_size; // ���������� ������� ��� ��������
    if(n % page_size != 0)
    	pages++;
	
	if(size >= n)
	{
		i = 0;
		while(n != 0)
	    {
	    	if(processes[i] == "" && numbers[i] == 0)
	    	{
	            if(free_pages > 0) //���������� ���������� ��������� ������� �� 1
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
	    			printf(Rus("\n������� ������� �������� � ������."));
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
	    		if(free_pages > 0) //���������� ���������� ��������� ������� �� 1
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
	    	else if(processes[i] != "" && numbers[i] != 0  && size == 0) //��� size = 0!!!!!!!!
	    	{
	    		if(Idx[i] != -1 && Idx[i] == min) // ��������� 
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
		    			printf(Rus("\n������� ������� �������� � ������ � ���������� �� ���� �������."));
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
    printf(Rus("������� ��� ��������, ������� ������ �������: "));
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
		printf(Rus("\n�������� �� �������������!"));
	else
    	printf(Rus("\n������ ����������� �� �������� ��������."));
}

void menu()
{
	puts(Rus("\n1. ����������"));
    puts(Rus("2. �������� �������"));
    puts(Rus("3. ������� �� ��������"));
    puts(Rus("4. ������� �������"));
    puts(Rus("5. ����� �� ���������"));
    printf(Rus("\n�������� ����� ����: "));
}

void table(int col_pages, string *processes, int *numbers) //����� �������
{
	int i;
	//�����
	const char *S;
	printf("%c", 218);
	for(i=0;i<16;i++) printf("%c", 196);  printf("%c", 194); for(i=0;i<19;i++) printf("%c", 196);  printf("%c", 194);
	for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 191);
	printf(Rus("%c ����� �������� %c �������� �������� %c ���������� ������� ���� %c\n"), 179,179,179,179);
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
	int size = 0; //������ ����� ������
    int col_pages = 0; //���������� �������
    int page_size = 0; // ������ ����� ��������
    int free_pages = 0; //���������� ��������� �������
    int j = 0, k1 = 0, min;
    
    printf(Rus("������� ����� ������ � ������: "));
    //cout << "Input size of memory (bites): ";
    while(size <= 0)
    	scanf("%d",&size);
    printf(Rus("������� ���������� �������: "));
    while(col_pages <= 0)
    	scanf("%d",&col_pages); //���������� �������
    
    page_size = size / col_pages; // ������ ����� ��������
    free_pages = col_pages;
    
    int size1 = size;
    int Idx[col_pages];
    min = Idx[0];
    
    string processes[col_pages]; //������ ���� ���������
    string Vprocesses[col_pages];
    
    int numbers[col_pages]; //������ ���������� ������ ���������
    int Vnumbers[col_pages];
    
    for(int i = 0; i < col_pages; i++)
	{
		processes[i] = "";
		Vprocesses[i] = "";
		numbers[i] = 0;
		Vnumbers[i] = 0;
	}
    
    char* memory[col_pages]; //������ ������ ��� ��������
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
			printf(Rus("����������:\n"));
			printf(Rus("����� ������ (� ������): %d\n"),size);
			printf(Rus("����� ��������� ������ (� ������): %d\n"),size1);
			printf(Rus("������ �������� (� ������): %d\n"), page_size);
			printf(Rus("����� �������: %d\n"), col_pages);
			printf(Rus("����� ��������� �������: %d\n"), free_pages);
			break;
		case 2:
			add_proc(processes, Vprocesses, numbers, Vnumbers, memory, Vmemory, Idx, min, col_pages, j, k1, size1, page_size, free_pages);
			break;
		case 3:
			delete_process(memory, Vmemory, processes, Vprocesses, numbers, Vnumbers, Idx, j, col_pages, k1, size1, page_size, free_pages);
			break;
		case 4:
			printf(Rus("\n ����������� ������ ����������\n"));
			table(col_pages, processes, numbers);
			//table(col_pages, processes, Idx);
			printf(Rus("\n\n ��������(��������) ������ ����������\n"));
			table(k1, Vprocesses, Vnumbers);
			break;
		case 5:
			exit(0);
			break;
		default:
			puts(Rus("������ ������������ ����� ����!"));
	   }
	   printf("\n");
    }
    return 0;
}

