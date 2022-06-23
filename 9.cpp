#include<iostream>

int numLength(int n){
	int s = 0;
	if(n == 0) 
		return 1;
	while(n > 0){ 
		n = n / 10;
		s++;
	}
	return s;
}

void makeSpaces(int n){
	for(int i = 0;i < n;i++)
		std::cout << " ";
}

struct data{
	std::string name;
	int size;
	int page_;
	int padding_;
};


void giveInfo(int available_memory, int attempts, int attempts_1){
	float attempts_1_percent;
	int translate;
	if(attempts != 0){
		attempts_1_percent = (float)attempts_1 * 100 / (float)attempts;
		translate = attempts_1_percent * 10;
		attempts_1_percent = (float)translate / 10;
	}
	else
		attempts_1_percent = 0;
		
	std::cout << "1.Добавить";
	makeSpaces(90 - numLength(available_memory));
	std::cout << "Свободной памяти: " << available_memory << "КБ\n" << "2.Удалить";
	makeSpaces(86 - numLength(attempts));
	std::cout << "Попыток выделить память: " << attempts << "\n3.Показать таблицу";
	makeSpaces(66 - numLength(attempts_1_percent));
	std::cout << "Удачных попыток выделить память: " << attempts_1_percent << "%\n4.Вывести физический адрес\n5.Выход\n";
}

void showAddress(int page, int padding, data *a, int prikol){
	int i = 0;
	std::string go_next;
	bool found = true;
	while(i < prikol && found){
		if((a+i)->page_ == page && (a+i)->padding_ == padding)
			found = false;
		
		i++;
	}
	std::cout << a+i << "\nВведите что-нибудь, чтобы продолжить\n";
	std::cin >> go_next;
	
}

void showTable(data *a, int prikol){
	for(int i = 0; i < 98;i++) 
		std::cout << "_";
	std::cout << "\n";	
	std::cout << "Имена процессов     |" << "Выделенная память" << "        |Номер страницы" << "           |Сдвиг                   |\n";
	
	for(int i = 0;i < 98;i++)
		std::cout << "-";
	std::cout << "\n";
	for(int i = 0;i < prikol;i++){
		std::cout << (a+i)->name;
		makeSpaces(19 - (a+i)->name.length());
		std::cout << " |" << (a+i)->size;
		makeSpaces(25 - numLength((a+i)->size));
		std::cout << "|" << (a+i)->page_;
		makeSpaces(25 - numLength((a+i)->page_));
		std::cout << "|" << (a+i)->padding_;
		makeSpaces(24 - numLength((a+i)->padding_));
		std::cout << "|\n";
	}
	
	for(int i = 0;i < 98;i++)
		std::cout << "-";
		
	std::cout << "\nВведите  что-нибудь, чтобы продолжить\n";
	std::string go;
	std::cin >> go;
}

void remove(data *a, int *n, int page_to_kill, int padding_to_kill, int *available_memory){
	bool i_find_it = false;
	
	for(int i = 0;i < *n;i++){
		if((a+i)->page_ == page_to_kill && (a+i)->padding_ == padding_to_kill){
			i_find_it = true;
			*(available_memory) += (a+i)->size;
		}
			
		if(i_find_it)
			*(a+i) = *(a+i+1);
	}
	*n = *n - 1;
}

void addPlace(data *a, int *n, int *j, int *prikol, int *available_memory, int *attempts_1){
	int size;
	std::string name;
	
	std::cout << "Введите имя процесса\n";
	std::cin >> name;
	std::cout << "Введите размер нужной памяти\n";
	std::cin >> size;
	
	if(size > *available_memory){
		std::cout << "В системе не хватает места, чтобы выделить память\nВведите что-нибудь, чтобы продолжить\n";
		std::cin >> name;
		return;
	}
	
	*attempts_1 = *attempts_1 + 1;
	
	*(available_memory) -= size;
	
	(a+*prikol)->size = size;
	(a+*prikol)->name = name; 
	
	if(*n > 10){
		*j = *j + 1;
		*n = 0;
	}
	
	(a+*prikol)->page_ = *j;
	(a+*prikol)->padding_ = *n;
	*n = *n + 1;
	*prikol = *prikol + 1;
}

int main(){
	setlocale(LC_ALL, "Russian");
	bool dialog = true;
	int your_choose;
	data memory[100];
	int n = 0;
	int j = 0;
	int prikol = 0;  // Кол-во элементов
	int available_memory;
	int attempts = 0;
	int attempts_1 = 0;
	
	std::cout << "Введите кол-во доступной памяти(КБ)\n";
	std::cin >> available_memory;
	
	while(dialog){
		system("cls");
		giveInfo(available_memory, attempts, attempts_1);
		std::cout << "Что вы хотите сделать?\n";
		std::cin >> your_choose;
		
		switch(your_choose){
			case 1:
				addPlace(&memory[0], &n, &j, &prikol, &available_memory, &attempts_1);
				attempts++;
				break;
			case 2:
				int page_to_kill;
				int padding_to_kill;
				std::cout << "Введите номер страницы и отступ\n";
				std::cin >> page_to_kill >> padding_to_kill;
				remove(&memory[0], &prikol, page_to_kill, padding_to_kill, &available_memory);
				break;
			case 3:
				showTable(&memory[0], prikol);
				break;
			case 4:
				std::cout << "Введите номер страницы и отступ\n";
				int page;
				int padding;
				std::cin >> page >> padding;
				showAddress(page, padding, &memory[0], prikol);
				break;
			case 5:
				dialog = false;
				break;
				
		}
	}
	std::cout << "\nХорошего дня!";
	return 0;
}
