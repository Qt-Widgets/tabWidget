#ifndef CORNERWIDGET_H
#define CORNERWIDGET_H

// Librerias Internas
#include "TabWidget_global.h"

// Librerías Qt
#include <QAction>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

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
              void removeToolbutton ( QAction *action );
              void setCornerPosition ( const Qt::Corner &value );
              void updateArrowDirection ( bool checked );

            public slots:
              void onToggle ( bool checked );

            private:
                           Qt::Corner  cornerPosition;
                           QBoxLayout *mainLayout;
                          QToolButton *showHideTabWidgetBtn;
              QTabWidget::TabPosition  tabPosition;

              void reorderButtonsCornerWithoutShowHideToolBtn ( QToolButton *toolBtn );
              void reorderButtonsCornerWithShowHideToolBtn ( QToolButton *toolBtn );
          };
        }
      }
    }
  }
}

#endif // CORNERWIDGET_H
