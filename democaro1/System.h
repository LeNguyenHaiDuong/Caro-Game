#pragma once
// các chức năng cho màn hình
void ScreenStartGame(int n); // Màn hình chính
void FixConsoleWindow(); // Hàm cố định màn hình 
void DrawBoard(int pSize); // Hàm vẽ bàn cờ caro
void PrintCaro(); // In ra màn hình logo của game
void Screen();
void Xwin(); // In ra dòng chữ X win
void Owin(); // In ra dòng chữ O win
void Tie(); // In ra dòng chữ Tie
void PrintScoreBoard(); // In ra các bản phụ 
// các hàm chức năng
void Play(); // Hàm điều khiển
void MoveRight(); // Di chuyển qua phải
void MoveLeft(); // Di chuyển qua trái
void MoveDown(); // Di chuyển xuống dưới
void MoveUp(); // Di chuyển lên trên
void GotoXY(int x, int y); // di chuyển tới toạ độ chỉ định
void Textcolor(int color); // Hàm màu sắc
// các cài đặt của game
void About(); // Thông tin của game
void Help(); // Hướng dẫn cách chơi
void Save(); // Lưu game
void Load(); // Tải game đã lưu
// các hàm cơ bản của game
void StartGame(); // màn hình khi chơi
void GabageCollect(); // dọn rác
void ResetData(); // khởi tạo dữ liệu gốc
void ExitGame(); // Thoát game
int AskContinue(); // hỏi người chơi có muốn tiếp tục không
// các hàm kiểm tra 
int checkwhowin(); // Kiểm tra theo hàng dọc, ngang, chéo
int TestBoard(); // Kiểm tra thắng thua
int CheckBoard(int pX, int pY); // đánh dấu vào bàn cờ
int demluotX(); // đếm số nước đi cuả X
int demluotO(); // đếm số nước đi của O
int soXthang(int n); // Số trận thắng của X
int soOthang(int n); // Số trận thắng của O
int ProcessFinish(int pWhoWin); // Xử lí màn hình khi có người thắng 









