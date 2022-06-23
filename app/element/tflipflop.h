/*
 * Copyright 2015 - 2022, GIBIS-Unifesp and the WiRedPanda contributors
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "graphicelement.h"
#include "thememanager.h"

class TFlipFlop : public GraphicElement
{
    Q_OBJECT
    Q_PROPERTY(QString pixmapPath MEMBER m_pixmapPath CONSTANT)
    Q_PROPERTY(QString titleText MEMBER m_titleText CONSTANT)
    Q_PROPERTY(QString translatedName MEMBER m_translatedName CONSTANT)

public:
    explicit TFlipFlop(QGraphicsItem *parent = nullptr);

    static QString pixmapPath()
    {
        return (ThemeManager::theme() == Theme::Light) ? ":/memory/light/T-flipflop.svg"
                                                       : ":/memory/dark/T-flipflop.svg";
    }

    void updatePorts() override;
    void updateTheme() override;

private:
    const QString m_pixmapPath = pixmapPath();
    const QString m_titleText = tr("<b>T-FLIPFLOP</b>");
    const QString m_translatedName = tr("T-FlipFlop");
};

Q_DECLARE_METATYPE(TFlipFlop)
