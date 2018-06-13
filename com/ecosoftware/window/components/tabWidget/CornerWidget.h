#ifndef CORNERWIDGET_H
#define CORNERWIDGET_H

// Librerias Internas
#include "TabWidget_global.h"
//#include "TabWidget.h"

// Librerías Qt
/*#include <QAbstractAnimation>*/
#include <QAction>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
/*#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>*/

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT CornerWidget : public QWidget {

              Q_OBJECT

            public:
              explicit CornerWidget ( Qt::Corner cornerPosition, QTabWidget::TabPosition tabPosition = QTabWidget::North, QWidget *parent = 0 );

              void addAction ( QAction *action );
              Qt::Corner getCornerPosition () const;
              void updateArrowDirection ( bool checked );
              void setCornerPosition ( const Qt::Corner &value );

            public slots:
              void onToggle ( bool checked );

            private:
              QToolButton *showHideTabWidgetBtn;
              QBoxLayout *mainLayout;
              Qt::Corner cornerPosition;
              QTabWidget::TabPosition tabPosition;

          };
        }
      }
    }
  }
}

#endif // CORNERWIDGET_H
