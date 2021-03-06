// MfcHookApi.h: MfcHookApi DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#pragma warning(disable:4996)
// CMfcHookApiApp
// 有关此类实现的信息，请参阅 MfcHookApi.cpp
//
#define CONTAINING_RECORD(address, type, field) \
  ((type *)((PCHAR)(address) - offsetof(type, field)))

#define IDropSource_QueryContinueDrag(This,fEscapePressed,grfKeyState) (This)->lpVtbl->QueryContinueDrag((IDropSource *)This,fEscapePressed,grfKeyState)


class CMfcHookApiApp : public CWinApp
{
public:
	CMfcHookApiApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern "C" __declspec(dllexport) void ActiveHook();
extern "C" __declspec(dllexport) void InstallHook4Api(HWND hwnd);

int* addrMsgBoxA = (int*)MessageBoxA;
int* addrMsgBoxW = (int*)MessageBoxW;
int WINAPI HookMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
int WINAPI HookMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
void SetHookMessageBox(HMODULE hModule);

typedef int(WINAPI* PfnMessageBox)(HWND, LPCSTR, LPCSTR, UINT);

int* addrDispatchA = (int*)DispatchMessageA;
int* addrDispatchW = (int*)DispatchMessageW;
LRESULT WINAPI HookDispatchMessageA(MSG* msg);
LRESULT WINAPI HookDispatchMessageW(MSG* msg);
void SetHookDispatchMessage(HMODULE hModule);

/*add by yangke start*/
/*
int* addrSendMsgA = (int*)SendMessageA;
int* addrSendMsgW = (int*)SendMessageW;
LRESULT WINAPI HookSendMessageA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT WINAPI HookSendMessageW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void SetHookDispatchMessage(HMODULE hModule);
*/
int* addrCreateWindowExA = (int*)CreateWindowExA;
int* addrCreateWindowExW = (int*)CreateWindowExW;
HWND WINAPI HookCreateWindowExA(
	_In_     DWORD     dwExStyle,
	_In_opt_ LPCSTR   lpClassName,
	_In_opt_ LPCSTR   lpWindowName,
	_In_     DWORD     dwStyle,
	_In_     int       x,
	_In_     int       y,
	_In_     int       nWidth,
	_In_     int       nHeight,
	_In_opt_ HWND      hWndParent,
	_In_opt_ HMENU     hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID    lpParam
);
HWND WINAPI HookCreateWindowExW(
	_In_     DWORD     dwExStyle,
	_In_opt_ LPCWSTR   lpClassName,
	_In_opt_ LPCWSTR   lpWindowName,
	_In_     DWORD     dwStyle,
	_In_     int       x,
	_In_     int       y,
	_In_     int       nWidth,
	_In_     int       nHeight,
	_In_opt_ HWND      hWndParent,
	_In_opt_ HMENU     hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID    lpParam
);
void SetHookCreateWindowEx(HMODULE hModule);



typedef struct IDropTargetVtbl {
	BEGIN_INTERFACE

		/*** IUnknown methods ***/
		HRESULT(STDMETHODCALLTYPE *QueryInterface)(
			IDropTarget *This,
			REFIID riid,
			void **ppvObject);

	ULONG(STDMETHODCALLTYPE *AddRef)(
		IDropTarget *This);

	ULONG(STDMETHODCALLTYPE *Release)(
		IDropTarget *This);

	/*** IDropTarget methods ***/
	HRESULT(STDMETHODCALLTYPE *DragEnter)(
		IDropTarget *This,
		IDataObject *pDataObj,
		DWORD grfKeyState,
		POINTL pt,
		DWORD *pdwEffect);

	HRESULT(STDMETHODCALLTYPE *DragOver)(
		IDropTarget *This,
		DWORD grfKeyState,
		POINTL pt,
		DWORD *pdwEffect);

	HRESULT(STDMETHODCALLTYPE *DragLeave)(
		IDropTarget *This);

	HRESULT(STDMETHODCALLTYPE *Drop)(
		IDropTarget *This,
		IDataObject *pDataObj,
		DWORD grfKeyState,
		POINTL pt,
		DWORD *pdwEffect);

	END_INTERFACE
} IDropTargetVtbl;
typedef struct IDropSourceVtbl {
	BEGIN_INTERFACE

		/*** IUnknown methods ***/
		HRESULT(STDMETHODCALLTYPE *QueryInterface)(
			IDropSource *This,
			REFIID riid,
			void **ppvObject);

	ULONG(STDMETHODCALLTYPE *AddRef)(
		IDropSource *This);

	ULONG(STDMETHODCALLTYPE *Release)(
		IDropSource *This);

	/*** IDropSource methods ***/
	HRESULT(STDMETHODCALLTYPE *QueryContinueDrag)(
		IDropSource *This,
		BOOL fEscapePressed,
		DWORD grfKeyState);

	HRESULT(STDMETHODCALLTYPE *GiveFeedback)(
		IDropSource *This,
		DWORD dwEffect);

	END_INTERFACE
} IDropSourceVtbl;
interface IDropTarget2 {
	CONST_VTBL IDropTargetVtbl* lpVtbl;
};
interface IDropSource2 {
	CONST_VTBL IDropSourceVtbl* lpVtbl;
};
typedef struct {
	IDropTarget2 IDropTarget_iface;
	HWND hwnd;
	LONG refs;
} DropTargetWrapper;
#define IDropTarget_AddRef(This) (This)->lpVtbl->AddRef(This)

typedef struct
{
	BOOL    bIsAscending;
	INT     nHeaderID;
	INT     nLastHeaderID;
}LISTVIEW_SORT_INFO, *LPLISTVIEW_SORT_INFO;
typedef struct IShellView3Vtbl {
	BEGIN_INTERFACE

		/*** IUnknown methods ***/
		HRESULT(STDMETHODCALLTYPE *QueryInterface)(
			IShellView3 *This,
			REFIID riid,
			void **ppvObject);

	ULONG(STDMETHODCALLTYPE *AddRef)(
		IShellView3 *This);

	ULONG(STDMETHODCALLTYPE *Release)(
		IShellView3 *This);

	/*** IOleWindow methods ***/
	HRESULT(STDMETHODCALLTYPE *GetWindow)(
		IShellView3 *This,
		HWND *phwnd);

	HRESULT(STDMETHODCALLTYPE *ContextSensitiveHelp)(
		IShellView3 *This,
		BOOL fEnterMode);

	/*** IShellView methods ***/
	HRESULT(STDMETHODCALLTYPE *TranslateAccelerator)(
		IShellView3 *This,
		MSG *pmsg);

	HRESULT(STDMETHODCALLTYPE *EnableModeless)(
		IShellView3 *This,
		BOOL fEnable);

	HRESULT(STDMETHODCALLTYPE *UIActivate)(
		IShellView3 *This,
		UINT uState);

	HRESULT(STDMETHODCALLTYPE *Refresh)(
		IShellView3 *This);

	HRESULT(STDMETHODCALLTYPE *CreateViewWindow)(
		IShellView3 *This,
		IShellView *psvPrevious,
		LPCFOLDERSETTINGS lpfs,
		IShellBrowser *psb,
		RECT *prcView,
		HWND *phWnd);

	HRESULT(STDMETHODCALLTYPE *DestroyViewWindow)(
		IShellView3 *This);

	HRESULT(STDMETHODCALLTYPE *GetCurrentInfo)(
		IShellView3 *This,
		LPFOLDERSETTINGS lpfs);

	HRESULT(STDMETHODCALLTYPE *AddPropertySheetPages)(
		IShellView3 *This,
		DWORD dwReserved,
		LPFNSVADDPROPSHEETPAGE pfn,
		LPARAM lparam);

	HRESULT(STDMETHODCALLTYPE *SaveViewState)(
		IShellView3 *This);

	HRESULT(STDMETHODCALLTYPE *SelectItem)(
		IShellView3 *This,
		LPCITEMIDLIST pidlItem,
		SVSIF uFlags);

	HRESULT(STDMETHODCALLTYPE *GetItemObject)(
		IShellView3 *This,
		UINT uItem,
		REFIID riid,
		void **ppv);

	/*** IShellView2 methods ***/
	HRESULT(STDMETHODCALLTYPE *GetView)(
		IShellView3 *This,
		SHELLVIEWID *view_guid,
		ULONG view_type);

	HRESULT(STDMETHODCALLTYPE *CreateViewWindow2)(
		IShellView3 *This,
		LPSV2CVW2_PARAMS view_params);

	HRESULT(STDMETHODCALLTYPE *HandleRename)(
		IShellView3 *This,
		LPCITEMIDLIST new_pidl);

	HRESULT(STDMETHODCALLTYPE *SelectAndPositionItem)(
		IShellView3 *This,
		LPCITEMIDLIST item,
		UINT flags,
		POINT *point);

	/*** IShellView3 methods ***/
	HRESULT(STDMETHODCALLTYPE *CreateViewWindow3)(
		IShellView3 *This,
		IShellBrowser *owner,
		IShellView *prev_view,
		SV3CVW3_FLAGS view_flags,
		FOLDERFLAGS mask,
		FOLDERFLAGS flags,
		FOLDERVIEWMODE mode,
		const SHELLVIEWID *view_id,
		const RECT *rect,
		HWND *hwnd);

	END_INTERFACE
} IShellView3Vtbl;


typedef struct
{
	/*
	IShellView3       IShellView3_iface;
	IOleCommandTarget IOleCommandTarget_iface;*/
	IDropTarget2       IShellView3_iface;
	IDropTarget2 IOleCommandTarget_iface;
	IDropTarget2       IDropTarget_iface;
	/*
	IDropSource       IDropSource_iface;
	IViewObject       IViewObject_iface;
	IFolderView2      IFolderView2_iface;
	IShellFolderView  IShellFolderView_iface;
	IShellFolderViewDual3 IShellFolderViewDual3_iface;*/
	IDropSource2       IDropSource_iface;
	IDropTarget2       IViewObject_iface;
	IDropTarget2      IFolderView2_iface;
	IDropTarget2  IShellFolderView_iface;
	IDropTarget2 IShellFolderViewDual3_iface;
	LONG              ref;
	IShellFolder*	pSFParent;
	IShellFolder2*	pSF2Parent;
	IShellBrowser*	pShellBrowser;
	ICommDlgBrowser*	pCommDlgBrowser;
	HWND		hWnd;		/* SHELLDLL_DefView */
	HWND		hWndList;	/* ListView control */
	HWND		hWndParent;
	FOLDERSETTINGS	FolderSettings;
	HMENU		hMenu;
	UINT		uState;
	UINT		cidl;
	LPITEMIDLIST	*apidl;
	LISTVIEW_SORT_INFO ListViewSortInfo;
	ULONG			hNotify;	/* change notification handle */
	HANDLE		hAccel;
	DWORD		dwAspects;
	DWORD		dwAdvf;
	IAdviseSink    *pAdvSink;
	IDropTarget*    pCurDropTarget; /* The sub-item, which is currently dragged over */
	IDataObject*    pCurDataObject; /* The dragged data-object */
	LONG            iDragOverItem;  /* Dragged over item's index, iff pCurDropTarget != NULL */
	UINT            cScrollDelay;   /* Send a WM_*SCROLL msg every 250 ms during drag-scroll */
	POINT           ptLastMousePos; /* Mouse position at last DragOver call */
} IShellViewImpl;
typedef struct {
	//IUnknown IUnknown_inner;
	IDropTarget2 IUnknown_inner;
	LONG ref;
	/*
	IShellFolder2 IShellFolder2_iface;
	IPersistFolder3 IPersistFolder3_iface;
	IDropTarget IDropTarget_iface;
	ISFHelper ISFHelper_iface;*/
	IDropTarget2 IShellFolder2_iface;
	IDropTarget2 IPersistFolder3_iface;
	IDropTarget2 IDropTarget_iface;
	IDropTarget2 ISFHelper_iface;
	IUnknown *outer_unk;

	CLSID *pclsid;

	/* both paths are parsible from the desktop */
	LPWSTR sPathTarget;     /* complete path to target used for enumeration and ChangeNotify */

	LPITEMIDLIST pidlRoot; /* absolute pidl */

	UINT cfShellIDList;    /* clipboardformat for IDropTarget */
	BOOL fAcceptFmt;       /* flag for pending Drop */
} IGenericSFImpl;
/*add by yangke end */


typedef struct tagTrackerWindowInfo
{
	IDataObject* dataObject;
	//IDropSource* dropSource; 
	IDropSource2 * dropSource;
	DWORD        dwOKEffect;
	DWORD*       pdwEffect;
	BOOL       trackingDone;
	HRESULT      returnValue;
	BOOL       escPressed;
	HWND       curTargetHWND;	/* window the mouse is hovering over */
	IDropTarget * curDragTarget;
	POINTL     curMousePos;       /* current position of the mouse in screen coordinates */
	DWORD      dwKeyState;        /* current state of the shift and ctrl keys and the mouse buttons */
} TrackerWindowInfo;

typedef LRESULT(WINAPI* DLLDISPATCHMESSAGE)(MSG* msg);