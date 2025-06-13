#include "framework.h"
#include "PassGen.h"

#define MAX_LOADSTRING 100

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    WCHAR szTitle[MAX_LOADSTRING];
    WCHAR szWindowClass[MAX_LOADSTRING];
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_PASSGEN, szWindowClass, MAX_LOADSTRING);

    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PASSGEN));
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDI_PASSGEN);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassEx(&wcex))
    {
        return -1;
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int windowWidth = screenWidth * 0.3;
    int windowHeight = screenHeight * 0.3;

    int windowPosX = screenWidth * 0.5 - windowWidth * 0.5;
    int windowPosY = screenHeight * 0.5 - windowHeight * 0.5;

    HWND hWnd = CreateWindowExW(
        WS_EX_STATICEDGE,
        szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        windowPosX, windowPosY,
        windowWidth, windowHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
