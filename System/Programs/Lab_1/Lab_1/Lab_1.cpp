// Lab_1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab_1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hName, hAge, hOut, hGenerate;              // controls
char name[30], age[10], out[50], title[100];    // for output 
const int timer = 5;                          // for moving window
int i = 0; 


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void MakeRectangular(HWND, int); 

// Constants 
#define GENERATE_BUTTON 1
#define GET_TITLE_BUTTON 2

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TREE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TREE));

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

   HWND hWnd = CreateWindowW(szWindowClass, L"Лабораторная работа №1, Чернов Д.С. А-05-18", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500
       , nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   MakeRectangular(hWnd, nCmdShow); 

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
    case WM_CREATE: 
        AddControls(hWnd);
        MessageBox(NULL, L"Hello, handsome!", L"WARNING", MB_OK);
        break; 
    case WM_RBUTTONDOWN:
        SetWindowTextA(hOut, "Righ button pressed");
        KillTimer(hWnd, timer);
        SetParent(hGenerate, hWnd);
        MoveWindow(hGenerate,100, 140, 98, 38, true);
        SetWindowTextW(hGenerate, L"Generate");
        i = 0; 
        break;
    case WM_LBUTTONDOWN: 
        SetWindowTextA(hOut, "Left button pressed");
        break;
    case WM_TIMER:
        i++;
        SetWindowTextW(hGenerate, L"Escaped");
        MoveWindow(hGenerate, 100 + i * 5, 140 + i * 5, 98, 38, true);
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
            case GENERATE_BUTTON:
                GetWindowTextA(hName, name, 30);
                GetWindowTextA(hAge, age, 10);

                strcpy_s(out, name);
                strcat_s(out, " is ");
                SetWindowTextA(hOut, out);
                strcat_s(out, age);
                strcat_s(out, " years old.");
                SetWindowTextA(hOut, out);

                break;
            case GET_TITLE_BUTTON: 
                GetWindowTextA(hWnd, title, 100);
                strcpy_s(out, title);
                SetWindowTextA(hOut, out);
                break;
            case IDC_SHOW :
                SetTimer(hWnd, timer, 70, (TIMERPROC)NULL);
                SetParent(hGenerate, NULL); 
                break; 
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        MessageBox(NULL, L"Goodbye, handsome !", L"WARNING", MB_OK);
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
    CreateWindow(L"Static", L"Name :", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindow(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

    CreateWindow(L"Static", L"Age :", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hAge = CreateWindow(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

    hGenerate = CreateWindow(L"Button", L"Generate", WS_VISIBLE | WS_CHILD, 100, 140, 98, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
    CreateWindow(L"Button", L"Get title", WS_VISIBLE | WS_CHILD, 280, 140, 120, 38, hWnd, (HMENU)GET_TITLE_BUTTON, NULL, NULL);

    hOut = CreateWindow(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 100, hWnd, NULL, NULL, NULL);
}

void MakeRectangular(HWND hWnd, int nCmdShow) {
    HRGN FormRgn1, FormRgn2;
    RECT WRect;


    GetWindowRect(hWnd, &WRect);

    FormRgn1 = CreateEllipticRgn(-100, -110, WRect.right - WRect.left + 80, WRect.bottom - WRect.top);
    FormRgn2 = CreateEllipticRgn(170, 360, 330, 480);
    //FormRgn1 = CreateEllipticRgn(NULL, NULL, NULL, NULL);

    CombineRgn(FormRgn1, FormRgn1, FormRgn2, RGN_XOR);

    SetWindowRgn(hWnd, FormRgn1, true);
}
