// lab_3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab_3.h"

#define MAX_LOADSTRING 100
#define BUTTON_HIDE    1 
#define BUTTON_DISABLE 2 
#define BUTTON_CLOSE   3 
#define BUTTON_PESS    4
#define BUTTON_PERFORM 5
#define BUTTON_RENAME  6
#define BUTTON_WINDOWS_RENAME 7

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hButtonHide;
HWND hButtonDisable; 
HWND hButtonClose; 
HWND hButtonPress; 
HWND hButtonPerform; 
HWND hButtonRename; 
HWND hButtonWindowRename; 
HWND hWindowCpp; 
HWND hWindpwCSharp; 
HWND hWindowLab2; 
int children = 1; 
int windows = 1; 


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
BOOL CALLBACK RenameWindow(HWND, LPARAM); 
BOOL CALLBACK RenameMain(HWND, LPARAM); 
BOOL CALLBACK RenameChild(HWND, LPARAM); 


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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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

   HWND hWnd = CreateWindowW(szWindowClass, L"Laboratory Work no. 3, Chernov Dmitrii", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500
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
    hWindowLab2 = FindWindow(NULL, L"Laboratory Work no. 2, Chernov Dmitrii");

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
            case BUTTON_HIDE: 
                hWindpwCSharp = FindWindowW(NULL, L"My Program"); 

                if (hWindpwCSharp == NULL)
                {
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                }
                else
                {
                    if (IsWindowVisible(hWindpwCSharp))
                        ShowWindow(hWindpwCSharp, SW_HIDE);
                    else 
                        ShowWindow(hWindpwCSharp, SW_SHOW); 
                }
                break; 
            case BUTTON_DISABLE:
                hWindpwCSharp = FindWindowW(NULL, L"My Program");

                if (hWindpwCSharp == NULL)
                {
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                }
                else
                {
                if (IsWindowEnabled(hWindpwCSharp))
                    EnableWindow(hWindpwCSharp, false);
                else
                    EnableWindow(hWindpwCSharp, true);
                }
                break; 
            case BUTTON_CLOSE:
                hWindpwCSharp = FindWindowW(NULL, L"My Program");

                if (hWindpwCSharp == NULL)
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                else
                    PostMessage(hWindpwCSharp, WM_QUIT, NULL, NULL);
                break; 
            case BUTTON_PESS: 
            {
                HWND hButton = FindWindowEx(hWindowLab2, NULL, L"Button", L"Make anther button work");

                if (hWindowLab2 == NULL)
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                else if (hButton == NULL)
                    MessageBoxW(hWnd, L"No such button! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                else
                {

                    SendMessageW(hButton, BM_CLICK, NULL, NULL);
                    MessageBeep(MB_ICONINFORMATION);
                }
                break;
            }
            case BUTTON_PERFORM: 
            {
                if (hWindowLab2 == NULL)
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                else
                {
                    SendMessageW(hWindowLab2, WM_COMMAND, IDM_ABOUT, NULL); 
                }
                break;
            }
            case BUTTON_RENAME:
            {

                if (hWindowLab2 == NULL)
                    MessageBoxW(hWnd, L"No such window! ", L"Error", MB_OK | MB_ICONEXCLAMATION);
                else
                {
                    EnumChildWindows(hWindowLab2, &RenameWindow, (LPARAM)L"The name was changed!");
                    MessageBeep(MB_ICONINFORMATION);
                }
                break; 
            }
            case BUTTON_WINDOWS_RENAME:
            {
                EnumWindows(&RenameMain, lParam); 
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_RBUTTONDOWN:
        if (hWindowLab2 != NULL)
        {
            SendMessageW(hWindowLab2, WM_RBUTTONDOWN, wParam, lParam);
            SendMessageW(hWindowLab2, WM_RBUTTONUP, wParam, lParam);
        }
        break; 
    case WM_LBUTTONDOWN:
        SendMessageW(hWindowLab2, WM_LBUTTONDOWN, wParam, lParam);
        break; 
    case WM_LBUTTONUP:
        SendMessageW(hWindowLab2, WM_LBUTTONUP, wParam, lParam);
        break;
    case WM_MOUSEMOVE:
        SendMessageW(hWindowLab2, WM_MOUSEMOVE, wParam, lParam); 
        break; 
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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

void AddControls(HWND hWnd) 
{
    CreateWindow(L"Static", L"Working with C# program", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hWnd, NULL, NULL, NULL); 
    hButtonHide = CreateWindowW(L"Button", L"Window Hide", WS_VISIBLE | WS_CHILD, 50, 90, 150, 50, hWnd, (HMENU)BUTTON_HIDE, NULL, NULL); 
    hButtonClose = CreateWindowW(L"Button", L"Window Disable", WS_VISIBLE | WS_CHILD, 50, 150, 150, 50, hWnd, (HMENU)BUTTON_DISABLE, NULL, NULL);
    hButtonDisable = CreateWindowW(L"Button", L"Window Close", WS_VISIBLE | WS_CHILD, 50, 210, 150, 50, hWnd, (HMENU)BUTTON_CLOSE, NULL, NULL);

    CreateWindow(L"Static", L"Working with Lab2 program", WS_VISIBLE | WS_CHILD, 230, 50, 200, 30, hWnd, NULL, NULL, NULL);
    hButtonPress = CreateWindowW(L"Button", L"Press Button", WS_VISIBLE | WS_CHILD, 230, 90, 150, 50, hWnd, (HMENU)BUTTON_PESS, NULL, NULL);
    hButtonPerform = CreateWindowW(L"Button", L"Open Menu", WS_VISIBLE | WS_CHILD, 230, 150, 150, 50, hWnd, (HMENU)BUTTON_PERFORM, NULL, NULL);
    hButtonRename = CreateWindowW(L"Button", L"Rename", WS_VISIBLE | WS_CHILD, 230,210, 150, 50, hWnd, (HMENU)BUTTON_RENAME, NULL, NULL);

    CreateWindow(L"Static", L"Renaming all system", WS_VISIBLE | WS_CHILD, 110, 270, 200, 30, hWnd, NULL, NULL, NULL);
    hButtonWindowRename = CreateWindowW(L"Button", L"Rename All", WS_VISIBLE | WS_CHILD, 130, 310, 150, 50, hWnd, (HMENU)BUTTON_WINDOWS_RENAME, NULL, NULL);

}

BOOL CALLBACK RenameWindow(HWND hWnd, LPARAM lParam) 
{
    SendMessageW(hWnd, WM_SETTEXT, NULL, lParam); 
    return true; 
}

BOOL CALLBACK RenameMain(HWND hWnd, LPARAM lParam) 
{
    EnumChildWindows(hWnd, &RenameChild, lParam);
    TCHAR name[MAX_LOADSTRING] = L"Parent";
    TCHAR number[MAX_LOADSTRING];

    _itot_s(windows, number, 10);
    _tcscat_s(name, number);

    SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)name);

    windows++;

    return true;

}

BOOL CALLBACK RenameChild(HWND hWnd, LPARAM lParam)
{
    TCHAR name[MAX_LOADSTRING] = L"Child";
    TCHAR number[MAX_LOADSTRING];

    _itot_s(children, number, 10);
    _tcscat_s(name, number);

    SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)name);

    children++;

    return true; 
}