#ifndef TABWIDGET_H
#define TABWIDGET_H

// Librerías Internas
#include "TabWidget_global.h"
#include "ShowHideTabAct.h"
#include "Corner.h"

// Librerías Qt
#include <QAction>
/*#include <QFlags>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QShowEvent>
#include <QSizePolicy>
#include <QString>
#include <QTabBar>*/
#include <QTabWidget>
/*#include <QThread>
#include <QTimerEvent>
#include <QWidget>*/

class Corner;

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT TabWidget : public QTabWidget {

              Q_OBJECT

            public:
              explicit TabWidget ( bool collapsible = true, bool animated = true, QTabWidget::TabPosition tabPosition = QTabWidget::North, QWidget *parent = 0 );

              enum CornerPosition {

                Top,
                Bottom,
                Left,
                Right
              };
              Q_ENUM ( CornerPosition )

              /*bool getLockedTabWidget () const;
    bool getOpenTabWidget () const;
    int getPreviousHeight () const;
    QParallelAnimationGroup *getToggleAnimation () const;
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void setAnimation ();
    void setCornerWidget ( QWidget *widget, Qt::Corner corner = Qt::TopRightCorner );
    void setLockedTabWidget ( bool value );
    void setOpenTabWidget ( bool value );
    void setPreviousHeight ( int value );*/

              void addAction ( QAction *action, TabWidget::CornerPosition cornerPosition );
              TabWidget::CornerPosition getIndicatorPosition () const;
              bool isAnimated () const;
              bool isCollapsible () const;
              bool isFloating () const;
              void setAnimated ( bool value );
              void setCollapsible ( bool value );
              void setIndicatorPosition ( TabWidget::CornerPosition cornerPosition );
              void setFloating ( bool value );
              void setTabPosition ( QTabWidget::TabPosition tabPosition );
              //void timerEvent ( QTimerEvent *timerEvent ) Q_DECL_OVERRIDE;

            protected:
              //void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE;

            public slots:
              //void launchAnimation ();
              void collapse ( bool collapse );

            private:
              Corner *cornerTopLeft= nullptr;
              Corner *cornerBottomRight = nullptr;
              /*QParallelAnimationGroup *toggleAnimation;
    bool lockedTabWidget = false;
    bool openTabWidget = true;
    int previousIndex;
    int timerId;
    bool finishedAnimation = false;*/
              bool collapsible = false;
              bool animated = false;
              bool floating = false;
              TabWidget::CornerPosition indicatorPosition = TabWidget::Right;
              ShowHideTabAct *showHideTabAct = nullptr;
              int previousHeight;
          };
        }
      }
    }
  }
}

#endif // TABWIDGET_H
