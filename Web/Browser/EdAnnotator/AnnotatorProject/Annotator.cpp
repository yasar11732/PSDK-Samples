/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// Annotator.cpp : Implementation of CAnnotator

#include "stdafx.h"
#include "EDAnnotator.h"
#include "Annotator.h"
#include "docobj.h"
#include "mshtmcid.h"
#include "mshtmhst.h"
#include "mshtmdid.h"

/////////////////////////////////////////////////////////////////////////////
// CAnnotator

// IHTMLEditDesigner
STDMETHODIMP
CAnnotator::PostEditorEventNotify(DISPID inEvtDispId, IHTMLEventObj *pIEventObj)
{
    return S_FALSE;
}

STDMETHODIMP
CAnnotator::PostHandleEvent(DISPID inEvtDispId, IHTMLEventObj *pIEventObj)
{

    return S_FALSE;
}

STDMETHODIMP
CAnnotator::PreHandleEvent(DISPID inEvtDispId, IHTMLEventObj *pIEventObj)
{
    USES_CONVERSION;

    CComQIPtr<IHTMLElement> spSrcElem;
    CComQIPtr<IHTMLElement3> spSrcElem3;
    VARIANT_BOOL bIsEditable;

    pIEventObj->get_srcElement(&spSrcElem);
    spSrcElem->QueryInterface(IID_IHTMLElement3, (void**)&spSrcElem3);
    spSrcElem3->get_isContentEditable(&bIsEditable);

    // Reject all events that aren't in content-editable areas
    if (bIsEditable == VARIANT_FALSE) return S_FALSE;

    CComQIPtr<IOleCommandTarget> spCmdTarg;
    CComBSTR bstrSrcTagName;
    CComVariant var;
    LPSTR szName;
    BOOL bAreObjectsEqual = FALSE;

    m_spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&spCmdTarg);

    spSrcElem->get_tagName(&bstrSrcTagName);
    szName = OLE2A(bstrSrcTagName);

    switch (inEvtDispId)
    {
    case DISPID_HTMLELEMENTEVENTS2_ONMOUSEOVER:

        if (!strcmp(szName, "!") || !strcmp(szName, "COMMENT"))
        {
            // Set cursor over comment to arrow
            var = TRUE;
            spCmdTarg->Exec(&CGID_MSHTML, IDM_OVERRIDE_CURSOR, OLECMDEXECOPT_DODEFAULT, &var, NULL);
            HCURSOR arrow = LoadCursor(NULL,IDC_ARROW);
            m_hOldCursor = SetCursor(arrow);
        }
        break;

    case DISPID_HTMLELEMENTEVENTS2_ONMOUSEOUT:

        if (!strcmp(szName, "!") || !strcmp(szName, "COMMENT"))
        {
            // Set cursor over comment back to auto
            var = FALSE;
            SetCursor(m_hOldCursor);
            spCmdTarg->Exec(&CGID_MSHTML, IDM_OVERRIDE_CURSOR, OLECMDEXECOPT_DODEFAULT, &var, NULL);
        }
        break;

    case DISPID_HTMLELEMENTEVENTS2_ONMOUSEUP:

        // Check if current src element is the same as any saved src element
        // which would be the comment that is currently being edited
        // If it is, we want to close the comment edit box without opening a new one.
        if (m_spSrcElem)
            bAreObjectsEqual = spSrcElem.IsEqualObject(m_spSrcElem);

        // If there is an open comment edit box already and the mouse release
        // didn't occur in the edit box, close the comment edit box
        if (m_spCommentEditBox &&
            !spSrcElem.IsEqualObject(m_spCommentEditBox))
                CloseCommentEditBox();

        // If there isn't an open comment edit box already, and
        // if the click was not on a glyph to close the comment edit box, and
        // if the click occurred on a comment element,
        // then open a comment edit box
        if (!m_spCommentEditBox &&
            !bAreObjectsEqual &&
            (!(strcmp(szName, "!")) || !(strcmp(szName, "COMMENT"))))
                OpenCommentEditBox(spSrcElem);
        
        break;
    }

    return S_FALSE;
}

STDMETHODIMP
CAnnotator::TranslateAccelerator(DISPID inEvtDispId, IHTMLEventObj *pIEventObj)
{
    return S_FALSE;
}

// IAnnotator
STDMETHODIMP CAnnotator::AttachAnnotator(IHTMLDocument2* pDoc)
{
    CComPtr<IServiceProvider> spSP;
    CComPtr<IHTMLEditServices> spES;

    m_spDoc = pDoc; // IUnknown::AddRef is automatically called 
                    // on smart pointer m_spDoc

    m_spDoc->QueryInterface(IID_IServiceProvider, (void**)&spSP);

    spSP->QueryService(SID_SHTMLEditServices, 
                       IID_IHTMLEditServices, 
                       (void**)&spES);

    this->QueryInterface(IID_IHTMLEditDesigner, (void**)&m_spDesigner);

    spES->AddDesigner(m_spDesigner);

    return S_OK;
}

STDMETHODIMP CAnnotator::DetachAnnotator()
{
    CComPtr<IServiceProvider> spSP;
    CComPtr<IHTMLEditServices> spES;

    m_spDoc->QueryInterface(IID_IServiceProvider, (void**)&spSP);

    spSP->QueryService(SID_SHTMLEditServices, 
                       IID_IHTMLEditServices, 
                       (void**)&spES);

    spES->RemoveDesigner(m_spDesigner);

    m_spDesigner = (IHTMLEditDesigner*)NULL; // Assignment of NULL causes automatic
                                             // call toIUnknown::Release on the
                                             // m_spDesigner smart pointer.
    return S_OK;
}

STDMETHODIMP CAnnotator::ShowCommentGlyphs(BOOL bShow)
{
    CComVariant vGlyphTableEntry;
    CComPtr<IOleCommandTarget> pCmdTarg;

    m_spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&pCmdTarg);

    if (bShow)
    {
        //Load Glyph Table Entry into VARIANT
        vGlyphTableEntry =
            "%%comment^^%%res://EDannotator.dll/comment.gif^^%%0^^%%3^^%%3^^%%4^^%%20^^%%15^^%%20^^%%15^^**";

        // Exec IDM_ADDTOGLYPHTABLE
        pCmdTarg->Exec(&CGID_MSHTML, 
                       IDM_ADDTOGLYPHTABLE,
                       OLECMDEXECOPT_DODEFAULT, 
                       &vGlyphTableEntry, 
                       NULL);
    }
    else
        pCmdTarg->Exec(&CGID_MSHTML, 
                       IDM_EMPTYGLYPHTABLE, 
                       OLECMDEXECOPT_DODEFAULT, 
                       NULL, 
                       NULL);

    return S_OK;
}

STDMETHODIMP
CAnnotator::AddComment()
{
    CComPtr<IDisplayServices> spDS;
    CComPtr<IHTMLCaret> spCaret;
    CComPtr<IDisplayPointer> spDP;
    CComPtr<IHTMLElement> spNewComment;
    CComPtr<IHTMLElement> spFElem;
	CComPtr<IHTMLElement3> spFElem3;
    CComPtr<IHTMLWindow2> spWin;
    CComPtr<IMarkupServices> spMS;
    CComPtr<IMarkupPointer> spMP;
	VARIANT_BOOL bIsEditable;

    // Retrieve interface for insertion point,
    // place display pointer at its location, and retrieve the
	// flow element containing the display pointer
    m_spDoc->QueryInterface(IID_IDisplayServices, (void**)&spDS);
    spDS->CreateDisplayPointer(&spDP);
    spDS->GetCaret(&spCaret);
    spCaret->MoveDisplayPointerToCaret(spDP);
    spDP->GetFlowElement(&spFElem);

	// Check if display pointer is in content-editable area
	spFElem->QueryInterface(IID_IHTMLElement3, (void**)&spFElem3);
	spFElem3->get_isContentEditable(&bIsEditable);
	if (bIsEditable != VARIANT_TRUE) return S_OK;

    // Check to see if comment is open;
    if (m_spCommentEditBox)
    {
        // If so, check to see if caret is in comment edit box

        if (spFElem.IsEqualObject(m_spCommentEditBox))
        {
            // If so, alert that comment can't be added to comment and return
            m_spDoc->get_parentWindow(&spWin);
            spWin->alert(L"Cannot add comment to comment.");
            return S_OK;
        }
        else
            CloseCommentEditBox();
    }

    // Add the new comment and open the comment edit box for it
    m_spDoc->QueryInterface(IID_IMarkupServices, (void**)&spMS);

    spMS->CreateElement(TAGID_COMMENT,
                        NULL,
                        &spNewComment);

    spMS->CreateMarkupPointer(&spMP);
    spDP->PositionMarkupPointer(spMP);

    spMS->InsertElement(spNewComment, spMP, NULL);
    OpenCommentEditBox(spNewComment);

    return S_OK;
}

//Helper methods
STDMETHODIMP 
CAnnotator::OpenCommentEditBox(IHTMLElement* pSrcElem)
{
    USES_CONVERSION;

    CComPtr<IHTMLElement> spBody;
    CComPtr<IHTMLElement2> spBody2;
    CComPtr<IHTMLElement2> spSrcElem2;
    CComPtr<IHTMLElement2> spCommentEditBox2;
    CComPtr<IHTMLElement3> spCommentEditBox3;
    CComPtr<IHTMLStyle> spStyle;
    CComPtr<IHTMLStyle2> spStyle2;
    CComBSTR bstrOuterHTML;
    CComBSTR spanString;
    CComBSTR tagName;
    CComVariant vBoxLeft, vBoxTop, vBoxWidth, vBoxHeight, vBoxBGColor;
    LPTSTR szName;

    // Retrieve entire comment and tag name
    m_spSrcElem = pSrcElem;
    m_spSrcElem->get_outerHTML(&bstrOuterHTML);
    m_spSrcElem->get_tagName(&tagName);
    szName = OLE2T(tagName);

    // Extract text from comment depending on comment style
    LONG lCommentLength = bstrOuterHTML.Length();

    if (!_tcscmp(szName, _T("!")))
    {
        for (int i = 4; i < lCommentLength - 3; i++)
        {
            LPTSTR onechar = (LPTSTR)&bstrOuterHTML.m_str[i];
            spanString.Append(onechar);
        }
    }

    if (!_tcscmp(szName, _T("COMMENT")))
    {
        int endbracket = 8;
        LPTSTR onechar = (LPTSTR)&bstrOuterHTML.m_str[endbracket];

        while (_tcscmp(onechar, _T(">"))) 
            onechar = (LPTSTR)&bstrOuterHTML.m_str[++endbracket];

        for (int i = ++endbracket; i < lCommentLength - 10; i++)
        {
            LPTSTR onechar = (LPTSTR)&bstrOuterHTML.m_str[i];
            spanString.Append(onechar);
        }
    }

    // Disable resizing handles on while in comment edit mode
    CComPtr<IOleCommandTarget> spCmdTarg;
    m_spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&spCmdTarg);
    spCmdTarg->Exec(&CGID_MSHTML, IDM_DISABLE_EDITFOCUS_UI, OLECMDEXECOPT_DODEFAULT, NULL, NULL);

    // Create the temporary comment edit box
    m_spDoc->createElement(L"span", &m_spCommentEditBox);
    m_spCommentEditBox->put_innerHTML(spanString);
    
    // insertAdjacentElement must be called after put_innerHTML 
    // or the undo command can erase the comment box's contents
    // insertAdjacentElement protects put_innerHTML from 
    // inclusion in undo stack
    m_spDoc->get_body(&spBody);
    spBody->QueryInterface(IID_IHTMLElement2, (void**)&spBody2);
    spBody2->insertAdjacentElement(L"beforeEnd", m_spCommentEditBox, NULL);

    CComPtr<IMarkupServices> spMUS;
    CComPtr<IMarkupPointer> spMUP;
    CComPtr<IDisplayServices> spDS;
    CComPtr<IDisplayPointer> spDP;
    CComPtr<ILineInfo> spLineInfo;
    POINT ptDPLocation;

    // Query for IMarkupServices and 
    // IDisplayServices interfaces
    m_spDoc->QueryInterface(IID_IMarkupServices, (void**)&spMUS);
    m_spDoc->QueryInterface(IID_IDisplayServices, (void**)&spDS);

    // Create markup pointer and move to end of source element
    spMUS->CreateMarkupPointer(&spMUP);
    spMUP->MoveAdjacentToElement(m_spSrcElem, ELEM_ADJ_AfterEnd);

    // Create display pointer and place at markup pointer
    spDS->CreateDisplayPointer(&spDP);
    spDP->MoveToMarkupPointer(spMUP, NULL);

    // Get ILineInfo interface from which to 
    // retrieve display pointer location
    spDP->GetLineInfo(&spLineInfo);
 
    // Get display pointer location and
    // tranfrom to global coordinate system
    spLineInfo->get_x(&(ptDPLocation.x));
    spLineInfo->get_baseLine(&(ptDPLocation.y));

    spDS->TransformPoint(&ptDPLocation,
                         COORD_SYSTEM_CONTENT, 
                         COORD_SYSTEM_GLOBAL, 
                         m_spSrcElem);

    // Transfer position, size and color for box to
    // VARIANT structures
    vBoxLeft = ptDPLocation.x;
    vBoxTop = ptDPLocation.y;
    vBoxWidth = 225;
    vBoxHeight = 150;
    vBoxBGColor = "#ff6666";

    // Set positioning and styles for comment edit box
    m_spCommentEditBox->get_style(&spStyle);
    spStyle->QueryInterface(IID_IHTMLStyle2, (void**)&spStyle2);
    spStyle2->put_position(L"absolute");
    spStyle->put_top(vBoxTop);
    spStyle->put_left(vBoxLeft);
    spStyle->put_width(vBoxWidth);
    spStyle->put_height(vBoxHeight);
    spStyle->put_backgroundColor(vBoxBGColor);
    spStyle->put_padding(L"5");
    spStyle->put_border(L"thin solid #666666");

    // Make Comment Edit Box contentEditable
    m_spCommentEditBox->QueryInterface(IID_IHTMLElement3, (void**)&spCommentEditBox3);
    spCommentEditBox3->put_contentEditable(L"true");

    // Place insertion point in box
    m_spCommentEditBox->QueryInterface(IID_IHTMLElement2, (void**)&spCommentEditBox2);
    spCommentEditBox2->focus();

    return S_OK;
}

STDMETHODIMP 
CAnnotator::CloseCommentEditBox()
{
    USES_CONVERSION;

    CComBSTR tagName;
    CComBSTR commentString;
    CComPtr<IHTMLWindow2> spWin;
    CComPtr<IHTMLElement> spBodyElem;
    CComPtr<IHTMLElement> spParElem;
    CComPtr<IHTMLDOMNode> spParElemNode;
    CComPtr<IHTMLDOMNode> spTempCommentBoxNode;
    CComPtr<IMarkupServices> spMUServ;
    CComPtr<IMarkupPointer> spMPSrcBeg;
    CComPtr<IMarkupPointer> spMPSrcEnd;
    CComPtr<IHTMLCommentElement> spCommentElement;
    CComPtr<IOleCommandTarget> spCmdTarg;

    m_spSrcElem->get_tagName(&tagName);
    LPSTR szName = OLE2A(tagName);

    // Format new comment from comment edit box inner text
    // Note: two different styles of comment
    if (!strcmp(szName, "!"))
        commentString = "<!--";

    CComBSTR spanString;
    m_spCommentEditBox->get_innerText(&spanString);
    commentString.AppendBSTR(spanString);

    if (!strcmp(szName, "!"))
        commentString.Append(_T("-->"));

    // Place new text in original comment
    m_spSrcElem->QueryInterface(IID_IHTMLCommentElement, (void**)&spCommentElement);
    spCommentElement->put_text(commentString);

    // Remove comment edit box
    m_spCommentEditBox->get_parentElement(&spParElem);

    m_spCommentEditBox->QueryInterface(IID_IHTMLDOMNode, 
                                       (void**)&spTempCommentBoxNode);

    spParElem->QueryInterface(IID_IHTMLDOMNode, 
                              (void**)&spParElemNode);

    spParElemNode->removeChild(spTempCommentBoxNode, NULL);

    // Release interface pointers; assignment of NULL causes automatic
    // call to IUnknown::Release on CComPtr smart pointers
    m_spCommentEditBox = (IHTMLElement*)NULL;
    m_spSrcElem = (IHTMLElement*)NULL;

    // Reactivate resizing handles when leaving comment edit mode
    m_spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&spCmdTarg);
    spCmdTarg->Exec(&CGID_MSHTML, IDM_DISABLE_EDITFOCUS_UI, OLECMDEXECOPT_DODEFAULT, NULL, NULL);

    return S_OK;
}

