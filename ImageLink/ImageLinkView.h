
// ImageLinkView.h : CImageLinkView 类的接口
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
protected: // 仅从序列化创建
	CImageLinkView();
	DECLARE_DYNCREATE(CImageLinkView)

// 特性
public:
	CImageLinkDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	double ratio = 0.6;			//粗匹配的阈值
	four_corners_t corners;
	Mat img_1, img_2, result_img;
	CImage image1, image2, image_result;
	CImageMat convert;
// 实现
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

// 生成的消息映射函数
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

#ifndef _DEBUG  // ImageLinkView.cpp 中的调试版本
inline CImageLinkDoc* CImageLinkView::GetDocument() const
   { return reinterpret_cast<CImageLinkDoc*>(m_pDocument); }
#endif

