#include<windows.h>  
//�򿪱����ļ��Ի���  
#include<Commdlg.h>  

//ѡ���ļ��жԻ���  
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
	TCHAR strFilename[MAX_PATH] = { 0 };//���ڽ����ļ���  
	ofn.lStructSize = sizeof(OPENFILENAME);//�ṹ���С  
	ofn.hwndOwner = NULL;//ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬�ģ�ʵ��Ӧ����һ�㶼Ҫ��������  
	ofn.lpstrFilter = TEXT("�����ļ�\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//���ù���  
	ofn.nFilterIndex = 1;//����������  
	ofn.lpstrFile = strFilename;//���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL  
	ofn.nMaxFile = sizeof(strFilename);//����������  
	ofn.lpstrInitialDir = NULL;//��ʼĿ¼ΪĬ��  
	ofn.lpstrTitle = TEXT("��ѡ��һ���ļ�");//ʹ��ϵͳĬ�ϱ������ռ���  
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//�ļ���Ŀ¼������ڣ�����ֻ��ѡ��  
	if (GetOpenFileName(&ofn))
	{
		MessageBox(NULL, strFilename, TEXT("ѡ����ļ�"), 0);
	}
	else {
		MessageBox(NULL, TEXT("��ѡ��һ���ļ�"), NULL, MB_ICONERROR);
		goto loop;
	}

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//Ŀ¼������ڣ������ļ�ǰ��������  
	ofn.lpstrTitle = TEXT("���浽");//ʹ��ϵͳĬ�ϱ������ռ���  
	ofn.lpstrDefExt = TEXT("cpp");//Ĭ��׷�ӵ���չ��  
	if (GetSaveFileName(&ofn))
	{
		MessageBox(NULL, strFilename, TEXT("���浽"), 0);
	}
	else {
		MessageBox(NULL, TEXT("������һ���ļ���"), NULL, MB_ICONERROR);
	}

	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = NULL;//ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬�ģ�ʵ��Ӧ����һ�㶼Ҫ��������  
	bi.pszDisplayName = szBuffer;//�����ļ��еĻ�����  
	bi.lpszTitle = TEXT("ѡ��һ���ļ���");//����  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (SHGetPathFromIDList(idl, szBuffer)) {
		MessageBox(NULL, szBuffer, TEXT("��ѡ����ļ���"), 0);
	}
	else {
		MessageBox(NULL, TEXT("��ѡ��һ���ļ���"), NULL, MB_ICONERROR);
	}

	return 0;
}