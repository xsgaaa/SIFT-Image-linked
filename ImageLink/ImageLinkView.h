
// ImageLinkView.h : CImageLinkView ��Ľӿ�
//
#pragma once
#include"CImageMat.h"
#include<iostream>
#include<math.h>
#include<opencv2\xfeatures2d\nonfree.hpp>
#include<opencv2\imgproc\imgproc.hpp>
typedef struct
{
	Point2f left_top;
	Point2f left_bottom;
	Point2f right_top;
	Point2f right_bottom;
}four_corners_t;

using namespace cv;
class CImageLinkView : public CView
{
protected: // �������л�����
	CImageLinkView();
	DECLARE_DYNCREATE(CImageLinkView)

// ����
public:
	CImageLinkDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	double ratio = 0.6;			//��ƥ�����ֵ
	four_corners_t corners;
	Mat img_1, img_2, result_img;
	CImage image1, image2, image_result;
	CImageMat convert;
// ʵ��
public:
	virtual ~CImageLinkView();
	void AverageFuse(Mat& img1, Mat& trans, Mat& dst);
	void Bright_Modify(Mat & img1, Mat & trans,  Mat & img2);
	void CalcCorners(const Mat& H, const Mat& src);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnImageLink();
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnMediumBlur();
	afx_msg void OnRotationShun();
	afx_msg void OnEnlarge();
	afx_msg void OnNarrow();
	afx_msg void OnRotationNi();
//	afx_msg void OnUpdateEnlarge(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateNarrow(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateRotationNi(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateRotationShun(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // ImageLinkView.cpp �еĵ��԰汾
inline CImageLinkDoc* CImageLinkView::GetDocument() const
   { return reinterpret_cast<CImageLinkDoc*>(m_pDocument); }
#endif

