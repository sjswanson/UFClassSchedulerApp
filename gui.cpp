#include <windows.h>
#define IDC_TEXT 101


using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hCurrInstance, HINSTANCE hPreviousInstance, PSTR szCommandLine, int nStartShow) {
    MessageBeep(MB_OK);
    static char szOurProgramName[] = "UF Class Organizer";

    HWND hMainWindow;
    MSG WindowsMessageStruct;
    WNDCLASSEX MainWindowStruc;
    MainWindowStruc.cbSize = sizeof (MainWindowStruc);
    MainWindowStruc.style = CS_HREDRAW | CS_VREDRAW;
    MainWindowStruc.lpfnWndProc = WndProc;
    MainWindowStruc.cbClsExtra = 0;
    MainWindowStruc.cbWndExtra = 0;
    MainWindowStruc.hInstance = hCurrInstance;
    MainWindowStruc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    MainWindowStruc.hCursor = LoadCursor(NULL, IDC_ARROW);
    MainWindowStruc.lpszMenuName = NULL;
    MainWindowStruc.lpszClassName = szOurProgramName;
    MainWindowStruc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //  MainWindowStruc.hIconSm = LoadIcon(hCurrInstance, "Icon");//This line will help us to
    //have our own icon in the future.

    RegisterClassEx(&MainWindowStruc);
    hMainWindow = CreateWindow(szOurProgramName, "UF Class Organizer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hCurrInstance, NULL);
    ShowWindow(hMainWindow, nStartShow);
    UpdateWindow(hMainWindow);
    while (GetMessage(&WindowsMessageStruct, NULL, 0, 0)) {
        TranslateMessage(&WindowsMessageStruct);
        DispatchMessage(&WindowsMessageStruct);
    }
    return WindowsMessageStruct.wParam;
}

LRESULT CALLBACK WndProc(HWND hOurWindowHandle, UINT iMessageToProcess, WPARAM wMessageParameterNr32bits, LPARAM wMessageParameterLong) {
    HDC hDeviceContextHandle;
    PAINTSTRUCT OurPaintStructure;
    RECT ClientRectangle;
    switch (iMessageToProcess) {
        case WM_CREATE:
        {
            HWND hEdit;

            hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                    20, 40, 160, 50, hOurWindowHandle, (HMENU) IDC_TEXT, GetModuleHandle(NULL), NULL);
            if (hEdit == NULL)
                MessageBox(hOurWindowHandle, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
            
            int len = GetWindowTextLength(GetDlgItem(hOurWindowHandle, IDC_TEXT));
            if (len > 0) {
                int i;
                char* buf;

                buf = (char*) GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hOurWindowHandle, IDC_TEXT, buf, len + 1);

                GlobalFree((HANDLE) buf);
            }

            return 0; //Means no error.
        }
            break;

        case WM_COMMAND:


        case WM_PAINT://Operating system wants to repaint our program window.
            hDeviceContextHandle = BeginPaint(hOurWindowHandle, &OurPaintStructure);
            GetClientRect(hOurWindowHandle, &ClientRectangle);
            EndPaint(hOurWindowHandle, &OurPaintStructure); //The end of repainting.

            //          FlashWindow(hOurWindowHandle, TRUE); // invert the title bar 
            //          MessageBeep(MB_ICONEXCLAMATION);//MB_OK, MB_ICONSTOP, MB_ICONASTERISK, MB_ICONEXCLAMATION
            //          Sleep(1000);              // A pause of 1 second.
            //          FlashWindow(hOurWindowHandle, TRUE); // invert again 

            return 0;
        case WM_DESTROY://The end of our program work, close everything.
            PostQuitMessage(0); //Game is over.
            return 0; //All is fine.
    }
    return DefWindowProc(hOurWindowHandle, iMessageToProcess, wMessageParameterNr32bits, wMessageParameterLong);
}