/*
 * Copyright (C) 2011 Adobe Systems Incorporated. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER “AS IS” AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef RenderRegion_h
#define RenderRegion_h

#include "core/rendering/RenderBlockFlow.h"

namespace blink {

class RenderFlowThread;

class RenderRegion : public RenderBlockFlow {
public:
    explicit RenderRegion(Element*, RenderFlowThread*);

    virtual bool isOfType(RenderObjectType type) const override { return type == RenderObjectRenderRegion || RenderBlockFlow::isOfType(type); }

    void setFlowThreadPortionRect(const LayoutRect& rect) { m_flowThreadPortionRect = rect; }
    LayoutRect flowThreadPortionRect() const { return m_flowThreadPortionRect; }
    LayoutRect flowThreadPortionOverflowRect() const;

    RenderFlowThread* flowThread() const { return m_flowThread; }

    // Valid regions do not create circular dependencies with other flows.
    bool isValid() const { return m_isValid; }
    void setIsValid(bool valid) { m_isValid = valid; }

    bool isFirstRegion() const;
    bool isLastRegion() const;

    // These methods represent the width and height of a "page" and for a RenderRegion they are just
    // the content width and content height of a region. For RenderMultiColumnSets, however, they
    // will be the width and height of a single column or page in the set.
    virtual LayoutUnit pageLogicalWidth() const;
    virtual LayoutUnit pageLogicalHeight() const;

    virtual bool canHaveChildren() const override final { return false; }
    virtual bool canHaveGeneratedChildren() const override final { return true; }

    virtual const char* renderName() const override { return "RenderRegion"; }

protected:
    virtual void computeIntrinsicLogicalWidths(LayoutUnit& minLogicalWidth, LayoutUnit& maxLogicalWidth) const override final;

    LayoutRect overflowRectForFlowThreadPortion(const LayoutRect& flowThreadPortionRect, bool isFirstPortion, bool isLastPortion) const;

private:
    virtual void layoutBlock(bool relayoutChildren) override final;

protected:
    RenderFlowThread* m_flowThread;

private:
    LayoutRect m_flowThreadPortionRect;
    bool m_isValid : 1;
};

DEFINE_RENDER_OBJECT_TYPE_CASTS(RenderRegion, isRenderRegion());

} // namespace blink

#endif // RenderRegion_h
