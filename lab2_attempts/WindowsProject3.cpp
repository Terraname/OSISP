// WindowsProject3.cpp : Определяет точку входа для приложения.
//


#include "framework.h"
#include "WindowsProject3.h"
#include <windows.h>
#include <windowsx.h>

#include <string.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// ОбЪявление функции перехвата нажатия правой кнопки мыши на поле
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);


void check_mines(int col, int row);
void check_nearby_cells(HWND c, int col, int row);
void assign_value(HWND c, int col, int row, int mines_near);

class minefield
{
public:
    static const int x = 100;
    static const int y = 100;
    static const int length = 20;
    static const int height = 20;
    static const int m = 7;
    static const int n = 9;
    static const int n_mines = 6;
    static bool** mines;
    static char** state;

    //static HWND field[m][n];
};
bool** minefield::mines;
char** minefield::state;
HWND Main_window;


HWND field[minefield::m][minefield::n];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(nullptr), 0);

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnhookWindowsHookEx(mouseHook);

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   Main_window = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   /*HWND hwndButton = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"OK",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       200,         // x position 
       10,         // y position 
       100,        // Button width
       100,        // Button height
       hWnd,     // Parent window
       NULL,       // No menu.
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed.*/

   //SendMessage(hwndButton, WM_SETTEXT, 0, (LPARAM)L"Command link");
   //SendMessage(hwndButton, BCM_SETNOTE, 0, (LPARAM)L"with note");

   /*const int m = 5;
   const int n = 7;

   HWND field[m][n];*/

   //HWND field[minefield::m][minefield::n];

   //minefield::field[i][j] = CreateWindow(
   minefield::mines = new bool* [minefield::m];
   minefield::state = new char* [minefield::m];
   for (int i = 0; i < minefield::m; i++)
   {
       minefield::mines[i] = new bool[minefield::n];
       minefield::state[i] = new char[minefield::n];
       for (int j = 0; j < minefield::n; j++)
       {
           minefield::mines[i][j] = false;
           minefield::state[i][j] = '\0';
           field[i][j] = CreateWindow(
           
               L"Button",
               L"",
               WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, //BS_OWNERDRAW,
               minefield::x + minefield::length * i,
               minefield::y + minefield::height * j,
               minefield::length,
               minefield::height,
               hWnd,
               NULL,
               (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
               NULL);      // Pointer not needed.*/
       };
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   for (int i = 0; i < minefield::n_mines; i++)
   {
       int loc = rand() % (minefield::n * minefield::m);
       while(minefield::mines[loc/minefield::n][loc% minefield::n]==true){}// find empty field
       minefield::mines[loc / minefield::n][loc % minefield::n] = true;
   }

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    // GPT triews to change text colour
    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
        if (lpdis->CtlType == ODT_BUTTON) {
            // Установите цвет текста кнопки
            SetTextColor(lpdis->hDC, RGB(255, 0, 0)); // Например, устанавливаем красный цвет текста
            // Выведите текст кнопки
            TCHAR szBuffer[256];
            GetWindowText(lpdis->hwndItem, szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0]));
            TextOut(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, szBuffer, lstrlen(szBuffer));
        }
        //return TRUE;
        break;
    }
    case WM_CTLCOLORBTN:
    {
        HDC hdcButton = (HDC)wParam;
        SetBkColor(hdcButton, RGB(255, 0, 0)); // устанавливаем цвет фона кнопки в красный (RGB(255, 0, 0))
        break;
        return (LRESULT)GetStockObject(NULL_BRUSH); // возвращаем объект кисти для закраски фона кнопки
    }
    case BN_CLICKED:
    {
        int wmId = LOWORD(wParam);
        int b = HIWORD(wParam);
        //DestroyWindow(hWnd);
        break;
    }
    case WM_COMMAND:
    {
        HDC hdc;
        int wmId = LOWORD(wParam);
        int b = HIWORD(wParam);
        HWND c = HWND(lParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        }
        case IDM_EXIT:
        {
            DestroyWindow(hWnd);
            break;
        }
        case BN_CLICKED:
        {
            RECT Rect;
            GetWindowRect(c, &Rect);
            MapWindowPoints(HWND_DESKTOP, GetParent(c), (LPPOINT)&Rect, 2);
            int row = (Rect.top - minefield::y) / minefield::height;
            //Rect.bottom;
            int col = (Rect.left - minefield::x) / minefield::length;
            //Rect.right;
            if (minefield::state[col][row] == 'P') { break; }
            //EnableWindow(c, false);
            if (minefield::mines[col][row])
            {
                for (int i = 0; i < minefield::m; i++)
                {
                    for (int j = 0; j < minefield::n; j++)
                    {
                        //EnableWindow(field[i][j], false);
                        if (minefield::mines[i][j] == true)
                        {
                            SendMessage(field[i][j], WM_SETTEXT, 0, (LPARAM)L"m");
                        }
                    }
                }
                SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"M");
                HWND handle = CreateWindow(
                    //minefield::field[i][j] = CreateWindow(
                    L"static",
                    L"Defeat",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    300,
                    200,
                    100,
                    40,
                    hWnd,
                    NULL,
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.*/
                SetTextColor(GetDC(c), RGB(0, 0, 200));
            }
            else
            {
                int mines_near = 0;
                if (col > 0)
                {
                    if (minefield::mines[col - 1][row] == true)
                    {
                        mines_near++;
                    }
                    if (row > 0)
                    {
                        if (minefield::mines[col - 1][row - 1] == true)
                        {
                            mines_near++;
                        }
                    }
                }
                if (col < minefield::m - 1)
                {
                    if (minefield::mines[col + 1][row] == true)
                    {
                        mines_near++;
                    }
                    if (row < minefield::n - 1)
                    {
                        if (minefield::mines[col + 1][row + 1] == true)
                        {
                            mines_near++;
                        }
                    }
                }
                if (row > 0)
                {
                    if (minefield::mines[col][row - 1] == true)
                    {
                        mines_near++;
                    }
                    if (col < minefield::m - 1)
                    {
                        if (minefield::mines[col + 1][row - 1] == true)
                        {
                            mines_near++;
                        }
                    }
                }
                if (row < minefield::n - 1)
                {
                    if (minefield::mines[col][row + 1] == true)
                    {
                        mines_near++;
                    }
                    if (col > 0)
                    {
                        if (minefield::mines[col - 1][row + 1] == true)
                        {
                            mines_near++;
                        }
                    }
                }

                bool first_click = false;
                /*char* text = new char[256];
                GetWindowText(c, (LPWSTR)text, 1);*/
                if (minefield::state[col][row] == '\0')
                {
                    first_click = true;
                }

                assign_value(c, col, row, mines_near);

                if (mines_near == 0)
                {
                    check_nearby_cells(c, col, row);
                }

            }
            break;
        }
        // Бред                                                                                                     
        case WM_CTLCOLORBTN:
            hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(255, 0, 0));
            return(LRESULT)GetStockObject(WHITE_BRUSH); // Возвращаем кисть для фона (можно выбрать любой цвет фона)
            break;
        case WM_RBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            int col = (x - minefield::x) / minefield::length;
            int row = (y - minefield::y) / minefield::height;
            if (col >= 0 && col < minefield::m)
            {
                if (row >= 0 && row < minefield::n)
                {
                    if (minefield::state[col][row] == '\0' && minefield::state[col][row] != 'P')
                    {
                        minefield::state[col][row] = 'P';
                        SendMessage(field[col][row], WM_SETTEXT, 0, (LPARAM)L"P");
                    }
                }
            }
            break;
        }
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
};

// Обработчик сообщений для окна "О программе".
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


void check_mines(int col, int row)
{
    HWND c = field[col][row];
    /*char* text = new char[256];
    GetWindowText(c, (LPWSTR)text, 1);*/
    if (minefield::state[col][row] != '\0'){return; } // do nothing if cell already has a value
    //EnableWindow(c, false);
    if (minefield::mines[col][row])
    {
        SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"M");
    }
    else
    {
        //SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"S");
        int mines_near = 0;
        if (col > 0)
        {
            if (minefield::mines[col - 1][row] == true)
            {
                mines_near++;
            }
            if (row > 0)
            {
                if (minefield::mines[col - 1][row - 1] == true)
                {
                    mines_near++;
                }
            }
        }
        if (col < minefield::m - 1)
        {
            if (minefield::mines[col + 1][row] == true)
            {
                mines_near++;
            }
            if (row < minefield::n - 1)
            {
                if (minefield::mines[col + 1][row + 1] == true)
                {
                    mines_near++;
                }
            }
        }
        if (row > 0)
        {
            if (minefield::mines[col][row - 1] == true)
            {
                mines_near++;
            }
            if (col < minefield::m - 1)
            {
                if (minefield::mines[col + 1][row - 1] == true)
                {
                    mines_near++;
                }
            }
        }
        if (row < minefield::n - 1)
        {
            if (minefield::mines[col][row + 1] == true)
            {
                mines_near++;
            }
            if (col > 0)
            {
                if (minefield::mines[col - 1][row + 1] == true)
                {
                    mines_near++;
                }
            }
        }

        assign_value(c, col, row, mines_near);

        if (mines_near == 0)
        {
            check_nearby_cells(c, col, row);
        }
    }
}

void check_nearby_cells(HWND c, int col, int row)
{

    if (col > 0)
    {
        check_mines(col - 1, row);
        if (row > 0)
        {
            check_mines(col - 1, row - 1);
        }
    }
    if (col < minefield::m - 1)
    {
        check_mines(col + 1, row);
        if (row < minefield::n - 1)
        {
            check_mines(col + 1, row + 1);
        }
    }
    if (row > 0)
    {
        check_mines(col, row - 1);
        if (col < minefield::m - 1)
        {
            check_mines(col + 1, row - 1);
        }
    }
    if (row < minefield::n - 1)
    {
        check_mines(col, row + 1);
        if (col > 0)
        {
            check_mines(col - 1, row + 1);
        }
    }

}

void assign_value(HWND c, int col, int row, int mines_near)
{
    //SetWindowText(c, L"9");
    //SendMessage();
    HDC hdc = GetDC(c);
    SendMessage(c, WM_PAINT, 0, (LPARAM)L"0");

    //// Получаем дескриптор окна кнопки
    //HWND hButton = c;

    //// Получаем контекст устройства для кнопки
    //HDC hdcButton = GetDC(hButton);

    //// Устанавливаем цвет текста
    //SetTextColor(hdcButton, RGB(255, 0, 0)); // Например, устанавливаем красный цвет текста

    //// Освобождаем контекст устройства
    //ReleaseDC(hButton, hdcButton);

    //SendMessage(c, WM_change_color, (WPARAM)hdc, (LPARAM)RGB(50, 50, 200));
    //SendMessage(c, WM_CTLCOLORBTN, (WPARAM)hdc, (LPARAM)RGB(50, 50, 200));
    //SendMessage(c, WM_CTLCOLORBTN, 0, (LPARAM)RGB(50, 50, 200));
    COLORREF a = SetBkColor(hdc, RGB(200, 50, 50));
    COLORREF b = SetTextColor(hdc, RGB(50, 50, 200));
    ReleaseDC(c, hdc);
    //SetTextColor(HDC(c), RGB(50, 50, 200));
    if (mines_near == 0) { minefield::state[col][row] = '0'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"0");SetTextColor(GetDC(c), RGB(50, 50, 200)); }
    else if (mines_near == 1) { minefield::state[col][row] = '1'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"1"); }
    else if (mines_near == 2) { minefield::state[col][row] = '2'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"2"); }
    else if (mines_near == 3) { minefield::state[col][row] = '3'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"3"); }
    else if (mines_near == 4) { minefield::state[col][row] = '4'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"4"); }
    else if (mines_near == 5) { minefield::state[col][row] = '5'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"5"); }
    else if (mines_near == 6) { minefield::state[col][row] = '6'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"6"); }
    else if (mines_near == 7) { minefield::state[col][row] = '7'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"7"); }
    else if (mines_near == 8) { minefield::state[col][row] = '8'; SendMessage(c, WM_SETTEXT, 0, (LPARAM)L"8"); }

    // Устанавливаем красный цвет текста
    /*SendMessage(hButton, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
    SendMessage(hButton, WM_SETTEXT, 0, (LPARAM)L"Y");
    HDC hdcStatic = GetDC(hButton);
    SetTextColor(hdcStatic, RGB(255, 0, 0));
    ReleaseDC(hButton, hdcStatic);
    InvalidateRect(hButton, NULL, TRUE);*/

    // Получаем дескриптор окна кнопки
    //HWND hButton = c;

    //// Устанавливаем красный цвет текста
    //SendMessage(hButton, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
    //SendMessage(hButton, WM_SETTEXT, 0, (LPARAM)L"Your Text");
    //HDC hdcStatic = GetDC(hButton);
    //SetTextColor(hdcStatic, RGB(255, 0, 0));
    //ReleaseDC(hButton, hdcStatic);
    //InvalidateRect(hButton, NULL, TRUE);
}

void do_something()
{

}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_RBUTTONDOWN) {
            
            POINT pt;
            //pt.x = LOWORD(lParam);
            //pt.y = HIWORD(lParam);
            //pt.x = GET_X_LPARAM(lParam);
            //pt.y = GET_Y_LPARAM(lParam);
            GetCursorPos(&pt);
            //ClientToScreen(Main_window, &pt);
            ClientToScreen(NULL, &pt);
            MapWindowPoints(NULL, Main_window, (LPPOINT)&pt, 1);
            int x1 = pt.x;
            int y1 = pt.y;
            int col = (x1 - minefield::x) / minefield::length;
            int row = (y1 - minefield::y) / minefield::height;
            if (col >= 0 && col < minefield::m)
            {
                if (row >= 0 && row < minefield::n)
                {
                    if (minefield::state[col][row] == '\0' && minefield::state[col][row] != 'P')
                    {
                        minefield::state[col][row] = 'P';
                        SendMessage(field[col][row], WM_SETTEXT, 0, (LPARAM)L"P");
                    }
                }
            }
            //do_something();
        }
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}
