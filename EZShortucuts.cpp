// EZShortucuts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int keys[] = {
VK_OEM_MINUS, //-
VK_OEM_PERIOD, //>
0x41, //angry
0x43, //copyright
0x4D, //magic
0x48, //happy
0x4C, //leon
0x53, //sad
0x5A, //zzzzzz
0x4B //kawai
};

const wstring emoticons[] = { L"( ͡° ͜ʖ ͡°)", L"ಠ_ಠ", L"ヽ༼ ಠ益ಠ ༽ﾉ", L"©", L"╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ", L"(　＾∇＾)", L"(̿▀̿ ̿Ĺ̯̿̿▀̿ ̿)̄", L"(╥_╥)", L"눈_눈",L"(`･ω･´)" };

void SendKeystrokes(const wstring text)
{
	UINT i, characterCount, keystrokesToSend, keystrokesSent;

	characterCount = _tcslen(text.c_str());
	keystrokesToSend = characterCount * 2;
	INPUT * keystroke = new INPUT[keystrokesToSend];

	for (i = 0; i < characterCount&&i < 84; ++i)
	{
		keystroke[i * 2].type = INPUT_KEYBOARD;
		keystroke[i * 2].ki.wVk = 0;
		keystroke[i * 2].ki.wScan = text[i];
		keystroke[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
		keystroke[i * 2].ki.time = 0;
		keystroke[i * 2].ki.dwExtraInfo = GetMessageExtraInfo();

		keystroke[i * 2 + 1].type = INPUT_KEYBOARD;
		keystroke[i * 2 + 1].ki.wVk = 0;
		keystroke[i * 2 + 1].ki.wScan = text[i];
		keystroke[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		keystroke[i * 2 + 1].ki.time = 0;
		keystroke[i * 2 + 1].ki.dwExtraInfo = GetMessageExtraInfo();
	}

	keystrokesSent = SendInput((UINT)keystrokesToSend, keystroke, sizeof(*keystroke));
	delete[] keystroke;
}

wstring s2ws(const string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

void gotoStartup(wstring Path) {

	HKEY hkey = NULL;
	LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	LONG status = RegSetValueEx(hkey, L"EZShortcuts", 0, REG_SZ, (BYTE *)Path.c_str(), (Path.size() + 1) * sizeof(wchar_t));
}

void checkKeys() {
	for (int i = 0; i < sizeof(keys); i++) {
		if (GetAsyncKeyState(keys[i])) {
			SendKeystrokes(emoticons[i]);
			return;
		}
		Sleep(2);
	}
}

int main(int argc, char** argv)
{
	gotoStartup(s2ws(argv[0]));
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	while (true) {
		if (GetAsyncKeyState(0x12) && GetAsyncKeyState(VK_CONTROL))//ctrl+alt
			checkKeys();
		Sleep(200);
	}
	return 0;
}

