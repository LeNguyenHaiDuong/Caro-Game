#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<mmsystem.h>
#include<fstream>
#include"System.h"
using namespace std;
//Hang So
#define BOARD_SIZE 14 // kich thuoc ma tran ban co
#define LEFT 0        // Toa do trai
#define TOP 0         // Toa do phai
#define Black			0 // các loại màu
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15
#define defaultColor	7 
// Khai bao kieu du lieu
struct _POINT { int x, y, c; }; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE];//Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _left;
int _top;
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
//Hàm khởi tạo dữ liệu mặc định ban đầu cho ma trận bàn cờ (hàm nhóm Model)
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Hàm màu sắc cho trò chơi
void Textcolor(int color)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
} 
// In ra màn hình logo của game
void PrintCaro()
{
	int x = 25, y = 0;
	Textcolor(Yellow);
	GotoXY(x, y);				   cout << "oooooooooooooo";
	GotoXY(x - 3, y + 1);		cout << "oooooooooooooooo";
	GotoXY(x - 5, y + 2);    cout << "oooooooooooooooooo";
	GotoXY(x - 6, y + 3);   cout << "ooooooooooooooooooo";
	GotoXY(x - 7, y + 4);  cout << "ooooooo";
	GotoXY(x - 8, y + 5); cout << "ooooooo";
	GotoXY(x - 8, y + 6); cout << "ooooooo";
	GotoXY(x - 8, y + 7); cout << "ooooooo";
	GotoXY(x - 8, y + 8); cout << "ooooooo";
	GotoXY(x - 8, y + 9); cout << "ooooooo";
	GotoXY(x - 8, y + 10); cout << "ooooooo";
	GotoXY(x - 7, y + 11); cout << "ooooooo";
	GotoXY(x - 6, y + 12);  cout << "ooooooooooooooooooo";
	GotoXY(x - 5, y + 13);   cout << "oooooooooooooooooo";
	GotoXY(x - 3, y + 14);		cout << "oooooooooooooooo";
	GotoXY(x, y + 15);			   cout << "ooooooooooooo";
	Textcolor(Yellow);
	GotoXY(x - 4 + 22, y + 4);			    cout << "ooooooooooo";
	GotoXY(x - 4 + 22 - 2, y + 5);	      cout << "ooooooooooooooo";
	GotoXY(x - 4 + 22 - 3, y + 6);	     cout << "ooooooooooooooooo";
	GotoXY(x - 4 + 22 - 3, y + 7);		 cout << "ooooooooooooooooo";
	GotoXY(x - 4 + 22 - 3, y + 8);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 9);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 10);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 11);		 cout << "ooooooooooooooooo";
	GotoXY(x - 4 + 22 - 3, y + 12);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 13);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 14);		 cout << "oooooo     oooooo";
	GotoXY(x - 4 + 22 - 3, y + 15);		 cout << "oooooo     oooooo";
	Textcolor(Yellow);

	GotoXY(x + 33, y + 4);			cout << "ooooo   ooooooooo";
	GotoXY(x + 33, y + 5);			cout << "oooooooooooooooooo";
	GotoXY(x + 33, y + 6);			cout << "ooooooooooooooooooo";
	GotoXY(x + 33, y + 7);			cout << "oooooooooooooooooooo";
	GotoXY(x + 1 + 33, y + 8);		 cout << "ooooooo     ooooooo";
	GotoXY(x + 1 + 33, y + 9);		 cout << "ooooooo     ooooooo";
	GotoXY(x + 1 + 33, y + 10);		 cout << "ooooooo";
	GotoXY(x + 1 + 33, y + 11);		 cout << "ooooooo";
	GotoXY(x + 1 + 33, y + 12);		 cout << "ooooooo";
	GotoXY(x + 1 + 33, y + 13);		 cout << "ooooooo";
	GotoXY(x + 1 + 33, y + 14);		 cout << "ooooooo";
	GotoXY(x + 1 + 33, y + 15);		 cout << "ooooooo";
	Textcolor(Yellow);
	GotoXY(x + 57, y + 4);					cout << "ooooooooooo";
	GotoXY(x + 57 - 2, y + 5);			  cout << "ooooooooooooooo";
	GotoXY(x + 57 - 3, y + 6);			 cout << "ooooooooooooooooo";
	GotoXY(x + 57 - 3, y + 7);			 cout << "ooooooooooooooooo";
	GotoXY(x + 57 - 3, y + 8);			 cout << "oooooo     oooooo";
	GotoXY(x + 57 - 3, y + 9);			 cout << "oooooo     oooooo";
	GotoXY(x + 57 - 3, y + 10);		     cout << "oooooo     oooooo";
	GotoXY(x + 57 - 3, y + 11);		     cout << "oooooo     oooooo";
	GotoXY(x + 57 - 3, y + 12);		     cout << "ooooooooooooooooo";
	GotoXY(x + 57 - 3, y + 13);		     cout << "ooooooooooooooooo";
	GotoXY(x + 57 - 2, y + 14);		      cout << "ooooooooooooooo";
	GotoXY(x + 57, y + 15);				    cout << "ooooooooooo";
	Textcolor(defaultColor);

}
// Các cài đặt chính
void About()
{
	system("cls");
	PrintCaro();
	Textcolor(Cyan);
	GotoXY(60, 18);
	cout << "ABOUT";
	GotoXY(50, 21);
	cout << "DO AN GAME CARO - LOP 20CTT3 - HCMUS" << endl;
	GotoXY(50, 22);
	cout << "-> Thanh vien: 20120348 - Pham Tran Gia Phu" << endl;
	GotoXY(50, 23);
	cout << "               20120460 - Nguyen Le Hai Duong" << endl;
	GotoXY(50, 24);
	cout << "               20120492 - Do Dang Huy" << endl;
	GotoXY(50, 25);    
	cout << "               20120438 - Dao Van Canh" << endl;
	GotoXY(50, 26);
	cout << "               20120397 - Bui Quang Tung" << endl;
	GotoXY(50, 27);
	cout << "-> GV huong dan : Truong Toan Thinh " << endl;
	GotoXY(50, 29);
	cout << "-> Chuc moi nguoi choi game vui ve !!" << endl;
	GotoXY(60, 30);
	cout << "BACK";
	char command = ' ';
	command = _getch();
	system("cls");
}
void Help()
{
	system("cls");
	PrintCaro();
	Textcolor(Cyan);
	GotoXY(60, 18);
	cout << "HELP";
	GotoXY(50, 21);
	cout << "HUONG DAN" << endl;
	GotoXY(30, 22);
	cout << "1. Ban co gom 14x14 o vuong." << endl;
	GotoXY(30, 23);
	cout << "2. Su dung cac phim W A S D de di chuyen va Enter de danh." << endl;
	GotoXY(30, 24);
	cout << "3. Luat choi cu du 5 quan co X hoac O theo hang ngang, doc, cheo se chien thang." << endl;
	GotoXY(30, 26);
	cout << "-> Chuc moi nguoi choi game vui ve !!" << endl;
	GotoXY(60, 30);
	cout << "BACK";
	char command = ' ';
	command = _getch();
	system("cls");
}
void Screen()
{
	int check = 1;
	while (check < 20)
	{
		PrintCaro();
		Sleep(100);
		check++;
	}
}
//Hàm chung
void ResetData() {
	for (int i = 0; i <= BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE; j++) {
			_A[i][j].x = 4 * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
		}
	}

	_TURN = true; _COMMAND = -1; // Gán lượt và phím mặc định
	_X = _A[0][0].x; _Y = _A[0][0].y; // Thiết lập lại tọa độ hiện hành ban đầu
}
// vẽ bàn cờ
void DrawBoard(int pSize)
{
	cout << char(218);
	int i, j;
	for (i = 0; i < pSize - 1; i++)
		cout << char(196) << char(196) << char(196) << char(194);
	cout << char(196) << char(196) << char(196) << char(191) << endl;

	for (i = 0; i < pSize - 1; i++)
	{
		for (j = 0; j < pSize + 1; j++)
			cout << char(179) << "   ";
		cout << endl << char(195);
		for (j = 0; j < pSize - 1; j++)
			cout << char(196) << char(196) << char(196) << char(197);
		cout << char(196) << char(196) << char(196) << char(180) << endl;
	}
	for (j = 0; j < pSize + 1; j++)
		cout << char(179) << "   ";
	cout << endl << char(192);
	for (i = 0; i < pSize - 1; i++)
		cout << char(196) << char(196) << char(196) << char(193);
	cout << char(196) << char(196) << char(196) << char(217);

}
// tính số trận thắng
int soXthang(int n) {
	static int Xthang = -1;
	if (n == 1) { Xthang++; }
	return Xthang;
}
int soOthang(int n) {
	static int Othang = -1;
	if (n == 0) { Othang = Othang + 1; }
	return Othang;
}
// Bảng thông tin
void PrintScoreBoard()
{
	//Bang 2
	for (int i = 0; i < 8; i++) {
		GotoXY(BOARD_SIZE * 4 + 25, 11 + i);
		cout << char(219);
	}
	for (int i = 0; i < 8; i++) {
		GotoXY(BOARD_SIZE * 4 + 61, 11 + i);
		cout << char(219);
	}
	GotoXY(BOARD_SIZE * 4 + 25, 10);
	for (int i = 0; i < 37; i++) {
		cout << char(220);
	}
	GotoXY(BOARD_SIZE * 4 + 25, 11 + 8);
	for (int i = 0; i < 37; i++) {
		cout << char(223);
	}
	// Bang 3
	for (int i = 0; i < 8; i++) {
		GotoXY(BOARD_SIZE * 4 + 25, BOARD_SIZE * 2 - i);
		cout << char(219);
	}
	for (int i = 0; i < 8; i++) {
		Sleep(1);
		GotoXY(BOARD_SIZE * 4 + 61, BOARD_SIZE * 2 - i);
		cout << char(219);
	}
	GotoXY(BOARD_SIZE * 4 + 25, BOARD_SIZE * 2);
	for (int i = 0; i < 37; i++) {
		Sleep(1);
		cout << char(223);
	}
	GotoXY(BOARD_SIZE * 4 + 25, 20);
	for (int i = 0; i < 37; i++) {
		Sleep(1);
		cout << char(220);
	}
	// Bang 1
	for (int i = 0; i < 8; i++) {
		Sleep(1);
		GotoXY(BOARD_SIZE * 4 + 25, i + 1);
		cout << char(219);
	}
	for (int i = 0; i < 8; i++) {
		Sleep(1);
		GotoXY(BOARD_SIZE * 4 + 61, i + 1);
		cout << char(219);
	}
	GotoXY(BOARD_SIZE * 4 + 25, 0);
	for (int i = 0; i < 37; i++) {
		Sleep(1);
		cout << char(220);
	}
	GotoXY(BOARD_SIZE * 4 + 25, 8 + 1);
	for (int i = 0; i < 37; i++) {
		Sleep(1);
		cout << char(223);
	}
	//
	GotoXY(BOARD_SIZE * 4 + 40, 2);
	cout << "PLAYER 1";
	GotoXY(BOARD_SIZE * 4 + 30, 4);
	cout << "So quan X: ";
	GotoXY(BOARD_SIZE * 4 + 30, 5);
	cout << "So tran da thang : " << (soXthang(0) + 1);
	//
	GotoXY(BOARD_SIZE * 4 + 40, 12);
	cout << "PLAYER 2";
	GotoXY(BOARD_SIZE * 4 + 30, 14);
	cout << "So quan O: ";
	GotoXY(BOARD_SIZE * 4 + 30, 15);
	cout << "So tran da thang : " << (soOthang(1) + 1) / 2;
	//
	GotoXY(BOARD_SIZE * 4 + 37, 22);
	Textcolor(Red);
	cout << "DEN LUOT X";
	Textcolor(7);
	GotoXY(BOARD_SIZE * 4 + 30, 23);
	cout << " W A S D : Move ";
	GotoXY(BOARD_SIZE * 4 + 30, 24);
	cout << " L : Save Game ";
	GotoXY(BOARD_SIZE * 4 + 30, 25);
	cout << " T : Load Game ";
	GotoXY(BOARD_SIZE * 4 + 30, 26);
	cout << " ESC : BACK ";
	GotoXY(0, 0);
} // IN BANG DIEM
void StartGame() {
	system("cls");
	ResetData(); // Khởi tạo dữ liệu gốc
	PrintScoreBoard();
	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
}
//Hàm dọn dẹp tài nguyên (hàm nhóm Model)
void GabageCollect()
{
	// Dọn dẹp tài nguyên nếu có khai báo con trỏ
}
// Xử lí thắng thua hoà
void Xwin() {
	int x = 10, y = 10;
	Textcolor(Red);
	GotoXY(x, y);        cout << "  oooooooo          oooooooo";
	GotoXY(x + 4, y + 1);	  cout << "oooooooo      ooooooo";
	GotoXY(x + 5, y + 2);       cout << "oooooooo   ooooooo ";
	GotoXY(x + 6, y + 3);        cout << " oooooooooooooo";
	GotoXY(x + 6, y + 4);          cout << "ooooooo oooooooo";
	GotoXY(x + 3, y + 5);        cout << "oooooooo     oooooooo";
	GotoXY(x + 1, y + 6);      cout << "oooooooo          ooooooo";
	Textcolor(Cyan);
	GotoXY(x + 35, y);                cout << "ooooooo             oooooo";
	GotoXY(x + 35 + 1, y + 1);          cout << "ooooooo     o     oooooo";
	GotoXY(x + 35 + 3, y + 2);           cout << "ooooooo  ooo  ooooooo";
	GotoXY(x + 35 + 4, y + 3);            cout << "ooooooooooooooooooo";
	GotoXY(x + 35 + 5, y + 4);             cout << "oooooooo oooooooo";
	GotoXY(x + 35 + 6, y + 5);              cout << "oooooo   oooooo";
	GotoXY(x + 35 + 7, y + 6);               cout << "oooo     oooo";
	Textcolor(Cyan);
	GotoXY(x + 65, y);         cout << "oooooo";
	GotoXY(x + 65, y + 1);     cout << "oooooo";
	GotoXY(x + 65, y + 2);     cout << "oooooo";
	GotoXY(x + 65, y + 3);     cout << "oooooo";
	GotoXY(x + 65, y + 4);     cout << "oooooo";
	GotoXY(x + 65, y + 5);     cout << "oooooo";
	GotoXY(x + 65, y + 6);     cout << "oooooo";
	Textcolor(Cyan);
	GotoXY(x + 75, y);         cout << "ooooo        ooooo";
	GotoXY(x + 75, y + 1);     cout << "ooooooo      ooooo";
	GotoXY(x + 75, y + 2);     cout << "ooooooooo    ooooo";
	GotoXY(x + 75, y + 3);     cout << "oooooooooooooooooo";
	GotoXY(x + 75, y + 4);     cout << "ooooo     oooooooo";
	GotoXY(x + 75, y + 5);     cout << "ooooo       oooooo";
	GotoXY(x + 75, y + 6);     cout << "ooooo        ooooo";
	Textcolor(defaultColor);
}
void Owin() {
	int x = 10, y = 10;
	Textcolor(Red);
	GotoXY(x + 3, y);             cout << " oooooooooooooo";
	GotoXY(x + 1, y + 1);      cout << " oooooooooooooooooo";
	GotoXY(x, y + 2);          cout << " ooooo          ooooo";
	GotoXY(x, y + 3);          cout << " ooooo          ooooo";
	GotoXY(x, y + 4);          cout << " ooooo          ooooo";
	GotoXY(x + 1, y + 5);      cout << " oooooooooooooooooo";
	GotoXY(x + 3, y + 6);          cout << "ooooooooooooooo";
	Textcolor(Cyan);
	GotoXY(x + 35, y);                cout << "ooooooo             oooooo";
	GotoXY(x + 35 + 1, y + 1);          cout << "ooooooo     o     oooooo";
	GotoXY(x + 35 + 3, y + 2);           cout << "ooooooo  ooo  ooooooo";
	GotoXY(x + 35 + 4, y + 3);            cout << "ooooooooooooooooooo";
	GotoXY(x + 35 + 5, y + 4);             cout << "oooooooo oooooooo";
	GotoXY(x + 35 + 6, y + 5);              cout << "oooooo   oooooo";
	GotoXY(x + 35 + 7, y + 6);               cout << "oooo     oooo";
	Textcolor(Cyan);
	GotoXY(x + 65, y);         cout << "oooooo";
	GotoXY(x + 65, y + 1);     cout << "oooooo";
	GotoXY(x + 65, y + 2);     cout << "oooooo";
	GotoXY(x + 65, y + 3);     cout << "oooooo";
	GotoXY(x + 65, y + 4);     cout << "oooooo";
	GotoXY(x + 65, y + 5);     cout << "oooooo";
	GotoXY(x + 65, y + 6);     cout << "oooooo";
	Textcolor(Cyan);
	GotoXY(x + 75, y);         cout << "ooooo        ooooo";
	GotoXY(x + 75, y + 1);     cout << "ooooooo      ooooo";
	GotoXY(x + 75, y + 2);     cout << "ooooooooo    ooooo";
	GotoXY(x + 75, y + 3);     cout << "oooooooooooooooooo";
	GotoXY(x + 75, y + 4);     cout << "ooooo     oooooooo";
	GotoXY(x + 75, y + 5);     cout << "ooooo       oooooo";
	GotoXY(x + 75, y + 6);     cout << "ooooo        ooooo";
	Textcolor(defaultColor);
}
void Tie() {
	int x = 30, y = 10;
	Textcolor(Cyan);
	GotoXY(x, y);          cout << "oooooooooooooooooo";
	GotoXY(x, y + 1);      cout << "oooooooooooooooooo";
	GotoXY(x + 6, y + 2);        cout << "oooooo";
	GotoXY(x + 6, y + 3);        cout << "oooooo";
	GotoXY(x + 6, y + 4);        cout << "oooooo";
	GotoXY(x + 6, y + 5);        cout << "oooooo";
	GotoXY(x + 6, y + 6);        cout << "oooooo";
	GotoXY(x + 6, y + 7);        cout << "oooooo";
	Textcolor(Cyan);
	GotoXY(x + 22, y);         cout << "oooooo";
	GotoXY(x + 22, y + 1);     cout << "oooooo";
	GotoXY(x + 22, y + 2);     cout << "oooooo";
	GotoXY(x + 22, y + 3);     cout << "oooooo";
	GotoXY(x + 22, y + 4);     cout << "oooooo";
	GotoXY(x + 22, y + 5);     cout << "oooooo";
	GotoXY(x + 22, y + 6);     cout << "oooooo";
	GotoXY(x + 22, y + 7);     cout << "oooooo";
	Textcolor(Cyan);
	GotoXY(x + 32, y);         cout << "oooooooooooooooooo";
	GotoXY(x + 32, y + 1);     cout << "oooooooooooooooooo";
	GotoXY(x + 32, y + 2);     cout << "oooooo";
	GotoXY(x + 32, y + 3);     cout << "oooooooooooooooooo";
	GotoXY(x + 32, y + 4);     cout << "oooooooooooooooooo";
	GotoXY(x + 32, y + 5);     cout << "oooooo";
	GotoXY(x + 32, y + 6);     cout << "oooooooooooooooooo";
	GotoXY(x + 32, y + 7);     cout << "oooooooooooooooooo";
	Textcolor(defaultColor);
}
//Hàm thoát game (hàm nhóm Control)
void ExitGame() {
	system("cls");
	GabageCollect();
	//Có thể lưu game trước khi exit
}
int ProcessFinish(int pWhoWin) {
	switch (pWhoWin) {
	case -1:
		system("cls");
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Xwin();
		break;
	case 1:
		system("cls");
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Owin();
		break;
	case 0:
		system("cls");
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Tie();
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra
	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}
int AskContinue() {
	GotoXY(40,20 );
	printf("Ban co muon tiep tuc khong [Y/N] ? ");
	return toupper(_getch());
}
// Hàm di chuyển
void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += 4;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
}
// Hàm kiểm tra 
int checkwhowin() {//check nguoi thang return 1:X thang,return 0:O thang
	int countngang = 0, countdoc = 0, countcheo13 = 0, countcheo24 = 0, XWin = -1, OWin = -1;
	for (int i = 0; i < BOARD_SIZE; i++) {//check ngang
		for (int j = 0; j < (BOARD_SIZE - 4); j++) {
			countngang = _A[i][j].c + _A[i][j + 1].c + _A[i][j + 2].c + _A[i][j + 3].c + _A[i][j + 4].c;
			if (countngang == -5) { XWin = 1; }
			if (countngang == 5) { OWin = 1; }
		}
	}
	for (int i = 0; i < (BOARD_SIZE - 4); i++) {//check doc
		for (int j = 0; j < BOARD_SIZE; j++) {
			countdoc = _A[i][j].c + _A[i + 1][j].c + _A[i + 2][j].c + _A[i + 3][j].c + _A[i + 4][j].c;
			if (countdoc == -5) { XWin = 1; }
			if (countdoc == 5) { OWin = 1; }
		}
	}
	for (int i = 0; i < (BOARD_SIZE - 4); i++) {//check cheo 13
		for (int j = 4; j < BOARD_SIZE; j++) {
			countcheo13 = _A[i][j].c + _A[i + 1][j - 1].c + _A[i + 2][j - 2].c + _A[i + 3][j - 3].c + _A[i + 4][j - 4].c;
			if (countcheo13 == -5) { XWin = 1; }
			if (countcheo13 == 5) { OWin = 1; }
		}
	}
	for (int i = 0; i < (BOARD_SIZE - 4); i++) {//check cheo 24
		for (int j = 0; j < (BOARD_SIZE - 4); j++) {
			countcheo24 = _A[i][j].c + _A[i + 1][j + 1].c + _A[i + 2][j + 2].c + _A[i + 3][j + 3].c + _A[i + 4][j + 4].c;
			if (countcheo24 == -5) { XWin = 1; }
			if (countcheo24 == 5) { OWin = 1; }
		}
	}
	if (XWin == 1) { soXthang(1); return 1; }
	else if (OWin == 1) { soOthang(0); return 0; }
	else { return -1; }
}
int TestBoard()
{
	int countnoblank = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0) countnoblank++;
			// 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
		}
	}
	if (countnoblank == (BOARD_SIZE * BOARD_SIZE)) return 0; // Hòa
	else {
		if (checkwhowin() == 1) { return -1; }
		if (checkwhowin() == 0) { return 1; }
		else { return 2; }
	}
}
int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1;// Nếu lượt hiện hành là true thì c = -1
				else _A[i][j].c = 1;// Nếu lượt hiện hành là false thì c = 1
				return _A[i][j].c;
			}
		}
	}
	return 0;
}
// Đếm số lượt X Y đã đánh
int demluotX() {
	int demX = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == -1) { demX = demX + 1; }
			// 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
			
		}
	}
	
	GotoXY(BOARD_SIZE * 4 + 42, 4);
	cout << demX;
	return 2;

}
int demluotO()
{
	int demO = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == 1) demO++;
			// 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
			
		}
	}
	
	GotoXY(BOARD_SIZE * 4 + 42, 14);
	cout << demO;
	return 3;


}
// Hàm lưu trũ và tải game
void Save() {
	system("cls");
	string filename, name, t;
	GotoXY(53, 16); cout << " ";
	GotoXY(53, 16);
	cout << "ENTER THE FILE NAME: ";
	cin >> filename;
	GotoXY(53, 16); cout << " ";
	ofstream fileOutput(filename + ".txt");
	fileOutput << _TURN << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			fileOutput << _A[i][j].c << " ";
		}
		fileOutput << endl;
	}
	ifstream fileInput("filesave.txt");

	fstream fs;
	fs.open("filesave.txt");
	fs << t + filename;
	fs.close();
	system("cls");
	ScreenStartGame(99);
}
void Load() {
	string filename, name;
	GotoXY(40, 10);
	ifstream fileIntput("filesave.txt");
	system("cls");
	PrintCaro();
	GotoXY(45, 20);
	cout << "Nhap ten file muon load: ";
	cin >> filename;
	system("cls");
	StartGame();
	ifstream fileInput(filename + ".txt");
	fileInput >> _TURN;
	while (!fileInput.eof()) {


		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				fileInput >> _A[i][j].c;
				GotoXY(_A[i][j].x, _A[i][j].y);
				if (_A[i][j].c == 1) {
					Textcolor(9); cout << "O";
				}
				else if (_A[i][j].c == -1) {
					Textcolor(12); cout << "X";
				}
			}
		}
	}
}
// Hàm điều khiển
void Play() {
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			system("cls");
			ScreenStartGame(99);
			return;
		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 72) MoveUp();
			else if (_COMMAND == 80) MoveDown();
			else if (_COMMAND == 75) MoveLeft();
			else if (_COMMAND == 77) MoveRight();
			else if (_COMMAND == 'L') Save();
			else if (_COMMAND == 'T') Load();
			else if (_COMMAND == 13) {// Người dùng đánh dấu trên màn hình bàn cờ
				switch (CheckBoard(_X, _Y)) {
				case -1:
					PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Textcolor(Red);
					printf("X");
					demluotX();
					GotoXY(BOARD_SIZE * 4 + 37, 22);
					Textcolor(Blue);
					cout << "DEN LUOT O";
					break;
				case 1:
					PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Textcolor(Blue);
					printf("O");
					demluotO();
					GotoXY(BOARD_SIZE * 4 + 37, 22);
					Textcolor(Red);
					cout << "DEN LUOT X";
					break;
				case 0: validEnter = false; // Khi đánh vào ô đã đánh rồi
				}
				// Tiếp theo là kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (validEnter == true) {
					switch (ProcessFinish(TestBoard())) {
					case -1: case 1: case 0:
						if (AskContinue() != 'Y' && AskContinue() != 'y') {
							PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME | SND_ASYNC);
							system("cls");
							ScreenStartGame(99);
						}
						else 
							PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME | SND_ASYNC);
							StartGame();
					}
				}
				validEnter = true; // Mở khóa
			}
		}
	}
}
// Màn hình chính
void ScreenStartGame(int n)
{

	int x = 50, y = 20;
	int i;
	char s[30] = " ";
	int check = 1;
	Textcolor(Red);
	GotoXY(50, 20); cout << "Play";
	Textcolor(7);
	GotoXY(50, 21); cout << "Load Game";
	GotoXY(50, 22); cout << "Help";
	GotoXY(50, 23); cout << "About";
	GotoXY(50, 24); cout << "Exit";
	GotoXY(50, 27); cout << "....... W - S : Move ( Off Unikey - Off Caps Lock ) ";
	GotoXY(50, 28); cout << "....... Enter : Select ";
	if (n == 100)
	{
		PlaySound(TEXT("nhacnen1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Screen();
		PrintCaro();
	}
	else
		PrintCaro();

	while (check)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (y > 20)
				{
					y--;
					GotoXY(x, y);
				}
				if (y == 20)
				{
					Textcolor(Red);
					GotoXY(50, 20); cout << "Play";
					Textcolor(7);
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 21)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					Textcolor(Red);
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(7);
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 22)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(Red);
					GotoXY(50, 22); cout << "Help";
					Textcolor(7);
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 23)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 23); cout << "About";
					Textcolor(7);
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 24)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 24); cout << "Exit";
				}
				break;
			case 72:

				if (y > 20)
				{
					y--;
					GotoXY(x, y);
				}
				if (y == 20)
				{
					Textcolor(Red);
					GotoXY(50, 20); cout << "Play";
					Textcolor(7);
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 21)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					Textcolor(Red);
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(7);
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 22)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(Red);
					GotoXY(50, 22); cout << "Help";
					Textcolor(7);
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 23)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 23); cout << "About";
					Textcolor(7);
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 24)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 24); cout << "Exit";
				}
				break;
			case 80:
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (y < 24)
				{
					y++;
					GotoXY(x, y);
				}
				if (y == 20)
				{
					Textcolor(Red);
					GotoXY(50, 20); cout << "Play";
					Textcolor(7);
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 21)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					Textcolor(Red);
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(7);
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 22)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(Red);
					GotoXY(50, 22); cout << "Help";
					Textcolor(7);
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 23)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 23); cout << "About";
					Textcolor(7);
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 24)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					Textcolor(Red);
					GotoXY(50, 24); cout << "Exit";
				}
				break;
			case 's':
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (y < 24)
				{
					y++;
					GotoXY(x, y);
				}
				if (y == 20)
				{
					Textcolor(Red);
					GotoXY(50, 20); cout << "Play";
					Textcolor(7);
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 21)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					Textcolor(Red);
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(7);
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 22)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					Textcolor(Red);
					GotoXY(50, 22); cout << "Help";
					Textcolor(7);
					GotoXY(50, 23); cout << "About";
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 23)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					Textcolor(Red);
					GotoXY(50, 23); cout << "About";
					Textcolor(7);
					GotoXY(50, 24); cout << "Exit";
				}
				if (y == 24)
				{
					Textcolor(7);
					GotoXY(50, 20); cout << "Play";
					GotoXY(50, 21); cout << "Load Game";
					GotoXY(50, 22); cout << "Help";
					GotoXY(50, 23); cout << "About";
					Textcolor(Red);
					GotoXY(50, 24); cout << "Exit";
				}
				break;
			case 13:
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (y == 20)
				{
					StartGame();
					Play();
				}
				if (y == 21)
				{
					
					Load();
					Play();
				}
				if (y == 22)
				{
					Help();
					ScreenStartGame(99);
				}
				if (y == 23)
				{
					About();
					ScreenStartGame(99);
				}
				if (y == 24)
				{
					exit(0);
				}
				break;
			}
		}
	}

}

