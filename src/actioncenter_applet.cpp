// actioncenter_applet.cpp

#include <tqpixmap.h>
#include <tqdialog.h>
#include <tqlayout.h>
#include <tqlabel.h>
#include <tqsplitter.h> 

#include <tdeapplication.h>
#include <tdeglobal.h>
#include <tdelocale.h>
#include <kstandarddirs.h>
#include <krun.h>

#include "action_tile.h"
#include "actioncenter_applet.h"

actioncenter_applet::actioncenter_applet(const TQString& configFile, Type type, int actions, TQWidget *parent, const char *name)
    : KPanelApplet(configFile, type, actions, parent, name),
      button1State(false),
      button2State(false),
      splitter(nullptr),
      internalSplitter1(nullptr),
      internalSplitter2(nullptr)
{
    mainView = new action_tile(this, "actioncenter");
    connect(mainView, SIGNAL(clicked()), this, SLOT(iconClicked()));

    TQSize size = mainView->size();
    setFixedSize(size.width() + 10, size.height());

    mainView->show();
}


void actioncenter_applet::showNewPanel()
{
    newDialog = new TQDialog(this);
    newDialog->setFixedSize(405, getScreenHeight());
    TQVBoxLayout *mainLayout = new TQVBoxLayout(newDialog);
    TQSplitter *projSplitter = new TQSplitter(newDialog);
    projSplitter->setOrientation(TQt::Vertical);
    mainLayout->addWidget(projSplitter, 0, TQt::AlignHCenter | TQt::AlignVCenter);
    TQLabel *textLabel = new TQLabel(" ", newDialog);
    int textHeight = (newDialog->height() * 0.55);
    textLabel->setFixedHeight(textHeight);
    mainLayout->addWidget(textLabel);
    TQSplitter *splitter1 = new TQSplitter(projSplitter);
    TQSplitter *splitter2 = new TQSplitter(projSplitter);
    TQSplitter *splitter3 = new TQSplitter(projSplitter);
    TQSplitter *splitter4 = new TQSplitter(projSplitter);

TQWidget *button1Widget = new TQWidget(splitter1);
button1Widget->setFixedWidth(405); 
TQHBoxLayout *button1Layout = new TQHBoxLayout(button1Widget);
TQLabel *textLabel1 = new TQLabel("Ecran du PC uniquement", button1Widget);
textLabel1->setFixedWidth(195);
button1Layout->addWidget(textLabel1);
addButton("proj1", SLOT(button11Clicked()), button1Widget);
button1Widget->setFixedHeight(80);
splitter1->addWidget(button1Widget);

TQWidget *button2Widget = new TQWidget(splitter2);
button2Widget->setFixedWidth(405); 
TQHBoxLayout *button2Layout = new TQHBoxLayout(button2Widget);
TQLabel *textLabel2 = new TQLabel("Dupliquer", button2Widget);
textLabel2->setFixedWidth(195);
button2Layout->addWidget(textLabel2);
addButton("proj2", SLOT(button12Clicked()), button2Widget);
button2Widget->setFixedHeight(80);
splitter2->addWidget(button2Widget);

TQWidget *button3Widget = new TQWidget(splitter3);
button3Widget->setFixedWidth(405);
TQHBoxLayout *button3Layout = new TQHBoxLayout(button3Widget);
TQLabel *textLabel3 = new TQLabel("Etendre", button3Widget);
textLabel3->setFixedWidth(195);
button3Layout->addWidget(textLabel3);
addButton("proj3", SLOT(button13Clicked()), button3Widget);
button3Widget->setFixedHeight(80);
splitter3->addWidget(button3Widget);

TQWidget *button4Widget = new TQWidget(splitter4);
button4Widget->setFixedWidth(405);
TQHBoxLayout *button4Layout = new TQHBoxLayout(button4Widget);
TQLabel *textLabel4 = new TQLabel("Deuxieme ecran uniquement", button4Widget);
textLabel4->setFixedWidth(195);
button4Layout->addWidget(textLabel4);
addButton("proj4", SLOT(button14Clicked()), button4Widget);
button4Widget->setFixedHeight(80);
splitter4->addWidget(button4Widget);

    int screenWidth = TDEApplication::desktop()->width();
    int dialogWidth = newDialog->width();
    int xPosition = screenWidth - dialogWidth;
    int screenHeight = TDEApplication::desktop()->height();
    int dialogHeight = newDialog->height();
    int yPosition = screenHeight - dialogHeight;
    newDialog->move(xPosition, yPosition);
    newDialog->setCaption("Projeter");
    newDialog->show();
}


actioncenter_applet::~actioncenter_applet()
{
}

void actioncenter_applet::iconClicked()
{

    if (newDialog  && newDialog->isVisible()) {
        newDialog->close();
        return;
    }

    if (customDialog && customDialog->isVisible()) {
        customDialog->close();
        return;
    }

    customDialog = new TQDialog(this);
    customDialog->setFixedSize(405, getScreenHeight());
    TQVBoxLayout *mainLayout = new TQVBoxLayout(customDialog);

    FILE *actionsScript = popen("/opt/trinity/share/apps/actioncenter_applet/actions.sh", "r");
    TQString actionsText;
if (actionsScript) {
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), actionsScript) != nullptr) {
        actionsText += TQString(buffer) + "\n";
    }
    pclose(actionsScript);
}

    TQStringList actionsList = TQStringList::split('\n', actionsText);

    if (actionsList.count() >= 2) {
        button1State = (actionsList[0].toInt() == 0);
        button2State = (actionsList[1].toInt() == 0);
    }

TQStringList sublist;
for (int i = 2; i < actionsList.count(); ++i) {
    TQString line = actionsList[i];
    sublist << line;
}

    TQLabel *textLabel = new TQLabel(sublist.join("\n"), customDialog);
    textLabel->setAlignment(TQt::AlignHCenter | TQt::AlignVCenter);
    TQFont font = textLabel->font();
    font.setBold(true);
    textLabel->setFont(font);

    int textHeight = (customDialog->height() * 0.67);
    textLabel->setFixedHeight(textHeight);

    mainLayout->addWidget(textLabel);

    TQSplitter *internalSplitter = new TQSplitter(customDialog);
    TQSplitter *internalSplitter2 = new TQSplitter(internalSplitter);
    TQSplitter *internalSplitter1 = new TQSplitter(internalSplitter);
    internalSplitter->setOrientation(TQt::Vertical);
    internalSplitter->addWidget(internalSplitter2);
    internalSplitter->addWidget(internalSplitter1);

mainLayout->addWidget(internalSplitter, 0, TQt::AlignHCenter | TQt::AlignVCenter);

    addImageButton("action1", "action1_on", SLOT(button1Clicked()), button1State, internalSplitter1);
    addImageButton("action2", "action2_on", SLOT(button2Clicked()), button2State, internalSplitter1);
    addButton("action3", SLOT(button3Clicked()), internalSplitter1);
    addButton("action4", SLOT(button4Clicked()), internalSplitter1);
    addButton("action5", SLOT(button5Clicked()), internalSplitter2);
    addButton("proj", SLOT(button6Clicked()), internalSplitter2);

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




void actioncenter_applet::addImageButton(const char *imagePathOn, const char *imagePathOff, const char *slot, bool &buttonState, TQWidget *parentWidget)
{
    action_tile *tile = new action_tile(parentWidget, imagePathOn, imagePathOff);
    connect(tile, SIGNAL(clicked()), this, slot);
}

void actioncenter_applet::addButton(const char *imagePath, const char *slot, TQWidget *parentWidget)
{
    action_tile *tile = new action_tile(parentWidget, imagePath);
    connect(tile, SIGNAL(clicked()), this, slot);
}




void actioncenter_applet::button1Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/actions.sh 1");
    button1State = !button1State;
    addImageButton("action1", "action1_on", SLOT(button1Clicked()), button1State,internalSplitter1);
}

void actioncenter_applet::button2Clicked()
{
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/actions.sh 2");
    button2State = !button2State;
    addImageButton("action2", "action2_on", SLOT(button2Clicked()), button2State,internalSplitter1);
}

void actioncenter_applet::button3Clicked()
{
 customDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/actions.sh 3");
}

void actioncenter_applet::button4Clicked()
{
 customDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/actions.sh 4");
}

void actioncenter_applet::button5Clicked()
{
 customDialog->close();
   // KRun::runCommand("konsole --nomenubar --notabbar -e nmtui");
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/actions.sh 5");
}
void actioncenter_applet::button6Clicked()
{
 customDialog->close();
showNewPanel();
}


void actioncenter_applet::button11Clicked()
{
 newDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/proj.sh pconly");
}

void actioncenter_applet::button12Clicked()
{
 newDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/proj.sh duplicate");
}

void actioncenter_applet::button13Clicked()
{
 newDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/proj.sh expand");
}

void actioncenter_applet::button14Clicked()
{
 newDialog->close();
    KRun::runCommand("/opt/trinity/share/apps/actioncenter_applet/proj.sh 2ndonly");
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
        TDEGlobal::locale()->insertCatalogue("actioncenter_panelapplet");
        return new actioncenter_applet(configFile, KPanelApplet::Normal, 0, parent, "actioncenter_panelapplet");
    }
}

#include "actioncenter_applet.moc"