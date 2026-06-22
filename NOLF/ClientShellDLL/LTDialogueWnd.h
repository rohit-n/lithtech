/****************************************************************************
;
;	 MODULE:		CLTDialogueWnd (.h)
;
;	PURPOSE:		Class for a window with an irregular shape (like a bitmap)
;
;	HISTORY:		12/10/98 [kml] This file was created
;
;	COMMENT:		Copyright (c) 1998, Monolith Productions, Inc.
;
****************************************************************************/
#ifndef _LTDIALOGUEWND_H_
#define _LTDIALOGUEWND_H_

// Includes
#include "LTMaskedWnd.h"
#include "Timer.h"
#include "LTDecisionWnd.h"
#include "CSDefs.h"
#include "AutoMessage.h"

#define DIALOGUEWND_COMMAND_CHAR	'^'

class CLTGUIFont;

class DIALOGUEWNDCREATESTRUCT : public LTWNDCREATESTRUCT
{
public:
    DIALOGUEWNDCREATESTRUCT();

    LTFLOAT      fAlpha;
    LTFLOAT      fDecisionAlpha;
	BOOL		bFrame;
	BOOL		bDecisionFrame;
	const char	*szFrame;
	char		*szDecisionBitmap;
	HSURFACE	hDecisionSurf;
	CLTGUIFont	*pFont;
	int			nWidth;
	int			nHeight;
};

inline DIALOGUEWNDCREATESTRUCT::DIALOGUEWNDCREATESTRUCT()
{
	memset(this, 0, sizeof(DIALOGUEWNDCREATESTRUCT));
	szWndName = "DialogueWnd";
}

// Classes
class CLTDialogueWnd : public CLTMaskedWnd
{
public:

	CLTDialogueWnd();
	virtual ~CLTDialogueWnd() { Term(); }
	virtual void Term();

	virtual BOOL Init(DIALOGUEWNDCREATESTRUCT *pcs);

	virtual BOOL DrawToSurface(HSURFACE hSurfDest);

	virtual BOOL Update(float fTimeDelta);
	virtual BOOL ShowWindow(BOOL bShow = TRUE, BOOL bPlaySound = TRUE, BOOL bAnimate = TRUE);

	BOOL	ShowPic(BOOL bShow = TRUE) { return(m_Pic.ShowWindow(bShow)); }
	BOOL	SetPic(char *szBitmap);
	void	SetText(const char *szString) { m_csText = szString; }
	BOOL	DisplayText(char *szText, char *szAvatar, BOOL bStayOpen, char *szDecisions = NULL);
	BOOL	DisplayText(DWORD dwID, char *szAvatar, BOOL bStayOpen, char *szDecisions = NULL);
	BOOL	DisplayTempText(char *szText);
	BOOL	Skip();
	void	DoneShowing(uint8 bySelection = 0, DWORD dwSelection = 0);
	void	Reset();
	BOOL	InitFrame(const char *szFrame);
	BOOL	ShowDecisions();
	void	Open();
	void	Close();

	virtual BOOL OnLButtonDown(int xPos, int yPos);
	virtual BOOL OnRButtonDown(int xPos, int yPos);

	CLTDecisionWnd*	GetDecisionWnd() { return &m_DecisionWnd; }
	void	SetImmediateDecisions(BOOL bSet = TRUE) { m_bImmediateDecisions = bSet; }
#ifdef RKN_FIXME
	void	SetDrawData(LITHFONTDRAWDATA* plfdd) { memcpy(&m_lfdd,plfdd,sizeof(LITHFONTDRAWDATA)); }
#endif
protected:

    void    SetAlpha(LTFLOAT fAlpha);

	CLTGUIFont *m_pFont;
	CString		m_csText;
	CLTMaskedWnd	m_Pic;
	BOOL		m_bOpening;
	BOOL		m_bClosing;
	CTimer		m_tmrClose;
	float		m_fCloseHeight;
	BOOL		m_bDecisions;
	BOOL		m_bCanClose;
	BOOL		m_bMore;
	CString		m_csDecisions;
	CLTDecisionWnd	m_DecisionWnd;
	CRect		m_rcFrame;
	CRect		m_rcTotal;
	BOOL		m_bImmediateDecisions;
	BOOL		m_bFrame;
#ifdef RKN_FIXME
	LITHFONTDRAWDATA m_lfdd;
	LITHFONTSAVEDATA m_lfsd;
#endif
	CLTSurfaceArray m_collFrames;
	CDWordArray m_collDialogueIDs;
};

// Inlines
inline CLTDialogueWnd::CLTDialogueWnd()
{
	m_rcFrame.SetRect(0,0,0,0);
	m_rcTotal.SetRect(0,0,0,0);
	m_pFont = NULL;
	m_bOpening = FALSE;
	m_bClosing = FALSE;
	m_bDecisions = FALSE;
	m_bCanClose = FALSE;
	m_bMore = FALSE;
	m_bImmediateDecisions = FALSE;
	m_bFrame = FALSE;
}

inline void CLTDialogueWnd::DoneShowing(uint8 bySelection, DWORD dwSelection)
{
	m_bDecisions = FALSE;
	m_DecisionWnd.ShowWindow(FALSE,TRUE,FALSE);
	m_bEnabled = TRUE;

	// Notify the server that we're done showing
	if (bySelection)
	{
		CAutoMessage cMsg;
		cMsg.Writeuint8(CSM_DIALOGUE_DONE_SELECTION);
		cMsg.Writeuint8(bySelection);
		cMsg.Writeuint32(dwSelection);
		g_pLTClient->SendToServer(cMsg.Read(), MESSAGE_GUARANTEED);
	}
	else
	{
		CAutoMessage cMsg;
		cMsg.Writeuint8(CSM_DIALOGUE_DONE);
		g_pLTClient->SendToServer(cMsg.Read(), MESSAGE_GUARANTEED);
	}

	if(!m_bMore)
	{
		ShowWindow(FALSE,FALSE);
	}
	else
	{
		// We need to disable us until our next text comes in
		m_bEnabled = FALSE;
	}
}

inline void CLTDialogueWnd::Reset()
{
	m_bClosing = FALSE;
	m_bOpening = FALSE;
	m_bDecisions = FALSE;
	m_bCanClose = FALSE;
	m_bMore = FALSE;
	m_csDecisions.Empty();
}

inline void CLTDialogueWnd::Open()
{
	// We're no longer visible, but we're enabled again
	m_bEnabled = TRUE;
	m_bOpening = FALSE;
	m_bClosing = FALSE;

	int yMid = m_yPos + (m_nHeight / 2);
	m_nHeight = (int)m_fCloseHeight;
	// Restore us to original size
	MoveWindow(m_xPos,yMid-(m_nHeight / 2));
}

inline void CLTDialogueWnd::Close()
{
	// We're no longer visible, but we're enabled again
	m_bVisible = FALSE;
	m_bEnabled = TRUE;
	m_bClosing = FALSE;
	m_bOpening = FALSE;

	int yMid = m_yPos + (m_nHeight / 2);
	m_nHeight = (int)m_fCloseHeight;
	// Restore us to original size
	MoveWindow(m_xPos,yMid-(m_nHeight / 2));
}

#endif