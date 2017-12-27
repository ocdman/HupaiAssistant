
// HupaiAssistant.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"					// ������

#define CONFIG_FILE_PATH				"./config.xml"


class Settings
{
public:
	Settings();

public:
	// ���������ļ� & ��������
	BOOL LoadSettings(void);
	BOOL SaveSettings(void);

public:
//------------------------------------------------------------------------------
	//
	// �����ļ��汾��Ϣ
	//
	CString cfg_version;
	CString cfg_time;
	CString cfg_desc;
	BOOL	isRealMode;

	//
	// ������Ϣ
	//
	CString bid_date;
	int bid_time;
	int bid_amount;
	int bid_cap_price;

	//
	// IE���������
	//
	int ie_width;
	int ie_height;
	CString ie_url;

	//
	// ����ϵͳ���沼��
	//
	CPoint pt_index;					// �ο��㣨������Ͻǵĵ㣩�ڿͻ�����λ��
	CPoint pt_jiajia;					// �Ӽ۰�ť
	CPoint pt_jiajia_input;				// �Ӽ������
	CPoint pt_chujia;					// ���۰�ť
	CPoint pt_chujia_input;				// �۸������
	CPoint pt_yzm_input;				// ��֤�룺����
	CPoint pt_yzm_refresh;				// ��֤�룺ˢ��
	CPoint pt_yzm_ok;					// ��֤�룺ȷ��
	CPoint pt_yzm_cancle;				// ��֤�룺ȡ��
	CPoint pt_ok;						// ֻ��һ����ť�������ȷ��
	CRect rgn_ocr_time;					// ����ʶ�𣺷�����ʱ��
	CRect rgn_ocr_price;				// ����ʶ�𣺵�ǰ��ͼ�
	CRect rgn_yzm_picture;				// ��֤��ͼƬ��
	CRect rgn_yzm_info;					// ��֤����ʾ��Ϣ��

	//
	// ϵͳ�ȼ�
	//
	DWORD hotkey_ok;
	DWORD hotkey_confirm;
	DWORD hotkey_cancle;
	DWORD hotkey_refresh;
	DWORD hotkey_clear;
	DWORD hotkey_chujia;				// �磺+700����
	DWORD hotkey_auto_confirm;
	DWORD hotkey_escape;				// �˳����ڽ��е�ģʽ
	DWORD hotkey_test_yzm;				// ���ԣ�Ԥ����֤��

	//
	// �Զ�����ģʽ
	//
	typedef struct tagBid {
		BOOL auto_trigger;				// �Զ����������˴���ʱ���Զ����ۣ�
		int trigger_time;				// ����ʱ�䣺һ���еĵڼ�����
		int add_price;					// ��ͼۼӼ۷���
		int commit_advance;				// ��߼���ǰ������
		int commit_delay;				// ������߼��ӳٶ��ٺ������
		int commit_before;				// �������ʱ�䣨ǿ�Ƴ��ۣ�
	} Bid;
	Bid	bid;							// == ����ģʽ��48s+700 ==
//------------------------------------------------------------------------------
};


class Status
{
public:
	Status();
//------------------------------------------------------------------------------
	//
	// ��������Ϣ
	//
	volatile int serverHour;
	volatile int serverMinute;
	volatile int serverSecond;
	volatile int serverDelay;
	volatile int price;					// ��ǰ��ͼ�
	volatile int bid_price;				// Ŀ������۸�

	//
	// ���۽׶α�־
	//
	typedef enum tagAutoBidStep {
		NORMAL,
		YZM,
		AUTO_CONFIRM,
		CONFIRMED,
		FINISHED
	} AutoBidStep;
	volatile AutoBidStep autoBidStep;
//------------------------------------------------------------------------------
};


class CHupaiAssistantApp : public CWinApp
{
public:
	CHupaiAssistantApp();

public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()

public:
	Settings	settings;
	Status		status;
};

extern CHupaiAssistantApp theApp;
