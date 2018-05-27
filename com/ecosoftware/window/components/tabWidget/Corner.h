#ifndef CORNER_H
#define CORNER_H

// Librerias Internas
#include "TabWidget_global.h"
//#include "TabWidget.h"

// Librerías Qt
/*#include <QAbstractAnimation>*/
#include <QAction>
#include <QBoxLayout>
#include <QHBoxLayout>
/*#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>*/
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT Corner : public QWidget {

              Q_OBJECT

            public:
              explicit Corner ( QTabWidget::TabPosition cornerPosition = QTabWidget::North, QWidget *parent = 0 );

              void addAction ( QAction *action );
              QTabWidget::TabPosition getCornerPosition () const;
              void updateArrowDirection ();
              void setCornerPosition ( const QTabWidget::TabPosition &value );

            public slots:
              void toggleShowHideTabWidgetBtn ( bool checked );

            private:
              QToolButton *showHideTabWidgetBtn;
              QBoxLayout *mainLayout;
              QTabWidget::TabPosition cornerPosition;

          };
        }
      }
    }
  }
}

#endif // CORNER_H
