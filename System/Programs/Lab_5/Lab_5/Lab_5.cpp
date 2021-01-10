// Lab_5.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab_5.h"
#include "math.h"

#define MAX_LOADSTRING 100
#define BUTTON_FIGURES 1
#define BUTTON_FLAG_CLIENT 2 
#define BUTTON_FLAG_WHOLE 3
#define BUTTON_FLAG_DESK 4
#define BUTTON_CIRCLE_LOCAL 5 
#define BUTTON_CIRCLE_CSH 6 
#define BUTTON_CIRCLE_DESK 7 
#define BUTTON_CIRCLE_CANCEL 8 
#define BUTTON_PAINTER 9
#define BUTTON_COLOR_RED 10 
#define BUTTON_COLOR_GREEN 11 
#define BUTTON_COLOR_BLUE 13 

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hButtonFigures; 
bool buttonFlag_1; 
HDC hDesktop; 

HWND hButtonFlagClient;
HWND hButtonFlagWhole;
HWND hButtonFlagDesk;
bool buttonFlag_2;
bool buttonFlag_3;
bool buttonFlag_4;

HWND hButtonCircleLocal; 
HWND hButtonCircleCSH;
HWND hButtonCircleDesk;
HWND hButtonUndo;
bool buttonFlag_5 = false;
bool buttonFlag_6 = false;
bool buttonFlag_7 = false;
const int timerIDLocal = 11;
const int timerIDCSH = 12;
const int timerIDesk = 1;
RECT circleLocal = { 400, 200, 490, 290 };
RECT circleCSH = { 400, 200, 490, 290 };
RECT circleDesk = { 400, 200, 490, 290 };
double countLocal = 0.0; 
double countCSH = 0.0;
double countDesk = 0.0;
HWND hWndCSH = FindWindow(0, L"My application");
HWND hWndDesk = GetDesktopWindow();
HDC hdcCSH; 
HDC hdcDesk;
RECT rectWindow;
RECT rectDesk;
RECT rectCSH; 

HWND hButtonPainter; 
HWND hButtonRed; 
HWND hButtonBlue; 
HWND hButtonGreen; 
bool buttonFlag_8 = false; 
COLORREF brushColor = (COLORREF)RGB(0, 0, 0); 
bool colorRed = false; 
bool colorBlue = false; 
bool colorGreen = false; 
RECT rectPaint = { 260, 50, 960, 520 }; 
HPEN penGlobal; 
bool drawing; 
POINT pBegin; 
POINT pEnd; 
POINT pTemp; 

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//Common
void AddControls(HWND);
// For Task 1 
COLORREF averageDesktopColor(); 
void paintText(HDC);
void paintRectangle(HDC);
void paintEllipse(HDC);
void paintLine(HDC);
// For task 2
void paintFlagClientArea(HDC, HWND);
void paitFlagWhole(HWND);
void paitFlagDesktop();
// For task 3
void drawCircle(HDC, RECT);


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
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
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

   HWND hWnd = CreateWindowW(szWindowClass, L"Laboratory Work no. 5, Chernov Dmitrii", WS_OVERLAPPEDWINDOW, 0, 0, 1000, 600
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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case BUTTON_FIGURES:
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                buttonFlag_1 = true; 
                break; 
            case BUTTON_FLAG_CLIENT:
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                buttonFlag_2 = true;
                break;
            case BUTTON_FLAG_WHOLE:
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                buttonFlag_3 = true;
                break; 
            case BUTTON_FLAG_DESK:
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                buttonFlag_4 = true;
                break; 
            case BUTTON_CIRCLE_LOCAL: 
                if (!buttonFlag_5)
                {
                    SetTimer(hWnd, timerIDLocal, 10, NULL);
                    buttonFlag_5 = true;
                }
                else
                {
                    KillTimer(hWnd, timerIDLocal); 
                    buttonFlag_5 = false; 
                    InvalidateRect(hWnd, &rectWindow, true);
                }
                break;
            case BUTTON_CIRCLE_CSH:
            {
                if (!buttonFlag_6)
                {
                    SetTimer(hWnd, timerIDCSH, 10, NULL);
                    buttonFlag_6 = true;
                    hdcCSH = GetDC(hWndCSH); 
                }
                else
                {
                    KillTimer(hWnd, timerIDCSH);
                    buttonFlag_6 = false;
                    InvalidateRect(hWnd, &rectCSH, true);
                    ReleaseDC(hWndCSH, hdcCSH); 
                }
                break;
            }
            case BUTTON_CIRCLE_DESK: 
            {
                if (!buttonFlag_7)
                {
                    SetTimer(hWnd, timerIDesk, 10, NULL);
                    buttonFlag_7 = true;
                    hdcDesk = GetDC(hWndDesk); 
                }
                else
                {
                    KillTimer(hWnd, timerIDesk);
                    buttonFlag_7 = false;
                    InvalidateRect(hWndDesk, &rectDesk, true);
                    ReleaseDC(hWndDesk, hdcDesk);
                }
                break;
            }
            case BUTTON_CIRCLE_CANCEL: 
                KillTimer(hWnd, timerIDLocal); 
                KillTimer(hWnd, timerIDCSH); 
                KillTimer(hWnd, timerIDesk);

                buttonFlag_5 = false; 
                buttonFlag_6 = false; 
                buttonFlag_7 = false; 

                InvalidateRect(hWnd, &rectCSH, true);
                InvalidateRect(hWnd, &rectCSH, true);
                InvalidateRect(hWndDesk, &rectDesk, true);

                break;
            case BUTTON_PAINTER:
                buttonFlag_8 = true; 
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                break;
            case BUTTON_COLOR_RED:
                MessageBeep(MB_OK);
                if (!colorRed)
                {
                    brushColor = (COLORREF)RGB(255, 0, 0);
                    colorRed = true; 
                }
                else
                {
                    brushColor = (COLORREF)RGB(0, 0, 0);
                    colorRed = false; 
                }
                break;
            case BUTTON_COLOR_GREEN:
                MessageBeep(MB_OK);
                if (!colorGreen)
                {
                    brushColor = (COLORREF)RGB(0, 255, 0);
                    colorGreen = true;
                }
                else
                {
                    brushColor = (COLORREF)RGB(0, 0, 0);
                    colorGreen = false; 
                }
                break;
            case BUTTON_COLOR_BLUE:
                MessageBeep(MB_OK);
                if (!colorBlue)
                {
                    brushColor = (COLORREF)RGB(0, 0, 255);
                    colorBlue = true; 
                }
                else
                {
                    brushColor = (COLORREF)RGB(0, 0, 0);
                    colorBlue = false; 
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            if (buttonFlag_1)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                COLORREF color = averageDesktopColor();
                
                HBRUSH hBrush = CreateSolidBrush(color);
                FillRect(hdc, &rectWindow, hBrush);
                SetBkColor(hdc, color); 

                paintText(hdc);
                paintRectangle(hdc); 
                paintEllipse(hdc); 
                paintLine(hdc); 

                DeleteObject(hBrush); 
                EndPaint(hWnd, &ps);
                buttonFlag_1 = false; 
            } 
            if (buttonFlag_2)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                paintFlagClientArea(hdc, hWnd);

                EndPaint(hWnd, &ps);
                buttonFlag_2 = false;
            }
            if (buttonFlag_3)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                paitFlagWhole(hWnd); 

                EndPaint(hWnd, &ps);
                buttonFlag_3 = false;
            }
            if (buttonFlag_4)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                paitFlagDesktop();

                EndPaint(hWnd, &ps);
                buttonFlag_4 = false;
            }
            if (buttonFlag_5)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                int i = int(8 * cos(countLocal));
                int j = int(8 * sin(countLocal));

                circleLocal.left += i; 
                circleLocal.top += j; 
                circleLocal.right += i; 
                circleLocal.bottom += j; 

                drawCircle(hdc, circleLocal);

                countLocal += 0.1;
                if (countLocal > 6.1) {
                    countLocal = 0;
                }

                EndPaint(hWnd, &ps);
            }
            if (buttonFlag_6)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                int i = int(8 * cos(countCSH));
                int j = int(8 * sin(countCSH));

                circleCSH.left += i;
                circleCSH.top += j;
                circleCSH.right += i;
                circleCSH.bottom += j;

                drawCircle(hdcCSH, circleCSH);

                countCSH += 0.1;
                if (countCSH > 6.1) {
                    countCSH = 0;
                }

                EndPaint(hWnd, &ps);
               
            }
            if (buttonFlag_7)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                int i = int(12 * cos(countLocal));
                int j = int(12 * sin(countLocal));

                circleDesk.left += i;
                circleDesk.top += j;
                circleDesk.right += i;
                circleDesk.bottom += j;

                drawCircle(hdcDesk, circleDesk);

                countLocal += 0.1;
                if (countLocal > 6.1) {
                    countLocal = 0;
                }
            }
            if (buttonFlag_8)
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); 

                SelectObject(hdc, pen); 
                Rectangle(hdc, rectPaint.left, rectPaint.top, rectPaint.right, rectPaint.bottom);

                DeleteObject(pen);
                EndPaint(hWnd, &ps);
                //buttonFlag_3 = false;
            }
   
        }
        break;
    case WM_TIMER:
    {
        switch (wParam)
        {
            case timerIDLocal:
            {
                GetClientRect(hWnd, &rectWindow);
                InvalidateRect(hWnd, &rectWindow, true);
                UpdateWindow(hWnd);
              
            }
            case timerIDCSH:
            {
                GetClientRect(hWndCSH, &rectCSH);
                InvalidateRect(hWndCSH, &rectCSH, true);
                UpdateWindow(hWndCSH);
            }
            case timerIDesk: 
            {
                InvalidateRect(hWndDesk, &rectDesk, true);
                UpdateWindow(hWndDesk);
            }
        }
    }
    case WM_LBUTTONDOWN:
        if (buttonFlag_8 && 
            LOWORD(lParam) > rectPaint.left  + 3 &&
            LOWORD(lParam) < rectPaint.right - 3 &&
            HIWORD(lParam) > rectPaint.top + 3 &&
            HIWORD(lParam) < rectPaint.bottom - 3)
        {
            drawing = true; 
            pBegin.x = pEnd.x = pTemp.x = LOWORD(lParam);
            pBegin.y = pEnd.y = pTemp.y = HIWORD(lParam);
            penGlobal = CreatePen(PS_SOLID, 2, brushColor);
        }
        break; 
    case WM_LBUTTONUP:
        if (drawing &&
            LOWORD(lParam) > rectPaint.left + 3 &&
            LOWORD(lParam) < rectPaint.right - 3 &&
            HIWORD(lParam) > rectPaint.top + 3 &&
            HIWORD(lParam) < rectPaint.bottom - 3)
        {
            DeleteObject(penGlobal); 
            drawing = false; 
        }
        break; 
    case WM_MOUSEMOVE:
        if (drawing &&
            LOWORD(lParam) > rectPaint.left + 3 &&
            LOWORD(lParam) < rectPaint.right - 3 &&
            HIWORD(lParam) > rectPaint.top + 3 &&
            HIWORD(lParam) < rectPaint.bottom - 3)
        {
            HDC hdc = GetDC(hWnd); 
            SelectObject(hdc, penGlobal); 
            SetROP2(hdc, R2_NOTXORPEN);
            
            //initial position 
            MoveToEx(hdc, pBegin.x, pBegin.y, NULL); 
            //Drawing a line 
            LineTo(hdc, pTemp.x, pTemp.y); 

            MoveToEx(hdc, pBegin.x, pBegin.y, NULL);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam)); 

            pTemp.x = LOWORD(lParam); 
            pTemp.y = HIWORD(lParam); 

            ReleaseDC(hWnd, hdc); 
        }
        break;
    case WM_CREATE:
    {
        AddControls(hWnd);
        break;
    }
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
        return (INT_PTR)FALSE;
    }
}

void AddControls(HWND hWnd) {
    hButtonFigures = CreateWindowW(L"Button", L"Draw Figures", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hWnd, (HMENU)BUTTON_FIGURES, NULL, NULL);

    hButtonFlagClient = CreateWindowW(L"Button", L"Draw Flag Client", WS_VISIBLE | WS_CHILD, 50, 90, 200, 30, hWnd, (HMENU)BUTTON_FLAG_CLIENT, NULL, NULL);
    hButtonFlagWhole = CreateWindowW(L"Button", L"Draw Flag Whole", WS_VISIBLE | WS_CHILD, 50, 130, 200, 30, hWnd, (HMENU)BUTTON_FLAG_WHOLE, NULL, NULL);
    hButtonFlagDesk = CreateWindowW(L"Button", L"Draw Flag Desktop", WS_VISIBLE | WS_CHILD, 50, 170, 200, 30, hWnd, (HMENU)BUTTON_FLAG_DESK, NULL, NULL);

    hButtonCircleLocal = CreateWindowW(L"Button", L"Local Circle", WS_VISIBLE | WS_CHILD, 50, 210, 200, 30, hWnd, (HMENU)BUTTON_CIRCLE_LOCAL, NULL, NULL, NULL);
    hButtonCircleCSH = CreateWindowW(L"Button", L"C# Circle", WS_VISIBLE | WS_CHILD, 50, 250, 200, 30, hWnd, (HMENU)BUTTON_CIRCLE_CSH, NULL, NULL, NULL);
    hButtonCircleDesk = CreateWindowW(L"Button", L"Desktop Circle", WS_VISIBLE | WS_CHILD, 50, 290, 200, 30, hWnd, (HMENU)BUTTON_CIRCLE_DESK, NULL, NULL, NULL);
    hButtonUndo = CreateWindowW(L"Button", L"Undo All Circles", WS_VISIBLE | WS_CHILD, 50, 330, 200, 30, hWnd, (HMENU)BUTTON_CIRCLE_CANCEL, NULL, NULL, NULL);
    
    hButtonPainter = CreateWindowW(L"Button", L"Painter Mode", WS_VISIBLE | WS_CHILD, 50, 370, 200, 30, hWnd, (HMENU)BUTTON_PAINTER, NULL, NULL, NULL);
    hButtonRed = CreateWindowW(L"Button", L"Red Brush", WS_VISIBLE | WS_CHILD, 50, 410, 200, 30, hWnd, (HMENU)BUTTON_COLOR_RED, NULL, NULL, NULL);
    hButtonGreen = CreateWindowW(L"Button", L"Green Brush", WS_VISIBLE | WS_CHILD, 50, 450, 200, 30, hWnd, (HMENU)BUTTON_COLOR_GREEN, NULL, NULL, NULL);
    hButtonBlue = CreateWindowW(L"Button", L"Blue Brush", WS_VISIBLE | WS_CHILD, 50, 490, 200, 30, hWnd, (HMENU)BUTTON_COLOR_BLUE, NULL, NULL, NULL);
}

COLORREF averageDesktopColor() {

    HWND hWnd = GetDesktopWindow(); 
    HDC hdc = GetDC(hWnd);
    RECT rectDescktop;
    COLORREF color; 

    int r = 0; 
    int g = 0; 
    int b = 0; 
    int count = 0; 

    GetWindowRect(hWnd, &rectDescktop); 

    for (size_t i = 0; i < rectDescktop.right; i+= 100)
    {
        for (size_t j = 0; j < rectDescktop.bottom; j+= 100)
        {
            color = GetPixel(hdc, i, j); 
            r += GetRValue(color); 
            g += GetGValue(color); 
            b += GetBValue(color); 

            count++; 
        }
    }

    r = int(r / count); 
    g = int(g / count); 
    b = int(b / count); 

    COLORREF newColor = RGB(r, g, b);

    ReleaseDC(hWnd, hdc); 
   
    return newColor;
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

void paintFlagClientArea(HDC hdc, HWND hWnd) {
    HBRUSH brushBlack = CreateSolidBrush((COLORREF)RGB(0, 0, 0));
    HBRUSH brushRed = CreateSolidBrush((COLORREF)RGB(255, 0, 0));
    HBRUSH brushYellow = CreateSolidBrush((COLORREF)RGB(255, 204, 0));
    HPEN penNull = CreatePen(PS_NULL, NULL, NULL); 

    RECT rect;
    GetClientRect(hWnd, &rect);
    SelectObject(hdc, penNull);

    int end = rect.bottom / 3; 

    SelectObject(hdc, brushBlack); 
    Rectangle(hdc, rect.left, rect.top, rect.right, end);

    SelectObject(hdc, brushRed);
    Rectangle(hdc, rect.left, rect.top + end, rect.right, end * 2);

    SelectObject(hdc, brushYellow);
    Rectangle(hdc, rect.left, rect.top + end * 2, rect.right, end * 3);

    DeleteObject(brushBlack);
    DeleteObject(brushRed);
    DeleteObject(brushYellow);
    DeleteObject(penNull); 
}

void paitFlagWhole(HWND hWnd) {
    HBRUSH brushBlack = CreateSolidBrush((COLORREF)RGB(0, 0, 0));
    HBRUSH brushRed = CreateSolidBrush((COLORREF)RGB(255, 0, 0));
    HBRUSH brushYellow = CreateSolidBrush((COLORREF)RGB(255, 204, 0));
    HPEN penNull = CreatePen(PS_NULL, NULL, NULL);

    HDC hdc = GetWindowDC(hWnd);

    RECT rect;
    GetWindowRect(hWnd, &rect);
    SelectObject(hdc, penNull);

    rect.bottom = rect.bottom - rect.top;
    rect.right = rect.right - rect.left;
    rect.left = 0;
    rect.top = 0;


    int end = rect.bottom / 3;

    SelectObject(hdc, brushBlack);
    Rectangle(hdc, rect.left, rect.top, rect.right, end);

    SelectObject(hdc, brushRed);
    Rectangle(hdc, rect.left, rect.top + end, rect.right, end * 2);

    SelectObject(hdc, brushYellow);
    Rectangle(hdc, rect.left, rect.top + end * 2, rect.right, end * 3);

    DeleteObject(brushBlack);
    DeleteObject(brushRed);
    DeleteObject(brushYellow);
    DeleteObject(penNull); 
    ReleaseDC(hWnd, hdc);
}

void paitFlagDesktop() {
    HBRUSH brushBlack = CreateSolidBrush((COLORREF)RGB(0, 0, 0));
    HBRUSH brushRed = CreateSolidBrush((COLORREF)RGB(255, 0, 0));
    HBRUSH brushYellow = CreateSolidBrush((COLORREF)RGB(255, 204, 0));
    HPEN penNull = CreatePen(PS_NULL, NULL, NULL);

    RECT rect;
    HWND hWnd = GetDesktopWindow();
    HDC hdc = GetDC(hWnd);
    GetWindowRect(hWnd, &rect);
    SelectObject(hdc, penNull);

    int end = rect.bottom / 3;

    SelectObject(hdc, brushBlack);
    Rectangle(hdc, rect.left, rect.top, rect.right, end);

    SelectObject(hdc, brushRed);
    Rectangle(hdc, rect.left, rect.top + end, rect.right, end * 2);

    SelectObject(hdc, brushYellow);
    Rectangle(hdc, rect.left, rect.top + end * 2, rect.right, end * 3);

    DeleteObject(brushBlack);
    DeleteObject(brushRed);
    DeleteObject(brushYellow);
    DeleteObject(penNull);
    ReleaseDC(hWnd, hdc);
}

void drawCircle(HDC hdc, RECT circle) {
    HBRUSH brush = CreateSolidBrush((COLORREF)RGB(rand() % 256, rand() % 256, rand() % 256));

    SelectObject(hdc, brush);
    Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);

    DeleteObject(brush);
}