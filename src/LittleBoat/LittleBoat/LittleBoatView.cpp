// Этот исходный код примеров MFC демонстрирует функционирование пользовательского интерфейса Fluent на основе MFC в Microsoft Office
// ("Fluent UI") и предоставляется исключительно как справочный материал в качестве дополнения к
// справочнику по пакету Microsoft Foundation Classes и связанной электронной документации,
// включенной в программное обеспечение библиотеки MFC C++.
// Условия лицензионного соглашения на копирование, использование или распространение Fluent UI доступны отдельно.
// Для получения дополнительных сведений о нашей программе лицензирования Fluent UI посетите веб-сайт
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) Корпорация Майкрософт (Microsoft Corp.)
// Все права защищены.

// LittleBoatView.cpp: реализация класса CLittleBoatView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "LittleBoat.h"
#endif

#include "LittleBoatDoc.h"
#include "LittleBoatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLittleBoatView

IMPLEMENT_DYNCREATE(CLittleBoatView, CView)

BEGIN_MESSAGE_MAP(CLittleBoatView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLittleBoatView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CLittleBoatView

CLittleBoatView::CLittleBoatView() noexcept
{
	// TODO: добавьте код создания

}

CLittleBoatView::~CLittleBoatView()
{
}

BOOL CLittleBoatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CLittleBoatView

void CLittleBoatView::OnDraw(CDC* /*pDC*/)
{
	CLittleBoatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CLittleBoatView


void CLittleBoatView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLittleBoatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CLittleBoatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CLittleBoatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CLittleBoatView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLittleBoatView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CLittleBoatView

#ifdef _DEBUG
void CLittleBoatView::AssertValid() const
{
	CView::AssertValid();
}

void CLittleBoatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLittleBoatDoc* CLittleBoatView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLittleBoatDoc)));
	return (CLittleBoatDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CLittleBoatView
