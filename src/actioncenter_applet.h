// actioncenter_applet.h

#ifndef ACTIONCENTER_APPLET_H
#define ACTIONCENTER_APPLET_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kpanelapplet.h>
#include <tqstring.h>
#include <tqlayout.h> 
#include <tqpushbutton.h> 
#include <tqdialog.h>

class actioncenter_applet : public KPanelApplet
{
    TQ_OBJECT

public:
    actioncenter_applet(const TQString& configFile, Type t = Normal, int actions = 0, TQWidget *parent = 0, const char *name = 0);
    ~actioncenter_applet();

    virtual int widthForHeight(int height) const;
    virtual int heightForWidth(int width) const;

protected:
    void resizeEvent(TQResizeEvent *);

private slots:
    void iconClicked();
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();

private:
    bool button1State;  
    bool button2State;  

    TDEConfig *ksConfig;
    TQWidget *mainView;
    TQDialog *customDialog;
    TQWidget *buttonWidget;
    TQHBoxLayout *buttonLayout;

    void addImageButton(const char *imagePathOn, const char *imagePathOff, const char *slot, bool& buttonState);
    void addButton(const char *imagePath, const char *slot);

    int getScreenHeight() const;
    int getScreenWidth() const;
};

#endif
