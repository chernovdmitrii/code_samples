// Lab_7-1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab_7-1.h"

#define MAX_LOADSTRING 100
#define BUTTON_FILE 1 
#define BUTTON_ANIMATION 2 
#define BUTTON_CLEAR 3

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HBITMAP hBmp_water;
HBITMAP hBmp_fish;
bool button_animation = false; 
RECT rectWindow;
int count = 0;  
const int timerIDLocal = 11;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void CreateMFile();
void paintText(HDC);
void paintRectangle(HDC);
void paintEllipse(HDC);
void paintLine(HDC);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB71, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB71));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB71));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB71);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Laboratory Work no. 7, Chernov Dmitrii", WS_OVERLAPPEDWINDOW, 0, 0, 800, 536
       , nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    hBmp_water = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    hBmp_fish = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BUTTON_FILE:
            {
                CreateMFile();
                break; 
            }
            case BUTTON_ANIMATION:
            {
                if (!button_animation)
                {
                    button_animation = true; 
                    GetClientRect(hWnd, &rectWindow);
                    InvalidateRect(hWnd, &rectWindow, true);
                    count = 0; 
                }
                else
                {
                    button_animation = false; 
                    GetClientRect(hWnd, &rectWindow);
                    InvalidateRect(hWnd, &rectWindow, true);
                }
                break; 
            }
            case BUTTON_CLEAR:
            {
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                button_animation = false; 
                
                break;
            }
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            if (button_animation)
            {
                PAINTSTRUCT ps; 
                HDC hdc = BeginPaint(hWnd, &ps);
                HDC hdc_bmp = CreateCompatibleDC(hdc);

                SelectObject(hdc_bmp, hBmp_water);
                BitBlt(hdc, 0, 0, 800, 536, hdc_bmp, 0, 0, SRCCOPY);

                if (count <= 570)
                {
                    count += 10;
                    GetClientRect(hWnd, &rectWindow);
                    InvalidateRect(hWnd, &rectWindow, true);
                }
                else {
                    button_animation = false; 
                }
                SelectObject(hdc_bmp, hBmp_fish);
                BitBlt(hdc, count, 360, 200, 117, hdc_bmp, 0, 0, SRCCOPY);
                Sleep(50); 

                EndPaint(hWnd, &ps);
                ReleaseDC(hWnd, hdc);
                DeleteDC(hdc_bmp);

            }
            
        }
        break;
    case WM_CREATE: 
        AddControls(hWnd); 
        break; 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
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

void AddControls(HWND hWnd) {
    CreateWindowW(L"Button", L"File", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hWnd, (HMENU)BUTTON_FILE, NULL, NULL);
    CreateWindowW(L"Button", L"Animate File", WS_VISIBLE | WS_CHILD, 50, 90, 200, 30, hWnd, (HMENU)BUTTON_ANIMATION, NULL, NULL);
    CreateWindowW(L"Button", L"Clear Screen", WS_VISIBLE | WS_CHILD, 50, 130, 200, 30, hWnd, (HMENU)BUTTON_CLEAR, NULL, NULL);

}

void CreateMFile() {
    HDC hdc;
    hdc = CreateMetaFile(L"file.wmf");
    if (hdc != NULL) {
        paintText(hdc);
        paintRectangle(hdc);
        paintEllipse(hdc);
        paintLine(hdc);
    }
    CloseMetaFile(hdc);
}

void paintText(HDC hdc) {
    HFONT font = CreateFont(26, NULL, NULL, NULL, NULL, FALSE, FALSE, FALSE, ANSI_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Times New Roman");

    SetTextColor(hdc, (COLORREF)RGB(0, 0, 0));
    SelectObject(hdc, font);
    TextOut(hdc, 300, 50, L"Here are my figures: ", sizeof("Here are my figures: "));

    DeleteObject(font);
}

void paintRectangle(HDC hdc) {
    HPEN pen = CreatePen(PS_DOT, 1, RGB(rand() % 256, rand() % 256, rand() % 256));
    HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Rectangle(hdc, 300, 100, 500, 200);

    DeleteObject(pen);
    DeleteObject(brush);
}

void paintEllipse(HDC hdc) {
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(rand() % 256, rand() % 256, rand() % 256));
    HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Ellipse(hdc, 550, 100, 650, 200);

    DeleteObject(pen);
    DeleteObject(brush);

}

void paintLine(HDC hdc) {
    HPEN pen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 0));

    SelectObject(hdc, pen);
    MoveToEx(hdc, 700, 100, NULL);
    LineTo(hdc, 900, 200);

    DeleteObject(pen);
}