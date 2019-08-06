
// ImageLinkView.cpp : CImageLinkView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageLink.h"
#endif

#include "ImageLinkDoc.h"
#include "ImageLinkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageLinkView

IMPLEMENT_DYNCREATE(CImageLinkView, CView)

BEGIN_MESSAGE_MAP(CImageLinkView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImageLinkView::OnFileOpen)
	ON_COMMAND(ID_IMAGE_LINK, &CImageLinkView::OnImageLink)
	ON_COMMAND(ID_FILE_CLOSE, &CImageLinkView::OnFileClose)
	ON_COMMAND(ID_FILE_SAVE, &CImageLinkView::OnFileSave)
	ON_COMMAND(ID_MEDIUM_BLUR, &CImageLinkView::OnMediumBlur)
	ON_COMMAND(ID_ROTATION_SHUN, &CImageLinkView::OnRotationShun)
	ON_COMMAND(ID_ENLARGE, &CImageLinkView::OnEnlarge)
	ON_COMMAND(ID_NARROW, &CImageLinkView::OnNarrow)
	ON_COMMAND(ID_ROTATION_NI, &CImageLinkView::OnRotationNi)
//	ON_UPDATE_COMMAND_UI(ID_ENLARGE, &CImageLinkView::OnUpdateEnlarge)
//	ON_UPDATE_COMMAND_UI(ID_NARROW, &CImageLinkView::OnUpdateNarrow)
//	ON_UPDATE_COMMAND_UI(ID_ROTATION_NI, &CImageLinkView::OnUpdateRotationNi)
//	ON_UPDATE_COMMAND_UI(ID_ROTATION_SHUN, &CImageLinkView::OnUpdateRotationShun)
END_MESSAGE_MAP()

// CImageLinkView 构造/析构

CImageLinkView::CImageLinkView()
{
	// TODO: 在此处添加构造代码

}

CImageLinkView::~CImageLinkView()
{
}

BOOL CImageLinkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CImageLinkView 绘制

void CImageLinkView::OnDraw(CDC* pDC)
{
	CImageLinkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int cx1, cy1;
	int cx2, cy2;
	int cx, cy;
	// TODO: 在此处为本机数据添加绘制代码
	
		// TODO: 在此处为本机数据添加绘制代码
	CRect rc;
	GetClientRect(rc);
	if (!image1.IsNull()&&image2.IsNull())
	{
		cx1 = image1.GetWidth();
		cy1 = image1.GetHeight();
		image1.Draw(pDC->GetSafeHdc(), (rc.Width()-cx1)/2, (rc.Height()-cy1)/2,cx1,cy1);
	}
	if ((!image2.IsNull())&&(!image1.IsNull())&&(image_result.IsNull()))
	{
		cx2 = image2.GetWidth();
		cy2 = image2.GetHeight();
		image2.Draw(pDC->GetSafeHdc(), (rc.Width() - cx2) / 2, (rc.Height() - cy2) / 2, cx2, cy2);
	}
	if ((!image2.IsNull()) && (!image1.IsNull()) && (!image_result.IsNull()))
	{
		cx = image_result.GetWidth();
		cy = image_result.GetHeight();
		image_result.Draw(pDC->GetSafeHdc(), (rc.Width() - cx) / 2, (rc.Height() - cy) / 2, cx, cy);
	}

}


// CImageLinkView 打印

BOOL CImageLinkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageLinkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageLinkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CImageLinkView 诊断

#ifdef _DEBUG
void CImageLinkView::AssertValid() const
{
	CView::AssertValid();
}

void CImageLinkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageLinkDoc* CImageLinkView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLinkDoc)));
	return (CImageLinkDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageLinkView 消息处理程序


void CImageLinkView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("所有文件(*.*)|*.bmp; *.dib; *.gif; *.jpg; *.jpe; *.jpeg; *.tif; *.tiff; *.raw | 位图文件(*.bmp; *.dib) | *.bmp; *.dib |GIF文件(*.gif) | *.gif | JPEG文件(*.jpg; *.jpe; *.jpeg) | *.jpg; *.jpe; *.jpeg |");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		if (image1.IsNull())
		{
			image1.Load(strFilePath);
			convert.CImageToMat(image1, img_1);
		}
		else if(image2.IsNull())
		{
			image2.Load(strFilePath);
			convert.CImageToMat(image2, img_2);
		}
		else
		{
			MessageBox(_T("每次只能选择两个图片！！"));
		}
	}
	Invalidate(TRUE);	
}


void CImageLinkView::OnImageLink()
{
	if (img_1.empty())
	{
		MessageBox(_T("图片未导入"));
		return;
	}
	if (img_2.empty())
	{
		MessageBox(_T("只导入了一张图片"));
		return;
	}
	//创建SIFT类的指针
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();

	//检测关键点
	vector<KeyPoint> keypoints_1, keypoints_2;		//创建向量用于存放关键点
	f2d->detect(img_1, keypoints_1);				//检测第一幅图的关键点	
	f2d->detect(img_2, keypoints_2);				//检测第二幅图的关键点	
													//计算特征点描述子（128维向量）
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//---------------------------【粗匹配】---------------------------------------
	BFMatcher matcher;
	vector<vector<DMatch>> matchePoints;
	vector<DMatch> matche_first;			//存放粗匹配的结果
	vector<DMatch> matche_second;			//存放阈值过滤之后的结果
	float mindst;							//粗匹配之后的最近距离
	matcher.knnMatch(descriptors_1, descriptors_2, matchePoints, 2);
	for (size_t i = 0; i < matchePoints.size(); i++)
	{
		const DMatch& bestMatch = matchePoints[i][0];
		const DMatch& betterMatch = matchePoints[i][1];
		float  distanceRatio = bestMatch.distance / betterMatch.distance;
		if (distanceRatio < ratio)
		{
			matche_first.push_back(bestMatch);
		}
	}
	cout << matche_first.size() << endl;
	//---------------------------【粗匹配】--------------------------------------

	//--------------------------【阈值过滤筛选特征点对】-------------------------

	mindst = matche_first[0].distance;
	for (size_t i = 0; i < matche_first.size(); i++)
	{
		if (mindst > matche_first[i].distance)
		{
			mindst = matche_first[i].distance;
		}
	}
	for (size_t i = 0; i < matche_first.size(); i++)
	{
		if (matche_first[i].distance < 5 * mindst)
		{
			matche_second.push_back(matche_first[i]);
		}
	}
	cout << matche_second.size() << endl;
	//--------------------------【阈值过滤筛选特征点对】--------------------------


	sort(matche_second.begin(), matche_second.end()); //特征点排序										  
	vector<Point2f> imagePoints1, imagePoints2;		//获取排在前N个的最优匹配特征点
	for (int i = 0; i<matche_second.size(); i++)
	{
		imagePoints1.push_back(keypoints_1[matche_second[i].queryIdx].pt);				//将关键点转换成Point2f类型
		imagePoints2.push_back(keypoints_2[matche_second[i].trainIdx].pt);
	}




	//获取图像1到图像2的投影映射矩阵，尺寸为3*3
	Mat homo = findHomography(imagePoints2, imagePoints1, CV_RANSAC);		
	//计算配准图的四个坐标点
	CalcCorners(homo, img_2);
	//图像配准
	Mat imageTransform1;
	warpPerspective(img_2, imageTransform1, homo, Size(MAX(corners.right_top.x, corners.right_bottom.x), img_1.rows));
	//创建拼接后的图像，需提前计算图的大小
	int result_img_width = imageTransform1.cols;
	int result_img_height = img_1.rows;
	Mat result_img(result_img_height, result_img_width, CV_8UC3);
	//如果输入的图像为灰度图像，则将结果图设定为灰度图
	if (img_1.channels() == 1&&img_2.channels()==1)	
	{
		cvtColor(result_img, result_img, CV_BGR2GRAY);
	}
	result_img.setTo(0);
	//调用亮度调整函数
	Bright_Modify(img_1, imageTransform1,img_2);						
	imageTransform1.copyTo(result_img(Rect(0, 0, imageTransform1.cols, imageTransform1.rows)));		//将经过配准的第二幅图像拷贝到目标图像中
	img_1.copyTo(result_img(Rect(0, 0, img_1.cols, img_1.rows)));									//将第一幅图像拷贝到目标图像中
	//调用渐入渐出融合函数，修改重合部分的图像																								
	AverageFuse(img_1, imageTransform1, result_img);			
	convert.MatToCImage(result_img, image_result);
	MessageBox(_T("拼接完成"));
	//修改系统的菜单显示
	CMenu *pMenu;
	pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->EnableMenuItem(ID_ENLARGE, MF_ENABLED);
	pMenu->EnableMenuItem(ID_NARROW, MF_ENABLED);
	pMenu->EnableMenuItem(ID_ROTATION_SHUN, MF_ENABLED);
	pMenu->EnableMenuItem(ID_ROTATION_NI, MF_ENABLED);
	//OnDraw函数重新加载图像
	Invalidate();
}
//渐入渐出法融合函数
void CImageLinkView::AverageFuse(Mat& img1, Mat& trans, Mat& dst)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);//开始位置，即重叠区域的左边界 
	double processWidth = img1.cols - start;//重叠区域的宽度  
	int rows = dst.rows;
	int cols = img1.cols;					//注意，是列数*通道数
	double alpha = 1;						//img1中像素的权重  
	for (int i = 0; i < rows; i++)
	{
		uchar* p = img1.ptr<uchar>(i);		//获取第i行的首地址
		uchar* t = trans.ptr<uchar>(i);
		uchar* d = dst.ptr<uchar>(i);
		for (int j = start; j < cols; j++)
		{
			if (dst.channels() == 3)		//判断图片的通道数，如果为彩色图像
			{
				//如果遇到图像trans中无像素的黑点，则完全拷贝img1中的数据
				if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
				{
					alpha = 1;
				}
				else
				{
					//img1中像素的权重，与当前处理点距重叠区域左边界的距离成正比，实验证明，这种方法确实好  
					alpha = (processWidth - (j - start)) / processWidth;
				}

				d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
				d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
				d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);
			}
			else							//为灰度图像
			{
				if (t[j] == 0)
				{
					alpha = 1;
				}
				else
				{
					alpha = (processWidth - (j - start)) / processWidth;
				}
				d[j] = p[j] * alpha + t[j] * (1 - alpha);
			}
		}
	}
}
//亮度调整函数
void CImageLinkView::Bright_Modify(Mat & img1, Mat & trans,Mat & img2)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);
	float processWidth = img1.cols - start;
	//-------------------【防止坐标点溢出，造成错误】-------------------------
	int y_coordinate;
	if (corners.left_top.y < 0)
		y_coordinate = 0;
	else
		y_coordinate = corners.left_top.y;
	int height = corners.left_bottom.y - y_coordinate;
	if (height > img1.rows)
	{
		height = img1.rows;
	}
	//-------------------【防止坐标点溢出，造成错误】-------------------------
	Mat img1_right_sp, img2_left_sp,img1_sp,img2_sp;
	Mat img1_right = img1(Rect(start, 0, processWidth, img1.rows));				//分别获取两幅图像重合区域的图像
	Mat img2_left = trans(Rect(start,0, processWidth, img1.rows));
	Scalar co_bright1,bright1;
	Scalar co_bright2,bright2;
	if (img1.channels() == 3)									//如果是彩色图像
	{
		//求左边图像重合区域的平均亮度
		cvtColor(img1_right, img1_right_sp, CV_BGR2HSV);		//将左边图像的重合区域转换成HSV空间	
		vector<Mat> channel1;
		split(img1_right_sp, channel1);							//分离通道，单独提取亮度通道
		co_bright1 = mean(channel1[2]);	
		//求右边图像重合区域的平均亮度
		cvtColor(img2_left, img2_left_sp, CV_BGR2HSV);			
		vector<Mat> channel2;
		split(img2_left_sp, channel2);
		co_bright2 = mean(channel2[2]);
		//求左边图像的平均亮度
		cvtColor(img1, img1_sp, CV_BGR2HSV);					//将左边图像转换成HSV空间	
		split(img1_sp, channel1);								//分离通道，单独提取亮度通道
		bright1 = mean(channel1[2]);
		//求右边图像的平均亮度
		cvtColor(img2, img2_sp, CV_BGR2HSV);					//将右边图像转换成HSV空间	
		split(img2_sp, channel2);								//分离通道，单独提取亮度通道
		bright2 = mean(channel2[2]);
	}
	else														//为灰度图像时，直接计算灰度值的平均值
	{
		co_bright1 = mean(img1_right);
		co_bright2 = mean(img2_left);
		bright1 = mean(img1);
		bright2 = mean(img2);
	}

	float average_bright = (co_bright1[0] + co_bright2[0]) / 2;	//得到平均亮度

	float ratio1 = average_bright / bright1[0];				//计算第一幅图的亮度补偿系数
	float ratio2 = average_bright / bright2[0];				//计算第二幅图的亮度补偿系数
	if (img1.channels() == 3)								//彩色图的亮度调整
	{
		for (int y = 0; y < img1.rows; y++)						//调整第一幅图像的亮度
		{
			for (int x = 0; x < img1.cols; x++)
			{
				for (int c = 0; c < 3; c++)
				{
					img1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(ratio1*(img1.at<Vec3b>(y, x)[c]));
				}
			}
		}
		for (int y = 0; y < trans.rows; y++)					////调整第二幅图像的亮度
		{
			for (int x = 0; x < trans.cols; x++)
			{
				for (int c = 0; c < 3; c++)
				{
					trans.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(ratio2*(trans.at<Vec3b>(y, x)[c]));
				}
			}
		}
	}
	else
	{
		//灰度图的亮度调整
		for (int y = 0; y < img1.rows; y++)						//调整第一幅图像的亮度
		{
			for (int x = 0; x < img1.cols; x++)
			{
				img1.at<uchar>(y, x)= saturate_cast<uchar>(ratio1*(img1.at<uchar>(y, x)));
			}
		}
		for (int y = 0; y < trans.rows; y++)					//调整第二幅图像的亮度
		{
			for (int x = 0; x < trans.cols; x++)
			{
				trans.at<uchar>(y, x) = saturate_cast<uchar>(ratio2*(trans.at<uchar>(y, x)));

			}
		}
	}
	
}

void CImageLinkView::CalcCorners(const Mat& H, const Mat& src)
{
	double v2[] = { 0, 0, 1 };//左上角
	double v1[3];//变换后的坐标值
	Mat V2 = Mat(3, 1, CV_64FC1, v2);  //列向量
	Mat V1 = Mat(3, 1, CV_64FC1, v1);  //列向量

	V1 = H * V2;
	//左上角(0,0,1)
	cout << "V2: " << V2 << endl;
	cout << "V1: " << V1 << endl;
	corners.left_top.x = v1[0] / v1[2];
	corners.left_top.y = v1[1] / v1[2];

	//左下角(0,src.rows,1)
	v2[0] = 0;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //列向量
	V1 = Mat(3, 1, CV_64FC1, v1);  //列向量
	V1 = H * V2;
	corners.left_bottom.x = v1[0] / v1[2];
	corners.left_bottom.y = v1[1] / v1[2];

	//右上角(src.cols,0,1)
	v2[0] = src.cols;
	v2[1] = 0;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //列向量
	V1 = Mat(3, 1, CV_64FC1, v1);  //列向量
	V1 = H * V2;
	corners.right_top.x = v1[0] / v1[2];
	corners.right_top.y = v1[1] / v1[2];

	//右下角(src.cols,src.rows,1)
	v2[0] = src.cols;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //列向量
	V1 = Mat(3, 1, CV_64FC1, v1);  //列向量
	V1 = H * V2;
	corners.right_bottom.x = v1[0] / v1[2];
	corners.right_bottom.y = v1[1] / v1[2];
}


void CImageLinkView::OnFileClose()
{
	// TODO: 在此添加命令处理程序代码
	image1.Destroy();
	image2.Destroy();
	image_result.Destroy();
	img_1.release();
	img_2.release();
	CMenu *pMenu;
	pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->EnableMenuItem(ID_ENLARGE, MF_GRAYED);
	pMenu->EnableMenuItem(ID_NARROW, MF_GRAYED);
	pMenu->EnableMenuItem(ID_ROTATION_SHUN, MF_GRAYED);
	pMenu->EnableMenuItem(ID_ROTATION_NI, MF_GRAYED);
	Invalidate();
}


void CImageLinkView::OnFileSave()
{
	TCHAR szFilter[] = _T("所有文件(*.*)|*.bmp; *.dib; *.gif; *.jpg; *.jpe; *.jpeg; *.tif; *.tiff; *.raw | 位图文件(*.bmp; *.dib) | *.bmp; *.dib |GIF文件(*.gif) | *.gif | JPEG文件(*.jpg; *.jpe; *.jpeg) | *.jpg; *.jpe; *.jpeg |");
	// 构造打开文件对话框   
	CFileDialog dlg(FALSE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (dlg.DoModal()== IDOK)
	{
		strFilePath = dlg.GetPathName();
		strFilePath = strFilePath;
		convert.MatToCImage(result_img, image_result);
		image_result.Save(strFilePath);
		HRESULT hResult = image_result.Save(strFilePath);
		if (FAILED(hResult))
			MessageBox(_T("保存图像文件失败！"));
	}
	
}


void CImageLinkView::OnMediumBlur()
{
	// TODO: 在此添加命令处理程序代码
	if (!image1.IsNull() && image2.IsNull())
	{
		medianBlur(img_1, img_1, 3);
		convert.MatToCImage(img_1, image1);
	}
	if ((!image2.IsNull()) && (!image1.IsNull()) && (image_result.IsNull()))
	{
		medianBlur(img_2, img_2, 3);
		convert.MatToCImage(img_2, image2);
	}
	if ((!image2.IsNull()) && (!image1.IsNull()) && (!image_result.IsNull()))
	{
		medianBlur(result_img, result_img, 3);
		convert.MatToCImage(result_img, image_result);
	}
	Invalidate();
}


void CImageLinkView::OnRotationShun()
{
	convert.CImageToMat(image_result, result_img);
	if (result_img.empty())
	{
		MessageBox(_T("目标图为空"));
		return;
	}
	Mat dst;
	transpose(result_img, dst);
	flip(dst, result_img, 1);
	convert.MatToCImage(result_img, image_result);
	Invalidate();
}



void CImageLinkView::OnEnlarge()
{
	convert.CImageToMat(image_result, result_img);
	Mat temImage;
	resize(result_img, temImage, Size(result_img.cols * 2, result_img.rows * 2), 0, 0, INTER_LINEAR);
	result_img = temImage;
	convert.MatToCImage(result_img, image_result);
	Invalidate();
}


void CImageLinkView::OnNarrow()
{
	convert.CImageToMat(image_result, result_img);
	Mat temImage;
	resize(result_img, temImage, Size(result_img.cols / 2, result_img.rows / 2), 0, 0, INTER_LINEAR);
	result_img = temImage;
	convert.MatToCImage(result_img, image_result);
	Invalidate();
}


void CImageLinkView::OnRotationNi()
{
	convert.CImageToMat(image_result, result_img);
	if (result_img.empty())
	{
		MessageBox(_T("目标图为空"));
		return;
	}
	Mat dst;
	transpose(result_img, dst);
	flip(dst, result_img, 0);
	convert.MatToCImage(result_img, image_result);
	Invalidate();
}



