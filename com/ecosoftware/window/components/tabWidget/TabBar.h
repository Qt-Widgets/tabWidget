#ifndef TABBAR_H
#define TABBAR_H

// Librerías Internas
#include "TabWidget_global.h"

// Librerías Qt
#include <QMouseEvent>
#include <QPaintEvent>
#include <QSize>
#include <QStyleOptionTabV2>
#include <QStylePainter>
#include <QTabBar>
#include <QTabWidget>

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT TabBar : public QTabBar {

              Q_OBJECT

            public:
              explicit TabBar ( QWidget *parent = 0 );

              void	paintEvent ( QPaintEvent *paintEvent ) Q_DECL_OVERRIDE;

            signals:
              void onDobleClick ();

            protected:
              void mouseDoubleClickEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE;
          };
        }
      }
    }
  }
}

#endif // TABBAR_H
