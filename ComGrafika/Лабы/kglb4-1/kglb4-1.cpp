// kglb4-1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "kglb4-1.h"

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
    LoadStringW(hInstance, IDC_KGLB41, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KGLB41));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KGLB41));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KGLB41);
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

void gist(HDC hdc, int x, int y) {
    COLORREF color = GetPixel(hdc, x, y);

    int R = GetRValue(color);
    int G = GetGValue(color);
    int B = GetBValue(color);
    int i, j, d = 0;
    MoveToEx(hdc, x + 100, y + 150, NULL);
    LineTo(hdc, x, 250);
    LineTo(hdc, x, y + 150);
    int sum;
    for (i = x; i < x + 100; i++) {
        sum = 0;
        MoveToEx(hdc, i, y + 150, NULL);
        for (j = y; j < y + 100; j++) {
            color = GetPixel(hdc, i, j);
            R = GetRValue(color);
            G = GetGValue(color);
            B = GetBValue(color);
            sum += (R + G + B) / 3;
        }
        sum = sum / 99;
        //if (sum > y) continue;
        LineTo(hdc, i, 240 + sum);
        d++;
    }
}
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
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        HBITMAP pic1 = (HBITMAP)LoadImage(NULL, L"riba2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        HDC memdc = CreateCompatibleDC(hdc);
        SelectObject(memdc, pic1);
        BitBlt(hdc, 100, 100, 350, 250, memdc, 0, 0, SRCCOPY);
        COLORREF color = GetPixel(hdc, 100, 100);
        RECT rect;
        GetClientRect(hWnd, &rect);

        int R = GetRValue(color);
        int G = GetGValue(color);
        int B = GetBValue(color);
        int i, j, d = 0;

        gist(hdc, 100, 100);

        COLORREF white = 0x00FFFFFF;
        COLORREF black = 0x00000000;
        int  move = 220, Vporog = 130, Nporog = 100;
        rect.left = 220;
        rect.top = 250;


            for (i = 100; i < 200; i++) {
                for (j = 100; j < 200; j++) {
                    color = GetPixel(hdc, i, j);
                    R = GetRValue(color);
                    G = GetGValue(color);
                    B = GetBValue(color);

                    int intensity = (R + G + B)/3;

                    if (intensity < Nporog) {
                        SetPixel(hdc, i + move, j, black);
                    }
                    else if (intensity > Vporog) {
                        SetPixel(hdc, i + move, j, white);
                    }
                    else {
                        R *= 255 / Vporog;
                        G *= 255 / Vporog;
                        B *= 255 / Vporog;
                        COLORREF pixel = RGB(R, G, B);
                        SetPixel(hdc, i + move, j, pixel);
                    }
                }
        }

            gist(hdc, 100 + move, 100);

            move += 220;

        int matI[3][3] = {
            {1,1,1},
            {1,0,1},
            {1,1,1} };

        int matK[5][5] = {
            {1,1,1,1,1},
            {1,1,1,1,1},
            {1,1,0,1,1},
            {1,1,1,1,1},
            {1,1,1,1,1} };

        COLORREF pixel;
        COLORREF colormat[3][3] = { 0 };
        int m, n, m1, n1;
        int sum1;

        for (i = 100; i < 200; i++) {
            for (j = 100; j < 200; j++) {
                m1 = 0;
                n1 = 0;
                R = 0;
                G = 0;
                B = 0;
                sum1 = 0;

                for (m = i - 1; m < i + 1; m++) {
                    for (n = j - 1; n < j + 1; n++) {
                        if (m < 100 or n < 100 or m >201 or n >201) {
                            m1++;
                        }else{
                            color = GetPixel(hdc, m, n);
                            R += matI[m1][n1] * GetRValue(color);
                            G += matI[m1][n1] * GetGValue(color);
                            B += matI[m1][n1] * GetBValue(color);
                            sum1 += matI[m1][n1];
                        }
                    }
                    n1++;
                }
                R = R / sum1;
                G = G / sum1;
                B = B / sum1;

                pixel = RGB(R, G, B);
                SetPixel(hdc, i + move, j, pixel);

            }
        }
        gist(hdc, 100 + move, 100);
        int move1 = 220;

            for (i = 100 + move; i < 200 + move; i++) {
                for (j = 100; j < 200; j++) {
                    m1 = 0;
                    n1 = 0;
                    R = 0;
                    G = 0;
                    B = 0;
                    sum1 = 0;

                    for (m = i - 2; m < i + 2; m++) {
                        m1 = 0;
                        for (n = j - 2; n < j + 2; n++) {
                            if (!(m < (100 + move) or n < 100 or m >(198 + move) or n >198)) {
                                color = GetPixel(hdc, m, n);
                                R += matK[m1][n1] * GetRValue(color);
                                G += matK[m1][n1] * GetGValue(color);
                                B += matK[m1][n1] * GetBValue(color);
                                sum1 += matK[m1][n1];
                            }
                            m1++;
                        }
                        n1++;
                    }

                    R = R / sum1;
                    G = G / sum1;
                    B = B / sum1;

                    pixel = RGB(R, G, B);
                    SetPixel(hdc, i + move1, j, pixel);

                }
            }
            gist(hdc, 100 + move1 + move, 100);

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
