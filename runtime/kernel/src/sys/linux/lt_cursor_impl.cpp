#include "bdefs.h"

#include "iltcursor.h"

typedef void* HCURSOR;

struct CLTCursorInst : public ILTCursorInst {
    CLTCursorInst() { m_hCursor = LTNULL; };
    ~CLTCursorInst() {};

    virtual LTRESULT IsValid() { return (m_hCursor ? LT_YES : LT_NO); };
    HCURSOR GetCursor() { return m_hCursor; };
    virtual void SetData(const void *pData) { m_hCursor = (HCURSOR)(pData); };
    virtual void *GetData() { return (void *)m_hCursor; };

    HCURSOR m_hCursor;
};


class CLTCursor : public ILTCursor {
public:
    declare_interface(CLTCursor);

    CLTCursor() {m_hCurrentCursor = LTNULL;  m_eCursorMode = CM_None; }

    // Enable/disable hardware cursor.
    virtual LTRESULT    SetCursorMode(CursorMode cMode, bool bForce = false);

    // Get current cursor mode.  Always returns LT_OK and always fills in cMode.
    virtual LTRESULT    GetCursorMode(CursorMode &cMode) {
        cMode = m_eCursorMode;
        return LT_OK;
    };

    // Returns LT_YES if a hardware cursor can be used, LT_NO otherwise.
    // Since we can't detect this, just return LT_YES for now.
    virtual LTRESULT IsCursorModeAvailable(CursorMode cMode) {return LT_YES;};

    // Set the current hardware cursor bitmap.  The bitmap comes from cshell.dll.
    virtual LTRESULT LoadCursorBitmapResource(const char *pName, HLTCURSOR &hCursor);

    // Free a cursor.
    virtual LTRESULT FreeCursor(const HLTCURSOR hCursor);

    // Set the current cursor.
    virtual LTRESULT SetCursor(HLTCURSOR hCursor) {return LT_OK;};

    // Check if an HLTCURSOR is a valid one; returns LT_YES or LT_NO
    virtual LTRESULT IsValidCursor(HLTCURSOR hCursor) {return LT_YES;};

    // Refresh the cursor
    virtual LTRESULT RefreshCursor() {return LT_OK;};

protected:

    LTRESULT        PreSetMode(CursorMode eNewMode) {return LT_UNSUPPORTED;};
    LTRESULT        PostSetMode(CursorMode eOldMode) {return LT_UNSUPPORTED;};

    CursorMode      m_eCursorMode;
    HLTCURSOR       m_hCurrentCursor;
};

//instantiate our implementation class.
define_interface(CLTCursor, ILTCursor);

LTRESULT CLTCursor::SetCursorMode(CursorMode cMode, bool bForce)
{
    m_eCursorMode = cMode;
    return LT_OK;
}

LTRESULT CLTCursor::FreeCursor(const HLTCURSOR hCursor) 
{
    delete reinterpret_cast<CLTCursorInst*>(hCursor);
    return LT_OK;
}

LTRESULT CLTCursor::LoadCursorBitmapResource(const char *pName, HLTCURSOR &hCursor)
{
    HLTCURSOR hNew;
    LT_MEM_TRACK_ALLOC(hNew = new CLTCursorInst(),LT_MEM_TYPE_MISC);
    hCursor = hNew;
    return LT_OK;
}


