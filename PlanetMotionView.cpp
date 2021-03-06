// PlanetMotionView.cpp : implementation of the CPlanetMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetMotion.h"
#endif

#include "PlanetMotionDoc.h"
#include "PlanetMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetMotionView

IMPLEMENT_DYNCREATE(CPlanetMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ANIMATION_START, &CPlanetMotionView::OnAnimationStart)
	ON_COMMAND(ID_ANIMATION_STOP, &CPlanetMotionView::OnAnimationStop)
	ON_COMMAND(ID_ANIMATION_RESUME, &CPlanetMotionView::OnAnimationResume)
END_MESSAGE_MAP()

// CPlanetMotionView construction/destruction

CPlanetMotionView::CPlanetMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;

     
}

CPlanetMotionView::~CPlanetMotionView()
{
}

BOOL CPlanetMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetMotionView drawing

void CPlanetMotionView::OnDraw(CDC* pDC)
{
	CPlanetMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&redPen);
	pDC->Ellipse(50, 50, 400, 400);
	pDC->SelectObject(pOldPen);
 
	CBrush rMine;
	CBrush* OldBrush = NULL;
	rMine.CreateSolidBrush(RGB(0, 0, 255));
	OldBrush = pDC->SelectObject(&rMine);
	pDC->Ellipse(90, 90, 120, 120);
	pDC->SelectObject(OldBrush);

	CBrush brMine;
	CBrush* pOldBrush = NULL;
	brMine.CreateSolidBrush(BLACK_BRUSH);
	pOldBrush = pDC->SelectObject(&brMine);
	pDC->Ellipse(200,200,250,250);
	pDC->SelectObject(pOldBrush);
	
	CPen greenPen;
	greenPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* OldPen = pDC->SelectObject(&greenPen);
	for (int i = 0; i < m_PointArray.GetSize() - 2; i++)
	{
		pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
		pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);

	}
	pDC->SelectObject(OldPen);
	// TODO: add draw code for native data here
}


// CPlanetMotionView printing

BOOL CPlanetMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPlanetMotionView diagnostics

#ifdef _DEBUG
void CPlanetMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetMotionDoc* CPlanetMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetMotionDoc)));
	return (CPlanetMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetMotionView message handlers


void CPlanetMotionView::OnAnimationStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPlanetMotionView::StartThread, this);
}


void CPlanetMotionView::OnAnimationStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPlanetMotionView::OnAnimationResume()
{

	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetMotionView::StartThread(LPVOID Param)
{
	CPlanetMotionView* pView = (CPlanetMotionView*)Param;
	CPoint Point(0,0);
	while (1)
	{
		Point.x = 120 + 100 + 90* cos(pView->m_iCounter);
		Point.y = 120 + 100 + 90 * sin(pView->m_iCounter);

		pView->m_PointArray.Add(Point);
		pView->m_iCounter = pView->m_iCounter + .1;
		pView->Invalidate();

		Sleep(200);


	}

	// TODO: Add your implementation code here.
	return 0;
}
