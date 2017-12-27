
// HupaiAssistant.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HupaiAssistant.h"
#include "MainDlg.h"
#include "TinyXML/tinyxml.h"
#include "tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//--------------------------------------------------------------------------------------------------

//
// Class: Setting
//

Settings::Settings() {

	if(FALSE == LoadSettings()) {
		AfxMessageBox(_T("����Config.xml�ļ�ʱ�����쳣��"));
	}
}


BOOL Settings::LoadSettings() {

	TiXmlDocument config_doc(CONFIG_FILE_PATH);
	TiXmlElement *eRoot, *e, *e1;
#define TI_FETCH(E, STR)				{ E = e->FirstChildElement(STR); ASSERT(E); }


	//
	// ���������ļ�
	//
	config_doc.LoadFile(TIXML_ENCODING_UTF8);
	if((eRoot = config_doc.RootElement()) == NULL) {
		return FALSE;
	}

	//
	// ��ȡ�����ļ�����
	//
	if(this->cfg_version = eRoot->Attribute("version")) {
		ASSERT(this->cfg_time = eRoot->Attribute("time"));
		ASSERT(this->cfg_desc = eRoot->Attribute("description"));
		ASSERT(eRoot->Attribute("real_mode"));
		this->isRealMode = (strcmp(eRoot->Attribute("real_mode"), "0") == 0) ? FALSE : TRUE;
	} else {
		return FALSE;
	}

	//
	// ��ȡ����������Ϣ
	//
	if(e = eRoot->FirstChildElement("BidInfo")) {
		// ��������
		TI_FETCH(e1, "BidDate");
		this->bid_date = e1->GetText();
		// ���Ľ���ʱ��
		TI_FETCH(e1, "EndTime");
		this->bid_time = Tools::TimeFromStr(e1->GetText());
		// ����ָ��
		TI_FETCH(e1, "Amount");
		this->bid_amount = atoi(e1->GetText());
		// ��ʾ��
		TI_FETCH(e1, "CapPrice");
		this->bid_cap_price = atoi(e1->GetText());
	} else {
		return FALSE;
	}

	//
	// ��ȡIE���������
	//
	if(e = eRoot->FirstChildElement("IE")) {
		// �������С
		TI_FETCH(e1, "Width");
		this->ie_width = atoi(e1->GetText());
		TI_FETCH(e1, "Height");
		this->ie_height = atoi(e1->GetText());
		// URL
		if(isRealMode) {
			TI_FETCH(e1, "URL");
		} else {
			TI_FETCH(e1, "URL_Practice");
		}
		this->ie_url = e1->GetText();
	} else {
		return FALSE;
	}

	//
	// ��ȡ�ͻ��˲����£�������ť��λ������
	//
	if(e = isRealMode ? eRoot->FirstChildElement("Position_alltobid") : eRoot->FirstChildElement("Position_51hupai")) {
		// �ο��������
		TI_FETCH(e1, "Index");
		this->pt_index = Tools::PointFromStr(e1->GetText());
		// �Ӽ�
		TI_FETCH(e1, "JJ_Input");
		this->pt_jiajia_input = Tools::PointFromStr(e1->GetText());
		TI_FETCH(e1, "JJ_Button");
		this->pt_jiajia = Tools::PointFromStr(e1->GetText());
		// ����
		TI_FETCH(e1, "CJ_Input");
		this->pt_chujia_input = Tools::PointFromStr(e1->GetText());
		TI_FETCH(e1, "CJ_Button");
		this->pt_chujia = Tools::PointFromStr(e1->GetText());
		// ��֤�벿��
		TI_FETCH(e1, "YZM_Input");
		this->pt_yzm_input = Tools::PointFromStr(e1->GetText());
		TI_FETCH(e1, "YZM_Refresh");
		this->pt_yzm_refresh = Tools::PointFromStr(e1->GetText());
		TI_FETCH(e1, "YZM_Submit");
		this->pt_yzm_ok = Tools::PointFromStr(e1->GetText());
		TI_FETCH(e1, "YZM_Cancle");
		this->pt_yzm_cancle = Tools::PointFromStr(e1->GetText());
		// ȷ�ϰ�ť����ָ������ť���
		TI_FETCH(e1, "OK_Button");
		this->pt_ok = Tools::PointFromStr(e1->GetText());
		// OCR����ʶ�𲿷֣�����
		TI_FETCH(e1, "OCR_Time");
		this->rgn_ocr_time = Tools::RectFromStr(e1->GetText());
		TI_FETCH(e1, "OCR_Price");
		this->rgn_ocr_price = Tools::RectFromStr(e1->GetText());
		TI_FETCH(e1, "YZM_Picture");
		this->rgn_yzm_picture = Tools::RectFromStr(e1->GetText());
		TI_FETCH(e1, "YZM_Info");
		this->rgn_yzm_info = Tools::RectFromStr(e1->GetText());
	} else {
		return FALSE;
	}

	//
	// �ȼ�����
	//
	if(e = eRoot->FirstChildElement("HotKey")) {
		// ���ȷ�ϰ�ť���Ի������һ����ť�����
		TI_FETCH(e1, "PressOK");
		this->hotkey_ok = Tools::LongFromStr(e1->GetText());
		// ���ȷ����֤�밴ť
		TI_FETCH(e1, "PressConfirm");
		this->hotkey_confirm = Tools::LongFromStr(e1->GetText());
		// ���ȡ����֤�밴ť
		TI_FETCH(e1, "PressCancle");
		this->hotkey_cancle = Tools::LongFromStr(e1->GetText());
		// ˢ����֤��
		TI_FETCH(e1, "PressRefresh");
		this->hotkey_refresh = Tools::LongFromStr(e1->GetText());
		// �����֤��
		TI_FETCH(e1, "ClearYZM");
		this->hotkey_clear = Tools::LongFromStr(e1->GetText());
		// ����Ĭ�Ϸ������ԣ���48s+700��
		TI_FETCH(e1, "ChuJia");
		this->hotkey_chujia = Tools::LongFromStr(e1->GetText());
		// �˳��κ��Զ�ģʽ
		TI_FETCH(e1, "AutoConfirm");
		this->hotkey_auto_confirm = Tools::LongFromStr(e1->GetText());
		// �˳��κ��Զ�ģʽ
		TI_FETCH(e1, "Escape");
		this->hotkey_escape = Tools::LongFromStr(e1->GetText());
		// ���ԣ�Ԥ����֤��
		TI_FETCH(e1, "TestYZM");
		this->hotkey_test_yzm = Tools::LongFromStr(e1->GetText());
	} else {
		return FALSE;
	}

	//
	// ��ȡ����ģʽ & ��������
	//
	if(e = eRoot->FirstChildElement("AutoBid")) {
		// ����ָ��ʱ���Զ����� �� �ֶ����� ��AutoTrigger = 0 �� 1��
		TI_FETCH(e1, "AutoTrigger");
		bid.auto_trigger = ("1" == e1->GetText()) ? TRUE : FALSE;
		TI_FETCH(e1, "TriggerTime");
		bid.trigger_time = Tools::TimeFromStr(e1->GetText());
		// ��ͼۼӼ���
		TI_FETCH(e1, "AddPrice");
		bid.add_price = atoi(e1->GetText());
		// ��ǰ���ٳ��ۣ�
		TI_FETCH(e1, "CommitAdvance");
		bid.commit_advance = atoi(e1->GetText());
		// ���������ʱ���ӳٶ���ʱ���ٳ��ۣ�
		TI_FETCH(e1, "CommitDelay");
		bid.commit_delay = Tools::TimeFromStr(e1->GetText());
		// �������ʱ�䣺�ڴ�ʱ�������ۣ�
		TI_FETCH(e1, "CommitBefore");
		bid.commit_before = Tools::TimeFromStr(e1->GetText());
	} else {
		return FALSE;
	}

	//
	// ������Ϣ���ؽ���
	//
	return TRUE;
}


BOOL Settings::SaveSettings() {

	return FALSE;
}


Status::Status() {

	serverHour = serverMinute = serverSecond = 0;
	serverDelay = 0;
	price = 0;
	bid_price = 0;
	autoBidStep = Status::NORMAL;
}

//--------------------------------------------------------------------------------------------------


//
// CHupaiAssistantApp
//

BEGIN_MESSAGE_MAP(CHupaiAssistantApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CHupaiAssistantApp::CHupaiAssistantApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


CHupaiAssistantApp theApp;


BOOL CHupaiAssistantApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = NULL; // new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	} else if (nResponse == IDCANCEL) {
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL) {
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
