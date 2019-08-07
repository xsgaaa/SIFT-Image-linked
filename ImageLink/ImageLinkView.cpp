
// ImageLinkView.cpp : CImageLinkView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CImageLinkView ����/����

CImageLinkView::CImageLinkView()
{
	// TODO: �ڴ˴���ӹ������

}

CImageLinkView::~CImageLinkView()
{
}

BOOL CImageLinkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CImageLinkView ����

void CImageLinkView::OnDraw(CDC* pDC)
{
	CImageLinkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int cx1, cy1;
	int cx2, cy2;
	int cx, cy;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CImageLinkView ��ӡ

BOOL CImageLinkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageLinkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageLinkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CImageLinkView ���

#ifdef _DEBUG
void CImageLinkView::AssertValid() const
{
	CView::AssertValid();
}

void CImageLinkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageLinkDoc* CImageLinkView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageLinkDoc)));
	return (CImageLinkDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageLinkView ��Ϣ�������


void CImageLinkView::OnFileOpen()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.bmp; *.dib; *.gif; *.jpg; *.jpe; *.jpeg; *.tif; *.tiff; *.raw | λͼ�ļ�(*.bmp; *.dib) | *.bmp; *.dib |GIF�ļ�(*.gif) | *.gif | JPEG�ļ�(*.jpg; *.jpe; *.jpeg) | *.jpg; *.jpe; *.jpeg |");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
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
			MessageBox(_T("ÿ��ֻ��ѡ������ͼƬ����"));
		}
	}
	Invalidate(TRUE);	
}


void CImageLinkView::OnImageLink()
{
	if (img_1.empty())
	{
		MessageBox(_T("ͼƬδ����"));
		return;
	}
	if (img_2.empty())
	{
		MessageBox(_T("ֻ������һ��ͼƬ"));
		return;
	}
	//����SIFT���ָ��
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();

	//���ؼ���
	vector<KeyPoint> keypoints_1, keypoints_2;		//�����������ڴ�Źؼ���
	f2d->detect(img_1, keypoints_1);				//����һ��ͼ�Ĺؼ���	
	f2d->detect(img_2, keypoints_2);				//���ڶ���ͼ�Ĺؼ���	
													//���������������ӣ�128ά������
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//---------------------------����ƥ�䡿---------------------------------------
	BFMatcher matcher;
	vector<vector<DMatch>> matchePoints;
	vector<DMatch> matche_first;			//��Ŵ�ƥ��Ľ��
	vector<DMatch> matche_second;			//�����ֵ����֮��Ľ��
	float mindst;							//��ƥ��֮����������
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
	//---------------------------����ƥ�䡿--------------------------------------

	//--------------------------����ֵ����ɸѡ������ԡ�-------------------------

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
	//--------------------------����ֵ����ɸѡ������ԡ�--------------------------


	sort(matche_second.begin(), matche_second.end()); //����������										  
	vector<Point2f> imagePoints1, imagePoints2;		//��ȡ����ǰN��������ƥ��������
	for (int i = 0; i<matche_second.size(); i++)
	{
		imagePoints1.push_back(keypoints_1[matche_second[i].queryIdx].pt);				//���ؼ���ת����Point2f����
		imagePoints2.push_back(keypoints_2[matche_second[i].trainIdx].pt);
	}




	//��ȡͼ��1��ͼ��2��ͶӰӳ����󣬳ߴ�Ϊ3*3
	Mat homo = findHomography(imagePoints2, imagePoints1, CV_RANSAC);		
	//������׼ͼ���ĸ������
	CalcCorners(homo, img_2);
	//ͼ����׼
	Mat imageTransform1;
	warpPerspective(img_2, imageTransform1, homo, Size(MAX(corners.right_top.x, corners.right_bottom.x), img_1.rows));
	//����ƴ�Ӻ��ͼ������ǰ����ͼ�Ĵ�С
	int result_img_width = imageTransform1.cols;
	int result_img_height = img_1.rows;
	Mat result_img(result_img_height, result_img_width, CV_8UC3);
	//��������ͼ��Ϊ�Ҷ�ͼ���򽫽��ͼ�趨Ϊ�Ҷ�ͼ
	if (img_1.channels() == 1&&img_2.channels()==1)	
	{
		cvtColor(result_img, result_img, CV_BGR2GRAY);
	}
	result_img.setTo(0);
	//�������ȵ�������
	Bright_Modify(img_1, imageTransform1,img_2);						
	imageTransform1.copyTo(result_img(Rect(0, 0, imageTransform1.cols, imageTransform1.rows)));		//��������׼�ĵڶ���ͼ�񿽱���Ŀ��ͼ����
	img_1.copyTo(result_img(Rect(0, 0, img_1.cols, img_1.rows)));									//����һ��ͼ�񿽱���Ŀ��ͼ����
	//���ý��뽥���ںϺ������޸��غϲ��ֵ�ͼ��																								
	AverageFuse(img_1, imageTransform1, result_img);			
	convert.MatToCImage(result_img, image_result);
	MessageBox(_T("ƴ�����"));
	//�޸�ϵͳ�Ĳ˵���ʾ
	CMenu *pMenu;
	pMenu = AfxGetMainWnd()->GetMenu();
	pMenu->EnableMenuItem(ID_ENLARGE, MF_ENABLED);
	pMenu->EnableMenuItem(ID_NARROW, MF_ENABLED);
	pMenu->EnableMenuItem(ID_ROTATION_SHUN, MF_ENABLED);
	pMenu->EnableMenuItem(ID_ROTATION_NI, MF_ENABLED);
	//OnDraw�������¼���ͼ��
	Invalidate();
}
//���뽥�����ںϺ���
void CImageLinkView::AverageFuse(Mat& img1, Mat& trans, Mat& dst)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);//��ʼλ�ã����ص��������߽� 
	double processWidth = img1.cols - start;//�ص�����Ŀ��  
	int rows = dst.rows;
	int cols = img1.cols;					//ע�⣬������*ͨ����
	double alpha = 1;						//img1�����ص�Ȩ��  
	for (int i = 0; i < rows; i++)
	{
		uchar* p = img1.ptr<uchar>(i);		//��ȡ��i�е��׵�ַ
		uchar* t = trans.ptr<uchar>(i);
		uchar* d = dst.ptr<uchar>(i);
		for (int j = start; j < cols; j++)
		{
			if (dst.channels() == 3)		//�ж�ͼƬ��ͨ���������Ϊ��ɫͼ��
			{
				//�������ͼ��trans�������صĺڵ㣬����ȫ����img1�е�����
				if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
				{
					alpha = 1;
				}
				else
				{
					//img1�����ص�Ȩ�أ��뵱ǰ�������ص�������߽�ľ�������ȣ�ʵ��֤�������ַ���ȷʵ��  
					alpha = (processWidth - (j - start)) / processWidth;
				}

				d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
				d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
				d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);
			}
			else							//Ϊ�Ҷ�ͼ��
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
//���ȵ�������
void CImageLinkView::Bright_Modify(Mat & img1, Mat & trans,Mat & img2)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);
	float processWidth = img1.cols - start;
	//-------------------����ֹ������������ɴ���-------------------------
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
	//-------------------����ֹ������������ɴ���-------------------------
	Mat img1_right_sp, img2_left_sp,img1_sp,img2_sp;
	Mat img1_right = img1(Rect(start, 0, processWidth, img1.rows));				//�ֱ��ȡ����ͼ���غ������ͼ��
	Mat img2_left = trans(Rect(start,0, processWidth, img1.rows));
	Scalar co_bright1,bright1;
	Scalar co_bright2,bright2;
	if (img1.channels() == 3)									//����ǲ�ɫͼ��
	{
		//�����ͼ���غ������ƽ������
		cvtColor(img1_right, img1_right_sp, CV_BGR2HSV);		//�����ͼ����غ�����ת����HSV�ռ�	
		vector<Mat> channel1;
		split(img1_right_sp, channel1);							//����ͨ����������ȡ����ͨ��
		co_bright1 = mean(channel1[2]);	
		//���ұ�ͼ���غ������ƽ������
		cvtColor(img2_left, img2_left_sp, CV_BGR2HSV);			
		vector<Mat> channel2;
		split(img2_left_sp, channel2);
		co_bright2 = mean(channel2[2]);
		//�����ͼ���ƽ������
		cvtColor(img1, img1_sp, CV_BGR2HSV);					//�����ͼ��ת����HSV�ռ�	
		split(img1_sp, channel1);								//����ͨ����������ȡ����ͨ��
		bright1 = mean(channel1[2]);
		//���ұ�ͼ���ƽ������
		cvtColor(img2, img2_sp, CV_BGR2HSV);					//���ұ�ͼ��ת����HSV�ռ�	
		split(img2_sp, channel2);								//����ͨ����������ȡ����ͨ��
		bright2 = mean(channel2[2]);
	}
	else														//Ϊ�Ҷ�ͼ��ʱ��ֱ�Ӽ���Ҷ�ֵ��ƽ��ֵ
	{
		co_bright1 = mean(img1_right);
		co_bright2 = mean(img2_left);
		bright1 = mean(img1);
		bright2 = mean(img2);
	}

	float average_bright = (co_bright1[0] + co_bright2[0]) / 2;	//�õ�ƽ������

	float ratio1 = average_bright / bright1[0];				//�����һ��ͼ�����Ȳ���ϵ��
	float ratio2 = average_bright / bright2[0];				//����ڶ���ͼ�����Ȳ���ϵ��
	if (img1.channels() == 3)								//��ɫͼ�����ȵ���
	{
		for (int y = 0; y < img1.rows; y++)						//������һ��ͼ�������
		{
			for (int x = 0; x < img1.cols; x++)
			{
				for (int c = 0; c < 3; c++)
				{
					img1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(ratio1*(img1.at<Vec3b>(y, x)[c]));
				}
			}
		}
		for (int y = 0; y < trans.rows; y++)					////�����ڶ���ͼ�������
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
		//�Ҷ�ͼ�����ȵ���
		for (int y = 0; y < img1.rows; y++)						//������һ��ͼ�������
		{
			for (int x = 0; x < img1.cols; x++)
			{
				img1.at<uchar>(y, x)= saturate_cast<uchar>(ratio1*(img1.at<uchar>(y, x)));
			}
		}
		for (int y = 0; y < trans.rows; y++)					//�����ڶ���ͼ�������
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
	double v2[] = { 0, 0, 1 };//���Ͻ�
	double v1[3];//�任�������ֵ
	Mat V2 = Mat(3, 1, CV_64FC1, v2);  //������
	Mat V1 = Mat(3, 1, CV_64FC1, v1);  //������

	V1 = H * V2;
	//���Ͻ�(0,0,1)
	cout << "V2: " << V2 << endl;
	cout << "V1: " << V1 << endl;
	corners.left_top.x = v1[0] / v1[2];
	corners.left_top.y = v1[1] / v1[2];

	//���½�(0,src.rows,1)
	v2[0] = 0;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.left_bottom.x = v1[0] / v1[2];
	corners.left_bottom.y = v1[1] / v1[2];

	//���Ͻ�(src.cols,0,1)
	v2[0] = src.cols;
	v2[1] = 0;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_top.x = v1[0] / v1[2];
	corners.right_top.y = v1[1] / v1[2];

	//���½�(src.cols,src.rows,1)
	v2[0] = src.cols;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_bottom.x = v1[0] / v1[2];
	corners.right_bottom.y = v1[1] / v1[2];
}


void CImageLinkView::OnFileClose()
{
	// TODO: �ڴ���������������
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
	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.bmp; *.dib; *.gif; *.jpg; *.jpe; *.jpeg; *.tif; *.tiff; *.raw | λͼ�ļ�(*.bmp; *.dib) | *.bmp; *.dib |GIF�ļ�(*.gif) | *.gif | JPEG�ļ�(*.jpg; *.jpe; *.jpeg) | *.jpg; *.jpe; *.jpeg |");
	// ������ļ��Ի���   
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
			MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}
	
}


void CImageLinkView::OnMediumBlur()
{
	// TODO: �ڴ���������������
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
		MessageBox(_T("Ŀ��ͼΪ��"));
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
		MessageBox(_T("Ŀ��ͼΪ��"));
		return;
	}
	Mat dst;
	transpose(result_img, dst);
	flip(dst, result_img, 0);
	convert.MatToCImage(result_img, image_result);
	Invalidate();
}



