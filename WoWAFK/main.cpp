#include <windows.h>

#include <thread>
#include <iostream>

#include <time.h>       /* time */

HANDLE cMainHandle;

   
int iMilliSleep = 1000;


unsigned int GetKeyboardCode(char cChar)
{
	if (toupper(cChar) == 'A')
		return 0x41;
	else if (toupper(cChar) == 'B')
		return 0x42;
	else if (toupper(cChar) == 'C')
		return 0x43;
	else if (toupper(cChar) == 'D')
		return 0x44;
	else if (toupper(cChar) == 'E')
		return 0x45;
	else if (toupper(cChar) == 'F')
		return 0x46;
	else if (toupper(cChar) == 'G')
		return 0x47;
	else if (toupper(cChar) == 'H')
		return 0x48;
	else if (toupper(cChar) == 'I')
		return 0x49;
	else if (toupper(cChar) == 'J')
		return 0x4A;
	else if (toupper(cChar) == 'K')
		return 0x4B;
	else if (toupper(cChar) == 'L')
		return 0x4C;
	else if (toupper(cChar) == 'M')
		return 0x4D;
	else if (toupper(cChar) == 'N')
		return 0x4E;
	else if (toupper(cChar) == 'O')
		return 0x4F;
	else if (toupper(cChar) == 'P')
		return 0x50;
	else if (toupper(cChar) == 'Q')
		return 0x51;
	else if (toupper(cChar) == 'R')
		return 0x52;
	else if (toupper(cChar) == 'S')
		return 0x53;
	else if (toupper(cChar) == 'T')
		return 0x54;
	else if (toupper(cChar) == 'U')
		return 0x55;
	else if (toupper(cChar) == 'V')
		return 0x56;
	else if (toupper(cChar) == 'W')
		return 0x57;
	else if (toupper(cChar) == 'X')
		return 0x58;
	else if (toupper(cChar) == 'Y')
		return 0x59;
	else if (toupper(cChar) == 'Z')
		return 0x5A;
	else if (cChar == '0')
		return 0x30;
	else if (cChar == '1')
		return 0x31;
	else if (cChar == '2')
		return 0x32;
	else if (cChar == '3')
		return 0x33;
	else if (cChar == '4')
		return 0x34;
	else if (cChar == '5')
		return 0x35;
	else if (cChar == '6')
		return 0x36;
	else if (cChar == '7')
		return 0x37;
	else if (cChar == '8')
		return 0x38;
	else if (cChar == '9')
		return 0x39;
	else if (cChar == '/')
		return VK_DIVIDE;
	else if (cChar == ' ')
		return VK_SPACE;
	else
		return 0;
}

DWORD WINAPI run(LPVOID lpParam)
{
    while (true)
    {
       
		INPUT ipKeyboard[1] = { 0 };

		ipKeyboard[0].type = INPUT_KEYBOARD;
		ipKeyboard[0].ki.wScan = MapVirtualKeyW(GetKeyboardCode(' '), MAPVK_VK_TO_VSC); // hardware scan code for key
		ipKeyboard[0].ki.time = 0;
		ipKeyboard[0].ki.dwExtraInfo = 0;
		ipKeyboard[0].ki.wVk = 0;
		ipKeyboard[0].ki.dwFlags = KEYEVENTF_SCANCODE;

        SendInput(1, ipKeyboard, sizeof(INPUT));

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		ipKeyboard[0].type = INPUT_KEYBOARD;
		ipKeyboard[0].ki.wScan = MapVirtualKeyW(GetKeyboardCode(' '), MAPVK_VK_TO_VSC); // hardware scan code for key
		ipKeyboard[0].ki.time = 0;
		ipKeyboard[0].ki.dwExtraInfo = 0;
		ipKeyboard[0].ki.wVk = GetKeyboardCode(' '); 
		ipKeyboard[0].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;

		SendInput(1, ipKeyboard, sizeof(INPUT));

		iMilliSleep = 10000 + rand() % ((60000 + 1) - 10000);

        std::this_thread::sleep_for(std::chrono::milliseconds(iMilliSleep));
    }
    return 0; 
}

int main()
{
    DWORD iMainThreadID;
    cMainHandle = CreateThread(0, 0, run, 0, 0, &iMainThreadID);

	srand(time(NULL));

    // Keep this app running until we're told to stop
    MSG msg;
    while (! GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CloseHandle(cMainHandle);
}