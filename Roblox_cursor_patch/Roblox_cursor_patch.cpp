#include <iostream>
#include <windows.h>

int center_x, center_y;
int toggle_key;

void MoveCursorToCenter()
{
    POINT center;
    center.x = center_x;
    center.y = center_y;
    SetCursorPos(center.x, center.y);
}

void SetConsoleTextColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    SetConsoleTitle(TEXT("Windows Roblox Cursor Fix"));
    SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout << "Press any key to set it as the toggle key" << std::endl;

    while (true)
    {
        for (int i = 8; i <= 255; i++)
        {
            if (GetAsyncKeyState(i) & 0x8000)
            {
                toggle_key = i;
                break;
            }
        }

        if (toggle_key != 0)
            break;
    }

    std::cout << "Toggle key set to code: " << toggle_key << std::endl;
    std::cout << "Press the key with code " << toggle_key << " to toggle ON/OFF" << std::endl;

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    int screen_width = desktop.right;
    int screen_height = desktop.bottom;

    center_x = screen_width / 2;
    center_y = screen_height / 2;

    bool toggle_state = false;
    bool previous_state = false;

    while (true)
    {
        bool current_state = (GetKeyState(toggle_key) & 0x8000) != 0;
        if (current_state && !previous_state)
        {
            toggle_state = !toggle_state;
            system("cls");
            if (toggle_state)
            {
                std::cout << "Toggle ON" << std::endl;
                std::cout << "Press the key with code " << toggle_key << " to toggle OFF" << std::endl;
            }
            else
            {
                std::cout << "Toggle OFF" << std::endl;
                std::cout << "Press the key with code " << toggle_key << " to toggle ON" << std::endl;
            }
        }

        previous_state = current_state;

        if (toggle_state)
            MoveCursorToCenter();
    }

    return 0;
}
