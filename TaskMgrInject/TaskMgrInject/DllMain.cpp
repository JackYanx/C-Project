/*********************************************************************************
���л��� Win32 x64 ,��Win10�����������Ч
**********************************************************************************/

#include <Windows.h>
#include <process.h>
#include <string>
#include <atlimage.h>
#include <sstream>
#include <vector>
#include <ctime>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") 

using namespace std;

HWND EnumHWnd;   //��������CPUʹ�ü�¼���ڵľ��
wstring ClassNameToEnum;
BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam) //Ѱ��CPUʹ�ü�¼������Ӵ���ID
{
	wchar_t WndClassName[255] = { 0 };
	GetClassName(hWnd, WndClassName, 255);
	wstring str;
	str = WndClassName;
	if (str == ClassNameToEnum)
	{
		wstringstream wsstr;
		wsstr << hWnd;

		RECT rect;
		GetWindowRect(hWnd, &rect);
		if (str == L"CtrlNotifySink")
			if ((rect.bottom - rect.top)<65)
				return true;
		if (str == L"CtrlNotifySink")
			if ((rect.right - rect.left)<65)
				return true;
		EnumHWnd = hWnd;   //����ҵ���CPUʹ�ü�¼�Ĵ��ڵĻ�, ������ֵ��EnumHWnd
		return false;
	}

	return true;
}
void FindCPUWnd()    //Ҫ�����������汾����������� �����������
{
	HWND h = FindWindow(L"TaskManagerWindow", L"���������");
	ClassNameToEnum = L"NativeHWNDHost";     //һ���Ӵ���
	EnumChildWindows(h, EnumChildWindowsProc, NULL);
	ClassNameToEnum = L"DirectUIHWND";		//�����Ӵ���
	EnumChildWindows(EnumHWnd, EnumChildWindowsProc, NULL);	//�Ӵ��ڵ���������Spy++���
	ClassNameToEnum = L"CtrlNotifySink";		//�����Ӵ���
	EnumChildWindows(EnumHWnd, EnumChildWindowsProc, NULL);
	ClassNameToEnum = L"CvChartWindow";		//�ļ��Ӵ���
	EnumChildWindows(EnumHWnd, EnumChildWindowsProc, NULL);

}

class FrameTimer //��ʱ��
{
private:
	unsigned int flag;
public:

	void start()
	{
		flag = clock();
	}
	operator int()
	{
		return ((clock() - flag));
	}

};


void MainThread(PVOID pv)
{
	MessageBoxW(NULL, (LPCWSTR)L"ע��ɹ�!", (LPCWSTR)L"ע��ɹ�!", MB_OK);
	printf("����ʱ5�뿪ʼ����...\n");
	Sleep(5400);
	printf("���ڲ���...\n");
	//FindCPUWnd(); //Ѱ��CPUʹ�ü�¼�Ĵ���,  ������Ѵ��ھ��������ȫ�ֱ���EnumHWnd
	EnumHWnd = (HWND)0x70358;
	HDC hdc = GetDC(EnumHWnd);
	vector<CImage> Frames;
	CImage img;
	wstringstream wsstr;
	WIN32_FIND_DATA wfd;
	HANDLE hFile = FindFirstFile(L"D:/Microsoft/Projects/TaskMgrInject/BadApple/Image/*.*", &wfd); //D:/TaskmgrPlayer/BadAppl Ϊ���ÿ֡ͼƬ��·��  
	FrameTimer ft;
	unsigned int FrameTick = 0;
	//ft.SetFPSAndVideoLong(30,9999);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		int UpPixel = RGB(0, 0, 0);
		FindNextFile(hFile, &wfd);
		PlaySound(L"D:/Microsoft/Projects/TaskMgrInject/BadApple/BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);  //��������
		ft.start();
		for (; FindNextFile(hFile, &wfd);)
		{
			wsstr.str(L"");
			wsstr << L"D:/Microsoft/Projects/TaskMgrInject/BadApple/Image/" << wfd.cFileName;    //D:/TaskmgrPlayer/BadAppl Ϊ���ÿ֡ͼƬ��·��
			img.Load(wsstr.str().c_str());
			wsstr.str(L"");
			byte* pRealData;
			pRealData = (byte*)img.GetBits();
			int pit = img.GetPitch();
			int bitCount = img.GetBPP() / 8;
			RECT rect;
			GetWindowRect(EnumHWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			//int w = rect.right;
			//rect.
			//int h = rect.bottom;
			for (int y = 0; y<img.GetHeight(); y++)   //��ͼ���ֵ��
			{
				for (int x = 0; x<img.GetWidth(); x++)
				{

					int grayVal = (int)(int)(*(pRealData + pit*y + x*bitCount))>192 ? 255 : 0;
					if (grayVal<128)
					{
						*(pRealData + pit*y + x*bitCount) = grayVal;       //B
						*(pRealData + pit*y + x*bitCount + 1) = grayVal;    //G
						*(pRealData + pit*y + x*bitCount + 2) = grayVal;     //R
					}
				}
			}

			for (int x = 0; x<img.GetWidth(); x++)   //��Ե���
			{
				for (int y = 0; y<img.GetHeight(); y++)
				{

					int grayVal = (int)(int)(*(pRealData + pit*y + x*bitCount))>192 ? 255 : 0;
					if (abs(grayVal - UpPixel)>250)
					{
						*(pRealData + pit*y + x*bitCount) = 187;
						*(pRealData + pit*y + x*bitCount + 1) = 152;
						*(pRealData + pit*y + x*bitCount + 2) = 17;
					}
					UpPixel = grayVal;
				}
			}

			for (int y = 0; y<img.GetHeight(); y++)   //��Ե���
			{
				for (int x = 0; x<img.GetWidth(); x++)
				{

					int grayVal = (int)(int)(*(pRealData + pit*y + x*bitCount))>192 ? 255 : 0;
					if (abs(grayVal - UpPixel)>250)
					{
						*(pRealData + pit*y + x*bitCount) = 187;       //B
						*(pRealData + pit*y + x*bitCount + 1) = 152;    //G
						*(pRealData + pit*y + x*bitCount + 2) = 17;     //R
					}
					if ((x == 0 || x == img.GetWidth() - 1) || (y == 0 || y == img.GetHeight() - 1))  //����ɫ�߿�
					{
						*(pRealData + pit*y + x*bitCount) = 187;       //B
						*(pRealData + pit*y + x*bitCount + 1) = 152;    //G
						*(pRealData + pit*y + x*bitCount + 2) = 17;     //R
					}
					UpPixel = grayVal;
				}
			}

			for (int y = 0; y<img.GetHeight(); y++)  //��������
			{
				for (int x = 0; x<img.GetWidth(); x++)
				{

					int grayVal = (int)(int)(*(pRealData + pit*y + x*bitCount));
					if (grayVal<128)       //������Ϊǳ��ɫ
					{
						*(pRealData + pit*y + x*bitCount) = 250;       //B
						*(pRealData + pit*y + x*bitCount + 1) = 246;    //G
						*(pRealData + pit*y + x*bitCount + 2) = 241;     //R
					}
					if ((y % (h / 10) == 0) && y != 0)   //������ĺ���
					{
						*(pRealData + pit*y + x*bitCount) = 240;       //B    
						*(pRealData + pit*y + x*bitCount + 1) = 226;    //G
						*(pRealData + pit*y + x*bitCount + 2) = 206;    //R
					}
					if ((x % (w / 20) == (ft / 1000)*((w / 40)) % (w / 20)) && x != 0)   //�����������
					{
						int rx = x;
						*(pRealData + pit*y + rx*bitCount) = 240;       //B
						*(pRealData + pit*y + rx*bitCount + 1) = 226;    //G
						*(pRealData + pit*y + rx*bitCount + 2) = 206;    //R
					}
				}
			}
			int x = img.GetWidth();
			int y = img.GetHeight();
			for (int i = (int)(ft / 41.66); i == (int)(ft / 41.66);) {
				img.Draw(hdc, 0, 0, (int)x, (int)y);
			}  //41.66Ϊÿ֡��ռ��ʱ��
				
			++FrameTick;
			img.Destroy();
		}
		FindClose(hFile);
	}
	printf("���Ž���\n");
	_endthread();
}




int WINAPI DllMain(HINSTANCE  hInstance, DWORD fdwReason, PVOID pReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		_beginthread(MainThread, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}