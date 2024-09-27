
#define _USE_MATH_DEFINES
#include "framework.h"
#include "kglb5.h"
#include <cmath>
#include <fstream>
using namespace std;
#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

double rancount = 0;
double rancount1 = 0;
int sw = 1, sw1 = 1;

double h = 350;
double c = 400, q = 400;
double mas1[8][4] = {
    {-2 * h, -2 * h, h, 1},
    {2 * h, -2 * h,  h, 1},
    {2 * h, 2 * h, h, 1},
    {-2 * h, 2 * h, h, 1},
    {-h, h, -h, 1},
    {-h, -h, -h, 1},
    {h, -h, -h, 1},
    {h, h, -h, 1}
};

double mas2[8][4] = { 0 };

double a = 20.0 /180.0*M_PI, b = 140.0/180.0 * M_PI, R = 1000, d = 800, A = 20 , B = 140;
//a,b полярные углы в горизонтальной и вертикальной плоскости, 
//A,B коэффициент который мы добавляем нажатием на кнопку
//d - коэффициент масштабирования
//A - угол обзора в горизонтальной оси
//B - угол обзора в вертикальной оси
//R - расстояние от точки наблюдения
//c - сдвиг по экранным координатам
//q - сдвиг по экранным координатам
double mas3[8][3] = { 0 };


void multiply3d() {
    int i, j, k; //переменные счётчики
    int n = 8; //рёбра

    //Матрица на которую нужно умножить мировые координаты чтобы получить
    //матрицу пользовательских координат
    double mas[4][4] = {
        {cos(a), sin(a)*sin(b),sin(a)*cos(b),0},
        {0, cos(b), -sin(b),0},
        {-sin(a), cos(a)*sin(b), cos(a)*cos(b) , 0},
        {0, 0, R, 1}
    };

    /*double mas[4][4] = {
    {-sin(a), -cos(b) * cos(a),-sin(b) * cos(a),0},
    {cos(a), -cos(b) * sin(a), -sin(b) * sin(a),0},
    {0, sin(b), -cos(b) , 0},
    {0, 0, R, 1}
    };*/


    //double mas[4][4] = {
    //{0.5, 0, 0, 0},   // X-координата остается неизменной
    //{0, 0.5, 0, 0},   // Y-координата остается неизменной
    //{0, 0, 0, 0},   // Z-координата игнорируется
    //{0, 0, 0, 0.5}    // Однородные координаты
    //};



    for (i = 0;i < n;i++) {
        mas2[i][0] = 0;
        mas2[i][1] = 0;
        mas2[i][2] = 0;
        mas2[i][3] = 1;
        
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4;k++) {
                //мас2 = видовые координаты = изначальные координаты * матрицу проекции
                mas2[i][j] += mas1[i][k] * mas[k][j]; 
            }
        }
    }
}

void make2d() {
    int i, n = 8;
    //экранные координаты = преобразование матрицы координат с учётом разрешения экрана, сдвига по осям
    for (i = 0;i < n;i++) {
        mas3[i][0] = d * mas2[i][0] / mas2[i][2] + c;
        mas3[i][1] = d * mas2[i][1] / mas2[i][2] + q;
        mas3[i][2] = 1;
    }
}

/*void make2d() {
    int i, n = 8;
    //экранные координаты = преобразование матрицы координат с учётом разрешения экрана, сдвига по осям
    for (i = 0;i < n;i++) {
        mas3[i][0] = mas2[i][0]  + c;
        mas3[i][1] = mas2[i][1] + q;
        mas3[i][2] = 1;
    }
}*/

void draw_figure(HDC hdc) {
    int i, n = 8;

    MoveToEx(hdc, mas3[3][0], mas3[3][1], NULL);
    LineTo(hdc, mas3[0][0], mas3[0][1]);
    for (i = 0; i < 7; i++) {
        LineTo(hdc, mas3[i+1][0], mas3[i+1][1]);
        
    }
    
    MoveToEx(hdc, mas3[7][0], mas3[7][1], NULL);
    LineTo(hdc, mas3[4][0], mas3[4][1]);
    for (i = 0; i < 3; i++) {
        MoveToEx(hdc, mas3[i][0], mas3[i][1], NULL);
        LineTo(hdc, mas3[i + 5][0], mas3[i + 5][1]);
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
    LoadStringW(hInstance, IDC_KGLB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KGLB5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KGLB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KGLB5);
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
    case WM_KEYDOWN: {
        switch (wParam)
        {
        case VK_LEFT: {
            A -= 3;
            a = A / 180.0 * M_PI;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case VK_RIGHT: {
            A += 3;
            a = A / 180.0 * M_PI;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case 0xBB: {
            B += 3;
            b = B / 180.0 * M_PI;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }

        case 0xBD: {
            B -= 3;
            b = B / 180.0 * M_PI;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case VK_DOWN: {
            R += 10;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case VK_UP: {
            R -= 10;
            InvalidateRect(hWnd, NULL, TRUE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case 0x41: {
            c -= 15;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        }
        case 0x44: {
            c += 15;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        }
        case 0x57: {
            q -= 15;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        }
        case 0x53: {
            q += 15;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;
        }
        default:
            break;
        }
    }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            multiply3d();
            make2d();
            draw_figure(hdc);

            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
