// Copyright 2015 - 2024, GIBIS-UNIFESP and the wiRedPanda contributors
// SPDX-License-Identifier: GPL-3.0-or-later

// Mudei o arquivo .h de dlatch para srlatch
#include "srlatch.h"

#include "globalproperties.h"
#include "qneport.h"

namespace
{
// Mudei o RegisterMetaType de DLatch para SRLatch
int id = qRegisterMetaType<SRLatch>();
}

// Mudei duas vezes de LLatch para RSLatch
SRLatch::SRLatch(QGraphicsItem *parent)
    // Outras mudanças
    : GraphicElement(ElementType::SRLatch, ElementGroup::Memory, pixmapPath(), tr("SR-LATCH"), tr("SR-Latch"), 2, 2, 2, 2, parent)
{
    if (GlobalProperties::skipInit) {
        return;
    }

    m_defaultSkins << m_pixmapPath;
    m_alternativeSkins = m_defaultSkins;
    setPixmap(0);

    setCanChangeSkin(true);

    // Outra mudança
    SRLatch::updatePortsProperties();
}

// Outra mudança
void SRLatch::updatePortsProperties()
{
    // Não alterei a posição das portas de entrada e saida

    // Muda o nome de Data para Set
    inputPort(0)->setPos(0, 16);      inputPort(0)->setName("Set");
    // Muda de Enable para Reset
    inputPort(1)->setPos(0, 48);      inputPort(1)->setName("Reset");

    // Mantém os nomes Q e ~Q
    outputPort(0)->setPos(64, 16);    outputPort(0)->setName("Q");
    outputPort(1)->setPos(64, 48);    outputPort(1)->setName("~Q");

    // Mantém as configurações de por padrão deixar Q como 0 e ~Q como 1
    outputPort(0)->setDefaultStatus(Status::Inactive);
    outputPort(1)->setDefaultStatus(Status::Active);
}

// Outra mudança
void SRLatch::updateTheme()
{
    setPixmap(pixmapPath());
    GraphicElement::updateTheme();
}
