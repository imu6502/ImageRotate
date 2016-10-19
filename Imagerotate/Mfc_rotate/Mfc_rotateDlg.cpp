
/**************************************************************************

Copyright:MyCompany

Author: Lesley

Date:2016-10-14

Description:Provide  functions  to rotate Digital Image automatically

**************************************************************************/
// Mfc_rotateDlg.cpp : Implementation files


#include "stdafx.h"
#include "Mfc_rotateDlg.h"
#include "afxdialogex.h"
#include <string.h>  

#ifdef _DEBUG
#define new DEBUG_NEW
#define PI 3.14

#define WM_UPDATE_MESSAGE (WM_USER+200)  //Defines a message
#endif

//Updatedata(TRUE) == 将控件的值赋值给成员变量(Assign the value of a control to a member variable);　　                                   
//Updatedata(FALSE) == 将成员变量的值赋值给控件(Assigns the value of the member variable to the control);

// The CAboutDlg dialog box for the application's About menu item

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据(Dialog box data)
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// implement
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//{{AFX_MSG_MAP(CCServerDlg)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMfc_rotateDlg 对话框



CMfc_rotateDlg::CMfc_rotateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMfc_rotateDlg::IDD, pParent)
	, m_exif(FALSE)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfc_rotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO11, m_exif);
	DDX_Control(pDX, IDC_LIST, m_list);

}

BEGIN_MESSAGE_MAP(CMfc_rotateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMfc_rotateDlg::OnBnClickedButton1)


	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(SAVE_BUTTON, &CMfc_rotateDlg::OnBnClickedButton)


	ON_BN_CLICKED(IDC_BUTTONROTATE, &CMfc_rotateDlg::OnBnClickedButtonrotate)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CMfc_rotateDlg::OnClickList)
END_MESSAGE_MAP()


// CMfc_rotateDlg 消息处理程序


BOOL CMfc_rotateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Brush.CreateSolidBrush(RGB(245,245,245));

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);



	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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


	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_Row=-1;
	m_Col=-1;


	CRect r;  
	m_list.GetClientRect(&r);  
	int iLength = r.Width();  
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS );  
	m_list.InsertColumn(0, "The processing image storage path", LVCFMT_CENTER, iLength/2);  
	m_list.InsertColumn(1, "The processed image storage path", LVCFMT_CENTER, iLength/2);  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMfc_rotateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfc_rotateDlg::OnPaint()
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
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,RGB(245,245,245));
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMfc_rotateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*Interface color beautification function*/

HBRUSH CMfc_rotateDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		if(pWnd->GetDlgCtrlID()== IDC_STATIC)
		{
			pDC->SetTextColor(RGB(0,0,0)); //文字颜色  
			pDC->SetBkColor(RGB(245, 245, 245));
			return (HBRUSH) m_Brush.GetSafeHandle();
		}
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	else
		return hbr;
}

/*   define jpeg quaity    */

#define CV_IMWRITE_JPEG_QUALITY 1


/* Processing function*/

void CMfc_rotateDlg::Fun_call()
{

	src= cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 
	E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);

	nIndex = m_list.GetItemCount();
	lvItem.mask = LVIF_TEXT ; 
	//Rows
	lvItem.iItem = nIndex;    
	lvItem.iSubItem = 0;
	//first row
	lvItem.pszText = (char*)(LPCTSTR)E_Imging;   
	//Call the judgment function
	judge(src);

	//插入其它列
	////////////////更新列表数据////////////////////////
	m_list.SetRedraw(FALSE);
	m_list.SetItemText(nIndex,1,E_Imged);
	m_list.SetRedraw(TRUE);
	m_list.Invalidate();
	m_list.UpdateWindow();
	//在最后一行插入记录值.
	m_list.InsertItem(&lvItem);
	while(_findnext(file_handle, &file_info) == 0)
	{
		////////更新列表数据////////////////

		m_list.SetRedraw(FALSE);
		m_list.SetItemText(nIndex,1,E_Imged);
		m_list.SetRedraw(TRUE);
		m_list.Invalidate();
		m_list.UpdateWindow();  

		E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);
		nIndex = m_list.GetItemCount();
		lvItem.mask = LVIF_TEXT ; 
		lvItem.iItem = nIndex;     //行数
		lvItem.iSubItem = 0;
		lvItem.pszText = (char*)(LPCTSTR)E_Imging;   //第一列
		//插入其它列

		resouse = cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 
		judge(resouse);
		m_list.SetRedraw(FALSE);
		m_list.SetItemText(nIndex,1,E_Imged); 
		m_list.SetRedraw(TRUE);
		m_list.Invalidate();
		m_list.UpdateWindow();  
		//在最后一行插入记录值.
		m_list.InsertItem(&lvItem);
	}
	/* the display of the last processed image stores path */
	m_list.SetRedraw(FALSE);
	m_list.SetItemText(nIndex,1,E_Imged); 
	m_list.SetRedraw(TRUE);
	m_list.Invalidate();
	m_list.UpdateWindow();  
	_findclose(file_handle);
	MessageBox("All images have been rotated, thanks to use this program!");

}

/*Face Rotate judge Function*/
/*
*@Src:Resourse Image
*/

void CMfc_rotateDlg::judge(IplImage* Src)
{

	IplImage* img0;
	int height,width,step,channels;
	uchar *data;

	int p[3];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 100;
	p[2] = 0;

	int center[2]={0,0};   //旋转图片的参数定义
	height    = Src->height;  
	width     = Src->width;	
	step      = Src->widthStep;	
	channels  = Src->nChannels;
	data = (uchar *)Src->imageData;
	printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
	center[0]=width/2;//这两句可以设置旋转中心的坐标
	center[1]=height/2;
	int count=0,count1=0;
	detect_and_draw(Src);
	cout<<Rd<<endl;

	if(Rd>0)           //图片方向正确就跳出
	{
		img0=cvCloneImage(Src);
		cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),img0,p);
		//	UpdateData(FALSE);
		E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);	
	}
	else
	{
		while((count<12)&&(Rd==0))
		{ 		
			myRotate(Src,0,0,count*30,center);
			detect_and_draw(Img_rotate);
			count++;
			if(Rd>0)
				break;
		}
		img0=cvCloneImage(Img_rotate);
		cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),img0,p);

		E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);


		cvReleaseImage( &img0 );  
	}
}


/*Face detect Function*/
/*
*@Rimg:Resourse Image
*/
void CMfc_rotateDlg::detect_and_draw( IplImage* Rimg )  
{  
	static CvHaarClassifierCascade* cascade = 0; 
	static CvMemStorage* storage = 0;  
	const char* cascade_name="haarcascade_frontalface_alt.xml";                //人脸检测要用到的分类器 
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );   //加载人脸检测所用的分类器  
	if(!cascade )  
	{  
		fprintf( stderr, "ERROR: Could not load faces classifier cascade\n" );  
		exit(0);  
	} 
	storage = cvCreateMemStorage(0); 
	static CvScalar colors[] =   
	{  
		{{0,0,255}},  
		{{0,128,255}},  
		{{0,255,255}},  
		{{0,255,0}},  
		{{255,128,0}},  
		{{255,255,0}},  
		{{255,0,0}},  
		{{255,0,255}}  
	};  
	double scale = 1.3;  
	CvSeq* faces;
	CvRect* r;
	IplImage* gray = cvCreateImage( cvSize(Rimg->width,Rimg->height), 8, 1 );  //灰度化图像
	IplImage* small_img = cvCreateImage( cvSize( cvRound (Rimg->width/scale), 
		cvRound (Rimg->height/scale)), 8, 1 );    //缩小图像
	cvCvtColor( Rimg, gray, CV_BGR2GRAY ); 
	cvResize( gray, small_img, CV_INTER_LINEAR );    //缩放灰度图到小图大小
	cvEqualizeHist( small_img, small_img );   //是灰度直方图均衡化
	cvClearMemStorage( storage );  //清除动态内存存储
	assert(cascade!=NULL);  
	/*函数cvHaarDetectObjects检测图像中的目标，由OpenCV提供。*/ 
	faces = cvHaarDetectObjects(small_img, cascade, storage, 1.1, 3, 0 ,  
		cvSize(30, 30) ); 
	for( int i = 0; i < (faces ? faces->total : 0); i++ )  
	{  
		r = (CvRect*)cvGetSeqElem( faces, i );  
	}
	Rd=faces->total;
}

/*Rotate Function*/
/*
*@img1:  Resourse Image
*@x:  Image's long
*@y:  Image's wide
*@degree:  rotate degree
*@center[2]:  the center of Image
*/

void CMfc_rotateDlg::myRotate(IplImage *img1, int x, int y, float degree,int center[2])
{

	double angle = degree  * CV_PI / 180.; // angle in radian
	double a = sin(angle), b = cos(angle); // sine and cosine of angle
	IplImage* imgSrc=cvCloneImage(img1);
	int w_src = imgSrc->width;
	int h_src = imgSrc->height;
	// Make w_dst and h_dst to fit the output image
	//int w_dst = int(h_src * a + w_src * b);
	//int h_dst = int(w_src * a + h_src * b);
	int w_dst = int(h_src * abs(a) + w_src * abs(b));
	int h_dst = int(w_src * abs(a) + h_src * abs(b));

	// map matrix for WarpAffine, stored in statck array
	double map[6];
	CvMat map_matrix = cvMat(2, 3, CV_64FC1, map);

	// Rotation center needed for cv2DRotationMatrix
	CvPoint2D32f pt = cvPoint2D32f(w_src / 2, h_src / 2);
	//	CvPoint2D32f pt = cvPoint2D32f(center[0], center[1]);
	cv2DRotationMatrix(pt, degree, 1.0, &map_matrix);

	// otherwise you will get only part of the result
	//map[2] +=x; 
	//map[5] +=y; 
	map[2] += (w_dst - w_src) / 2;  
	map[5] += (h_dst - h_src) / 2;  


	Img_rotate=cvCreateImage(cvSize(w_dst, h_dst), 8, 3);  
	// We need a destination image	
	cvWarpAffine(
		imgSrc, 
		Img_rotate,
		&map_matrix,
		CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,
		cvScalarAll(0)
		); 
	cvReleaseImage(&imgSrc);  
}


/*  Gets the original picture folder   */

void CMfc_rotateDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	BROWSEINFO bi;
	TCHAR name[MAX_PATH];
	name[0]='d';

	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;

	bi.lpszTitle=_T("Select folder");
	bi.ulFlags=0x0040 | BIF_EDITBOX;         //新建文件夹
	//bi.ulFlags=0x80;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
		return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_Path=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		m_Path+="\\";
	UpdateData(FALSE);

	m_ImageDir=(LPSTR)(LPCTSTR)m_Path;
	//将图像的dir设置到界面
	SetDlgItemText(IDC_EDIT1,m_ImageDir);
	//文件的句柄
}
/*
//边缘检测//
void CMfc_rotateDlg::Soble(IplImage *img,IplImage* gradientImage)  
{  
IplImage* H = cvCreateImage(cvGetSize(img), 32,1);  
IplImage* V = cvCreateImage(cvGetSize(img), 32,1);  
IplImage* HV = cvCreateImage(cvGetSize(img), 32,1);  
//both horizontal and vertical gradient  
cvSobel(img,H,0,1,3);   
cvSobel(img,V,1,0,3);  
//total gradient = sqrt(horizontal*horizontal+vertical*vertical)  
int i,j,num;  
double v1,v2,v,max=0;  
float m[360]={0};
for (i=0;i<img->height;i++)  
{  
for (j=0;j<img->width;j++)  
{  
v1 = cvGetReal2D(H,i,j);  
v2 = cvGetReal2D(V,i,j);  
v = sqrt(v1*v1+v2*v2);
if(v1==0)
m[90]+=v;
else if(v2==0)
m[0]+=v;
else
{
double a=(atan(v2/v1))*(180/PI);
//double b=fabs(a);
num=(int)a;
if(num<0)
{
int _num=abs(num);
m[_num]+=v;
}
else
{
m[num]+=v;
}
}
}  
}  	
for(int k=0;k<180;k++)
{
if(max<=m[k])
{
max=m[k];
num=k;
}
}	
mag[0]=max;
mag[1]=num;
//	 cout<<max<<","<<num<<endl;
cvNormalize(HV,gradientImage,0,255,CV_MINMAX,0);  
cvReleaseImage(&H);  
cvReleaseImage(&V);  
cvReleaseImage(&HV);  
}   
//建筑旋转角度判断//
void CMfc_rotateDlg::b_judge(IplImage *b)
{
//	CString save_Path="E://毕业设计//building_save//";
int height,width,step,channels;
uchar *data;
int center[2]={0,0};   //旋转图片的参数定义
height    = b->height;  
width     = b->width;	
step      = b->widthStep;	
channels  = b->nChannels;
data = (uchar *)b->imageData;
printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
center[0]=width/2;//这两句可以设置旋转中心的坐标
center[1]=height/2;

int p[3];
p[0] = CV_IMWRITE_JPEG_QUALITY;
p[1] = 100;
p[2] = 0;


grayImage = cvCreateImage(cvGetSize(b), 8, 1);  
gradientImage = cvCreateImage(cvGetSize(b),8,1);  
cvCvtColor(b, grayImage, CV_BGR2GRAY);  // color to gray  
double t = cvGetTickCount();  
Soble(grayImage,gradientImage); 
if(mag[1]>=85)
{
//	cvShowImage("resouse",b);
cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),b,p);
UpdateData(FALSE);
E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);
SetDlgItemText(IDC_FINIIMG,E_Imged);
}
else
{
myRotate(b,0,0,mag[1],center);
cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),Img_rotate,p);
UpdateData(FALSE);
E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);
SetDlgItemText(IDC_FINIIMG,E_Imged);
}  
cvReleaseImage(&s_Building);  
cvReleaseImage(&grayImage);  
cvReleaseImage(&gradientImage); 
}
*/


/*EXIF Rotate Judge Function*/
/*
*@hFile:  Resourse file
*/
void CMfc_rotateDlg::E_judge(CString &hFile)
{

	//Esave_path="E://毕业设计//E_save//";
	s_Exif = cvLoadImage(hFile, 1 ); 
	height    = s_Exif->height;  
	width     = s_Exif->width;	
	step      = s_Exif->widthStep;	
	channels  = s_Exif->nChannels;
	data      = (uchar *)s_Exif->imageData;
	printf("Processing a %dx%d image with %d channels\n",height,width,channels); 

	center[0]=width/2;//这两句可以设置旋转中心的坐标
	center[1]=height/2;

	FILE* File=fopen(hFile,"rb");//待检测图像(包含绝对路径)   
	if(File)
	{
		memset(&m_exifinfo,0,sizeof(EXIFINFO));
		Cexif exif(&m_exifinfo);
		exif.DecodeExif(File);    //获取exif信息

		int p[3];
		p[0] = CV_IMWRITE_JPEG_QUALITY;
		p[1] = 100;
		p[2] = 0;

		if (m_exifinfo.IsExif) 
		{
			//	MessageBox((LPCTSTR)m_exifinfo.Orientation);
			switch(m_exifinfo.Orientation)
			{
			case 1:
				myRotate(s_Exif,0,0,0,center);
				cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),Img_rotate,p);
				E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);
				break;
			case 3:
				myRotate(s_Exif,0,0,180,center);
				break;
			case 6:
				myRotate(s_Exif,0,0,270,center);
				break;
			case 8:
				myRotate(s_Exif,0,0,90,center);
				break;
			default:
				break;
			}

			cvSaveImage((LPCTSTR)(m_SavePath+file_info.name),Img_rotate,p);
			E_Imged=(LPSTR)(LPCTSTR)(m_SavePath + file_info.name);
		}
	}
	fclose(File);	
}

/* Stored image path function */
void CMfc_rotateDlg::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	BROWSEINFO bi;
	TCHAR name[MAX_PATH];
	name[0]='d';

	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;

	bi.lpszTitle=_T("Select folder");
	bi.ulFlags=0x0040 | BIF_EDITBOX;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
		return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_SavePath=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		m_SavePath+="\\";
	UpdateData(FALSE);

	m_ImageDir=(LPSTR)(LPCTSTR)m_SavePath;
	//将图像的dir设置到界面
	SetDlgItemText(IDC_EDIT2,m_ImageDir);
	//文件的句柄
}

/* Call functions */

void CMfc_rotateDlg::Face()
{
	// TODO: 在此添加控件通知处理程序代码
	file_handle = _findfirst((LPCTSTR)(m_Path + "*.jpg"), &file_info);
	//读取文件夹下文件，判断.jpg是否存在
	if (file_handle == -1)
	{
		printf("No .jpg files！\n");
		exit(0);
	}
	else
		Fun_call();
}
/*
void CMfc_rotateDlg::Building()
{
// TODO: 在此添加控件通知处理程序代码
file_handle = _findfirst((LPCTSTR)(m_Path + "*.jpg"), &file_info);
//读取文件夹下文件，判断.jpg是否存在
if (file_handle == -1)
{
printf("没有找到.jpg文件！\n");
exit(0);
}
s_Building= cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 

UpdateData(FALSE);
E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);
SetDlgItemText(IDC_READIMG,E_Imging);

b_judge(s_Building);	
while(_findnext(file_handle, &file_info) == 0)
{
printf("%s\n",file_info.name);
resouse = cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 
UpdateData(FALSE);
E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);
SetDlgItemText(IDC_READIMG,E_Imging);
b_judge(resouse);
}
_findclose(file_handle);
MessageBox("图片已经全部旋转完成，谢谢使用！");
cvReleaseImage(&s_Building);
}*/

/* Call functions */
void CMfc_rotateDlg::Exif()
{
	// TODO: 在此添加控件通知处理程序代码

	file_handle = _findfirst((LPCTSTR)(m_Path + "*.jpg"), &file_info);

	//读取文件夹下文件，判断.jpg是否存在
	if (file_handle == -1)
	{
		printf("NO.jpg FILES！\n");
		exit(0);
	}
	s_Exif= cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 
	Exif_ImagePath=(LPCTSTR)(m_Path + file_info.name);
	E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);
	/////////////显示图像路径////////////////////////
	nIndex = m_list.GetItemCount();
	lvItem.mask = LVIF_TEXT ; 
	lvItem.iItem = nIndex;     //行数
	lvItem.iSubItem = 0;
	lvItem.pszText = (char*)(LPCTSTR)E_Imging;   //第一列
	//////////////////////////////////////////////
	E_judge(Exif_ImagePath);	
	//插入其它列
	////////////////更新列表数据////////////////////////
	m_list.SetRedraw(FALSE);
	m_list.SetItemText(nIndex,1,E_Imged);
	m_list.SetRedraw(TRUE);
	m_list.Invalidate();
	m_list.UpdateWindow();
	//在最后一行插入记录值.
	m_list.InsertItem(&lvItem);

	while(_findnext(file_handle, &file_info) == 0)
	{
		////////更新列表数据////////////////

		m_list.SetRedraw(FALSE);
		m_list.SetItemText(nIndex,1,E_Imged);
		m_list.SetRedraw(TRUE);
		m_list.Invalidate();
		m_list.UpdateWindow();   


		////////////////////////////////////////////////////////////////////////////////////
		resouse = cvLoadImage( (LPCTSTR)(m_Path + file_info.name), 1 ); 
		Exif_ImagePath=(LPCTSTR)(m_Path + file_info.name);
		E_Imging=(LPSTR)(LPCTSTR)(m_Path + file_info.name);
		//////////////////////////////////////////////////////////////////////////////////

		nIndex = m_list.GetItemCount();
		//	LV_ITEM lvItem;
		lvItem.mask = LVIF_TEXT ; 
		lvItem.iItem = nIndex;     //行数
		lvItem.iSubItem = 0;
		lvItem.pszText = (char*)(LPCTSTR)E_Imging;   //第一列
		//插入其它列
		E_judge(Exif_ImagePath);

		m_list.SetRedraw(FALSE);
		m_list.SetItemText(nIndex,1,E_Imged); 
		m_list.SetRedraw(TRUE);
		m_list.Invalidate();
		m_list.UpdateWindow();  
		//在最后一行插入记录值.
		m_list.InsertItem(&lvItem);
		//////////////////////////////////////////////////////////

	}
	///////////////最后一张图片路径的显示///////////////////////////
	m_list.SetRedraw(FALSE);
	m_list.SetItemText(nIndex,1,E_Imged); 
	m_list.SetRedraw(TRUE);
	m_list.Invalidate();
	m_list.UpdateWindow();  
	////////////////////////////////////
	_findclose(file_handle);
	MessageBox("All images have been rotated, thanks to use this program!");
	//	m_list.DeleteAllItems();
	cvReleaseImage(&s_Exif);
}
/* Gets the rotation mode function */
void CMfc_rotateDlg::OnBnClickedButtonrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	E_Imged="";
	UpdateData(TRUE);
	int radio1=((CButton *)GetDlgItem(IDC_RADIO11))->GetCheck();//返回1表示选上，0表示没选上
	int radio2=((CButton *)GetDlgItem(IDC_RADIO12))->GetCheck();//返回1表示选上，0表示没选上
	//int radio3=((CButton *)GetDlgItem(IDC_RADIO13))->GetCheck();//返回1表示选上，0表示没选上
	if(radio1==1)
	{

		Exif();
	}
	else if(radio2==1)
	{
		Face();
	}
	//else if(radio3==1)
	//{
	//	 Building();
	//	}
}

/* Show image function */

void CMfc_rotateDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//////////////////得到单击的行列号////////////////////////
	// 方法一：           
	IplImage *img1;
	CString strtemp;
	DWORD dwPos = GetMessagePos();    
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );         
	m_list.ScreenToClient(&point);          
	LVHITTESTINFO lvinfo;         
	lvinfo.pt = point;        
	lvinfo.flags = LVHT_ABOVE;        
	int nItem = m_list.SubItemHitTest(&lvinfo);    
	if(nItem != -1)          

	{             

		strtemp=m_list.GetItemText(lvinfo.iItem, lvinfo.iSubItem);
		cvNamedWindow("result",0);
		img1=cvLoadImage((LPCTSTR)strtemp, 1 ); 

		cvShowImage("result",img1);
		cvWaitKey(0);
		cvDestroyWindow("result");
		cvReleaseImage(&img1);

		/*	////////////////////调用windows图片查看器查看图片/////////////////////////////
		CString s1,s2;
		s1 = "C:\\Windows\\System32\\rundll32.exe";
		s2=(LPCTSTR)strtemp;
		CString strSystemDir="";  
		::GetSystemDirectory(strSystemDir.GetBuffer(256), 256);  //用于取得系统目录名
		strSystemDir.ReleaseBuffer();  
		CString strRundll = strSystemDir + "\\rundll32.exe";  
		CString strParm;  
		strParm.Format("%s//shimgvw.dll imageview_fullscreen %s", strSystemDir, s2);   
		HINSTANCE hNewExe = ShellExecute(NULL, "Open", strRundll, strParm, NULL, SW_SHOW);  */

	}                       
	*pResult = 0;
}
