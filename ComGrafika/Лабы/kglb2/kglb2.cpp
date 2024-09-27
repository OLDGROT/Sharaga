// kglb2.cpp : Определяет точку входа для приложения.
//


#define _USE_MATH_DEFINES
#include "framework.h"
#include "kglb2.h"
#include <cmath>
using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

double mas[11][3] = {
    {40,80,1},
    {100,40,1},
    {190,100,1},
    {180,80,1},
    {190,60,1},
    {100,120,1},
    {70,60,1},
    {70,100,1},
    {65,70,1},
    {65,80,1},
    {55,80,1}
};

double rotate_angle = 20;

double find_length() {
    int i, maxind = 0, minind = 0;
    double max, min;
    max = mas[0][0];
    min = mas[0][0];
    for (i = 0; i < 11; i++) {
        if (mas[i][0] > max) {
            max = mas[i][0];
            maxind = i;

        }
        if (mas[i][0] < min) {
            min = mas[i][0];
            minind = i;
        }
    }
    double result = max - min;
    return result;
}

double find_middle_x() {
    int i, maxind = 0, minind = 0;
    double max, min;
    max = mas[0][0];
    min = mas[0][0];
    for (i = 0; i < 11; i++) {
        if (mas[i][0] > max) {
            max = mas[i][0];
            maxind = i;

        }
        if (mas[i][0] < min) {
            min = mas[i][0];
            minind = i;
        }
    }
    double result = mas[minind][0] + (max - min) / 2;
    return result;
}

double find_middle_y() {
    int i, maxind = 0, minind = 0;
    double max, min;
    max = mas[0][1];
    min = mas[0][1];
    for (i = 0; i < 11; i++) {
        if (mas[i][1] > max) {
            max = mas[i][1];
            maxind = i;

        }
        if (mas[i][1] < min) {
            min = mas[i][1];
            minind = i;
        }
    }
    double result = mas[minind][1] + (max - min) / 2;
    return result;
}

void draw_mas(HDC hdc, int start, int end) {
    int i;
    MoveToEx(hdc, mas[start - 1][0], mas[start - 1][1], NULL);
    for (i = start; i < end; i++) {
        LineTo(hdc, mas[i][0], mas[i][1]);
    }
    LineTo(hdc, mas[start - 1][0], mas[start - 1][1]);
}

void draw_pic(HDC hdc) {
    draw_mas(hdc, 1, 6);
    draw_mas(hdc, 7, 8);
    draw_mas(hdc, 9, 11);
}

void matrixonmatrix(double a, double b, double c, double d, double m, double n) {
    double Afin[3][3] = {
            {a,b,0},
            {c,d,0},
            {m,n,1}
    };

    int i;
    double bufx, bufy, buf1;
    for (i = 0; i < 11; i++) {
        bufx = mas[i][0];
        bufy = mas[i][1];
        buf1 = mas[i][2];
        mas[i][0] = a * bufx + c * bufy + m * buf1;
        mas[i][1] = b * bufx + d * bufy + n * buf1;
        mas[i][2] = Afin[0][2] * bufx + Afin[1][2] * bufy + Afin[2][2] * buf1;
    }
}

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KGLB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KGLB2));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KGLB2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KGLB2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

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
    case WM_CREATE: {
        HWND button1 = CreateWindow(L"BUTTON", L"Move x3.5 length", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 15, 600, 130, 50, hWnd, reinterpret_cast<HMENU>(1), NULL, NULL);
        HWND button2 = CreateWindow(L"BUTTON", L"Rotate -20", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 600, 130, 50, hWnd, reinterpret_cast<HMENU>(2), NULL, NULL);
        HWND button3 = CreateWindow(L"BUTTON", L"Shrink x by 2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 285, 600, 130, 50, hWnd, reinterpret_cast<HMENU>(3), NULL, NULL);
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 1: {
            double L;
            L = find_length();
            matrixonmatrix(1, 0, 0, 1, L * 3.5, 0);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case 2: {
            double x, y, a = -M_PI / 180 * rotate_angle;
            x = find_middle_x();
            y = find_middle_y();
            matrixonmatrix(cos(a), sin(a), -sin(a), cos(a), -x * (cos(a) - 1) + y * sin(a), -y * (cos(a) - 1) - x * sin(a));
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case 3: {
            matrixonmatrix(0.5, 0, 0, 1, find_middle_x() / 2, 0);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

        draw_pic(hdc);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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