#ifndef CORNER_H
#define CORNER_H

// Librerias Internas
#include "TabWidget_global.h"
//#include "TabWidget.h"

// Librerías Qt
/*#include <QAbstractAnimation>*/
#include <QAction>
#include <QHBoxLayout>
/*#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTabWidget>*/
#include <QToolButton>
#include <QWidget>

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT Corner : public QWidget {

              Q_OBJECT

            public:
              explicit Corner ( QWidget *parent = 0 );

              void addAction ( QAction *action );
              void updateArrowDirection ();

            public slots:
              void toggleShowHideTabWidgetBtn ( bool checked );

            private:
              QToolButton *showHideTabWidgetBtn;
              QHBoxLayout *mainLayout;
          };
        }
      }
    }
  }
}

#endif // CORNER_H
