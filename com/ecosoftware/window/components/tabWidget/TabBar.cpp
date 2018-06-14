#include "TabBar.h"
#include "TabWidget.h"
#include <QDebug>

using namespace Com::Ecosoftware::Window::Components::TabWidget;

TabBar::TabBar ( QWidget *parent ) : QTabBar ( parent ) {}

void TabBar::paintEvent ( QPaintEvent *paintEvent ) {

  // TODO: Como redibujar los bordes de la pestaña.
  // TODO: Como redibujar el indicador de la pestaña activa.
  // TODO: Como ajustar el espaciado entre los bordes superio, inferior, izquierda, derecha y entre el icono y el texto.
  TabWidget *tabWidget = ( TabWidget * ) this->parentWidget ();

  switch ( tabWidget->getTabFlag () ) {

    case TabWidget::IconOverText: {

      QStylePainter painter ( this );
      for ( int i = 0; i < this->count (); ++i ) {

        QStyleOptionTab option;
        this->initStyleOption ( &option, i );
        painter.drawItemPixmap ( option.rect, Qt::AlignTop | Qt::AlignHCenter, option.icon.pixmap ( QSize ( 16, 16 ) ) );
        painter.drawItemText ( option.rect, Qt::AlignBottom | Qt::AlignHCenter, this->palette (), 1, option.text );
      }
      break;
    }
    default:

      QTabBar::paintEvent ( paintEvent );
      break;
  }
}

void TabBar::mouseDoubleClickEvent ( QMouseEvent *event ) {

  Q_UNUSED ( event )
  emit onDobleClick ();
}
