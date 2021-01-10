// Lab_2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab_2.h"
#include <iostream>
#pragma warning(disable:4996)

#define MAX_LOADSTRING 100
#define BUTTON_POWER 1 
#define BUTTON_MAKER 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hButtonPower; 
HWND hButtonMaker; 
HWND hData; 
HWND hInfo, hInfo2, hInfo3, hInfo4, hInfo5; 
WORD x_cursor, y_cursor;
POINT lastLocation; 

int doubleClick = 0; 
int leftButtonUp = 0; 
int leftButtonDown = 0; 
int mouseControls = 0; 
bool mouseDown = false;

void AddControls(HWND); 

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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

   HWND hWnd = CreateWindowW(szWindowClass, L"Laboratory Work no. 2, Chernov Dmitrii", WS_OVERLAPPEDWINDOW, 0, 0, 500, 600
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
    wchar_t data[MAX_LOADSTRING];
    wchar_t out[MAX_LOADSTRING];

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BUTTON_POWER:
            {

                int length = GetWindowTextLengthW(hData) + 1;
                wchar_t* number = new wchar_t[length];
                GetWindowTextW(hData, number, length);
                int digit = _wtoi(number);
                digit *= digit;
                _itow(digit, number, 10);
                if (number[0] == '0') {
                    SetWindowTextW(hInfo, L"Enter a number: ");
                }
                else {
                    SetWindowTextW(hInfo, L"Power of two was calculated: ");
                }
                SetWindowTextW(hData, number);
                break; 
            }
            case BUTTON_MAKER:
                //quick push 
                SendMessageW(hButtonPower, BM_CLICK, NULL, NULL);

                //long push 
                SendMessageW(hButtonPower, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(5, 5)); 
                SendMessageW(hButtonPower, WM_LBUTTONUP, NULL, MAKELONG(5, 5)); 
                break; 
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
    case WM_CREATE:
        AddControls(hWnd);
        SetWindowTextW(hInfo, L"Enter a number: ");
        break; 
    case WM_RBUTTONDOWN: {
        SetWindowTextW(hInfo, L"Right button was prssed. Coordinates: ");

        TCHAR x_axis[MAX_LOADSTRING]; 
        TCHAR y_axis[MAX_LOADSTRING];

        WORD x_data = LOWORD(lParam); 
        WORD y_data = HIWORD(lParam);

        _itot_s(x_data, x_axis, MAX_LOADSTRING, 10);
        _itot_s(y_data, y_axis, MAX_LOADSTRING, 10);

        _tcscat_s(x_axis, L" - "); 
        _tcscat_s(x_axis, y_axis); 
        SetWindowText(hData, x_axis);
        break;
    }
    case WM_NCLBUTTONDOWN:
        //SetCapture(hWnd); // just blocking 
        //return DefWindowProc(hWnd, message, wParam, lParam);

        if (wParam == HTCAPTION) {
            break;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_LBUTTONDBLCLK:
        doubleClick++; 
        data[MAX_LOADSTRING]; 
        out[MAX_LOADSTRING]; 
        wcscpy(out, L"Number of double clicks    : "); 
        _itow(doubleClick, data, 10);
        wcscat(out, data); 
        SetWindowTextW(hInfo2, out);

        break; 
    case WM_LBUTTONDOWN:
        leftButtonDown++; 
        data[MAX_LOADSTRING];
        out[MAX_LOADSTRING];
        wcscpy(out, L"Number of left down clicks : ");
        _itow(leftButtonDown, data, 10);
        wcscat(out, data);
        SetWindowTextW(hInfo3, out);

        SetCapture(hWnd);
        mouseDown = true;
        //GetCursorPos(&lastLocation); // Getting mouse position
        lastLocation.x = LOWORD(lParam);
        lastLocation.y = HIWORD(lParam);

        RECT rect;
        GetWindowRect(hWnd, &rect);
        lastLocation.x = lastLocation.x + rect.left;
        lastLocation.y = lastLocation.y + rect.top;

        break; 
    case WM_LBUTTONUP:
        leftButtonUp++; 
        data[MAX_LOADSTRING];
        out[MAX_LOADSTRING];
        wcscpy(out, L"Number of left up clicks     : ");
        _itow(leftButtonUp, data, 10);
        wcscat(out, data);
        SetWindowTextW(hInfo4, out);


        ReleaseCapture(); 
        mouseDown = false;
        break; 
    case WM_MOUSEMOVE:
    {
        if (mouseDown) {
            POINT currentpos;
            RECT rect;
            GetWindowRect(hWnd, &rect);
            //GetCursorPos(&currentpos);
            currentpos.x = LOWORD(lParam) + rect.left;
            currentpos.y = HIWORD(lParam) + rect.top;

            int x = lastLocation.x - currentpos.x ;
            int y = lastLocation.y - currentpos.y ;
            //MoveWindow(hWnd, rect.left - x, rect.top - y, 500, 600, false);
            MoveWindow(hWnd, rect.left - x, rect.top - y, rect.right - rect.left, rect.bottom - rect.top, false);

            lastLocation.x = currentpos.x; 
            lastLocation.y = currentpos.y; 
        }
        break;

    }
    case WM_NCHITTEST:
    {
        mouseControls++;
        data[MAX_LOADSTRING];
        out[MAX_LOADSTRING];
        wcscpy(out, L"Mouse controls                  :");
        _itow(mouseControls, data, 10);
        wcscat(out, data);
        SetWindowTextW(hInfo5, out);

        return DefWindowProc(hWnd, message, wParam, lParam);

        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:
    {
        int val = MessageBoxW(hWnd, L"Are you sure ?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
        if (val == IDYES)
        {
            DestroyWindow(hWnd);
        }
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
    }
    return (INT_PTR)FALSE;
}

void AddControls(HWND hWnd) {
    hButtonPower = CreateWindowW(L"Button", L"^2", WS_VISIBLE | WS_CHILD, 50, 50, 80, 40, hWnd, (HMENU)BUTTON_POWER, NULL, NULL);
    hButtonMaker = CreateWindowW(L"Button", L"Make anther button work", WS_VISIBLE | WS_CHILD, 50, 100, 200, 40, hWnd, (HMENU)BUTTON_MAKER, NULL, NULL);
    hInfo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 150, 300, 40, hWnd, NULL, NULL, NULL); 
    hData = CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 200, 100, 50, hWnd, NULL, NULL, NULL);

    hInfo2 = CreateWindowW(L"Static", L"Number of double clicks    : ", WS_VISIBLE | WS_CHILD | WS_BORDER, 50,260, 300, 40, hWnd, NULL, NULL, NULL);
    hInfo3 = CreateWindowW(L"Static", L"Number of left down clicks : ", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 310, 300, 40, hWnd, NULL, NULL, NULL);
    hInfo4 = CreateWindowW(L"Static", L"Number of left up clicks     : ", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 360, 300, 40, hWnd, NULL, NULL, NULL);
    hInfo5 = CreateWindowW(L"Static", L"Mouse controls                  :", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 410, 300, 40, hWnd, NULL, NULL, NULL);

}
