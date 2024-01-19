#ifndef ACTION_TILE_H
#define ACTION_TILE_H

#include <tqtoolbutton.h>

class action_tile : public TQToolButton {
  public:
    action_tile(TQWidget *parent, TQString iconOn, TQString iconOff = TQString::null);
    ~action_tile();

    TQPixmap pixmap();
    TQString locateIcon(TQString icon);

  protected:
    void drawButton(TQPainter *);
};

#endif