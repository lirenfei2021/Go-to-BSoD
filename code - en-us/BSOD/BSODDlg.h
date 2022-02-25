
// BSODDlg.h: 头文件
//

#pragma once

class CBSODDlgAutoProxy;


// CBSODDlg 对话框
class CBSODDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBSODDlg);
	friend class CBSODDlgAutoProxy;

// 构造
public:
	CBSODDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CBSODDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BSOD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CBSODDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	bool GetPrivilege(void);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
};
