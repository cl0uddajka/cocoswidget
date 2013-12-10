/****************************************************************************
Copyright (c) 2013 viva-Lijunlin

Created by Li JunLin on 2013

csdn_viva@foxmail.com
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "WidgetProtocol.h"

NS_CC_WIDGET_BEGIN



CDataSourceAdapterProtocol::CDataSourceAdapterProtocol()
: m_pDataSourceAdapterListener(NULL)
, m_pDataSourceAdapterHandler(NULL)
{
	
}

void CDataSourceAdapterProtocol::setDataSourceAdapter(CCObject* pListener, SEL_DataSoucreAdapterHandler pHandler)
{
	m_pDataSourceAdapterListener = pListener;
	m_pDataSourceAdapterHandler = pHandler;
}


CCObject* CDataSourceAdapterProtocol::executeDataSourceAdapterHandler(CCObject* pConvertCell, unsigned int uIdx)
{
	if( m_pDataSourceAdapterListener && m_pDataSourceAdapterHandler )
	{
		return (m_pDataSourceAdapterListener->*m_pDataSourceAdapterHandler)(pConvertCell, uIdx);
	}
	return NULL;
}


CPageChangeableProtocol::CPageChangeableProtocol()
: m_pPageChangedListener(NULL)
, m_pPageChangedHandler(NULL)
, m_nPageIndex(0)
{

}

void CPageChangeableProtocol::setOnPageChangedListener(CCObject* pListener, SEL_PageChangedHandler pHandler)
{
	m_pPageChangedListener = pListener;
	m_pPageChangedHandler = pHandler;
}

void CPageChangeableProtocol::executePageChangedHandler(CCObject* pSender, unsigned int uPageIdx)
{
	if( m_pPageChangedListener && m_pPageChangedHandler )
	{
		(m_pPageChangedListener->*m_pPageChangedHandler)(pSender, uPageIdx);
	}
}




CScrollableProtocol::CScrollableProtocol()
: m_pScrollingListener(NULL)
, m_pScrollingHandler(NULL)
{
	
}

void CScrollableProtocol::setOnScrollingListener(CCObject* pListener, SEL_ScrollingHandler pHandler)
{
	m_pScrollingListener = pListener;
	m_pScrollingHandler = pHandler;
}

void CScrollableProtocol::executeScrollingHandler(CCObject* pSender)
{
	if( m_pScrollingListener && m_pScrollingHandler )
	{
		(m_pScrollingListener->*m_pScrollingHandler)(pSender);
	}
}



CProgressEndedProtocol::CProgressEndedProtocol()
: m_pProgressEndedListener(NULL)
, m_pProgressEndedHandler(NULL)
{
	
}

void CProgressEndedProtocol::setOnProgressEndedListener(CCObject* pListener, SEL_ProgressEndedHandler pHandler)
{
	m_pProgressEndedListener = pListener;
	m_pProgressEndedHandler = pHandler;
}

void CProgressEndedProtocol::executeProgressEndedHandler(CCObject* pSender)
{
	if( m_pProgressEndedListener && m_pProgressEndedHandler )
	{
		(m_pProgressEndedListener->*m_pProgressEndedHandler)(pSender);
	}
}




CValueChangeableProtocol::CValueChangeableProtocol()
: m_pValueChangedListener(NULL)
, m_pValueChangedHandler(NULL)
, m_nValue(0)
{
	
}

void CValueChangeableProtocol::setOnValueChangedListener(CCObject* pListener, SEL_ValueChangedHandler pHandler)
{
	m_pValueChangedListener = pListener;
	m_pValueChangedHandler = pHandler;
}

void CValueChangeableProtocol::executeValueChangedHandler(CCObject* pSender, int nValue)
{
	if( m_pValueChangedListener && m_pValueChangedHandler )
	{
		(m_pValueChangedListener->*m_pValueChangedHandler)(pSender, nValue);
	}
}



CClickableProtocol::CClickableProtocol()
: m_pClickHandler(NULL)
, m_pClickListener(NULL)
{
	
}

void CClickableProtocol::setOnClickListener(CCObject* pListener, SEL_ClickHandler pHandler)
{
	m_pClickListener = pListener;
	m_pClickHandler = pHandler;
}

void CClickableProtocol::executeClickHandler(CCObject* pSender)
{
	if( m_pClickListener && m_pClickHandler )
	{
		(m_pClickListener->*m_pClickHandler)(pSender);
	}
}




CLongClickableProtocol::CLongClickableProtocol()
: m_pLongClickListener(NULL)
, m_pLongClickHandler(NULL)
, m_bLongClickedUpdate(false)
, m_fLongClickLastTouchDuration(0.0f)
, m_pLongClickLastTouch(NULL)
, m_bLongClickEnabled(false)
, m_fLongClickTimeCounter(0.0f)
{

}

void CLongClickableProtocol::setOnLongClickListener(CCObject* pListener, SEL_LongClickHandler pHandler)
{
	m_bLongClickEnabled  = pListener && pHandler;
	m_pLongClickListener = pListener;
	m_pLongClickHandler  = pHandler;
}

bool CLongClickableProtocol::executeLongClickHandler(CCObject* pSender, CCTouch* pTouch)
{
	if( m_pLongClickListener && m_pLongClickHandler )
	{
		return (m_pLongClickListener->*m_pLongClickHandler)(pSender, pTouch);
	}
	return false;
}







CCheckableProtocol::CCheckableProtocol()
: m_bChecked(false)
, m_pCheckListener(NULL)
, m_pCheckHandler(NULL)
, m_nExclusion(CC_WIDGET_NONE_EXCLUSION)
{

}

bool CCheckableProtocol::isChecked() const
{
	return m_bChecked;
}

void CCheckableProtocol::setChecked(bool bChecked)
{
	m_bChecked = bChecked;
}

void CCheckableProtocol::setOnCheckListener(CCObject* pListener, SEL_CheckHandler pHandler)
{
	m_pCheckListener = pListener;
	m_pCheckHandler = pHandler;
}

void CCheckableProtocol::setExclusion(int nExclusion)
{
	m_nExclusion = nExclusion;
}

int CCheckableProtocol::getExclusion() const
{
	return m_nExclusion;
}

void CCheckableProtocol::executeCheckHandler(CCObject* pSender, bool bChecked)
{
	if( m_pCheckListener && m_pCheckHandler  )
	{
		(m_pCheckListener->*m_pCheckHandler)(pSender, bChecked);
	}
}

void CCheckableProtocol::setUnCheckedForOtherWidgetsByExclusion(CCNode* pParent)
{
	if( pParent && m_nExclusion != CC_WIDGET_NONE_EXCLUSION )
	{
		CCArray* pChildren = pParent->getChildren();
		CCObject* pChildObject = NULL;
		CCARRAY_FOREACH(pChildren, pChildObject)
		{
			CCheckableProtocol* pCheckableWidget = dynamic_cast<CCheckableProtocol*>(pChildObject);
			if( pCheckableWidget && pCheckableWidget != this )
			{
				if( pCheckableWidget->getExclusion() == m_nExclusion )
				{
					pCheckableWidget->setChecked(false);
				}
			}
		}
	}
}



CControlableProtocol::CControlableProtocol()
: m_pControlListener(NULL)
, m_pControlHandler(NULL)
{
	
}

void CControlableProtocol::setOnControlListener(CCObject* pListener, SEL_ControlHandler pHandler)
{
	m_pControlListener = pListener;
	m_pControlHandler = pHandler;
}

void CControlableProtocol::executeControlHandler(CCObject* pSender, float cx, float cy)
{
	if( m_pControlListener && m_pControlHandler )
	{
		(m_pControlListener->*m_pControlHandler)(pSender, cx, cy);
	}
}

NS_CC_WIDGET_END