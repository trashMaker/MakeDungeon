#include <Windows.h>
#include <cstdio>
#include <locale.h> 
#define APP_NAME TEXT("Game")
#define FIELD_WIDTH 20
#define FIELD_HEIGHT 20

#define BLOCK_SIZE 24
#define WND_WIDTH BLOCK_SIZE * FIELD_WIDTH
#define  WND_HEIGHT BLOCK_SIZE * FIELD_HEIGHT

/*アプリケーションウィンドウのハンドル*/
HWND hMainWindow = NULL;
HINSTANCE hThisInstance;

HDC hMemDC;
HBITMAP hBitMap;

LRESULT CALLBACK WindowProc(
	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
	){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (uMsg){
	case WM_DESTROY:

		DeleteObject(hBitMap);
		DeleteObject(hMemDC);

		PostQuitMessage(0);
		return 0;
	case WM_CREATE:

		hdc = GetDC(hWnd);
		//stage
		hMemDC = CreateCompatibleDC(hdc);
		hBitMap = CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT);
		SelectObject(hMemDC, hBitMap);

		ReleaseDC(hWnd, hdc);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow){

	setlocale(LC_ALL, "JPN");            //ロケール（地域言語）を日本語でセット

	WNDCLASS wc;
	MSG msg;

	AllocConsole(); //コンソール作成
	freopen("CONOUT$", "w", stdout); //標準出力をコンソールにする
	freopen("CONIN$", "r", stdin);   //標準入力をコンソールにする

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APP_NAME;
	/*ウィンドウクラスの作成が失敗したときの処理*/
	if (!RegisterClass(&wc))return 0;

	//CLIENT WINDOWサイズを設定
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = WND_WIDTH;
	r.bottom = WND_HEIGHT;
	//ウィンドウの
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION, FALSE);

	int CLIENT_WIDTH = (GetSystemMetrics(SM_CXFULLSCREEN) - (r.right - r.left)) / 2;//Width
	int CLIENT_HEIGHT = (GetSystemMetrics(SM_CYFULLSCREEN) - (r.bottom - r.top)) / 2;//Height

	int WINDOW_WIDTH = r.right - r.left;    //幅
	int WINDOW_HIEGHT = r.bottom - r.top;    //高さ


	hMainWindow = CreateWindow(
		APP_NAME, APP_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CLIENT_WIDTH, CLIENT_HEIGHT,
		WINDOW_WIDTH, WINDOW_HIEGHT,
		NULL, NULL, hInstance, NULL
		);

	if (hMainWindow == NULL){
		return 0;
	}
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

