// Copyright 2015 - 2024, GIBIS-UNIFESP and the wiRedPanda contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "logicelement.h"

// Muda nome
class LogicSRLatch : public LogicElement
{
public:
    // Muda nome
    explicit LogicSRLatch();

    void updateLogic() override;

private:
    // Muda nome
    Q_DISABLE_COPY(LogicSRLatch)
};
