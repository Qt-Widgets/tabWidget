#ifndef TABWIDGETCORNER_H
#define TABWIDGETCORNER_H

// Librerias Internas
#include "TabWidget.h"

// Librerías Qt
#include <QAbstractAnimation>
#include <QAction>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTabWidget>
#include <QToolButton>
#include <QWidget>

class TabWidgetCorner : public QWidget {

    Q_OBJECT

  public:
    explicit TabWidgetCorner ( QWidget *parent = 0 );

    void addAction ( QAction *action );
    void updateArrowDirection ();

  public slots:
    void toggleShowHideTabWidgetBtn ( bool checked );

  private:
    QToolButton *showHideTabWidgetBtn;
    QHBoxLayout *mainLayout;
};

#endif // TABWIDGETCORNER_H
