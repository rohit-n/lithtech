// BaseFolder.h: interface for the CBaseFolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEFOLDER_H__88EE6E21_1515_11D3_B2DB_006097097C7B__INCLUDED_)
#define AFX_BASEFOLDER_H__88EE6E21_1515_11D3_B2DB_006097097C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ltguimgr.h"
#include "BitmapCtrl.h"
#include "GroupCtrl.h"
#include "ListCtrl.h"
#ifdef RKN_FIXME
#include "SliderCtrl.h"
#include "CycleCtrl.h"
#endif
#include "stdlith.h"
#include "BaseScaleFX.h"
#ifdef RKN_FIXME
#include "StaticTextCtrl.h"
#endif

#define MAX_INT_ATTACHMENTS 5
struct INT_ATTACH
{
	INT_ATTACH() { fScale = 1.0f;nAttachmentID = -1;pszSocket=LTNULL;}

	LTFLOAT	fScale;
	int		nAttachmentID;
	char	*pszSocket;
};
struct AttachmentData
{
	AttachmentData() { socket = INVALID_MODEL_SOCKET; }

	CBaseScaleFX	sfx;
	HMODELSOCKET	socket;
};

class CFolderMgr;

class CPageBreakCtrl : public CLTGUICtrl
{
public:
	void	Render ( HSURFACE hDestSurf ) {}
	uint16		GetWidth ( ) {return 0; }
	uint16		GetHeight ( ) {return 0; }
    uint32  GetID() { return m_nCommandID; }

};

const int kNoSelection = -999;

class CBaseFolder : public CLTGUICommandHandler
{
public:
	CBaseFolder();
	virtual ~CBaseFolder();

	// Initialization/Termination
    virtual LTBOOL   Init(int nFolderID);
	virtual void	Term();

	// Builds the folder
    virtual LTBOOL   Build();
    inline  LTBOOL   IsBuilt() const { return m_bBuilt; }

    virtual LTBOOL   IsAvailable() { return LTTRUE; }  //used for folders that may or may not be available


	virtual void	Escape();

    virtual uint32 OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2);

	// Get the folder ID
	inline int	GetFolderID() const	{ return m_nFolderID; }


	// Renders the folder to a surface
    virtual LTBOOL   Render(HSURFACE hDestSurf);
	virtual void	UpdateInterfaceSFX();

	// Creates the title for the folder
    LTBOOL           CreateTitle(HSTRING hString);
    LTBOOL           CreateTitle(int nStringID);
    LTBOOL           CreateTitle(char *lpszTitle);

	//set the background for the folder
	virtual void SetBackground(char *lpszBitmap);
    void         UseArrows(LTBOOL bArrows, LTBOOL bLeft=LTTRUE, LTBOOL bRight=LTTRUE);
    void         UseBack(LTBOOL	bBack=LTTRUE,LTBOOL	bOK=LTFALSE, LTBOOL bReturn = LTFALSE );
    void         UseContinue(int nContinueID, int nHelpID = LTNULL, int nStringID = LTNULL);
    void         UseMain(LTBOOL bMain=LTTRUE);

	// This is called when the folder gets or loses focus
    virtual void    OnFocus(LTBOOL bFocus);

	// Handles a key press.  Returns FALSE if the key was not processed through this method.
	// Left, Up, Down, Right, and Enter are automatically passed through OnUp(), OnDown(), etc.
    virtual LTBOOL   HandleKeyDown(int key, int rep);
    virtual LTBOOL   HandleKeyUp(int key) { return LTFALSE; }
    virtual LTBOOL   HandleChar(char c);
    virtual LTBOOL   HandleForceUpdate() { return LTFALSE; }

	//reset selection and help display
	virtual void	ForceMouseUpdate();
	virtual void	UpdateHelpText();

	// Mouse messages
    virtual LTBOOL   OnLButtonDown(int x, int y);
    virtual LTBOOL   OnLButtonUp(int x, int y);
    virtual LTBOOL   OnLButtonDblClick(int x, int y);
    virtual LTBOOL   OnRButtonDown(int x, int y);
    virtual LTBOOL   OnRButtonUp(int x, int y);
    virtual LTBOOL   OnRButtonDblClick(int x, int y);
    virtual LTBOOL   OnMouseMove(int x, int y);

	inline int 		GetPageLeft() const {return m_PageRect.left;}
	inline int 		GetPageRight() const {return m_PageRect.right;}
	inline int 		GetPageTop() const {return m_PageRect.top;}
	inline int 		GetPageBottom() const {return m_PageRect.bottom;}

	CLTGUIFont		*GetTitleFont();
	CLTGUIFont		*GetHelpFont();
	CLTGUIFont		*GetSmallFont();
	CLTGUIFont		*GetMediumFont();
	CLTGUIFont		*GetLargeFont();
	CLTGUIFont		*GetDefaultFont();

    inline void     SetTitleColor(HLTCOLOR titleColor)  { m_hTitleColor = titleColor; }

	//these return the index of the added control
    int             AddFixedControl(CLTGUICtrl* pCtrl, LTIntPt pos, LTBOOL bSelectable = LTTRUE);
	int				AddFreeControl(CLTGUICtrl* pCtrl);

	int				SetSelection(int select, LTBOOL bFindSelectable = LTFALSE);
	int				NextSelection();
	int				PreviousSelection();
	inline int		GetSelection() const		{return m_nSelection;}

	void			SetCapture(CLTGUICtrl *pCtrl)	{m_pCaptureCtrl = pCtrl;}
	CLTGUICtrl*		GetCapture()					{return m_pCaptureCtrl;}

	inline CLTGUICtrl*		GetSelectedControl()  {return GetControl(m_nSelection);}
	CLTGUICtrl*				GetControl(int nIndex);
	int						GetIndex(CLTGUICtrl* pCtrl);

    inline LTBOOL    IsFirstPage() const {return (m_nFirstDrawn == 0);}
    inline LTBOOL    IsLastPage() const  {return (m_nLastDrawn >= (int)m_controlArray.GetSize()-1);}

    virtual LTBOOL   NextPage(LTBOOL bChangeSelection = LTTRUE);
    virtual LTBOOL   PreviousPage(LTBOOL bChangeSelection = LTTRUE);
	void			CheckArrows();

	inline void		SetItemSpacing(int space)	{m_nItemSpacing = space;}

	//this function creates a string, the caller must free it
    virtual         HSTRING GetHelpString(uint32 dwHelpId, int nControlIndex);

	//default font for items is the large font
	// These AddXXX() functions call CreateXXX() and then add the control to the FreeControl list
    CLTGUITextCtrl*     AddTextItem(HSTRING hString, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*     AddTextItem(int stringID, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*     AddTextItem(char *pString, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*        AddStaticTextItem(HSTRING hString, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUITextCtrl*        AddStaticTextItem(int stringID, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed = LTFALSE,  CLTGUIFont *pFont = LTNULL);
    CLTGUITextCtrl*        AddStaticTextItem(char *pString, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed = LTFALSE,  CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         AddEditCtrl(HSTRING hDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         AddEditCtrl(int nDescriptionID, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         AddEditCtrl(char *pszDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUICycleCtrl*             AddCycleItem(HSTRING hText, int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUICycleCtrl*             AddCycleItem(int stringID,  int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUICycleCtrl*             AddCycleItem(char *pString, int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            AddToggle(HSTRING hText, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            AddToggle(int stringID, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            AddToggle(char *pString, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUISlider*            AddSlider(HSTRING hText, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUISlider*            AddSlider(int stringID,  int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUISlider*            AddSlider(char *pString, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUIColumnCtrl*   AddColumnText(DWORD dwCommandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, DWORD dwParam1 = 0, DWORD dwParam2 = 0);

	CGroupCtrl*				AddGroup(int nWidth , int nHeight, int helpID);

	// These CreateXXX() create controls but do not add them to any list
    CLTGUITextCtrl*     CreateTextItem(HSTRING hString, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*     CreateTextItem(int stringID, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*     CreateTextItem(char *pString, uint32 commandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, int *pnValue=LTNULL);
    CLTGUITextCtrl*        CreateStaticTextItem(HSTRING hString, uint32 commandID, int helpID, int width, int height = 0, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUITextCtrl*        CreateStaticTextItem(int stringID, uint32 commandID, int helpID, int width, int height = 0, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUITextCtrl*        CreateStaticTextItem(char *pString, uint32 commandID, int helpID, int width, int height = 0, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         CreateEditCtrl(HSTRING hDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         CreateEditCtrl(int nDescriptionID, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUIEditCtrl*         CreateEditCtrl(char *pszDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset = 25, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL);
    CLTGUICycleCtrl*             CreateCycleItem(HSTRING hText, int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUICycleCtrl*             CreateCycleItem(int stringID,   int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUICycleCtrl*             CreateCycleItem(char *pString, int helpID, int nHeaderWidth, int nSpacerWidth=25, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            CreateToggle(HSTRING hText, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            CreateToggle(int stringID, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUIToggle*            CreateToggle(char *pString, int helpID, int nRightColumnOffset, LTBOOL *pbValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont=LTNULL);
    CLTGUISlider*            CreateSlider(HSTRING hText, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUISlider*            CreateSlider(int stringID,  int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUISlider*            CreateSlider(char *pString, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue=LTNULL, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont =LTNULL);
    CLTGUIColumnCtrl*   CreateColumnText(DWORD dwCommandID, int helpID, LTBOOL bFixed = LTFALSE, CLTGUIFont *pFont = LTNULL, DWORD dwParam1 = 0, DWORD dwParam2 = 0);
	CGroupCtrl*				CreateGroup(int nWidth , int nHeight, int helpID);



	void				AddPageBreak();
	void				AddBlankLine();


protected:
	// Calls UpdateData on each control in the folder
    void            UpdateData(LTBOOL bSaveAndValidate=LTTRUE);

	// Handle input
    virtual LTBOOL   OnUp();
    virtual LTBOOL   OnDown();
    virtual LTBOOL   OnLeft();
    virtual LTBOOL   OnRight();
    virtual LTBOOL   OnEnter();
    virtual LTBOOL   OnPageUp();
    virtual LTBOOL   OnPageDown();
    virtual LTBOOL   OnTab();

	// Sets the position of the title
	inline void		SetTitlePos(int x, int y)				{ m_titlePos.x=x; m_titlePos.y=y; }
    inline void     SetTitlePos(LTIntPt pt)                  { SetTitlePos(pt.x, pt.y); }
	inline void		SetTitleAlignment(int nAlignment)		{ m_nTitleAlign = nAlignment; }

	// Gets the index of the control that is under the specific screen point.
	// Returns FALSE if there isn't one under the specified point.
    LTBOOL       GetControlUnderPoint(int xPos, int yPos, int *pnIndex);

protected:

	void			RemoveAll();
	void			RemoveFree();
	void			RemoveFixed();
	void			CalculateLastDrawn();

	void			CreateUpArrow();
	void			CreateDownArrow();
	void			CreateBack(LTBOOL bOK = LTFALSE, LTBOOL bReturn = LTFALSE);
	void			CreateMain();
	void			CreateContinue(int nStringID, int nHelpID);
	void			RemoveFixedControl(CLTGUICtrl* pControl);
	LTBOOL			SkipControl(CLTGUICtrl* pControl);

	virtual void	CreateInterfaceSFX();
	virtual void	RemoveInterfaceSFX();

	void			CreateScaleFX(char *szFXName);
	void			CreateCharFX(INT_CHAR *pChar);
	void			CreateAttachFX(INT_ATTACH *pAttach);
	void			ClearAttachFX();

	//converts to and from the negative indexes used for fixed controls
	int				FixedIndex(int x) {return -1 - x;}

protected:

    LTBOOL           m_bInit;
    LTBOOL           m_bBuilt;

	CFolderMgr*		m_pFolderMgr;

	int				m_nFolderID;		// The ID of this folder
	int				m_nContinueID;		// The ID of the folder to show when continue is clicked

	HSTRING			m_hTitleString;		// The title string

    LTIntPt          m_titlePos;         // The title position
	int				m_nTitleAlign;		// the title alignment

	LTBOOL			m_bHaveFocus;

	// Array of SFX owned by this folder
	CMoArray<CSpecialFX *>	m_SFXArray;

	// Array of fixed controls that this folder owns
	CMoArray<CLTGUICtrl *>	m_fixedControlArray;

	// Array of fixed controls that should be skipped by next/previous selection
	CMoArray<CLTGUICtrl *>	m_skipControlArray;

	// Array of free controls that this folder owns
	CMoArray<CLTGUICtrl *>	m_controlArray;


	int				m_nSelection;
	int				m_nFirstDrawn;
	int				m_nLastDrawn;
	int				m_nLMouseDownItemSel;
	int				m_nRMouseDownItemSel;
	int				m_nItemSpacing;

	CLTGUICtrl*		m_pCaptureCtrl;

    LTBOOL           m_bScrollWrap;
	char			m_sBackground[128];

    LTRect           m_PageRect;
	int				m_nAlignment;
    HLTCOLOR        m_hSelectedColor;
    HLTCOLOR        m_hNonSelectedColor;
    HLTCOLOR        m_hDisabledColor;

    HLTCOLOR        m_hTransparentColor; // The transparent color
    HLTCOLOR        m_hTitleColor;       // Color to use for title

    uint32          m_dwCurrHelpID;
	static HSURFACE		m_hHelpSurf;

	CBitmapCtrl			*m_pUpArrow;
	CBitmapCtrl			*m_pDownArrow;
	CLTGUITextCtrl	*m_pBack;
	CLTGUITextCtrl	*m_pMain;
	CLTGUITextCtrl	*m_pContinue;
	

    LTIntPt      m_UpArrowPos;
    LTIntPt      m_DownArrowPos;

    static  LTBOOL       m_bReadLayout;
    static  LTRect       m_HelpRect;
    static  LTIntPt      m_BackPos;
    static  LTIntPt      m_ContinuePos;
    static  LTIntPt      m_MainPos;
    static  HLTCOLOR    m_hShadeColor;
    static  HLTCOLOR    m_hBarColor;
	static	int			m_nBarHt;
	static	int			m_nTopShadeHt;
	static	int			m_nBottomShadeHt;
	static	char		m_sArrowBack[128];
	static	char		m_sArrowNext[128];
    static  LTIntPt      m_ArrowBackPos;
    static  LTIntPt      m_ArrowNextPos;


	CBaseScaleFX	m_CharSFX;
	int				m_nNumAttachments;
	AttachmentData	m_aAttachment[MAX_INT_ATTACHMENTS];



};

inline  CLTGUITextCtrl* CBaseFolder::AddTextItem(HSTRING hString, uint32 commandID, int helpID, LTBOOL bFixed, CLTGUIFont *pFont, int *pnValue)
{
	CLTGUITextCtrl* pCtrl = CreateTextItem(hString, commandID, helpID, bFixed, pFont, pnValue);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUITextCtrl* CBaseFolder::AddTextItem(int stringID, uint32 commandID, int helpID, LTBOOL bFixed, CLTGUIFont *pFont, int *pnValue)
{
	CLTGUITextCtrl* pCtrl = CreateTextItem(stringID, commandID, helpID, bFixed, pFont, pnValue);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUITextCtrl* CBaseFolder::AddTextItem(char *pString, uint32 commandID, int helpID, LTBOOL bFixed, CLTGUIFont *pFont, int *pnValue)
{
	CLTGUITextCtrl* pCtrl = CreateTextItem(pString, commandID, helpID, bFixed, pFont, pnValue);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline  CLTGUITextCtrl* CBaseFolder::AddStaticTextItem(HSTRING hString, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUITextCtrl* pCtrl = CreateStaticTextItem(hString, commandID, helpID, width, height, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUITextCtrl* CBaseFolder::AddStaticTextItem(int stringID, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUITextCtrl* pCtrl = CreateStaticTextItem(stringID, commandID, helpID, width, height, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUITextCtrl* CBaseFolder::AddStaticTextItem(char *pString, uint32 commandID, int helpID, int width, int height, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUITextCtrl* pCtrl = CreateStaticTextItem(pString, commandID, helpID, width, height, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline  CLTGUIEditCtrl*     CBaseFolder::AddEditCtrl(HSTRING hDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIEditCtrl*	pCtrl = CreateEditCtrl(hDescription, commandID, helpID, pBuffer, nBufferSize, nTextOffset, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUIEditCtrl*     CBaseFolder::AddEditCtrl(int nDescriptionID, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIEditCtrl*	pCtrl = CreateEditCtrl(nDescriptionID, commandID, helpID, pBuffer, nBufferSize, nTextOffset, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUIEditCtrl*     CBaseFolder::AddEditCtrl(char *pszDescription, uint32 commandID, int helpID, char *pBuffer, int nBufferSize, int nTextOffset, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIEditCtrl*	pCtrl = CreateEditCtrl(pszDescription, commandID, helpID, pBuffer, nBufferSize, nTextOffset, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline	CLTGUICycleCtrl*			CBaseFolder::AddCycleItem(HSTRING hText, int helpID, int nHeaderWidth, int nSpacerWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUICycleCtrl*	pCtrl = CreateCycleItem(hText, helpID, nHeaderWidth, nSpacerWidth, pnValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CLTGUICycleCtrl*			CBaseFolder::AddCycleItem(int stringID,	int helpID, int nHeaderWidth, int nSpacerWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUICycleCtrl*	pCtrl = CreateCycleItem(stringID, helpID, nHeaderWidth, nSpacerWidth, pnValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CLTGUICycleCtrl*			CBaseFolder::AddCycleItem(char *pString, int helpID, int nHeaderWidth, int nSpacerWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUICycleCtrl*	pCtrl = CreateCycleItem(pString, helpID, nHeaderWidth, nSpacerWidth, pnValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline  CLTGUIToggle*        CBaseFolder::AddToggle(HSTRING hText, int helpID, int nRightColumnOffset, LTBOOL *pbValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIToggle* pCtrl = CreateToggle(hText, helpID, nRightColumnOffset, pbValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUIToggle*        CBaseFolder::AddToggle(int stringID, int helpID, int nRightColumnOffset, LTBOOL *pbValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIToggle* pCtrl = CreateToggle(stringID, helpID, nRightColumnOffset, pbValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline  CLTGUIToggle*        CBaseFolder::AddToggle(char *pString, int helpID, int nRightColumnOffset, LTBOOL *pbValue, LTBOOL bFixed, CLTGUIFont *pFont)
{
	CLTGUIToggle* pCtrl = CreateToggle(pString, helpID, nRightColumnOffset, pbValue, bFixed, pFont);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline	CLTGUISlider*		CBaseFolder::AddSlider(HSTRING hText, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont )
{
	CLTGUISlider* pCtrl = CBaseFolder::CreateSlider(hText, helpID, nSliderOffset, nSliderWidth, pnValue, bFixed, pFont );
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CLTGUISlider*		CBaseFolder::AddSlider(int stringID,  int helpID, int nSliderOffset, int nSliderWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont )
{
	CLTGUISlider* pCtrl = CBaseFolder::CreateSlider(stringID, helpID, nSliderOffset, nSliderWidth, pnValue, bFixed, pFont );
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CLTGUISlider*		CBaseFolder::AddSlider(char *pString, int helpID, int nSliderOffset, int nSliderWidth, int *pnValue, LTBOOL bFixed, CLTGUIFont *pFont )
{
	CLTGUISlider* pCtrl = CBaseFolder::CreateSlider(pString, helpID, nSliderOffset, nSliderWidth, pnValue, bFixed, pFont );
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CLTGUIColumnCtrl*	CBaseFolder::AddColumnText(DWORD dwCommandID, int helpID, LTBOOL bFixed, CLTGUIFont *pFont, DWORD dwParam1, DWORD dwParam2)
{
	CLTGUIColumnCtrl* pCtrl = CBaseFolder::CreateColumnText(dwCommandID, helpID, bFixed, pFont, dwParam1, dwParam2);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}
inline	CGroupCtrl* CBaseFolder::AddGroup(int nWidth , int nHeight, int helpID)
{
	CGroupCtrl* pCtrl = CBaseFolder::CreateGroup(nWidth,nHeight,helpID);
	if (pCtrl)
		AddFreeControl(pCtrl);
	return pCtrl;
}

inline	LTBOOL CBaseFolder::SkipControl(CLTGUICtrl* pControl)
{
	if (!pControl) return  LTFALSE;
	uint32 i = m_skipControlArray.FindElement(pControl);
	return i < m_skipControlArray.GetSize();
}

#endif // !defined(AFX_BASEFOLDER_H__88EE6E21_1515_11D3_B2DB_006097097C7B__INCLUDED_)