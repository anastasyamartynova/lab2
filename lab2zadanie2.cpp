#include <windows.h>
#include <vector>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    // Глобальное хранилище для фигур
    vector<RECT> rectangles; // Вектор для прямоугольников
    vector<RECT> circles; // Вектор для окружностей
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    {
        HDC hdc; // Контекст устройства
        PAINTSTRUCT ps; // Структура для отрисовки окна

        switch (message) // Обработчик сообщений окна
        {
        case WM_CREATE: // Сообщение о создании окна
        {
            // Создать две фигуры и добавить их в соответствующие контейнеры
            RECT rect = { 10, 10, 100, 50 }; // Координаты прямоугольника
            rectangles.push_back(rect); // Добавить прямоугольник в вектор

            RECT circle = { 150, 10, 200, 60 }; // Координаты окружности
            circles.push_back(circle); // Добавить окружность в вектор

            break;
        }

        case WM_PAINT: // Сообщение о перерисовке окна
        {
            hdc = BeginPaint(hWnd, &ps); // Получить контекст устройства

            // Для рисования всех фигуры из контейнеров
            for (const auto& rect : rectangles) // Проходит по вектору прямоугольников 
            {
                Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom); // Рисует прямоугольник
            }

            for (const auto& circle : circles) // Проходится по вектору окружностей
            {
                Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom); // Рисует окружность
            }

            EndPaint(hWnd, &ps); // Освободить контекст устройства
            break;
        }

        case WM_DESTROY: // Сообщение об уничтожении окна
        {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam); // Если сообщение не обработано, передаем его системной функции
        }

        return 0;
    }
}