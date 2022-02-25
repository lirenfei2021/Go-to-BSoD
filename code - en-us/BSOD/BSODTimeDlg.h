#pragma once
#include "afxdialogex.h"


// CBSODTimeDlg 对话框

class CBSODTimeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBSODTimeDlg)

public:
	CBSODTimeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBSODTimeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BSOD_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 蓝屏时间
	double time;
};
