
#include <cmath>
#include "framework.h"
#include "ComGraf1.h"
#define MAX_LOADSTRING 100

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double maxX = 0;
double maxY = 0;
double minX = 2000;
double minY = 2000;
double centX;
double centY;
double rad = 0;
double trans[3][3] = { {1,0,0},
                   {0,1,0},
                   {0,minY - maxY,1} };
double reflect[3][3] = { {1,0,0},
                       {0,-1,0},
                       {0,maxY,1} };
double rotate[3][3] = { {cos(rad),sin(rad),0},
                   {-sin(rad),cos(rad),0},
                   {-centX * (cos(rad) - 1) + centY * sin(rad),-centY * (cos(rad) - 1) - centX * sin(rad),1} };

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COMGRAF1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMGRAF1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMGRAF1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COMGRAF1);
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

void minMaxCent(double arr[][3], int size) {
    maxX = 0;
    maxY = 0;
    minX = 2000;
    minY = 2000;
    for (int i = 0;i < size;i++) {
        if (arr[i][0] < minX) {
            minX = arr[i][0];
        }
        if(arr[i][0]> maxX)
        {
            maxX = arr[i][0];
        }
        if (arr[i][1] < minY) {
            minY = arr[i][1];
        }
        if (arr[i][1] > maxY)
        {
            maxY = arr[i][1];
        }

    }
    centX = (maxX + minX) / 2;
    centY = (maxY + minY) / 2;

    trans[2][1] = minY - maxY;

    reflect[2][1] = 2*centY;

    int angle = 90;
    rad = angle * M_PI / 180.0;
    rotate[0][0] = cos(rad);
    rotate[0][1] = sin(rad);
    rotate[1][1] = cos(rad);
    rotate[1][0] = -sin(rad);
    rotate[2][0] = -centX * (cos(rad) - 1) + centY * sin(rad);
    rotate[2][1] = -centY * (cos(rad) - 1) - centX * sin(rad);


}

void multiplyMatrices(double arr[][3], double arr1[][3], int size)
{
    for (int i = 0; i <= size; i++) {
        double x = arr[i][0];
        double y = arr[i][1];
        double z = arr[i][2];
        arr[i][0] = arr1[0][0] * x + arr1[1][0] * y + arr1[2][0];
        arr[i][1] = arr1[0][1] * x + arr1[1][1] * y + arr1[2][1];
        arr[i][2] = arr1[0][2] * z + arr1[1][2] * z + arr1[2][2];
    }
}


void draw(HDC hdc,double arr[][3], double size)
{
    for (int i = 0;i < size; i+=2)
    {
        MoveToEx(hdc, arr[i][0], arr[i][1], NULL);
        LineTo(hdc, arr[i+1][0], arr[i+1][1]);
    }

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int size = 28;
    static double arr[28][3] = { {970, 760,1}, { 970,690,1 },
        { 1000,740,1 },{940,740,1},
        {940,740,1},{940,340,1},
        {940,340,1},{970,280,1},
        {970,280,1},{1000,340,1},
        {1000,340,1},{1000,740,1},
        {1000,740,1},{1000,710,1},
        {1000,710,1},{1050,740,1},
        {1050,740,1},{890,740,1},
        {890,740,1},{940,710,1},
        {940,580,1},{650,620,1},
        {650,620,1},{940,430,1},
        {1000,580,1},{1290,620,1},
        {1290,620,1},{1000,430,1} };
    minMaxCent(arr, size);

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
        break;
    case WM_KEYDOWN:
        // Handle keyboard input
        switch (wParam)
        {
        case VK_UP:

            multiplyMatrices(arr, trans, size);
            minMaxCent(arr, size);
            break;
        case VK_DOWN:

            multiplyMatrices(arr, reflect, size);
            minMaxCent(arr, size);
            break;
        case VK_LEFT:
            multiplyMatrices(arr, rotate, size);
            minMaxCent(arr, size);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        // Redraw the window after transformation
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            draw(hdc, arr, size);
            draw(hdc, arr, size);
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
