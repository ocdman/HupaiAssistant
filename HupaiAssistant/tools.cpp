#include "StdAfx.h"
#include "tools.h"
#include <stdlib.h>


//
// 数字0-9字模：
//
static const unsigned char numMask[10][16] = {
	0x00, 0x00, 0xF8, 0x00, 0xFC, 0x01, 0x06, 0x03, 0x02, 0x02, 0x06, 0x03, 0xFC, 0x01, 0xF8, 0x00, // 0
	0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x04, 0x02, 0xFE, 0x03, 0xFE, 0x03, 0x00, 0x02, 0x00, 0x02, // 1
	0x00, 0x00, 0x00, 0x00, 0x0C, 0x03, 0x8E, 0x03, 0xC2, 0x02, 0x62, 0x02, 0x3E, 0x03, 0x1C, 0x03, // 2
	0x00, 0x00, 0x00, 0x00, 0x8C, 0x01, 0x8E, 0x03, 0x12, 0x02, 0x12, 0x02, 0xFE, 0x03, 0xEC, 0x01, // 3
	0x00, 0x00, 0x40, 0x00, 0xF0, 0x00, 0xB8, 0x00, 0x8C, 0x02, 0xFF, 0x03, 0xFF, 0x03, 0x80, 0x02, // 4
	0x00, 0x00, 0x00, 0x00, 0xBE, 0x01, 0xBE, 0x03, 0x12, 0x02, 0x12, 0x02, 0xF2, 0x03, 0xE2, 0x01, // 5
	0x00, 0x00, 0xF8, 0x01, 0xFC, 0x03, 0x36, 0x02, 0x12, 0x02, 0x12, 0x02, 0xF6, 0x03, 0xE6, 0x01, // 6
	0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0xE2, 0x03, 0xFA, 0x03, 0x1E, 0x00, 0x06, 0x00, // 7
	0x00, 0x00, 0xCC, 0x01, 0xFE, 0x03, 0x32, 0x02, 0x22, 0x02, 0x32, 0x02, 0xFE, 0x03, 0xCC, 0x01, // 8
	0x00, 0x00, 0x3C, 0x03, 0x7E, 0x03, 0x42, 0x02, 0x42, 0x02, 0x62, 0x03, 0xFE, 0x01, 0xFC, 0x00, // 9
};
/*
FILE *fp = fopen("./mask.bmp", "rb");
FILE *fp2 = fopen("./mask.bin", "wb");
BITMAPFILEHEADER fileheader={0};
BITMAPINFOHEADER head={0};
fread(&fileheader,sizeof(fileheader),1,fp);
fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
BYTE *pData = new BYTE[head.biWidth*head.biHeight*head.biBitCount/8];
WORD *pMask = new WORD[head.biWidth * 2];
fread(pData, head.biWidth*head.biHeight*head.biBitCount/8, 1, fp);
memset(pMask, 0, head.biWidth * 2);
if(fileheader.bfType == 0x4D42 && head.biBitCount == 24) {
for(int i=0; i<head.biWidth; i++) {
for(int j=0; j<head.biHeight; j++) {
COLORREF c = *(COLORREF*)(pData+(head.biWidth*(head.biHeight-j-1)+i)*3) & 0xffffff;
pMask[i] |= (c == 0xffffff) ? 0 : 1 << j;
}
}
fwrite(pMask, head.biWidth*2, 1, fp2);
} 
delete [] pData;
delete [] pMask;
fclose(fp); 
fclose(fp2);
*/


Tools::Tools(void)
{
}


Tools::~Tools(void)
{
}


int Tools::MakeTime(int h, int m, int s, int ms/* =0 */) {

	return (((h * 60 + m) * 60) + s) * 1000 + ms;
}


int Tools::TimeFromStr(const char *p_t) {

	int h, m, s, ms;

	sscanf_s(p_t, "%d:%d:%d.%d", &h, &m, &s, &ms);

	return ((h*60+m)*60 + s)*1000 + ms;
}


CString Tools::TimeToStr(int i_t) {

	int h, m, s, ms;
	CString time;

	ms = i_t % 1000;
	i_t /= 1000;
	s = i_t % 60;
	i_t /= 60;
	m = i_t % 60;
	h = i_t / 60;
	time.Format(_T("%d:%d:%d.%d"), h, m, s, ms);

	return time;
}


CPoint Tools::PointFromStr(const char *p_p) {

	int x, y;

	sscanf_s(p_p, "%d,%d", &x, &y);

	return CPoint(x, y);
}


CString Tools::PointToStr(const CPoint *pt) {

	CString p_r;

	p_r.Format(_T("%d,%d"), pt->x, pt->y);

	return p_r;
}


CRect Tools::RectFromStr(const char *p_r) {

	int x1, x2, y1, y2;

	sscanf_s(p_r, "%d,%d,%d,%d", &x1, &y1, &x2, &y2);

	return CRect(x1, y1, x1+x2, y1+y2);
}


CString Tools::RectToStr(const CRect *rect) {

	CString r_r;

	r_r.Format(_T("%d,%d,%d,%d"), rect->left, rect->top, rect->Width(), rect->Height());

	return r_r;
}


LONG Tools::LongFromStr(const char *p_l) {

	if(NULL == p_l || "" == p_l) {
		return 0;
	}

	return atol(p_l);
}


BOOL Tools::SaveBitmap(const CDC *pdc, const char *name) {

	FILE *fp;
	CBitmap *bitmap;
	BITMAP bmp;
	BYTE *pData;
	BITMAPINFOHEADER bih = {0};
	BITMAPFILEHEADER bfh = {0};

	fopen_s(&fp, name, "wb");
	bitmap = pdc->GetCurrentBitmap();
	bitmap->GetBitmap(&bmp);
	
	bih.biBitCount = bmp.bmBitsPixel;
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
	bih.biWidth = bmp.bmWidth;

	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;
	bfh.bfType = (WORD)0x4d42;

	pData = new BYTE[bmp.bmWidthBytes * bmp.bmHeight];
	GetDIBits(pdc->m_hDC, (HBITMAP)bitmap->m_hObject, 0, bmp.bmHeight, pData, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
	fwrite(pData, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);
	fclose(fp);
	delete [] pData;

	return TRUE;
}

//
// 保存.bmp格式的图像文件
//
BOOL Tools::SaveBitmap2(HBITMAP hBitmap, const char *name) {

	FILE *fp;
	CBitmap *bitmap;
	BITMAP bmp;
	BYTE *pData;
	BITMAPINFOHEADER bih = { 0 };
	BITMAPFILEHEADER bfh = { 0 };

	fopen_s(&fp, name, "wb");
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	bih.biBitCount = bmp.bmBitsPixel;
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
	bih.biWidth = bmp.bmWidth;

	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;
	bfh.bfType = (WORD)0x4d42;

	pData = new BYTE[bmp.bmWidthBytes * bmp.bmHeight];
	GetDIBits(GetDC(NULL), hBitmap, 0, bmp.bmHeight, pData, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
	fwrite(pData, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);
	fclose(fp);
	delete[] pData;

	return TRUE;
}

BOOL Tools::SaveBitmap3(char *szFilename, HBITMAP hBitmap) {
	HDC					hdc = NULL;
	FILE*				fp = NULL;
	LPVOID				pBuf = NULL;
	BITMAPINFO			bmpInfo;
	BITMAPFILEHEADER	bmpFileHeader;

	do {

		hdc = GetDC(NULL);
		ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);

		if (bmpInfo.bmiHeader.biSizeImage <= 0)
			bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

		if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
		{
			MessageBox(NULL, _T("Unable to Allocate Bitmap Memory"), _T("Error"), MB_OK | MB_ICONERROR);
			break;
		}

		bmpInfo.bmiHeader.biCompression = BI_RGB;
		GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

		if ((fp = fopen(szFilename, "wb")) == NULL)
		{
			MessageBox(NULL, _T("Unable to Create Bitmap File"), _T("Error"), MB_OK | MB_ICONERROR);
			break;
		}

		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
		bmpFileHeader.bfType = 'MB';
		bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(pBuf, bmpInfo.bmiHeader.biSizeImage, 1, fp);

	} while (false);

	if (hdc)
		ReleaseDC(NULL, hdc);

	if (pBuf)
		free(pBuf);

	if (fp)
		fclose(fp);

	return TRUE;
}

BOOL Tools::GetBitmapMask(void *pData, const CDC *pdc) {

	CBitmap *bitmap;
	BITMAP bmp;
	BITMAPINFOHEADER bih = {0};
	BYTE *pBuff;
	WORD *pMask = (WORD *)pData;

	bitmap = pdc->GetCurrentBitmap();
	bitmap->GetBitmap(&bmp);

	// 必须为RGBA32格式，且高度为10px
	if(bmp.bmBitsPixel != 32 || bmp.bmHeight != 10) {
		return FALSE;
	}

	bih.biBitCount = bmp.bmBitsPixel;
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
	bih.biWidth = bmp.bmWidth;

	memset(pData, 0, bmp.bmWidth * 2);
	pBuff = new BYTE[bmp.bmWidthBytes * bmp.bmHeight];
	GetDIBits(pdc->m_hDC, (HBITMAP) bitmap->m_hObject, 0, bmp.bmHeight, pBuff, (LPBITMAPINFO) &bih, DIB_RGB_COLORS);

	// 先逐列扫描
	for(int i = 0; i < bmp.bmWidth; i++) {
		// 再逐行扫描
		for(int j = 0; j < bmp.bmHeight; j++) {
			COLORREF c = *(COLORREF *)(pBuff + (bmp.bmHeight - j - 1) * bmp.bmWidthBytes + i * 4) & 0xFFFFFF;
			pMask[i] |= (c == 0xFFFFFF) ? 0 : 1 << j;
		}
	}
	delete [] pBuff;

	return TRUE;
}

BOOL Tools::GetBitmapMask2(void *pData, HBITMAP hBitmap) {

	//CBitmap *bitmap;
	BITMAP bmp;
	BITMAPINFOHEADER bih = { 0 };
	BYTE *pBuff;
	WORD *pMask = (WORD *)pData;

	//bitmap = pdc->GetCurrentBitmap();
	//bitmap->GetBitmap(&bmp);

	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	// 必须为RGBA32格式，且高度为10px
	if (bmp.bmBitsPixel != 32 || bmp.bmHeight != 10) {
		return FALSE;
	}

	bih.biBitCount = bmp.bmBitsPixel;
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
	bih.biWidth = bmp.bmWidth;

	memset(pData, 0, bmp.bmWidth * 2);
	pBuff = new BYTE[bmp.bmWidthBytes * bmp.bmHeight];
	GetDIBits(GetDC(NULL), hBitmap, 0, bmp.bmHeight, pBuff, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);

	// 先逐列扫描
	for (int i = 0; i < bmp.bmWidth; i++) {
		// 再逐行扫描
		for (int j = 0; j < bmp.bmHeight; j++) {
			COLORREF c = *(COLORREF *)(pBuff + (bmp.bmHeight - j - 1) * bmp.bmWidthBytes + i * 4) & 0xFFFFFF;
			pMask[i] |= (c == 0xFFFFFF) ? 0 : 1 << j;
		}
	}
	delete[] pBuff;

	return TRUE;
}


int Tools::OCR_Number(const void *pData, int w, int h /* 10 */) {

	WORD *p = (WORD *)pData;
	int fst = 8, wlimit = w - fst, cnt;
	int val = 0;

	if(h != 10) { // 暂时只支持高10px的图像
		return -1;
	}

	for(int i=0; i<=wlimit;) {

		for(cnt=0; cnt<10; cnt++) {
			if(0 == memcmp(p + i, numMask[cnt], 16)) {
				val = val * 10 + cnt;
				i += fst;
				break;
			}
		}

		if(cnt == 10) {
			i++;
		}
	}

	return val;
}

//
// 执行外部命令行
//
CString Tools::ExecuteExternalFile(CString csExecute)
{
	SECURITY_ATTRIBUTES secattr;
	ZeroMemory(&secattr, sizeof(secattr));
	secattr.nLength = sizeof(secattr);
	secattr.bInheritHandle = TRUE;

	HANDLE rPipe, wPipe;

	//Create pipes to write and read data
	CreatePipe(&rPipe, &wPipe, &secattr, 0);
	//
	STARTUPINFO sInfo;
	ZeroMemory(&sInfo, sizeof(sInfo));

	PROCESS_INFORMATION pInfo;
	ZeroMemory(&pInfo, sizeof(pInfo));

	sInfo.cb = sizeof(sInfo);
	sInfo.dwFlags = STARTF_USESTDHANDLES;
	sInfo.hStdInput = NULL;
	sInfo.hStdOutput = wPipe;
	sInfo.hStdError = wPipe;

	char command[1024];
	strcpy(command, csExecute.GetBuffer(csExecute.GetLength()));

	//Create the process here.
	CreateProcess(0, command, 0, 0, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, 0, 0, &sInfo, &pInfo);
	CloseHandle(wPipe);

	//now read the output pipe here.

	char buf[100];
	DWORD reDword;
	CString m_csOutput, csTemp;
	BOOL res;
	do
	{
		res = ::ReadFile(rPipe, buf, 100, &reDword, 0);
		csTemp = buf;
		m_csOutput += csTemp.Left(reDword);
	} while (res);


	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);

	return  m_csOutput;
}
