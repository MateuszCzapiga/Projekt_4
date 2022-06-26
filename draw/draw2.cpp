// draw.cpp : Defines the entry point for the application.
//test

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <algorithm>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// buttons
HWND hwndButton;
void Jezdzenie();


std::vector<Point> data;
RECT drawArea1 = { 0, 0, 150, 200 };
RECT drawArea2 = { 50, 400, 650, 422 };
RECT winda = { 710, 70, 890, 720 };
RECT kolejka1 = { 610, 718, 690, 668 };
RECT kolejka2 = { 910, 590, 990, 540 };
RECT kolejka3 = { 610, 462, 690, 412 };
RECT kolejka4 = { 910, 334, 990, 284 };
RECT kolejka5 = { 610, 206, 690, 156 };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);
void Przerysuj_Winde(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea);

int col = 0;
int obecne_pietro = 1;
int podloga = 0;
int pietro_1 = 1;
int pietro_2 = 2;
int pietro_3 = 3;
int pietro_4 = 4;
int pietro_5 = 5;
struct informacje
{
	std::vector<int>osoby_w_windzie;

	std::vector<int>pietra_do_odwiedzenia;

	std::vector<std::vector<int>>osoby_na_pietrach;
};

informacje dane;



//void jezdzenie(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, informacje dane, int pietro_poczatkowe, int pietro_koncowe)
//{
//	bool czy_jechac_dalej = true;
//	int ile_osob_na_pietrach = 0;
//
//	for (int i = 1; i <= dane.osoby_na_pietrach.size(); i++)
//		for (int j = 0; j < dane.osoby_na_pietrach[i - 1].size(); j++)
//			ile_osob_na_pietrach += 1;
//
//	Sleep(1000);
//	dane.pietra_do_odwiedzenia.push_back(pietro_poczatkowe); // przy przycisku ustalane
//	dane.pietra_do_odwiedzenia.push_back(pietro_koncowe);
//	sort(dane.pietra_do_odwiedzenia.begin(), dane.pietra_do_odwiedzenia.end());
//
//	//if (ile_osob_na_pietrach !=)
//
//	while (!dane.pietra_do_odwiedzenia.empty() && czy_jechac_dalej)
//	{
//
//		Sleep(1000);
//		obecne_pietro = dane.pietra_do_odwiedzenia.front();
//
//		// usuniecie z listy do odwiedzenia
//		dane.pietra_do_odwiedzenia.erase(dane.pietra_do_odwiedzenia.begin());
//
//		// rysuje winde na oczekiwanym pietrze
//		Przerysuj_Winde(hWnd, hdc, ps, drawArea);
//	}
//}

void zbieranie_danych(informacje& dane, int pietro_poczatkowe, int pietro_koncowe)
{
	if (dane.osoby_na_pietrach.size() == 0)
		dane.osoby_na_pietrach.resize(5);
	Sleep(200);
	//for (int i = pietro_poczatkowe; i <= pietro_koncowe; i++)
	bool czy_wpisac = true;

	for (int i = 0; i < dane.pietra_do_odwiedzenia.size(); i++)
		if (dane.pietra_do_odwiedzenia[i] == pietro_poczatkowe)
			czy_wpisac = false;
	if (czy_wpisac)
		dane.pietra_do_odwiedzenia.push_back(pietro_poczatkowe);

	czy_wpisac = true;

	for (int i = 0; i < dane.pietra_do_odwiedzenia.size(); i++)
		if (dane.pietra_do_odwiedzenia[i] == pietro_koncowe)
			czy_wpisac = false;
	if (czy_wpisac)
		dane.pietra_do_odwiedzenia.push_back(pietro_koncowe);

	dane.osoby_na_pietrach[pietro_poczatkowe - 1].push_back(pietro_koncowe);

	//dane.pietra_do_odwiedzenia.push_back(pietro_poczatkowe);
	//dane.pietra_do_odwiedzenia.push_back(pietro_koncowe);

//	sort(dane.pietra_do_odwiedzenia.begin(), dane.pietra_do_odwiedzenia.end());
}

void przejazd(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, informacje& dane, int pietro_poczatkowe, int pietro_koncowe)
{
	if (!dane.pietra_do_odwiedzenia.empty())
	{
		Sleep(1000);
		obecne_pietro = dane.pietra_do_odwiedzenia.front();

		// usuniecie z listy do odwiedzenia
		dane.pietra_do_odwiedzenia.erase(dane.pietra_do_odwiedzenia.begin());

		// rysuje winde na oczekiwanym pietrze
		Przerysuj_Winde(hWnd, hdc, ps, drawArea);
	}
}



//void MyOnPaint(HDC hdc)
//{
//	Graphics graphics(hdc);
//	Pen pen(Color(255, 0, 0, 255));
//	Pen pen2(Color(255, 25*col, 0, 255));
//
//	for (int i = 1; i < 100; i++)
//		graphics.DrawLine(&pen2, data[i - 1].X, data[i - 1].Y, data[i].X, data[i].Y);
//
//	graphics.DrawRectangle(&pen, 50 + value, 400, 10, 20);
//}

void Rysuj_Winde(HDC hdc)
{
	Graphics graphics(hdc);
	Pen obramowanie(Color(255, 0, 0, 0));
	Pen pietro1(Color(255, 128, 255, 255));
	Pen pietro2(Color(255, 0, 255, 64));
	Pen pietro3(Color(255, 255, 0, 128));
	Pen pietro4(Color(255, 0, 0, 255));
	Pen pietro5(Color(255, 255, 255, 0));
	Pen zakres_windy(Color(255, 255, 0, 0));
	Pen winda(Color(255, 0, 0, 255));

	//obramowanie
	graphics.DrawLine(&obramowanie, 700, 50, 700, 750); // lewa linia
	graphics.DrawLine(&obramowanie, 900, 50, 900, 750); // prawa linia
	graphics.DrawLine(&obramowanie, 700, 50, 900, 50); // gora
	graphics.DrawLine(&obramowanie, 700, 750, 900, 750); // dol
	// pietra
	graphics.DrawLine(&pietro5, 700, 208, 600, 208); // 5.pietro
	graphics.DrawLine(&pietro5, 700, 207, 600, 207); // 5.pietro
	graphics.DrawLine(&pietro4, 900, 336, 1000, 336); // 4.pietro
	graphics.DrawLine(&pietro4, 900, 335, 1000, 335); // 4.pietro
	graphics.DrawLine(&pietro3, 700, 464, 600, 464); // 3.pietro
	graphics.DrawLine(&pietro3, 700, 463, 600, 463); // 3.pietro
	graphics.DrawLine(&pietro2, 900, 592, 1000, 592); // 2.pietro
	graphics.DrawLine(&pietro2, 900, 591, 1000, 591); // 2.pietro
	graphics.DrawLine(&pietro1, 700, 720, 600, 720); // 1.pietro
	graphics.DrawLine(&pietro1, 700, 719, 600, 719); // 1.pietro
	//zakres windy
	graphics.DrawLine(&zakres_windy, 710, 80, 890, 80); // gora
	graphics.DrawLine(&zakres_windy, 710, 720, 890, 720); // dol
	graphics.DrawLine(&zakres_windy, 710, 80, 710, 720); // lewa
	graphics.DrawLine(&zakres_windy, 890, 80, 890, 720); // prawa
	// winda 180X100
	graphics.DrawLine(&zakres_windy, 710, 720 + (obecne_pietro - 1) * (-128), 890, 720 + (obecne_pietro - 1) * (-128)); // dol
	graphics.DrawLine(&zakres_windy, 710, 620 + (obecne_pietro - 1) * (-128), 890, 620 + (obecne_pietro - 1) * (-128)); // gora
	//graphics.DrawLine(&winda, 710, 720 + obecne_pietro, 710, 620 + obecne_pietro); // lewa
	//graphics.DrawLine(&winda, 890, 720 + obecne_pietro, 890, 620 + obecne_pietro); // prawa
}

void rysuj_osobe(HDC& hdc, int poczatek, int cel, informacje dane, HWND hWnd, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	EndPaint(hWnd, &ps);
	hdc = BeginPaint(hWnd, &ps);
	int r, g, b;
	Graphics graphics(hdc);
	for (int i = 0; i < dane.osoby_na_pietrach[poczatek - 1].size(); i++)
	{

	switch (dane.osoby_na_pietrach[poczatek-1][i])
	{
	case 1:
		r = 128, g = 255, b = 255;
		break;
	case 2:
		r = 0, g = 255, b = 64;
		break;
	case 3:
		r = 255, g = 0, b = 128;
		break;
	case 4:
		r = 0, g = 0, b = 255;
		break;
	case 5:
		r = 255, g = 255, b = 0;
		break;
	default:
		break;
	}
	Pen pietro(Color(255, r, g, b));
	int przesuniecie = dane.osoby_na_pietrach[poczatek - 1][dane.osoby_na_pietrach[poczatek - 1].size()-1];
	switch (poczatek)
	{//RECT kolejka1 = { 610, 718, 690, 698 };
	/*	RECT kolejka1 = { 610, 718, 690, 698 };
		RECT kolejka2 = { 1010, 590, 1090, 570 };
		RECT kolejka3 = { 610, 462, 690, 442 };
		RECT kolejka4 = { 1010, 334, 1090, 314 };
		RECT kolejka5 = { 610, 206, 690, 186 };*/
		
	case 1:
		graphics.DrawLine(&pietro, 685 - i*10, 717, 685 - i * 10, 670); // 1.pietro
		break;
	case 2:
		graphics.DrawLine(&pietro, 915 + i * 10, 589, 915 + i * 10, 542); // 2.pietro
		break;
	case 3:
		graphics.DrawLine(&pietro, 685 - i * 10, 461, 685 - i * 10, 414); // 3.pietro
		break;
	case 4:
		graphics.DrawLine(&pietro, 915 + i * 10, 333, 915 + i * 10, 286); // 4.pietro
		break;
	case 5:
		graphics.DrawLine(&pietro, 685 - i * 10, 205, 685 - i * 10, 158); // 5.pietro
		break;
	default:
		break;
	}
	}
	EndPaint(hWnd, &ps);
}

void Przerysuj_Winde(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	EndPaint(hWnd, &ps);
	hdc = BeginPaint(hWnd, &ps);

	Rysuj_Winde(hdc);
	EndPaint(hWnd, &ps);
}
int szukanie_min_pietra(informacje dane)
{
	for (int i = 0; i < dane.osoby_na_pietrach.size(); i++)
	{
		if (!dane.osoby_na_pietrach[i].empty())
			return i + 1;
	}
	return 1;
}

int szukanie_max_pietra(informacje dane, int obecne_pietro)
{
	int max = -1;
	for (int i = 0; i < dane.osoby_na_pietrach[obecne_pietro].size(); i++)
	{
		if (dane.osoby_na_pietrach[obecne_pietro][i] > max)
			max = dane.osoby_na_pietrach[obecne_pietro][i];
	}
	return max;
}

void Jezdzenie (informacje &dane)
{
	int obecne_pietro = 0;
	while (!dane.osoby_na_pietrach.empty() && dane.osoby_w_windzie.empty())
	{
		int min_pietro = szukanie_min_pietra(dane);
		obecne_pietro = min_pietro;
		//przejazd();wizualny
		int max_pietro = szukanie_max_pietra(dane, obecne_pietro);
		for (int i = 0; i < dane.osoby_na_pietrach[obecne_pietro].size(); i++)
		{
			if (dane.osoby_na_pietrach[obecne_pietro][i] > obecne_pietro && dane.osoby_w_windzie.size()<7)
				dane.osoby_w_windzie.push_back(dane.osoby_na_pietrach[obecne_pietro][i]);
		}
		if (!dane.osoby_w_windzie.empty())
		{
			for (int j = obecne_pietro; j < max_pietro; j++)
			{
				//przejazd na j+1
				obecne_pietro = j + 1;
				max_pietro = szukanie_max_pietra(dane, obecne_pietro);
				for (int k = 0; k < dane.osoby_w_windzie.size(); k++)
				{
					if (dane.osoby_w_windzie[k] == obecne_pietro) //wysiadka
						dane.osoby_w_windzie.erase(dane.osoby_w_windzie.begin()+k, dane.osoby_w_windzie.begin() + k+1);
				}
				for (int i = 0; i < dane.osoby_na_pietrach[obecne_pietro].size(); i++)
				{//wsiadanko
					if (dane.osoby_na_pietrach[obecne_pietro][i] > obecne_pietro && dane.osoby_w_windzie.size() < 7)
						dane.osoby_w_windzie.push_back(dane.osoby_na_pietrach[obecne_pietro][i]);
				}

			}
		}
	}
}

void Pisz_1(HDC hdc, int przesuniecie)
{
	TextOut(hdc, 10 + przesuniecie, 10, TEXT("1"), strlen("1"));
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

	//hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	//	TEXT("Draw"),                  // the caption of the button
	//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	//	300, 60,                                  // the left and top co-ordinates
	//	80, 50,                              // width and height
	//	hWnd,                                 // parent window handle
	//	(HMENU)ID_BUTTON1,                   // the ID of your button
	//	hInstance,                            // the instance of your application
	//	NULL);                               // extra bits you dont really need

	//hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	//	TEXT("DrawAll"),                  // the caption of the button
	//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	//	300, 0,                                  // the left and top co-ordinates
	//	80, 50,                              // width and height
	//	hWnd,                                 // parent window handle
	//	(HMENU)ID_BUTTON2,                   // the ID of your button
	//	hInstance,                            // the instance of your application
	//	NULL);                               // extra bits you dont really need
//p1
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		400, 690,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_1_2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need          

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		430, 690,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_1_3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need    

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		460, 690,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_1_4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		490, 690,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_1_5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

//p2
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1080, 562,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_2_1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need          

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1110, 562,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_2_3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need    

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1140, 562,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_2_4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1170, 562,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_2_5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need  
//p3
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		400, 434,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_3_1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need          

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		430, 434,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_3_2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need    

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		460, 434,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_3_4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		490, 434,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_3_5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need  
//p4
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1080, 306,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_4_1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need          

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1110, 306,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_4_2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need    

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1140, 306,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_4_3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1170, 306,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_4_5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need  
//p5
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		400, 178,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_5_1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need          

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		430, 178,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_5_2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need    

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		460, 178,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_5_3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need   

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		490, 178,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_5_4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need 

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("START"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		770, 50,                                  // the left and top co-ordinates
		60, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_GO,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need 


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//hdc = BeginPaint(hWnd, &ps);
	int pietro_poczatkowe = 1, pietro_koncowe = 1;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_1_2:
			//hdc = BeginPaint(hWnd, &ps);
			zbieranie_danych(dane, 1, 2);
			rysuj_osobe(hdc, 1, 2, dane, hWnd, ps, &kolejka1);
			break;
		case ID_1_3:
			zbieranie_danych(dane, 1, 3);
			rysuj_osobe(hdc, 1, 3, dane, hWnd, ps, &kolejka1);
			break;
		case ID_1_4:
			zbieranie_danych(dane, 1, 4);
			rysuj_osobe(hdc, 1, 4, dane, hWnd, ps, &kolejka1);
			break;
		case ID_1_5:
			zbieranie_danych(dane, 1, 5);
			rysuj_osobe(hdc, 1, 5, dane, hWnd, ps, &kolejka1);
			break;
		case ID_2_1:
			zbieranie_danych(dane, 2, 1);
			rysuj_osobe(hdc, 2, 1, dane, hWnd, ps, &kolejka2);
			break;
		case ID_2_3:
			zbieranie_danych(dane, 2, 3);
			rysuj_osobe(hdc, 2, 3, dane, hWnd, ps, &kolejka2);
			break;
		case ID_2_4:
			zbieranie_danych(dane, 2, 4);
			rysuj_osobe(hdc, 2, 4, dane, hWnd, ps, &kolejka2);
			break;
		case ID_2_5:
			zbieranie_danych(dane, 2, 5);
			rysuj_osobe(hdc, 2, 5, dane, hWnd, ps, &kolejka2);
			break;
		case ID_3_1:
			zbieranie_danych(dane, 3, 1);
			rysuj_osobe(hdc, 3, 1, dane, hWnd, ps, &kolejka3);
			break;
		case ID_3_2:
			zbieranie_danych(dane, 3, 2);
			rysuj_osobe(hdc, 3, 2, dane, hWnd, ps, &kolejka3);
			break;
		case ID_3_4:
			zbieranie_danych(dane, 3, 4);
			rysuj_osobe(hdc, 3, 4, dane, hWnd, ps, &kolejka3);
			break;
		case ID_3_5:
			zbieranie_danych(dane, 3, 5);
			rysuj_osobe(hdc, 3, 5, dane, hWnd, ps, &kolejka3);
			break;
		case ID_4_1:
			zbieranie_danych(dane, 4, 1);
			rysuj_osobe(hdc, 4, 1, dane, hWnd, ps, &kolejka4);
			break;
		case ID_4_2:
			zbieranie_danych(dane, 4, 2);
			rysuj_osobe(hdc, 4, 2, dane, hWnd, ps, &kolejka4);
			break;
		case ID_4_3:
			zbieranie_danych(dane, 4, 3);
			rysuj_osobe(hdc, 4, 3, dane, hWnd, ps, &kolejka4);
			break;
		case ID_4_5:
			zbieranie_danych(dane, 4, 5);
			rysuj_osobe(hdc, 4, 5, dane, hWnd, ps, &kolejka4);
			break;
		case ID_5_1:
			zbieranie_danych(dane, 5, 1);
			rysuj_osobe(hdc, 5, 1, dane, hWnd, ps, &kolejka5);
			break;
		case ID_5_2:
			zbieranie_danych(dane, 5, 2);
			rysuj_osobe(hdc, 5, 2, dane, hWnd, ps, &kolejka5);
			break;
		case ID_5_3:
			zbieranie_danych(dane, 5, 3);
			rysuj_osobe(hdc, 5, 3, dane, hWnd, ps, &kolejka5);
			break;
		case ID_5_4:
			zbieranie_danych(dane, 5, 4);
			rysuj_osobe(hdc, 5, 4, dane, hWnd, ps, &kolejka5);
			break;
		case ID_GO:
			Jezdzenie(dane);

			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		Rysuj_Winde(hdc);



		//PAINTSTRUCT ps;
		//
		//for (int i = 1; i <= 4; i++)
		//{
		//	int przesuniecie = i * 10;
		//	Pisz_1(hdc, przesuniecie);
		//}
		////MessageBoxA(NULL, buffer, "Lesson1", MB_OK);



		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			//repaintWindow(hWnd, hdc, ps, &drawArea2);
			value++;
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	//while (!dane.pietra_do_odwiedzenia.empty())
	//	przejazd(hWnd, hdc, ps, &winda, dane, pietro_poczatkowe, pietro_koncowe);
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
