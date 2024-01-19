#include <tdeglobal.h>
#include <tqpainter.h>
#include <kstandarddirs.h>

#include "action_tile.h"

action_tile::action_tile(TQWidget *parent, TQString iconOn, TQString iconOff)
: TQToolButton(parent)
{
  TQIconSet iconSet;

  TQPixmap on(locateIcon(iconOn));
  iconSet.setPixmap(on, TQIconSet::Large, TQIconSet::Normal, TQIconSet::On);
  setFixedSize(on.size());

  if (!iconOff.isNull()) {
    TQPixmap off(locateIcon(iconOff));
    iconSet.setPixmap(off, TQIconSet::Large, TQIconSet::Normal, TQIconSet::Off);
  }

  setIconSet(iconSet);
  show();
}

action_tile::~action_tile()
{
}

TQString action_tile::locateIcon(TQString icon)
{
  return locate("data", TQString("actioncenter_applet/%1.png").arg(icon));
}

TQPixmap action_tile::pixmap()
{
  return iconSet().pixmap(TQIconSet::Large, TQIconSet::Normal,
                          isOn() ? TQIconSet::On : TQIconSet::Off);
}

void action_tile::drawButton(TQPainter *pe)
{
  pe->drawPixmap(rect(), pixmap());
}

#include "action_tile.moc"