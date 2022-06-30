/*
 * Copyright 2015 - 2022, GIBIS-Unifesp and the WiRedPanda contributors
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "graphicelement.h"

class GraphicElementInput : public GraphicElement
{
    Q_OBJECT

public:
    explicit GraphicElementInput(ElementType type, ElementGroup group, const int minInputSize, const int maxInputSize, const int minOutputSize, const int maxOutputSize, QGraphicsItem *parent = nullptr)
        : GraphicElement(type, group, minInputSize, maxInputSize, minOutputSize, maxOutputSize, parent){};

    bool isLocked() const { return m_locked; }
    virtual bool isOn(const int port = 0) const = 0;
    virtual int outputSize() const { return 1; }
    virtual int outputValue() const { return isOn(); }
    virtual void setOff() = 0;
    virtual void setOn() = 0;
    virtual void setOn(const bool value, const int port = 0) = 0;
    void setLocked(const bool locked) { m_locked = locked; }
    void updatePortsOutputs();

protected:
    bool m_locked = false;
};

inline void GraphicElementInput::updatePortsOutputs()
{
    for (int port = 0; port < outputSize(); ++port) {
        logic()->setOutputValue(port, isOn(port));
    }
}
