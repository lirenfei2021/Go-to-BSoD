// BSODTimeDlg.cpp: 实现文件
//

#include "pch.h"
#include "BSOD.h"
#include "afxdialogex.h"
#include "BSODTimeDlg.h"


// CBSODTimeDlg 对话框

IMPLEMENT_DYNAMIC(CBSODTimeDlg, CDialogEx)

CBSODTimeDlg::CBSODTimeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BSOD_TIME, pParent)
	, time(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CBSODTimeDlg::~CBSODTimeDlg()
{
}

void CBSODTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, time);
}


BEGIN_MESSAGE_MAP(CBSODTimeDlg, CDialogEx)
END_MESSAGE_MAP()


// CBSODTimeDlg 消息处理程序
