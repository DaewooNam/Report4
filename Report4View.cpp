
// Report4View.cpp: CReport4View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Report4.h"
#endif

#include "Report4Doc.h"
#include "Report4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReport4View

IMPLEMENT_DYNCREATE(CReport4View, CView)

BEGIN_MESSAGE_MAP(CReport4View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CReport4View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CReport4View 생성/소멸

CReport4View::CReport4View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
	m_ptStart.x = m_ptStart.y = 0;
	m_ptEnd.x   = m_ptStart.y = 0;
	m_enDrawType = DT_RECTANGLE;

}

CReport4View::~CReport4View()
{
}

BOOL CReport4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CReport4View 그리기

void CReport4View::OnDraw(CDC* pDC)
{
	CReport4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	CString str;

	pDC->Rectangle(m_ptStart.x, m_ptStart.y, m_ptEnd.x, m_ptEnd.y);

	//Invalidate();

	if (m_enDrawType == DT_RECTANGLE)
		str = "그리기 타입 : 사각형";
	else if (m_enDrawType == DT_ELLIPSE)
		str = "그리기 타입 : 원";
	else
		str = "그리기 타입 : 라인";

	pDC->TextOut(10, 30, str);


}


// CReport4View 인쇄


void CReport4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CReport4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CReport4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CReport4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CReport4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);


}

void CReport4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CReport4View 진단

#ifdef _DEBUG
void CReport4View::AssertValid() const
{
	CView::AssertValid();
}

void CReport4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReport4Doc* CReport4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReport4Doc)));
	return (CReport4Doc*)m_pDocument;
}
#endif //_DEBUG


// CReport4View 메시지 처리기


void CReport4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	/*
	if (nFlags & VK_LBUTTON)
	{
		m_ptEnd = point;
		Invalidate();

	}
	*/

	CView::OnMouseMove(nFlags, point);
}


void CReport4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	m_ptStart = point;

	CView::OnLButtonDown(nFlags, point);
}


void CReport4View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_ptEnd = point;

	CRect rc = { m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y };

	m_listRects.push_back(rc);

	Invalidate();


	CView::OnLButtonUp(nFlags, point);
}


void CReport4View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACE("KeyValue : %d",nChar);
	if (nChar == VK_F1)
		m_enDrawType = DT_RECTANGLE;
	else if (nChar == VK_F2)
		m_enDrawType = DT_ELLIPSE;
	else if (nChar == VK_F3)
		m_enDrawType = DT_LINE;


	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
