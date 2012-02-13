/*
 * This file is part of telepathy-accounts-kcm
 *
 * Copyright (C) 2011 Florian Reinhard <florian.reinhard@googlemail.com>
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

#include "simple-profile-select-widget.h"

#include "profile-item.h"
#include "profile-list-model.h"
#include "dictionary.h"

#include "ui_simple-profile-select-widget.h"

#include <KDebug>

#include <TelepathyQt/PendingReady>
#include <TelepathyQt/ProfileManager>
#include <TelepathyQt/Feature>

#include <QtCore/QSignalMapper>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QCommandLinkButton>

class SimpleProfileSelectWidget::Private
{
public:
    Private()
     : profileListModel(0),
       ui(0),
       signalMapper(0)
    {
    }

    ProfileListModel *profileListModel;
    Ui::SimpleProfileSelectWidget *ui;
    QSignalMapper *signalMapper;
    QString profileName;
};

SimpleProfileSelectWidget::SimpleProfileSelectWidget(ProfileListModel *profileListModel, QWidget *parent)
 : QWidget(parent),
   d(new Private)
{
    // Set up the models
    d->profileListModel = profileListModel;
    d->signalMapper = new QSignalMapper(this);

    // Set up the widget
    d->ui = new Ui::SimpleProfileSelectWidget;
    d->ui->setupUi(this);

    // Create the buttons for the Major Profiles
    QCommandLinkButton *buttonJabber = new QCommandLinkButton(Dictionary::instance()->string(QLatin1String("jabber")), QString());
    buttonJabber->setIcon(KIcon(QLatin1String("im-jabber")));
    buttonJabber->setIconSize(QSize(32,32));
    buttonJabber->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));

    QCommandLinkButton *buttonGTalk = new QCommandLinkButton(Dictionary::instance()->string(QLatin1String("google-talk")));
    buttonGTalk->setIcon(KIcon(QLatin1String("im-google-talk")));
    buttonGTalk->setIconSize(QSize(32,32));
    buttonGTalk->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));


    QCommandLinkButton *buttonFacebook = new QCommandLinkButton(Dictionary::instance()->string(QLatin1String("facebook")));
    buttonFacebook->setIcon(KIcon(QLatin1String("im-facebook")));
    buttonFacebook->setIconSize(QSize(32,32));
    buttonFacebook->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    QCommandLinkButton *buttonIcq = new QCommandLinkButton(Dictionary::instance()->string(QLatin1String("icq")));
    buttonIcq->setIcon(KIcon(QLatin1String("im-icq")));
    buttonIcq->setIconSize(QSize(32,32));
    buttonIcq->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));

    QCommandLinkButton *buttonMsn = new QCommandLinkButton(Dictionary::instance()->string(QLatin1String("msn")));
    buttonMsn->setIcon(KIcon(QLatin1String("im-msn")));
    buttonMsn->setIconSize(QSize(32,32));
    buttonMsn->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
   
    QCommandLinkButton *buttonOthers = new QCommandLinkButton(i18n("Others"), i18n("AOL, Gadu-Gadu, IRC, Yahoo and more..."));
    buttonOthers->setIcon(KIcon(QLatin1String("go-next")));
    buttonOthers->setIconSize(QSize(32,32));
    buttonOthers->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    
    // Add them to the SignalMapper
    d->signalMapper->setMapping(buttonJabber,   QLatin1String("jabber"));
    d->signalMapper->setMapping(buttonGTalk,    QLatin1String("google-talk"));
    d->signalMapper->setMapping(buttonFacebook, QLatin1String("facebook"));
    d->signalMapper->setMapping(buttonIcq,      QLatin1String("haze-icq"));
    d->signalMapper->setMapping(buttonMsn,      QLatin1String("msn"));

    // Connect them to the SignalMapper
    connect(buttonJabber,   SIGNAL(clicked()), d->signalMapper, SLOT(map()));
    connect(buttonGTalk,    SIGNAL(clicked()), d->signalMapper, SLOT(map()));
    connect(buttonFacebook, SIGNAL(clicked()), d->signalMapper, SLOT(map()));
    connect(buttonIcq,      SIGNAL(clicked()), d->signalMapper, SLOT(map()));
    connect(buttonMsn,      SIGNAL(clicked()), d->signalMapper, SLOT(map()));
    connect(buttonOthers,   SIGNAL(clicked()), this,            SIGNAL(othersChosen()));

    connect(d->signalMapper,SIGNAL(mapped(const QString &)),
            this,           SLOT(onProfileClicked(const QString &)));

    // Add them to the Layout
    d->ui->verticalLayout->addWidget(buttonJabber);
    d->ui->verticalLayout->addWidget(buttonGTalk);
    d->ui->verticalLayout->addWidget(buttonFacebook);
    d->ui->verticalLayout->addWidget(buttonIcq);
    d->ui->verticalLayout->addWidget(buttonMsn);
    d->ui->verticalLayout->addWidget(buttonOthers);
    d->ui->verticalLayout->addStretch();

    // Disable everything until Tp::ProfileManager is ready
    d->ui->verticalLayout->setEnabled(false);
}

SimpleProfileSelectWidget::~SimpleProfileSelectWidget()
{
    delete d->ui;
    delete d;
}

// Return the selected ProfileItem or 0 if nothing is selected.
ProfileItem *SimpleProfileSelectWidget::selectedProfile()
{
   return d->profileListModel->itemForService(d->profileName);
}

// FIXME: before we proceed here, we should check if there's everything installed we need.
void SimpleProfileSelectWidget::onProfileClicked(QString profileName)
{
    d->profileName = profileName;

    kDebug() << "Selected profile: " << d->profileName;

    Q_EMIT profileChosen();
}

#include "simple-profile-select-widget.moc"

