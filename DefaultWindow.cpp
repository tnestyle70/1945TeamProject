#include "pch.h"
#include "framework.h"
#include "DefaultWindow.h"
#include "CMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND        g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    CMainGame       MainGame;
    MainGame.Initialize();

    MSG msg;
    msg.message = WM_NULL;

    DWORD   dwTime = GetTickCount64();

    // 기본 메시지 루프입니다:
    while (true)
    {
        // PM_REMOVE : 메세지 큐로부터 메세지 유무를 확인 뒤, 메세지를 가져오면서 삭제
        // PM_NOREMOVE : 메세지 큐의 메세지 유무만 판단, 만약 메세지를 가져오려면 GetMessage 함수를 따로 호출

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            if (dwTime + 10 < GetTickCount64())
            {
                MainGame.Update();
                MainGame.Render();

                dwTime = GetTickCount64();
            }
        }      
    }
    MainGame.Release();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rc{ 0, 0, WINCX, WINCY };

   // rc = rc + 기본 창 옵션 + 메뉴 바 크기 고려 여부

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, 0, // 생성되는 창의 LEFT, TOP 좌표
                            rc.right - rc.left, 
                            rc.bottom - rc.top, //생성되는 창의 가로, 세로 사이즈
                            nullptr, 
                            nullptr,
                            hInstance, 
                            nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// KERNEL : 창 생성, 메모리 관리와 관련된 명령어 집합
// USER : 각종 UI나 창 관련 명령어 집합
// GDI : 각종 그리기 명령어 집합

//RECT        rc{ 100, 100, 200, 200 };
//list<RECT>  BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
   // case WM_CREATE:
   //
   //     SetTimer(hWnd, 0, 0, 0);
   //     // 타이머 설치
   //      
   //     // 2. 타이머의 ID 번호
   //     // 3. 타이머의 주기, 기본값으로 1 / 1000 초
   //     // 4. NULL인 경우 설정한 주기대로 WM_TIMER 메세지를 발생
   //
   //     break;
   //
   // case WM_TIMER:
   //     InvalidateRect(hWnd, NULL, TRUE);
   //     // 윈도우(창) 갱신 함수 : WM_PAINT 메세지를 발생
   //
   //     //1. 갱신할 창 핸들
   //     //2. 창 갱신 범위(본래 RECT 주소를 넣으나 NULL인 경우 화면 전체 영역에 해당)
   //     //3. TRUE : 그려져 있는 않는 화면 모든 영역을 갱신
   //     //     FALSE : 그리는 부분만 화면 갱신        
   //
   //     break;

    case WM_KEYDOWN:

        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;

        //case VK_RIGHT:
        //    rc.left  += 10;
        //    rc.right += 10;
        //    break;
        //
        //case VK_LEFT:
        //    rc.left  -= 10;
        //    rc.right -= 10;
        //    break;
        //
        //case VK_UP:
        //    rc.top    -= 10;
        //    rc.bottom -= 10;
        //    break;
        //
        //case VK_DOWN:
        //    rc.top    += 10;
        //    rc.bottom += 10;
        //    break;
        //
        //case VK_SPACE:
        //    BulletList.push_back(rc);
        //    break;
        }

        break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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

    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //   
    //        // 커서의 위치를 이동(nullptr : 이전 커서의 위치를 반환 받고 싶을때 point 구조체 주소를 넣어줌)
    //        //MoveToEx(hdc, 100, 100, nullptr);
    //        //
    //        //LineTo(hdc, 200, 200);
    //        //LineTo(hdc, 200, 300);
    //
    //        //MoveToEx(hdc, 100, 100, nullptr);
    //        //LineTo(hdc, 200, 100);
    //        //LineTo(hdc, 200, 200);
    //        //LineTo(hdc, 100, 200);
    //        //LineTo(hdc, 100, 100);
    //        //LineTo(hdc, 200, 200);
    //        //
    //        //MoveToEx(hdc, 200, 100, nullptr);
    //        //LineTo(hdc, 100, 200);
    //
    //        // 사각형 그리기 함수
    //
    //        //Rectangle(hdc, 100, 100, 200, 200);
    //
    //        // 원 그리기 함수
    //        //Ellipse(hdc, 300, 300, 400, 400);
    //
    //        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    //
    //        for (auto& rect : BulletList)
    //        {
    //            Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
    //
    //            rect.top -= 10;
    //            rect.bottom -= 10;
    //        }
    //
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
