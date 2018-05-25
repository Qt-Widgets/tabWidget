#ifndef TABWIDGET_H
#define TABWIDGET_H

// Librerías Internas
#include "TabWidget_global.h"
#include "Corner.h"

// Librerías Qt
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
              explicit TabWidget ( bool collapsible = true, bool animated = true, QWidget *parent = 0 );

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

              QTabWidget::TabPosition getIndicatorPosition () const;
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

            private:
              Corner *cornerLeft = nullptr;
              Corner *cornerRight = nullptr;
              /*QParallelAnimationGroup *toggleAnimation;
    bool lockedTabWidget = false;
    bool openTabWidget = true;
    int previousIndex;
    int previousHeight;
    int timerId;
    bool finishedAnimation = false;*/
              bool collapsible = false;
              bool animated = false;
              bool floating = false;
              TabWidget::CornerPosition indicatorPosition;
          };
        }
      }
    }
  }
}

#endif // TABWIDGET_H
