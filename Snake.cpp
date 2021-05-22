#include <iostream>
#include <fstream>
#include <list>
#include <Windows.h>
std::fstream file;
class Utilities {
private:
	HANDLE handle;
	enum objects { AIR = 0, HEAD = 1, BODY = 2, WALL = 3, FRUIT = 4 };

public:
	Utilities(HANDLE handle) {
		this->handle = handle;
	}

	void setColor(int color) {
		SetConsoleTextAttribute(handle, color);
	}

	void upCursor() {
		SetConsoleCursorPosition(handle, { 0,0 });
	}

	void newFruit(int width, int height, int** table) {
		while (1) {
			int x = rand() % width;
			int y = rand() % height;
			if (x > 0 && y > 0 && x < width && y < height && table[y][x] == objects::AIR) {
				table[y][x] = objects::FRUIT;
				return;
			}
		}
	}

	void menuColor(bool selected) {
		if (selected) {
			setColor(2);
		}
		else {
			setColor(8);
		}
	}

	void drawOneMenuLine() {
		setColor(6);
		for (int i = 1; i <= 33; ++i) {
			if (i % 2 != 0) {
				std::cout << "-";
			}
			else {
				std::cout << "=";
			}
		}std::cout << '\n';
	}

	void menu(int option) {
		upCursor();
		drawOneMenuLine();

		setColor(2);
		std::cout << "         < Snake V3.0 >         \n";
		int x = 1;

		menuColor(x == option); ++x;
		std::cout << "   Start\n";

		menuColor(x == option); ++x;
		std::cout << "   Max Scores\n";

		menuColor(x == option); ++x;
		std::cout << "   Developer\n";

		menuColor(x == option); ++x;
		std::cout << "   Exit\n";

		drawOneMenuLine();
	}

	void drawGameLine(int width) {
		int dist = width + width % 2 + 15;
		setColor(6);
		for (int j = 1; j <= dist; ++j)
			if (j % 2)
				std::cout << "-";
			else
				std::cout << "=";
		std::cout << '\n';
	}

	void showScore(int score) {
		setColor(6);
		std::cout << "   SCORE: ";
		setColor(4);
		std::cout << score;
		if (score < 10)
			std::cout << "    ";
		else
			std::cout << "   ";
	}

	void showDetails() {
		drawOneMenuLine();
		setColor(4);
		std::cout << "   NickName";
		setColor(8);
		std::cout << " : ";
		setColor(2);
		std::cout << "TheAncientOwl\n";
		setColor(4);
		std::cout << "   Age";
		setColor(8);
		std::cout << " : ";
		setColor(2);
		std::cout << "18\n";
		drawOneMenuLine();
	}
};
class Snake {
public:
	Snake(int width, int height) {
		util = new Utilities(GetStdHandle(STD_OUTPUT_HANDLE));
		this->width = width;
		this->height = height;
		this->drawMenu();
	}

private:
	friend Utilities;
	Utilities* util;

	int dx[5] = { 0, 1, 0, -1 };///N E S V
	int dy[5] = { -1, 0, 1, 0 };
	enum directions { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, };
	directions currentDirection;

	enum objects { AIR = 0, HEAD = 1, BODY = 2, WALL = 3, FRUIT = 4 };
	int width, height;
	int** table;

	struct point { int x, y; };
	std::list<point> body;

	int score;
	bool gameOver;



	void drawMenu() {
		system("cls");
		int option = 1;
		int numberOfOptions = 4;
		util->menu(option);
		while (true) {
			if (GetAsyncKeyState(VK_RETURN)) {
				run(option);
				return;
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				++option;
				if (option > numberOfOptions)
					option = 1;
				util->menu(option);
				Sleep(170);
				continue;
			}
			if (GetAsyncKeyState(VK_UP)) {
				--option;
				if (option < 1)
					option = numberOfOptions;
				util->menu(option);
				Sleep(170);
				continue;
			}
		}
	}

	void run(int option) {
		if (option == 1) {
			initGame();
			loop();
			return;
		}if (option == 2) {
			showMaxScore();
			returnToMenu();
			return;
		}
		if (option == 3) {
			system("cls");
			util->showDetails();
			returnToMenu();
			return;
		}
	}

	void initGame() {
		currentDirection = UP;

		table = new int* [height];
		for (int i = 0; i < height; ++i) {
			table[i] = new int[width];
			for (int j = 0; j < width; ++j) {
				table[i][j] = objects::AIR;
			}
		}

		int width1 = width - 1;
		for (int i = 0; i < height; ++i) {
			table[i][0] = table[i][width1] = objects::WALL;
		}

		int height1 = height - 1;
		for (int j = 0; j < width; ++j) {
			table[0][j] = table[height1][j] = objects::WALL;
		}

		std::list<point>().swap(body);
		point head;
		head.x = width / 2;
		head.y = height / 2;
		table[head.y][head.x] = objects::HEAD;
		body.push_back(head);

		score = 0;
		gameOver = false;

		util->newFruit(width, height, table);
	}

	void loop() {
		system("cls");
		while (!gameOver) {
			userInput();
			move();
			draw();
		}

		util->setColor(4);
		std::cout << "GAME OVER!                         \n";
		util->setColor(6);
		std::cout << "SCORE: " << score << "                           \n";

		dealWithScore(score);

		delete[] table;
		returnToMenu();
	}

	void userInput() {
		if (GetAsyncKeyState(VK_LEFT))
			if (currentDirection != directions::RIGHT) {
				currentDirection = directions::LEFT;
				return;
			}
		if (GetAsyncKeyState(VK_UP))
			if (currentDirection != directions::DOWN) {
				currentDirection = directions::UP;
				return;
			}
		if (GetAsyncKeyState(VK_RIGHT))
			if (currentDirection != directions::LEFT) {
				currentDirection = directions::RIGHT;
				return;
			}
		if (GetAsyncKeyState(VK_DOWN))
			if (currentDirection != directions::UP) {
				currentDirection = directions::DOWN;
				return;
			}
	}

	void move() {
		std::list<point>::iterator itH;
		std::list<point>::reverse_iterator itT;
		itH = body.begin();
		itT = body.rbegin();

		point head;
		head.x = itH->x + dx[currentDirection];
		head.y = itH->y + dy[currentDirection];

		if (table[head.y][head.x] == objects::BODY ||
			table[head.y][head.x] == objects::WALL) {
			gameOver = true;
			return;
		}

		body.push_front(head);
		table[itH->y][itH->x] = objects::BODY;

		if (table[head.y][head.x] == objects::FRUIT) {
			++score;
			util->newFruit(width, height, table);

			table[head.y][head.x] = objects::HEAD;
			return;
		}

		table[head.y][head.x] = objects::HEAD;
		table[itT->y][itT->x] = objects::AIR;
		body.pop_back();
	}

	void draw() {
		Sleep(110);
		util->upCursor();
		util->drawGameLine(width);
		int height1 = height - 1;
		for (int i = 0; i < height; ++i) {

			for (int j = 0; j < width; ++j) {
				switch (table[i][j]) {
				case objects::AIR: std::cout << " "; break;
				case objects::WALL: util->setColor(8); std::cout << "8"; break;
				case objects::BODY: util->setColor(2); std::cout << "0"; break;
				case objects::HEAD: util->setColor(10); std::cout << "O"; break;
				case objects::FRUIT: util->setColor(12); std::cout << "F"; break;
				}
			}

			if (i == 2) {
				util->showScore(score);
			}
			else
				if (i != height1)
					std::cout << "               ";
				else {
					util->setColor(2);
					std::cout << "  SNAKE V3.0   ";
				}

			std::cout << '\n';
		}
		util->drawGameLine(width);
	}

	void returnToMenu() {
		util->setColor(2);
		std::cout << "\nPress ENTER to return to menu\n\n";

		Sleep(170);
		while (!GetAsyncKeyState(VK_RETURN));
		Sleep(170);
		drawMenu();
	}

	void showMaxScore() {
		system("cls");
		util->drawOneMenuLine();
		util->setColor(6);
		std::cout << "            Scores\n";
		util->setColor(4);
		std::cout << "     1. TheAncientOwl : 666\n";
		file.open("score.txt");
		if (!file.eof()) {
			int n;
			file >> n;
			file.get();
			for (int i = 1; i <= n; ++i) {
				char s[10001];
				file.getline(s, 10001);
				std::cout << "   " << s << '\n';
			}
			file.close();
		}

		util->drawOneMenuLine();
		returnToMenu();
	}

	void dealWithScore(int score) {
		return;
		file.open("score.txt");
		if (!file.eof()) {
			std::cout << "GOALA\n";
			file << 1 << '\n';
			util->setColor(4);
			std::cout << "Congratulations!  This is your first score!\n";
			util->setColor(2);
			std::cout << "Enter your nickname (max 40 characters)\n";
			char s[41];
			std::cin.getline(s, 41);
			file << s << '\n';
			file.close();
			return;
		}
		int n;
		file >> n;
	}
};


int main() {
	Snake* game = new Snake(30, 15);
	return 0;
}