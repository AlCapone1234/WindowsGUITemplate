#include <windows.h>

static int running = 1;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (uMsg)
    {
        case WM_CLOSE:
        case WM_DESTROY: 
        {
            running = 0;
        } break;

        default: 
        {
            result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
        }

    }

    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = {0};
    
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClass(&wc);
    
    // Create the window.
    
    HWND hwnd = CreateWindowEx(
                               0,                              // Optional window styles.
                               wc.lpszClassName,                     // Window class
                               L"Calculator",    // Window text
                               WS_VISIBLE|WS_OVERLAPPEDWINDOW,            // Window style
                               
                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
                               
                               0,       // Parent window    
                               0,       // Menu
                               0,  // Instance handle
                               0        // Additional application data
                               );  
    
    if (hwnd == NULL)
    {
        return 0;
    }

    while (running)
    {
        MSG message;
        while (PeekMessageA(&message, hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
  
    ShowWindow(hwnd, nShowCmd);
    return 0;

}
