#ifndef TABWIDGET_H
#define TABWIDGET_H

// Librerías Internas
#include "TabWidget_global.h"
#include "TabWidgetCorner.h"

// Librerías Qt
#include <QFlags>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QShowEvent>
#include <QSizePolicy>
#include <QString>
#include <QTabBar>
#include <QTabWidget>
#include <QThread>
#include <QTimerEvent>
#include <QWidget>

class TabWidgetCorner;

class TABWIDGETSHARED_EXPORT TabWidget : public QTabWidget {

    Q_OBJECT

  public:
    explicit TabWidget ( QWidget *parent = Q_NULLPTR );

    bool getLockedTabWidget () const;
    bool getOpenTabWidget () const;
    int getPreviousHeight () const;
    QParallelAnimationGroup *getToggleAnimation () const;
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void setAnimation ();
    void setCornerWidget ( QWidget *widget, Qt::Corner corner = Qt::TopRightCorner );
    void setLockedTabWidget ( bool value );
    void setOpenTabWidget ( bool value );
    void setPreviousHeight ( int value );
    void setTabPosition ( QTabWidget::TabPosition tabPosition );
    void timerEvent ( QTimerEvent *timerEvent ) Q_DECL_OVERRIDE;

  protected:
    void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE;

  public slots:
    void launchAnimation ();

  private:
    TabWidgetCorner *cornerActionsContainer;
    QParallelAnimationGroup *toggleAnimation;
    bool lockedTabWidget = false;
    bool openTabWidget = true;
    int previousIndex;
    int previousHeight;
    int timerId;
    bool finishedAnimation = false;
};

#endif // TABWIDGET_H
