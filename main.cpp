#include <fstream>
#include <iostream>

//void readFile(char* filename);

int main() {

	setlocale(LC_ALL, "RUS");//поддержка русской кодировки
	
	//char* filename=0;

	//std::cout << "Введите название файла" << std::endl;
	//std::cin >> filename;
	//readFile(filename);

	char buff[50];//буфер для обмена с файлом
	
	
	std::ifstream input("schedule.txt", std::ios_base::in);//входной файловый поток
	if (!input.is_open()) {
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		//return -1;
	}
	
	input.getline(buff, 50);//чтение строки из файла
	input.close();
	std::cout << buff << std::endl;

	system("pause");
	return 0;
}
//
//void readFile(char* filename) {
//	char buff[50];//буфер для обмена с файлом
//
//
//	std::ifstream input(filename, std::ios_base::in);//входной файловый поток
//	if (!input.is_open()) {
//		std::cout << "Файл не найден!" << std::endl;
//		system("pause");
//		//return -1;
//	}
//
//	input.getline(buff, 50);//чтение строки из файла
//	input.close();
//	std::cout << buff << std::endl;
//};