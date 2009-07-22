/*
 * This file is part of telepathy-accounts-kcm
 *
 * Copyright (C) 2009 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "add-account-wizard.h"

#include "protocol-select-widget.h"

#include <KDebug>
#include <KLocale>
#include <KPageWidgetItem>

class AddAccountWizard::Private
{
public:
    Private()
     : pageOne(0)
    {
        kDebug();
    }

    ProtocolSelectWidget *widgetOne;
    KPageWidgetItem *pageOne;
};

AddAccountWizard::AddAccountWizard(QWidget *parent)
 : KAssistantDialog(parent),
   d(new Private)
{
    kDebug();

    // Set up the pages of the Wizard.
    d->widgetOne = new ProtocolSelectWidget(this);
    d->pageOne = new KPageWidgetItem(d->widgetOne);
    d->pageOne->setHeader(i18n("Step 1: Select an Instant Messaging Network."));

    addPage(d->pageOne);
}

AddAccountWizard::~AddAccountWizard()
{
    kDebug();

    delete d;
}

void AddAccountWizard::back()
{
    kDebug();

    // TODO: Implement me!
}

void AddAccountWizard::next()
{
    kDebug();

    // TODO: Implement me!
}

void AddAccountWizard::accept()
{
    kDebug();

    // TODO: Implement me!
}

void AddAccountWizard::reject()
{
    kDebug();

    // TODO: Implement me!
}

