/*
 * Copyright 2015 - 2022, GIBIS-Unifesp and the WiRedPanda contributors
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "graphicelementinput.h"

class InputSwitch : public GraphicElementInput
{
    Q_OBJECT

public:
    explicit InputSwitch(QGraphicsItem *parent = nullptr);

    bool isOn(const int port = 0) const override;
    void load(QDataStream &stream, QMap<quint64, QNEPort *> &portMap, const double version) override;
    void save(QDataStream &stream) const override;
    void setOff() override;
    void setOn() override;
    void setOn(const bool value, const int port = 0) override;
    void setSkin(const bool defaultSkin, const QString &fileName) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool m_isOn = false;
};

Q_DECLARE_METATYPE(InputSwitch)
