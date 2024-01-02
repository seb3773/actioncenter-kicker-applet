// actioncenter_applet.cpp

#include <tdeglobal.h>
#include <tdelocale.h>
#include <tdeapplication.h>
#include <tqpixmap.h> 
#include "actioncenter_applet.h"
#include <krun.h>
#include <tqdialog.h>
#include <tqlayout.h>
#include <tqlabel.h>
#include <tqsplitter.h>
#include <kprocess.h>

actioncenter_applet::actioncenter_applet(const TQString& configFile, Type type, int actions, TQWidget *parent, const char *name)
    : KPanelApplet(configFile, type, actions, parent, name),
      button1State(false),
      button2State(false),
      button3State(false),
      button4State(false),
      buttonWidget(nullptr),
      buttonLayout(nullptr)
{
    TQPixmap icon("/opt/trinity/share/apps/kicker/pics/actioncenter.png");
    TQPushButton *iconButton = new TQPushButton("", this);
    iconButton->setIcon(icon);
    iconButton->setIconSet(icon);
    iconButton->setFixedSize(icon.size());
    setFixedSize(icon.size().width() + 10, icon.size().height());

    connect(iconButton, SIGNAL(clicked()), this, SLOT(iconClicked()));
    mainView = iconButton;
    mainView->show();
}

actioncenter_applet::~actioncenter_applet()
{
}

void actioncenter_applet::iconClicked()
{
    if (customDialog && customDialog->isVisible()) {
        customDialog->close();
        return; 
    }

    customDialog = new TQDialog(this);
    customDialog->setFixedSize(400, getScreenHeight());

    TQVBoxLayout *mainLayout = new TQVBoxLayout(customDialog);

    TQLabel *textLabel = new TQLabel("Votre systeme est a jour.", customDialog);
    textLabel->setAlignment(TQt::AlignHCenter | TQt::AlignVCenter);

    int textHeight = (customDialog->height() * 2) / 3;
    textLabel->setFixedHeight(textHeight);

    mainLayout->addWidget(textLabel);

    TQSplitter *splitter = new TQSplitter(customDialog);
    mainLayout->addWidget(splitter);

    buttonWidget = new TQWidget(splitter);
    buttonLayout = new TQHBoxLayout(buttonWidget);

//button1State = (KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action1.sh check") == "1");
//button2State = (KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action2.sh check") == "1");

    addImageButton("/opt/trinity/share/apps/actioncenter_applet/action1.png", "/opt/trinity/share/apps/actioncenter_applet/action1_on.png", SLOT(button1Clicked()), button1State);
    addImageButton("/opt/trinity/share/apps/actioncenter_applet/action2.png", "/opt/trinity/share/apps/actioncenter_applet/action2_on.png", SLOT(button2Clicked()), button2State);

    addButton("/opt/trinity/share/apps/actioncenter_applet/action3.png", SLOT(button3Clicked()));
    addButton("/opt/trinity/share/apps/actioncenter_applet/action4.png", SLOT(button4Clicked()));

    splitter->addWidget(buttonWidget);

    int screenWidth = TDEApplication::desktop()->width();
    int dialogWidth = customDialog->width();
    int xPosition = screenWidth - dialogWidth;
    int screenHeight = TDEApplication::desktop()->height();
    int dialogHeight = customDialog->height();
    int yPosition = screenHeight - dialogHeight;
    customDialog->move(xPosition, yPosition);
    customDialog->setCaption("Action center");
    customDialog->show();
}

void actioncenter_applet::addImageButton(const char *imagePathOn, const char *imagePathOff, const char *slot, bool& buttonState)
{
    const char *imagePath = buttonState ? imagePathOff : imagePathOn;
    TQPixmap buttonIcon(imagePath);
    TQPushButton *button = new TQPushButton("", buttonWidget);
    button->setPixmap(buttonIcon);
    button->setFixedSize(buttonIcon.size());
    connect(button, SIGNAL(clicked()), this, slot);
    buttonLayout->addWidget(button);
}

void actioncenter_applet::addButton(const char *imagePath, const char *slot)
{
    TQPixmap buttonIcon(imagePath);
    TQPushButton *button = new TQPushButton("", buttonWidget);
    button->setPixmap(buttonIcon);
    button->setFixedSize(buttonIcon.size());
    connect(button, SIGNAL(clicked()), this, slot);
    buttonLayout->addWidget(button);
}

void actioncenter_applet::button1Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action1.sh");
    button1State = !button1State;
    addImageButton("/opt/trinity/share/apps/actioncenter_applet/action1.png", "/opt/trinity/share/apps/actioncenter_applet/action1_on.png", SLOT(button1Clicked()), button1State);
}

void actioncenter_applet::button2Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action2.sh");
    button2State = !button2State;
    addImageButton("/opt/trinity/share/apps/actioncenter_applet/action2.png", "/opt/trinity/share/apps/actioncenter_applet/action2_on.png", SLOT(button2Clicked()), button2State);
}

void actioncenter_applet::button3Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action3.sh");
}

void actioncenter_applet::button4Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/action4.sh");
}

int actioncenter_applet::widthForHeight(int height) const
{
    return width();
}

int actioncenter_applet::heightForWidth(int width) const
{
    return getScreenHeight();
}

void actioncenter_applet::resizeEvent(TQResizeEvent *e)
{
}

int actioncenter_applet::getScreenHeight() const
{
    return TDEApplication::desktop()->height();
}

extern "C"
{
    KPanelApplet* init(TQWidget *parent, const TQString& configFile)
    {
        TDEGlobal::locale()->insertCatalogue("actioncenter_applet");
        return new actioncenter_applet(configFile, KPanelApplet::Normal, 0, parent, "actioncenter_applet");
    }
}
