#ifndef TABWIDGET_H
#define TABWIDGET_H

// Librerías Internas
#include "TabWidget_global.h"
#include "CornerWidget.h"
#include "TabBar.h"
#include "ShowHideTabAct.h"

// Librerías Qt
#include <QAction>
#include <QEvent>
#include <QIcon>
#include <QMouseEvent>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QShowEvent>
#include <QSize>
#include <QTabBar>
#include <QTabWidget>
#include <QTransform>
#include <QToolButton>
/*
#include <QFlags>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QString>
#include <QTimerEvent>
#include <QWidget>
*/

class CornerWidget;
//class CustomTabBar;

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

              enum TabFlag {

                IconNextText = 0,
                IconOverText,
                OnlyIcon,
                OnlyText
              };
              Q_ENUM ( TabFlag )

              void addActionCorner ( QAction *action, TabWidget::CornerPosition cornerPosition );
              int	addTab ( QWidget *page, const QString &label );
              int addTab ( QWidget *page, const QIcon &icon, const QString &label );
              TabWidget::CornerPosition getIndicatorPosition () const; // LISTO
              TabWidget::TabFlag getTabFlag () const;
              bool isAnimated () const; // LISTO
              bool isCollapsible () const; // LISTO
              bool isFloating () const;
              bool isTabLocked () const; // LISTO
              bool isTabOpened () const; // LISTO
              void setAnimated ( bool value );
              void setCollapsible ( bool value );
              void setDuration ( int msecs ); // LISTO
              void setEasingCurve ( const QEasingCurve &easing ); // LISTO
              void setFloating ( bool value );
              void setIndicatorPosition ( TabWidget::CornerPosition cornerPosition );
              void setTabFlag ( const TabWidget::TabFlag &value );
              void setTabPosition ( QTabWidget::TabPosition tabPosition );


            public slots:
              void launchAnimation (); // LISTO
              void onDobleClick (); // LISTO

            signals:
              void toCollapse ( bool toCollapse ); // LISTO

            protected:
              void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE; // LISTO
              void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE; // LISTO
              void showEvent ( QShowEvent *event ) Q_DECL_OVERRIDE; // LISTO

            private slots:
              void onCollapse ( bool onCollapse ); // LISTO
              void onStoppedAnimation (); // LISTO

            private:
              /**
               * @brief cornerTopLeft
               * Esquina izquierda/superior del QTabWidget para las posiciones North/West del QTabBar
               */
              CornerWidget *cornerTopLeft = nullptr; // LISTO
              /**
               * @brief cornerBottomRight
               * Esquina derecha/inferior del QTabWidget para las posiciones South/East del QTabBar
               */
              CornerWidget *cornerBottomRight = nullptr; // LISTO
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
              TabWidget::CornerPosition indicatorPosition = TabWidget::None;
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
              int previousIndex = 0;
              int minimunValue = 0;
              bool openTabWidget = true;
              TabWidget::TabFlag tabFlag = TabWidget::IconNextText;

              void collapsed (); // LISTO
              void collapsedAnimated (); // LISTO
              void collapsedUnanimated (); // LISTO
              QIcon fixIcon ( const QIcon &icon );
              void removeShowHideBtn (); // LISTO
              void setAnimation ();
              void uncollapsed (); // LISTO
              void uncollapsedAnimated (); // LISTO
              void uncollapsedUnanimated (); // LISTO
          };
        }
      }
    }
  }
}

#endif // TABWIDGET_H
