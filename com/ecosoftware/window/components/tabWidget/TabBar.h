#ifndef TABBAR_H
#define TABBAR_H

// Librerías Internas
#include "TabWidget_global.h"

// Librerías Qt
#include <QMouseEvent>
#include <QTabBar>

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT TabBar : public QTabBar {

              Q_OBJECT

            public:
              explicit TabBar ( QWidget *parent = 0 );

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
