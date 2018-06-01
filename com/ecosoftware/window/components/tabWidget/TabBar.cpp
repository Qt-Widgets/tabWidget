#include "TabBar.h"
#include <QDebug>

using namespace Com::Ecosoftware::Window::Components::TabWidget;

TabBar::TabBar ( QWidget *parent ) : QTabBar ( parent ) {}

void TabBar::mouseDoubleClickEvent ( QMouseEvent *event ) {

  qDebug () << "Se hizo docle click en el tabbar";
  emit onDobleClick ();
}
