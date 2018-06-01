#ifndef TABWIDGET_H
#define TABWIDGET_H

// Librerías Internas
#include "TabWidget_global.h"
#include "Corner.h"
#include "TabBar.h"
#include "ShowHideTabAct.h"

// Librerías Qt
#include <QAction>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QTabBar>
#include <QTabWidget>
#include <QToolButton>
/*
#include <QFlags>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QShowEvent>
#include <QSizePolicy>
#include <QString>
#include <QTimerEvent>
#include <QWidget>
*/

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

                None = -1,
                Top,
                Bottom,
                Left,
                Right
              };
              Q_ENUM ( CornerPosition )

              /*bool getLockedTabWidget () const;
    bool getOpenTabWidget () const;
    int getPreviousHeight () const;
    void setCornerWidget ( QWidget *widget, Qt::Corner corner = Qt::TopRightCorner );
    void setLockedTabWidget ( bool value );
    void setOpenTabWidget ( bool value );
    void setPreviousHeight ( int value );*/

              void addAction ( QAction *action, TabWidget::CornerPosition cornerPosition );
              TabWidget::CornerPosition getIndicatorPosition () const;
              bool isAnimated () const; // LISTO
              bool isCollapsible () const; // LISTO
              bool isFloating () const;
              void setAnimated ( bool value );
              void setCollapsible ( bool value );
              void setDuration ( int msecs ); // LISTO
              void setEasingCurve ( const QEasingCurve &easing ); // LISTO
              void setIndicatorPosition ( TabWidget::CornerPosition cornerPosition );
              void setFloating ( bool value );
              void setTabPosition ( QTabWidget::TabPosition tabPosition );
              //void timerEvent ( QTimerEvent *timerEvent ) Q_DECL_OVERRIDE;

            public slots:
              void launchAnimation ();
              void onDobleClick ();

            signals:
              void toCollapse ( bool toCollapse );

            protected:
              void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
              void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE;

            private slots:
              void onCollapse ( bool onCollapse );
              void onStoppedAnimation (); // LISTO

            private:
              /*
    bool openTabWidget = true;
    int previousIndex;
    int timerId;
    bool finishedAnimation = false;*/
              /**
               * @brief cornerTopLeft
               * Esquina izquierda/superior del QTabWidget para las posiciones North/West del QTabBar
               */
              Corner *cornerTopLeft = nullptr; // LISTO
              /**
               * @brief cornerBottomRight
               * Esquina derecha/inferior del QTabWidget para las posiciones South/East del QTabBar
               */
              Corner *cornerBottomRight = nullptr; // LISTO
              /**
               * @brief collapsible
               * Indica si se puede expandir/contraer el QTabWidget.
               */
              bool collapsible = false;
              /**
               * @brief animated
               * Indica si la acción expandir/contraer del QTabWidget será animada.
               */
              bool animated = false;
              bool floating = false;
              /**
               * @brief indicatorPosition
               * Indica la posición de la acción showHideTabAct, puede ser Top, Bottom, Left, Right.
               */
              TabWidget::CornerPosition indicatorPosition = TabWidget::Right;
              /**
               * @brief showHideTabAct
               * Acción indicadora para expandir/contraer del QTabWidget.
               */
              ShowHideTabAct *showHideTabAct = nullptr;
              /**
               * @brief previousHeight
               * Indica el valor de la altura que deberá retornar al momento de expandir el QTabWidget.
               */
              int previousHeight;
              /**
               * @brief maxHeightPropertyAnimation
               * Representa la animación que se realizará para contraer el QTabWidget si animated es true.
               */
              QPropertyAnimation *collapsedAnimation = nullptr;
              /**
               * @brief minHeightPropertyAnimation
               * Representa la animación que se realizará para expandir el QTabWidget si animated es true.
               */
              QPropertyAnimation *uncollapsedAnimation = nullptr;
              TabBar *customTabBar = nullptr;
              bool lockedTabWidget = false;


              void collapsed ();
              void uncollapsed ();
              void collapsedAnimated ();
              void collapsedUnanimated ();
              void uncollapsedAnimated ();
              void uncollapsedUnanimated ();
              void setAnimation ();
          };
        }
      }
    }
  }
}

#endif // TABWIDGET_H
