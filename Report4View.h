
// Report4View.h: CReport4View 클래스의 인터페이스
//

#pragma once

enum DRAWTYPE { DT_RECTANGLE, DT_ELLIPSE, DT_LINE };


class CReport4View : public CView
{
protected: // serialization에서만 만들어집니다.
	CReport4View();
	DECLARE_DYNCREATE(CReport4View)

// 특성입니다.
public:
	CReport4Doc* GetDocument() const;

// 작업입니다.
public:

	list<CRect> m_listRects;
	
	CPoint m_ptStart;
	CPoint m_ptEnd;
	DRAWTYPE m_enDrawType;


	

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CReport4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // Report4View.cpp의 디버그 버전
inline CReport4Doc* CReport4View::GetDocument() const
   { return reinterpret_cast<CReport4Doc*>(m_pDocument); }
#endif

