#include <windows.h>
#include <vector>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    // ���������� ��������� ��� �����
    vector<RECT> rectangles; // ������ ��� ���������������
    vector<RECT> circles; // ������ ��� �����������
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    {
        HDC hdc; // �������� ����������
        PAINTSTRUCT ps; // ��������� ��� ��������� ����

        switch (message) // ���������� ��������� ����
        {
        case WM_CREATE: // ��������� � �������� ����
        {
            // ������� ��� ������ � �������� �� � ��������������� ����������
            RECT rect = { 10, 10, 100, 50 }; // ���������� ��������������
            rectangles.push_back(rect); // �������� ������������� � ������

            RECT circle = { 150, 10, 200, 60 }; // ���������� ����������
            circles.push_back(circle); // �������� ���������� � ������

            break;
        }

        case WM_PAINT: // ��������� � ����������� ����
        {
            hdc = BeginPaint(hWnd, &ps); // �������� �������� ����������

            // ��� ��������� ���� ������ �� �����������
            for (const auto& rect : rectangles) // �������� �� ������� ��������������� 
            {
                Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom); // ������ �������������
            }

            for (const auto& circle : circles) // ���������� �� ������� �����������
            {
                Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom); // ������ ����������
            }

            EndPaint(hWnd, &ps); // ���������� �������� ����������
            break;
        }

        case WM_DESTROY: // ��������� �� ����������� ����
        {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam); // ���� ��������� �� ����������, �������� ��� ��������� �������
        }

        return 0;
    }
}