
// PlanetMotionView.h : interface of the CPlanetMotionView class
//

#pragma once


class CPlanetMotionView : public CView
{
	CWinThread* m_pCurrentThread;
	CArray<CPoint, CPoint> m_PointArray;

protected: // create from serialization only
	CPlanetMotionView() noexcept;
	DECLARE_DYNCREATE(CPlanetMotionView)

// Attributes
public:
	float m_iCounter;
	
	CPlanetMotionDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlanetMotionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnimationStart();
	afx_msg void OnAnimationStop();
	afx_msg void OnAnimationResume();
	static UINT StartThread(LPVOID Param);
};

#ifndef _DEBUG  // debug version in PlanetMotionView.cpp
inline CPlanetMotionDoc* CPlanetMotionView::GetDocument() const
   { return reinterpret_cast<CPlanetMotionDoc*>(m_pDocument); }
#endif

