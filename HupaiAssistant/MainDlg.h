
// HupaiAssistantDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#define MIN_ADD_INTERVAL				100 // ��С�Ӽ���
#define PRICE_INTERVAL					300 // ���ܳ�������

#define DISP_WIDTH						500
#define DISP_HEIGHT						400

#define CLICK_DELAY						50

//
// �ȼ�����
//
#define HOTKEY_OK						WM_USER + 1000
#define HOTKEY_CONFIRM					WM_USER + 1001
#define HOTKEY_CANCLE					WM_USER + 1002
#define HOTKEY_REFRESH					WM_USER + 1003
#define HOTKEY_CLEAR					WM_USER + 1004
#define HOTKEY_CHUJIA					WM_USER + 1005
#define HOTKEY_AUTO_CONFIRM				WM_USER + 1006
#define HOTKEY_ESCAPE					WM_USER + 1007
#define HOTKEY_TEST_YZM					WM_USER + 100


// CHupaiAssistantDlg �Ի���
class CMainDlg : public CDialogEx
{
public:
	CMainDlg(CWnd* pParent = NULL);
	~CMainDlg();
protected:
	enum { IDD = IDD_MAIN_DIALOG };
	HICON m_hIcon;

	CButton		m_EnableHotKey;			// ��ϵͳ�ȼ���
	CHotKeyCtrl	m_HotKey;				// �ȼ��ؼ�
	CButton		m_CalcHotKey;			// �����ȼ�ֵ�İ�ť

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedHotkeyMode();
	afx_msg void OnBnClickedHotkeyCalc();
	DECLARE_MESSAGE_MAP()

private:

	CPen		penSolid;
	CPen		penDot;
	CBrush		brush;
	CFont		font;
	CFont		fontS;
	CFont		fontM;
	CFont		fontL;

	BOOL RegistHotKey();
	BOOL UnregisteHotKey();
	// static BOOL IEScreenShot(CDC *, CBitmap *, CRect *);

public:
	// IE�����Ϣ
	static CWnd	*pWndIE;

	// ���ϵͳ��Ϣ��ϵͳʱ�䡢��ǰ��ͼ�
	static volatile BOOL canNormal;
	static volatile BOOL isNormal;
	static void Thread_Normal(void *);

	// �Զ������߳�
	static volatile BOOL canAutoConfirm;
	static volatile BOOL isAutoConfirm;
	static void Thread_AutoConfirm(void *);

	// ���ԣ�Ԥ����֤�루����HOTKEY��Ϣ��
	// static void Thread_TestYZM(void *);
};
