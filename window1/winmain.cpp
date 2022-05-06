#include <Windows.h>
#include <sstream>

//1.������ Ŭ���� ���
//2.������ ����� (1���� ������ Ŭ����)
//3. ������ �޽��� ����ó��
//4. ������ ���ν���(Procedure) �ۼ�

const wchar_t gClassName[] = L"MyWindowClass";

// ������ ���ν��� ����
	//HWND : �޽����� ���� ������
	//UINT : message ����
	//WPARAM : Word Parameter
	//LPARAM : Long Parameter
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	// ������ Ŭ����
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	// ������ Ŭ���� ���(os��)
	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed To Register Class!", L"Error", MB_OK);
		return 0;
	}

	//Ŭ������ ���� 
	HWND hwnd;

	hwnd = CreateWindowEx(
		0,
		gClassName,
		L"SimpleWindow App",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(nullptr, L"Failed To Create Window!", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	//�޽��� ����
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			std::stringstream ss;

			ss << "Virtual Key : " << wParam << ", Extra : " << lParam << std::endl;
				OutputDebugStringA(ss.str().c_str());
		}
	case WM_LBUTTONDOWN :
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		std::stringstream ss;
		ss << " x : " << x << ", y : " << y << std::endl;

		//MessageBoxA(hwnd, ss.str().c_str(), "Messagee test", MB_OK);
		OutputDebugStringA(ss.str().c_str());

		break;
		}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
