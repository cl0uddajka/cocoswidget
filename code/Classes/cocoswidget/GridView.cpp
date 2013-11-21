﻿/****************************************************************************
Copyright (c) 2013 viva

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
#include "GridView.h"
using namespace std;

NS_CC_WIDGET_BEGIN

#define CGRIDVIEW_AUTO_RELOCATE_SPPED 350.0f

CGridViewCell::CGridViewCell()
: m_uRow(CC_INVALID_INDEX)
, m_uIdx(CC_INVALID_INDEX)
{
	
}

CGridViewCell::~CGridViewCell()
{
	
}

CGridView::CGridView()
: m_tCellsSize(CCSizeZero)
, m_uCellsCount(0)
, m_uColumns(0)
, m_uRows(0)
, m_pDataSourceListener(NULL)
, m_pDataSourceHandler(NULL)
, m_bAutoRelocate(false)
{
	setTouchEnabled(false);
	m_eDirection = eScrollViewDirectionVertical;
}

CGridView::~CGridView()
{
	
}

void CGridView::setCountOfCell(unsigned int uCellsCount)
{
	m_uCellsCount = uCellsCount;
}

unsigned int CGridView::getCountOfCell() const
{
	return m_uCellsCount;
}

void CGridView::setSizeOfCell(const CCSize& tCellsSize)
{
	m_tCellsSize = tCellsSize;
}

const CCSize& CGridView::getSizeOfCell() const
{
	return m_tCellsSize;
}

void CGridView::setColumns(unsigned int uColumns)
{
	m_uColumns = uColumns;
}

unsigned int CGridView::getColumns() const
{
	return m_uColumns;
}

unsigned int CGridView::getRows() const
{
	return m_uRows;
}

bool CGridView::isAutoRelocate() const
{
	return m_bAutoRelocate;
}

void CGridView::setAutoRelocate(bool bAuto)
{
	m_bAutoRelocate = bAuto;
}

void CGridView::setDataSourceSelector(CCObject* pTarget, SEL_GridViewDataSourceHandler pDataSourceHandler)
{
	if( pTarget && pDataSourceHandler )
	{
		m_pDataSourceListener = pTarget;
		m_pDataSourceHandler = pDataSourceHandler;
	}
}

CGridViewCell* CGridView::executeDataSource(CGridView* pGrid, unsigned int idx)
{
	if( m_pDataSourceListener && m_pDataSourceHandler )
	{
		return (m_pDataSourceListener->*m_pDataSourceHandler)(pGrid, idx);
	}
	return NULL;
}

CGridView* CGridView::create(const CCSize& tViewSize)
{
	CGridView * pRet = new CGridView();
	if( pRet && pRet->initWithSize(tViewSize) )
    {
		pRet->autorelease();
		return pRet;
    }
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CGridView* CGridView::create(const CCSize& tViewSize, const CCSize& tCellSize, unsigned int uCellCount,
		CCObject* pTarget, SEL_GridViewDataSourceHandler pDataSourceHandler)
{
	CGridView * pRet = new CGridView();
	if( pRet && pRet->initWithParams(tViewSize, tCellSize, uCellCount, pTarget, pDataSourceHandler))
    {
		pRet->autorelease();
		return pRet;
    }
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CGridView::initWithParams(const CCSize& tViewSize, const CCSize& tCellSize, unsigned int uCellCount,
		CCObject* pTarget, SEL_GridViewDataSourceHandler pDataSourceHandler)
{
	if( initWithSize(tViewSize) )
	{
		setSizeOfCell(tCellSize);
		setCountOfCell(uCellCount);
		setDataSourceSelector(pTarget, pDataSourceHandler);
		return true;
	}
	return false;
}

void CGridView::removeAllFromUsed()
{
	if( !m_lCellsUsed.empty() )
	{
		list<CGridViewCell*>::iterator iter = m_lCellsUsed.begin();
		for(; iter != m_lCellsUsed.end(); ++iter)
		{
			m_pContainer->removeChild((*iter));
			(*iter)->release();
		}
		m_lCellsUsed.clear();
	}
}

void CGridView::removeAllFromFreed()
{
	if( !m_lCellsFreed.empty() )
	{
		list<CGridViewCell*>::iterator iter = m_lCellsFreed.begin();
		for(; iter != m_lCellsFreed.end(); ++iter)
		{
			(*iter)->release();
		}
		m_lCellsFreed.clear();
	}
}

void CGridView::insertSortableCell(CGridViewCell* pCell, unsigned int idx)
{
	if( m_lCellsUsed.empty() )
	{
		m_lCellsUsed.push_back(pCell);
	}
	else
	{
		list<CGridViewCell*>::iterator iter = m_lCellsUsed.begin();
		for(; iter != m_lCellsUsed.end(); ++iter)
		{
			if( (*iter)->getIdx() > idx )
			{
				m_lCellsUsed.insert(iter, pCell);
				return;
			}
		}
		m_lCellsUsed.push_back(pCell);
		return;
	}
}

const CCPoint& CGridView::cellPositionFromIndex(unsigned int idx)
{
	if( idx == CC_INVALID_INDEX )
    {
        return m_vPositions[0];
    }

	return m_vPositions[idx];
}

void CGridView::updateCellAtIndex(unsigned int idx, unsigned int row)
{
	CGridViewCell* pCell = executeDataSource(this, idx);
#if 0
    CCAssert(pCell != NULL, "cell can not be null");
#endif

	pCell->setIdx(idx);
	pCell->setRow(row);
	pCell->setAnchorPoint(CCPoint(0, 1));
	pCell->setContentSize(m_tCellsSize);
	pCell->setPosition(cellPositionFromIndex(idx));

    m_pContainer->addChild(pCell);
	insertSortableCell(pCell, idx);
    pCell->retain();

	m_sIndices.insert(idx);
}

unsigned int CGridView::cellBeginRowFromOffset(const CCPoint& offset)
{
	int ofy = offset.y + m_pContainer->getContentSize().height;
	int xos = ofy - m_obContentSize.height;
	int row = xos / m_tCellsSize.height;

	row = MAX(row, 0);
	row = MIN((int)m_uRows - 1, row);

	return (unsigned int)row;
}

unsigned int CGridView::cellEndRowFromOffset(const CCPoint& offset)
{
	int ofy = offset.y + m_pContainer->getContentSize().height;
	int row = ofy / m_tCellsSize.height;

	row = MAX(row, 0);
	row = MIN((int)m_uRows - 1, row);

	return (unsigned int)row;
}

unsigned int CGridView::cellFirstIndexFromRow(unsigned int row)
{
	return m_uColumns * row;
}

void CGridView::updatePositions()
{
	m_uRows = m_uCellsCount % m_uColumns == 0 ? m_uCellsCount / m_uColumns : m_uCellsCount / m_uColumns + 1;
	float fHeight = MAX(m_uRows * m_tCellsSize.height, m_obContentSize.height);
	float fWidth = m_uColumns * m_tCellsSize.width;
	setContainerSize(CCSizeMake(fWidth, fHeight));

	float nX = 0.0f;
	float nY = fHeight;

	for(unsigned int idx = 0; idx < m_uCellsCount; ++idx)
	{
		if( idx != 0 && idx % m_uColumns == 0 )
		{
			nX = 0.0f;
			nY = nY - m_tCellsSize.height;
		}
		m_vPositions.push_back(CCPoint(nX, nY));
		nX += m_tCellsSize.width;
	}
}

CCArray* CGridView::getCells()
{
	CCArray* pArray = new CCArray();
	pArray->initWithCapacity(10);

	if( !m_lCellsUsed.empty() )
	{
		list<CGridViewCell*>::iterator iter = m_lCellsUsed.begin();
		for(; iter != m_lCellsUsed.end(); ++iter)
		{
			pArray->addObject(*iter);
		}
	}

	if( !m_lCellsFreed.empty() )
	{
		list<CGridViewCell*>::iterator iter = m_lCellsFreed.begin();
		for(; iter != m_lCellsFreed.end(); ++iter)
		{
			pArray->addObject(*iter);
		}
	}

	pArray->autorelease();
	return pArray;
}

CGridViewCell* CGridView::cellAtIndex(unsigned int idx)
{
	if( m_sIndices.find(idx) == m_sIndices.end() )
	{
		return NULL;
	}

    list<CGridViewCell*>::iterator iter = m_lCellsUsed.begin();
    for(; iter != m_lCellsUsed.end() ; ++iter)
    {
        if( (*iter)->getIdx() == idx )
        {
            return (*iter);
        }
    }
    return NULL;
}

CGridViewCell* CGridView::dequeueCell()
{
	CGridViewCell* pCell = NULL;
    if( m_lCellsFreed.empty() )
    {
        return NULL;
    }
    else
    {
        pCell = m_lCellsFreed.front();
        m_lCellsFreed.pop_front();
        pCell->autorelease();
    }
    return pCell;
}

void CGridView::reloadData()
{
	if( !m_pDataSourceListener || !m_pDataSourceHandler )
	{
		return;
	}

	if( m_eDirection != eScrollViewDirectionVertical )
	{
		return;
	}

	if( m_uColumns == 0 )
	{
		return;
	}

	if( m_uCellsCount == 0 )
	{
		return;
	}

	if( m_tCellsSize.width == 0 || m_tCellsSize.height == 0 )
    {
        return;
    }

	list<CGridViewCell*>::iterator iter = m_lCellsUsed.begin();
	while(iter != m_lCellsUsed.end())
	{
		CGridViewCell* pCell = (*iter);
		m_lCellsFreed.push_back(pCell);
		iter = m_lCellsUsed.erase(iter);
		m_pContainer->removeChild(pCell, true);
	}

	setTouchEnabled(true);
	m_sIndices.clear();
    m_vPositions.clear();
	this->updatePositions();
	this->setContentOffsetToTop();
    this->onScrolling();
}

void CGridView::onScrolling()
{
	unsigned uBeginRow = 0, uEndRow = 0;

	uBeginRow = cellBeginRowFromOffset( getContentOffset() );
	uEndRow = cellEndRowFromOffset( getContentOffset() );
	
#if 0
	CCLOG("row begin %u  end %u", uBeginRow, uEndRow);
#endif

	while( !m_lCellsUsed.empty() )
    {
        CGridViewCell* pCell = m_lCellsUsed.front();
		unsigned int uRow = pCell->getRow();
		unsigned int uIdx = pCell->getIdx();

        if( uRow < uBeginRow )
        {
			m_sIndices.erase(uIdx);
			m_lCellsUsed.pop_front();
            m_lCellsFreed.push_back(pCell);
            pCell->reset();
            m_pContainer->removeChild(pCell, true);
        }
        else
        {
            break;
        }
    }

	while( !m_lCellsUsed.empty() )
    {
        CGridViewCell* pCell = m_lCellsUsed.back();
		unsigned int uRow = pCell->getRow();
		unsigned int uIdx = pCell->getIdx();

        if( uRow > uEndRow && uRow < m_uRows )
        {
			m_sIndices.erase(uIdx);
			m_lCellsUsed.pop_back();
            m_lCellsFreed.push_back(pCell);
            pCell->reset();
            m_pContainer->removeChild(pCell, true);
        }
        else
        {
            break;
        }
    }

	for( unsigned int row = uBeginRow; row <= uEndRow && row < m_uRows; ++row )
    {
		unsigned int nCellBeginIndex = cellFirstIndexFromRow(row);
		unsigned int nCellEndIndx = nCellBeginIndex + m_uColumns;
		unsigned int idx = nCellBeginIndex;

		for(; idx < nCellEndIndx && idx < m_uCellsCount; ++idx)
		{
			if( m_sIndices.find(idx) != m_sIndices.end() )
			{
				continue;
			}
			updateCellAtIndex(idx, row);
		}
    }
}

void CGridView::onDeaccelerateScrollEnded()
{
	onDraggingScrollEnded();
}

void CGridView::onDraggingScrollEnded()
{
	if( m_bAutoRelocate )
	{
		CCPoint tOffset = getContentOffset();
		unsigned int uRow = cellBeginRowFromOffset(tOffset);
		CCPoint tAPoint = cellPositionFromIndex(cellFirstIndexFromRow(uRow));
		CCPoint tBPoint = CCPoint(0, tAPoint.y - m_tCellsSize.height);
		CCPoint tContentPoint = CCPoint(0, m_obContentSize.height);
		tOffset = tOffset - tContentPoint;
		tAPoint.x = 0;

		float fADistance = tOffset.getDistance(-tAPoint);
		float fBDistance = tOffset.getDistance(-tBPoint);

		if( fADistance < fBDistance )
		{
			float fDuration = fabs(fADistance) / CGRIDVIEW_AUTO_RELOCATE_SPPED;
			setContentOffsetInDuration(-tAPoint + tContentPoint, fDuration);
		}
		else
		{
			float fDuration = fabs(fBDistance) / CGRIDVIEW_AUTO_RELOCATE_SPPED;
			setContentOffsetInDuration(-tBPoint + tContentPoint, fDuration);
		}
	}
}

NS_CC_WIDGET_END