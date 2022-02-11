﻿
// DlgProxy.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BSOD.h"
#include "DlgProxy.h"
#include "BSODDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBSODDlgAutoProxy

IMPLEMENT_DYNCREATE(CBSODDlgAutoProxy, CCmdTarget)

CBSODDlgAutoProxy::CBSODDlgAutoProxy()
{
	EnableAutomation();

	// 为使应用程序在自动化对象处于活动状态时一直保持
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CBSODDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CBSODDlg)))
		{
			m_pDialog = reinterpret_cast<CBSODDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CBSODDlgAutoProxy::~CBSODDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CBSODDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CBSODDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBSODDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IBSOD 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {6032051b-2d38-4413-b773-7b33f62a30dc}
static const IID IID_IBSOD =
{0x6032051b,0x2d38,0x4413,{0xb7,0x73,0x7b,0x33,0xf6,0x2a,0x30,0xdc}};

BEGIN_INTERFACE_MAP(CBSODDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CBSODDlgAutoProxy, IID_IBSOD, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏是在此项目的 pch.h 中定义的
// {8dc935a0-9c49-4977-8e49-9cbdc9eb0d32}
IMPLEMENT_OLECREATE2(CBSODDlgAutoProxy, "BSOD.Application", 0x8dc935a0,0x9c49,0x4977,0x8e,0x49,0x9c,0xbd,0xc9,0xeb,0x0d,0x32)


// CBSODDlgAutoProxy 消息处理程序
