#include <fstream>
#include <iostream>

//void readFile(char* filename);

int main() {

	setlocale(LC_ALL, "RUS");//��������� ������� ���������
	
	//char* filename=0;

	//std::cout << "������� �������� �����" << std::endl;
	//std::cin >> filename;
	//readFile(filename);

	char buff[50];//����� ��� ������ � ������
	
	
	std::ifstream input("schedule.txt", std::ios_base::in);//������� �������� �����
	if (!input.is_open()) {
		std::cout << "���� �� ������!" << std::endl;
		system("pause");
		//return -1;
	}
	
	input.getline(buff, 50);//������ ������ �� �����
	input.close();
	std::cout << buff << std::endl;

	system("pause");
	return 0;
}
//
//void readFile(char* filename) {
//	char buff[50];//����� ��� ������ � ������
//
//
//	std::ifstream input(filename, std::ios_base::in);//������� �������� �����
//	if (!input.is_open()) {
//		std::cout << "���� �� ������!" << std::endl;
//		system("pause");
//		//return -1;
//	}
//
//	input.getline(buff, 50);//������ ������ �� �����
//	input.close();
//	std::cout << buff << std::endl;
//};