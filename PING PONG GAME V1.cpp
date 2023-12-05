#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

enum Move {STOP = 0, UP, DOWN}; // Перечисление для управления правой ракеткой
Move run;

enum Move1 {STOP1 = 0, UP1, DOWN1}; // Перечисление для управления левой ракеткой
Move1 run1;

enum Ball {STOP2 = 0, UPLEFT = 1, UPRIGHT = 2, DOWNLEFT = 3, DOWNRIGHT = 4}; // Перечисление для управления траектории мяча
Ball ran;

const int COL = 40; // Количество колонок в игровом поле. Можно свободно менять
const int ROW = 10; // Количество строк в игровом поле. Можно свободно менять

int x = COL - 2; // Координаты правой ракетки
int y = ROW / 2;

int xl = COL - COL + 1; // Координаты левой ракетки
int yl = ROW / 2;

int bx = COL / 2; // Координаты мяча
int by = ROW / 2;

int racketRX[3]{ x, x, x }; // Массив с координатами правой ракетки
int racketRY[3]{ y + 1, y, y - 1 };

int racketLX[3]{ xl, xl, xl }; // Массив с координатами левой ракетки
int racketLY[3]{ yl + 1, yl, yl - 1 };

int score1 = 0; // Счет первого игрока
int score2 = 0; // Счет второго игрока
int maxScore = 0; // До какого счета играют игроки
char Gamer1[20]; // Имена игроков
char Gamer2[20];

bool gameOwer = false;

void Draw() 
{
	for (int i = 0; i < COL; i++) // Рисуем верхнюю границу поля
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < ROW; i++) { // Рисуем центр поля и управляемые обьекты
		for (int j = 0; j < COL; j++) {
			
			if (j == 0 || j == COL - 1) { // Боковые границы поля
				cout << "#";
			}	
			else if (bx == j && by == i) { // Мяч
				cout << "O";
			}
			else {
				bool yas = false;
				for (int k = 0; k < 3; k++) {
					if (racketRX[k] == j && racketRY[k] == i) { // Правая ракетка
						yas = true;
						cout << "[";
					}
					else if (racketLX[k] == j && racketLY[k] == i) { // Левая ракетка
						yas = true;
						cout << "]";
					}
				}
				if (yas == false) {
					cout << " "; // Пустота
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < COL; i++) //Нижняя граница поля
	{
		cout << "#";
	}
	cout << endl;

	cout << Gamer1 << " score: " << score1 << endl; // Вывод имен игроков
	cout << Gamer2 << " score: " << score2 << endl;
}

void Input() 
{
	if (_kbhit()) // Отслеживаем нажатые клавиши пользователем
	{
		switch (_getch()) // Задаем клавиши для управления ракетками
		{
		case 'w':
			run = UP; // Правая ракетка - вверх
			break;
		case 'x':
			run = DOWN; // Правая ракетка - вниз
			break;
		case 'q':
			run1 = UP1; // Левая ракетка - вверх
			break;
		case 'z':
			run1 = DOWN1; // Левая ракетка - вниз 
			break;
		case 's':
			run = STOP; // Правая ракетка - стоп
			break;
		case 'a':
			run1 = STOP1; // Левая ракетка - стоп
		}
	}
}

void Logik()
{
	if (bx == COL / 2 && by == ROW / 2 && ran == STOP2) { // Создаем варианты траектории движения мяча (недоработано)
		ran = UPLEFT;
	}
	if (by == 0 && ran == UPRIGHT) {
		ran = DOWNRIGHT;
	}
	if (by == ROW && bx != COL - COL + 1 && ran == DOWNLEFT) {
		ran = UPLEFT;
	}
	if (by == 0 && ran == UPLEFT) {
		ran = DOWNLEFT;
	}
	if (by == ROW && bx == COL - COL + 1 && ran == DOWNLEFT) {
		ran = UPRIGHT;
	}
	if (by == ROW && ran == DOWNRIGHT) {
		ran = UPRIGHT;
	}
	if (bx == COL / 2 && by == ROW / 2 && ran == DOWNLEFT) {
		ran = DOWNLEFT;
	}

	if (bx == 0 && ran == UPLEFT) { // Варианты пролета меча в случае пропуска ракеткой
		bx = COL;
		ran = UPLEFT;
		score1 += 1; // В случае пропуска мяча - сопернику начисляется очко
	}
	if (bx == 0 && ran == DOWNLEFT) {
		bx = COL;
		ran = DOWNLEFT;
		score1 += 1;
	}
	if (bx == COL - 1 && ran == DOWNRIGHT) {
		bx = 0;
		ran = DOWNRIGHT;
		score2 += 1;
	}
	if (bx == COL - 1 && ran == UPRIGHT) {
		bx = 0;
		ran = UPRIGHT;
		score2 += 1;
	}

	for (int i = 0; i < 3; i++) { // Варианты отбивания мяча ракеткой
		if (bx == COL - 2 && by == racketRY[i] && ran == DOWNRIGHT) {
			ran = DOWNLEFT;
		}
		else if (bx == COL - 2 && by == racketRY[i] && ran == UPRIGHT) {
			ran = UPLEFT;
		}
		else if (bx == COL - COL + 1 && by == racketLY[i] && ran == DOWNLEFT) {
			ran = DOWNRIGHT;
		}
		else if (bx == COL - COL + 1 && by == racketLY[i] && ran == UPLEFT) {
			ran = UPRIGHT;
		}
	}
	
	switch (ran) // Движение мяча по заданной траектории
	{
	case UPLEFT:
		by--;
		bx--;
		break;
	case UPRIGHT:
		by--;
		bx++;
		break;
	case DOWNLEFT:
		by++;
		bx--;
		break;
	case DOWNRIGHT:
		by++;
		bx++;
		break;
	}

	switch (run) // Управление правой ракеткой
	{
	case STOP:
		break;
	case UP:
		for (int i = 0; i < 3; i++) {
			racketRY[i]--;
		}
		break;
	case DOWN:
		for (int i = 0; i < 3; i++) {
			racketRY[i]++;
		}
		break;
	}

	switch (run1) // Управление левой ракеткой
	{
	case STOP1:
		break;
	case UP1:
		for (int i = 0; i < 3; i++) {
			racketLY[i]--;
		}
		break;
	case DOWN1:
		for (int i = 0; i < 3; i++) {
			racketLY[i]++;
		}
		break;
	}

	for (int i = 0; i < 3; i++) { // Остановка ракеток на границе поля
		if (racketLY[i] == 0 || racketLY[i] == ROW - 1) {
			run1 = STOP1;
		}
		else if (racketRY[i] == 0 || racketRY[i] == ROW - 1) {
			run = STOP;
		}
	}
}

int main() // Точка входа в программу
{
	cout << "How many points are we playing for? " << endl; // Спрашиваем игроков - до скольки очков играем
	cin >> maxScore;
	cout << "Gamer 1 Input you name: "; // Запрашиваем имя первого игрока
	cin >> Gamer1;
	cout << "Gamer 2 Input you name:  "; // Запрашиваем имя второго игрока
	cin >> Gamer2;

	while (gameOwer == false) { // Условие завершения игры
		Sleep(50); // Замедление движения всех элементов
		system("cls"); // Обновление консоли
		Draw(); // Функции отвечающие за игру
		Input();
		Logik();

		if (maxScore == score1 || maxScore == score2) { // Условие завершения игры
			gameOwer = true;
		}
	}
	if (maxScore == score1) { // Условие победы одного из игроков
		system("cls"); // Очищаем консоль от игрового поля
		cout << "Game Ower! " << "Victory: " << Gamer1 << " " << score1 << endl;
	}
	else if (maxScore == score2) {
		system("cls"); // Очищаем консоль от игрового поля
		cout << "Game Ower! " << "Victory: " << Gamer2 << " " << score2 << endl;
	}
	return 0;
}