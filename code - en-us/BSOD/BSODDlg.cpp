
// BSODDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BSOD.h"
#include "BSODDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "BSODTimeDlg.h"
#include "sstream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::stringstream;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBSODDlg 对话框


IMPLEMENT_DYNAMIC(CBSODDlg, CDialogEx);

CBSODDlg::CBSODDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BSOD_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CBSODDlg::~CBSODDlg()
{
	// 如果该对话框有自动化代理，则
	//  此对话框的返回指针为 null，所以它知道
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CBSODDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBSODDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBSODDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CBSODDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CBSODDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CBSODDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CBSODDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CBSODDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CBSODDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CBSODDlg 消息处理程序

BOOL CBSODDlg::OnInitDialog()
{
	GetPrivilege();

	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	/*CString strload;
	strload.LoadString(BTN_OK);
	GetDlgItem(IDOK)->SetWindowText(strload);
	strload.LoadString(BTN_CANCEL);
	GetDlgItem(IDCANCEL)->SetWindowText(strload);*/

	SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBSODDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBSODDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBSODDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CBSODDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CBSODDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CBSODDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CBSODDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CBSODDlg::OnBnClickedButton1()
{
	GetPrivilege();
	if (MessageBox(_T("Do you want to go to BSoD?"), _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
	{
		EndDialog(0);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton4()
{
	GetPrivilege();
	if (MessageBoxEx(NULL, L"Do you want to go to BSoD after 20 sec?", _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(20000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton2()
{
	GetPrivilege();
	if (MessageBoxEx(NULL, L"Do you want to go to BSoD after 5 sec?", _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(5000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton5()
{
	GetPrivilege();
	if (MessageBoxEx(NULL, L"Do you want to go to BSoD after 30 sec?", _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(30000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton3()
{
	GetPrivilege();
	if (MessageBoxEx(NULL, L"Do you want to go to BSoD after 10 sec?", _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(10000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton6()
{
	GetPrivilege();
	if (MessageBoxEx(NULL, L"Do you want to go to BSoD after 1 min?", _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(60000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CBSODDlg::OnBnClickedButton8()
{
	GetPrivilege();
	CBSODTimeDlg time;
	double bsod_time;
	INT_PTR nRes = time.DoModal();
	if (IDCANCEL == nRes)
	{
		return;
	}
	else
	{
		bsod_time = time.time;
	}
	CString str;
	str.Format((CString)"Do you want to go to BSoD after %g sec ? ", bsod_time);
	if (MessageBoxEx(NULL, str, _T(""), MB_ICONWARNING | MB_OKCANCEL | MB_SYSTEMMODAL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDOK)
	{
		EndDialog(0);
		Sleep(bsod_time * 1000);
		WinExec("taskkill -f -im svchost.exe", SW_HIDE);
		WinExec("taskkill -f -im wininit.exe", SW_HIDE);
	}
	// TODO: 在此添加控件通知处理程序代码
}
bool CBSODDlg::GetPrivilege(void)
{
	// 提权成功 记得关闭该进程；
	CreateEvent(NULL, FALSE, FALSE, _T("{29544E05-024F-4BC1-A272-452DBC8E17A4}"));
	if (ERROR_SUCCESS != GetLastError())
	{
		return false;
	}
	else
	{
		TCHAR strPath[MAX_PATH] = { 0 };
		HMODULE hModule = NULL;
		GetModuleFileName(hModule, strPath, MAX_PATH);

		SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
		sei.lpVerb = TEXT("runas");
		sei.lpFile = strPath;
		sei.nShow = SW_SHOWNORMAL;
		if (!ShellExecuteEx(&sei))
		{
			DWORD dwStatus = GetLastError();
			if (dwStatus == ERROR_CANCELLED)
			{
				exit(0);
			}
			else if (dwStatus == ERROR_FILE_NOT_FOUND)
			{
				exit(0);
			}
		}
	}
	Sleep(100);        // 防止退出的太早
	exit(1);
}

BOOL CBSODDlg::PreTranslateMessage(MSG *pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CDialogEx::PreTranslateMessage(pMsg);
}
