
/**************************************************************************

Copyright:MyCompany

Author: Lesley

Date:2016-10-14

Description:Provide  functions  to rotate Digital Image automatically

**************************************************************************/
// Mfc_rotateDlg.h : ͷ�ļ�

#include "stdafx.h"
#include "dirent.h"
#include "resource.h"
#include "Mfc_rotate.h"
#include "Exif.h"
#include "afx.h"   //ʹ��CString,��Ӵ˿⺯����ͬʱ���޸ģ��ھ�̬����ʹ�� MFC��ʹ�ö��ֽ��ַ���
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/ml/ml.hpp"  
#include "opencv2/objdetect/objdetect.hpp" 
#include "io.h"
#include "cv.h"
#include <windows.h>
#include<iostream>
#include "afxwin.h"
#include "afxcmn.h"
using namespace std;
using namespace cv;


#pragma once


// CMfc_rotateDlg �Ի���
class CMfc_rotateDlg : public CDialogEx
{
// ����
public:

	int nIndex;
	LV_ITEM lvItem;

	int m_Row;
	int m_Col;

	CBrush m_Brush;

	CMfc_rotateDlg(CWnd* pParent = NULL);	// ��׼���캯��
	//��ȡ�ļ���·��
	
	CString m_Path;
	CString m_SavePath;
	char* m_ImageDir;
	int Rd;
	struct _finddata_t  file_info;
	intptr_t  file_handle;
	//��ȡ����ͼ����ر���
	//������ת��ر���
	//CString building_Path;
	//IplImage* s_Building;
	IplImage* grayImage;
	IplImage* gradientImage;
	int mag[2];
//	void b_judge(IplImage *b);
//	void Soble(IplImage *img,IplImage* gradientImage) ;
	//exif��ת��ر���
	IplImage* s_Exif;
	CString Exif_Path;
	CString Exif_ImagePath;
	CString Esave_path;

	CString E_Imging;
	CString E_Imged;

	EXIFINFO m_exifinfo;
	int height,width,step,channels;
	uchar *data;
	int center[2];  //��תͼ��Ҫ�õı���
	void E_judge(CString &hFile);
	///������ת��ر���
	IplImage* resouse;
	IplImage* src;  
	IplImage* Img_rotate;
	DIR *m_pDir;
	struct dirent *m_pEnt;
	void Fun_call();
	void  detect_and_draw( IplImage* image );  //�������
	void detectEyes(IplImage* Eimg);           //�������
	void  myRotate(IplImage *img1, int x, int y, float degree,int center[2]);//��תͼ��
	void judge(IplImage* Src);//������תͼ��
	void check_radio();
	void Face();
//void Building();
	void Exif();
// �Ի�������
	enum { IDD = IDD_MFC_ROTATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton();
	BOOL m_exif;
	afx_msg void OnBnClickedButtonrotate();
	CListCtrl m_list;
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
