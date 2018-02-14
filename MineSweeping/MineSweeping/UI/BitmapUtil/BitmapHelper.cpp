#include "BitmapHelper.h"  
//#include "string.h"  

BitmapHelper::BitmapHelper(TCHAR* file)
{
	this->hBitmap = NULL;
	this->desX = -9999;
	this->desY = -9999;
	lstrcpyn(this->fileName, file, 256);
	//StrCpyNW(this->fileName, file, 256);
	this->fileName[255] = TEXT('\0');
}

/*
功能:从位图文件创建DDB
参数: hdc 设备DC
返回值: DDB句柄，错误返回NULL
*/
HBITMAP BitmapHelper::CreateBitmapObjectFromDibFile(HDC hdc)
{
	BITMAPFILEHEADER* pbmfh = NULL;
	HANDLE hFile = NULL;
	DWORD dwFileSize = 0;

	hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	pbmfh = (BITMAPFILEHEADER*)malloc(dwFileSize);
	if (pbmfh == NULL)
	{
		CloseHandle(hFile);
		return NULL;
	}
	DWORD dwBytesRead = 0;
	BOOL bSuccess = ::ReadFile(hFile, pbmfh, dwFileSize, &dwBytesRead, NULL);
	::CloseHandle(hFile);
	// 验证文件确实是位图文件  
	if (!bSuccess || dwBytesRead != dwFileSize || pbmfh->bfType != *(WORD*) "BM" || pbmfh->bfSize != dwFileSize)
	{
		free(pbmfh);
		return NULL;
	}

	HBITMAP hBitmap = ::CreateDIBitmap(hdc,
		(BITMAPINFOHEADER*)(pbmfh + 1),
		CBM_INIT,
		(BYTE*)pbmfh + pbmfh->bfOffBits,
		(BITMAPINFO*)(pbmfh + 1),
		DIB_RGB_COLORS);

	free(pbmfh);

	return hBitmap;
}
/*
功能：在指定的设备上显示图片
参数：hdc 设备DC, (x,y)为目的左上角坐标
*/
void BitmapHelper::ShowOnDevice(HDC hdc, int x, int y)
{
	if (this->hBitmap == NULL)
	{
		this->hBitmap = this->CreateBitmapObjectFromDibFile(hdc);
	}
	if (this->hBitmap != NULL)
	{
		BITMAP bitmap;
		::GetObject(this->hBitmap, sizeof(BITMAP), &bitmap);

		HDC hdcMem = ::CreateCompatibleDC(hdc);
		::SelectObject(hdcMem, this->hBitmap);
		::BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		::DeleteDC(hdcMem);
	}
}
/*
功能：在指定窗口上显示位图
参数：hwnd 窗口句柄, (x,y) 目的左上角坐标
*/
void BitmapHelper::ShowOnWindow(HWND hwnd, int x, int y)
{
	if (this->hBitmap == NULL)
	{
		HDC hdc = ::GetDC(hwnd);
		this->hBitmap = this->CreateBitmapObjectFromDibFile(hdc);
		::ReleaseDC(hwnd, hdc);
	}
	if (this->hBitmap != NULL)
	{
		BITMAP bitmap;
		::GetObject(this->hBitmap, sizeof(BITMAP), &bitmap);

		HDC hdc = ::GetDC(hwnd);

		HDC hdcMem = ::CreateCompatibleDC(hdc);
		::SelectObject(hdcMem, this->hBitmap);
		::BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		::DeleteDC(hdcMem);

		::ReleaseDC(hwnd, hdc);
	}
}
/*
功能：根据文件名解析位置显示位图文件到指定窗口
参数: hwnd 目的窗口
说明: 位图文件命名规范 name_xxx-yyy.bmp
*/
void BitmapHelper::ShowOnWindow(HWND hwnd)
{
	// 解析文件名  
	if (this->desX == -9999)
	{
		int i = 0;
		int indexLast_ = 0; //最后一个_，表示坐标的开始  
		int indexLastDot = 0;   //最后一个.，表示扩展名的开始  
		int indexSep = 0;       // 坐标分割标志-  
		int n = wcslen(this->fileName);
		for (i = n - 1; i >= 0; i--)
		{
			if (this->fileName[i] == L'_')
			{
				break;
			}
		}
		indexLast_ = (i == 0 ? -1 : i); // -1 表示没有目录部分  
		for (i = n - 1; i >= 0; i--)
		{
			if (this->fileName[i] == L'.')
			{
				break;
			}
		}
		indexLastDot = (i == 0 ? n : i); // n表示没有扩展名部分  

		int xyStart = indexLast_ + 1; // 坐标起始位置  
		int xyEnd = indexLastDot - 1;     // 坐标结束位置  

		for (i = xyStart; i <= xyEnd; i++)
		{
			if (this->fileName[i] == L'-')
			{
				break;
			}
		}
		indexSep = i == xyEnd ? -1 : i; // -1 表示没有找到-  

		if (n == 0 || indexSep == -1) {
			this->desX = 0;
			this->desY = 0;
		}
		else
		{
			TCHAR s_x[10];
			int count = indexSep - xyStart;
			wcsncpy_s(s_x, 10, this->fileName + xyStart, count);
			s_x[count] = L'\0';
			this->desX = _wtoi(s_x);

			WCHAR s_y[10];
			count = xyEnd - indexSep;
			wcsncpy_s(s_y, 10, this->fileName + indexSep + 1, count);
			s_y[count] = L'\0';
			this->desY = _wtoi(s_y);
		}
	}
	this->ShowOnWindow(hwnd, this->desX, this->desY);
}
BitmapHelper::~BitmapHelper()
{
	if (this->hBitmap != NULL)         // 清理位图资源  
	{
		::DeleteObject(this->hBitmap);
	}
}