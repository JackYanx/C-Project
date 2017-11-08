#include<windows.h>  
//打开保存文件对话框  
#include<Commdlg.h>  

//选择文件夹对话框  
#include<Shlobj.h>  
#pragma comment(lib,"Shell32.lib")  
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int WINAPI aaaWinMain( HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow)
{
loop:
	OPENFILENAME ofn = { 0 };
	TCHAR strFilename[MAX_PATH] = { 0 };//用于接收文件名  
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小  
	ofn.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	ofn.lpstrFilter = TEXT("所有文件\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//设置过滤  
	ofn.nFilterIndex = 1;//过滤器索引  
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL  
	ofn.nMaxFile = sizeof(strFilename);//缓冲区长度  
	ofn.lpstrInitialDir = NULL;//初始目录为默认  
	ofn.lpstrTitle = TEXT("请选择一个文件");//使用系统默认标题留空即可  
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//文件、目录必须存在，隐藏只读选项  
	if (GetOpenFileName(&ofn))
	{
		MessageBox(NULL, strFilename, TEXT("选择的文件"), 0);
	}
	else {
		MessageBox(NULL, TEXT("请选择一个文件"), NULL, MB_ICONERROR);
		goto loop;
	}

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//目录必须存在，覆盖文件前发出警告  
	ofn.lpstrTitle = TEXT("保存到");//使用系统默认标题留空即可  
	ofn.lpstrDefExt = TEXT("cpp");//默认追加的扩展名  
	if (GetSaveFileName(&ofn))
	{
		MessageBox(NULL, strFilename, TEXT("保存到"), 0);
	}
	else {
		MessageBox(NULL, TEXT("请输入一个文件名"), NULL, MB_ICONERROR);
	}

	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	bi.pszDisplayName = szBuffer;//接收文件夹的缓冲区  
	bi.lpszTitle = TEXT("选择一个文件夹");//标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (SHGetPathFromIDList(idl, szBuffer)) {
		MessageBox(NULL, szBuffer, TEXT("你选择的文件夹"), 0);
	}
	else {
		MessageBox(NULL, TEXT("请选择一个文件夹"), NULL, MB_ICONERROR);
	}

	return 0;
}