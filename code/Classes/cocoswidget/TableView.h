/****************************************************************************
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
#ifndef __CCWIDGET_TABLEVIEW_H__
#define __CCWIDGET_TABLEVIEW_H__

/////////////////////////////////////////////////////////////////////////////
/// BugFix : [1]
/// Update : [1] changed text "SEL_TableViewDataSourceHandler" to "SEL_TableViewDataSourceHandler"
/// Update : [2] changed text "tabledatasource_selector" to "tableviewdatasource_selector"
/////////////////////////////////////////////////////////////////////////////

#include "cocos2d.h"
#include "WidgetMacros.h"
#include "Widget.h"
#include "ScrollView.h"
#include "WidgetProtocol.h"
#include <list>
#include <vector>
#include <set>

NS_CC_WIDGET_BEGIN

class CTableView;
class CTableViewCell;


/**
 * ���� : CTableViewCell
 * ���� : Xi'an-Lijunlin csdn_viva@foxmail.com
 * ���� : csdn_viva@foxmail.com
 * ���� : �б���ؼ����ַ��¼�
 */
class CTableViewCell : public CPanel
{
public:
    CTableViewCell();
    virtual ~CTableViewCell();

	/**
	 * ���� : getIdx()
	 * ���� : ��ȡ�б�����±�
	 * ���� : 
	 * ��� : �±�
	 */
    unsigned int getIdx() { return m_uIdx; }

	/**
	 * ���� : setIdx()
	 * ���� : �����б�����±�
	 * ���� : uIdx - �±�
	 * ��� : 
	 */
    void setIdx(unsigned int uIdx) { m_uIdx = uIdx; }

	/**
	 * ���� : reset()
	 * ���� : ���б���������״̬��ʱ�����״̬
	 * ���� : 
	 * ��� : 
	 */
    virtual void reset(){ m_uIdx = CC_INVALID_INDEX; }
    
protected:
	/// �б��±�
    unsigned int m_uIdx;
};

/**
 * ���� : CTableView
 * ���� : Xi'an-Lijunlin csdn_viva@foxmail.com
 * ���� : csdn_viva@foxmail.com
 * ���� : �б�ؼ�
 */
class CTableView : public CScrollView, public CDataSourceAdapterProtocol
{
public:
    CTableView();
    virtual ~CTableView();

	/**
	 * ���� : setCountOfCell()
	 * ���� : �����б�������� ��ҪreloadData��Ч
	 * ���� : uCellsCount - ����
	 * ��� : 
	 */
    void setCountOfCell(unsigned int uCellsCount);

	/**
	 * ���� : getCountOfCell()
	 * ���� : ��ȡ�б�������� ��ҪreloadData��Ч
	 * ���� : 
	 * ��� : ����
	 */
    unsigned int getCountOfCell() const;

	/**
	 * ���� : setSizeOfCell()
	 * ���� : �����б���Ĵ�С ��ҪreloadData��Ч
	 * ���� : tCellsSize - �б���Ĵ�С
	 * ��� : 
	 */
    void setSizeOfCell(const CCSize& tCellsSize);

	/**
	 * ���� : getSizeOfCell()
	 * ���� : ��ȡ�б���Ĵ�С ��ҪreloadData��Ч
	 * ���� : 
	 * ��� : �б���Ĵ�С
	 */
    const CCSize& getSizeOfCell() const;

	/**
	 * ���� : isAutoRelocate()
	 * ���� : ��ȡ�Ƿ��Զ����뵽Cell;
	 * ���� : 
	 * ��� : �Ƿ��Զ�����
	 */
	bool isAutoRelocate() const;

	/**
	 * ���� : setAutoRelocate()
	 * ���� : �����Ƿ��Զ����뵽Cell;
	 * ���� : bAuto - �Ƿ��Զ�����
	 * ��� : 
	 */
	void setAutoRelocate(bool bAuto);

	/**
	 * ���� : getAutoRelocateSpeed()
	 * ���� : ��ȡ�Զ�����cellʱ���ٶ�
	 * ���� : 
	 * ��� : �Զ�������ٶ�
	 */
	float getAutoRelocateSpeed() const;

	/**
	 * ���� : setAutoRelocateSpeed()
	 * ���� : �����Զ�����cellʱ���ٶ�
	 * ���� : fSpeed - �Զ�������ٶ�
	 * ��� : 
	 */
	void setAutoRelocateSpeed(float fSpeed);

	/**
	 * ���� : initWithParams()
	 * ���� : ͨ��������ʼ��
	 * ���� : tViewSize - ���ӷ�Χ��С
	 *        tCellSize - ÿһ��Ĵ�С
	 *        uCellCount - �ܹ��ж�����
	 *        pTarget - ���ݺ����������
	 *        pDataSourceHandler - ���ݺ���
	 * ��� : �Ƿ��ʼ���ɹ�
	 */
	bool initWithParams(const CCSize& tViewSize, const CCSize& tCellSize, unsigned int uCellCount, 
		CCObject* pListener, SEL_DataSoucreAdapterHandler pHandler);
		
    static CTableView* create(const CCSize& tViewSize);
	static CTableView* create(const CCSize& tViewSize, const CCSize& tCellSize, unsigned int uCellCount, 
		CCObject* pListener, SEL_DataSoucreAdapterHandler pHandler);

public:
	/**
	 * ���� : getCells()
	 * ���� : ��ȡ�����б���
	 * ���� : 
	 * ��� : �����б���
	 */
	CCArray* getCells();

	/**
	 * ���� : cellAtIndex()
	 * ���� : ��ȡ�б��� ͨ���±꣬������cellû�б�ʹ�ã��򷵻�NULL
	 * ���� : idx - �±�
	 * ��� : �б���
	 */
	CTableViewCell* cellAtIndex(unsigned int idx);

	/**
	 * ���� : dequeueCell()
	 * ���� : �����ؼ��б������ͷ�����б���
	 * ���� : 
	 * ��� : �б���
	 */
    CTableViewCell* dequeueCell();

	/**
	 * ���� : reloadData()
	 * ���� : ���¼�������
	 * ���� : 
	 * ��� : 
	 */
	void reloadData();
    
protected:

	/**
	 * ���� : onScrolling()
	 * ���� : �������ؼ�����ʱ����
	 * ���� : 
	 * ��� : 
	 */
    virtual void onScrolling();

	/**
	 * ���� : onDeaccelerateScrollEnded()
	 * ���� : �������ؼ����ٹ������ʱ����
	 * ���� : 
	 * ��� : 
	 */
	virtual void onDeaccelerateScrollEnded();

	/**
	 * ���� : onDeaccelerateScrollEnded()
	 * ���� : �������ؼ���ק�������ʱ����
	 * ���� : 
	 * ��� : 
	 */
	virtual void onDraggingScrollEnded();

protected:
	void removeAllFromUsed();
    void removeAllFromFreed();
	void insertSortableCell(CTableViewCell* pCell, unsigned int idx);
	unsigned int cellBeginIndexFromOffset(const CCPoint& offset);
	unsigned int cellEndIndexFromOffset(const CCPoint& offset);
	CCPoint cellPositionFromIndex(unsigned int idx);
	virtual void updateCellAtIndex(unsigned int idx);
	void updatePositions();

protected:
    CCSize m_tCellsSize;
    unsigned int m_uCellsCount;
	bool m_bAutoRelocate;
	float m_fAutoRelocateSpeed;
    
	std::set<unsigned int>* m_pIndices;
	std::vector<float>* m_pPositions;
	std::list<CTableViewCell*>* m_pCellsUsed;
	std::list<CTableViewCell*>* m_pCellsFreed;
};

NS_CC_WIDGET_END

#endif //__CCWIDGET_TABLEVIEW_H__
