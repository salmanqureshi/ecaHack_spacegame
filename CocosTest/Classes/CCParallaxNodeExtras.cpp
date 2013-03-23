/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "CCParallaxNodeExtras.h"
#include "CCPointExtension.h"
#include "support/data_support/ccCArray.h"

namespace cocos2d {

	class CCPointObject : CCObject
	{
		CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
		CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
		CC_SYNTHESIZE(CCNode *,m_pChild, Child)	// weak ref

		static CCPointObject * pointWithCCPoint(CCPoint ratio, CCPoint offset)
		{
			CCPointObject *pRet = new CCPointObject();
			pRet->initWithCCPoint(ratio, offset);
			pRet->autorelease();
			return pRet;
		}
		bool initWithCCPoint(CCPoint ratio, CCPoint offset)
		{
			m_tRatio = ratio;
			m_tOffset = offset;
			m_pChild = NULL;
			return true;
		}
	};

	CCParallaxNodeExtras * CCParallaxNodeExtras::node()
	{
		CCParallaxNodeExtras *pRet = new CCParallaxNodeExtras();
		pRet->autorelease();
		return pRet;
	}
	void CCParallaxNodeExtras::incrementOffset(CCPoint offset,CCNode* node)
	{
		for( unsigned int i=0;i < m_pParallaxArray->num;i++) {
			CCPointObject *point = (CCPointObject *)m_pParallaxArray->arr[i];
			if( point->getChild()->isEqual(node) ) {
				point->setOffset( ccpAdd(point->getOffset(), offset) );
				break;
			}
		}
	}

}// namespace cocos2d
