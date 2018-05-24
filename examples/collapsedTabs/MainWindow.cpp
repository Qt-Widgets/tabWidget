#include "MainWindow.h"
#include <QDebug>
#include <QSplitter>
#include <QTextEdit>

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  this->resize ( 400, 250 );
  TabWidget *collapsibleTabWidget = new TabWidget ( this );

  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 1" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 2" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 3" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 4" );

  //collapsibleTabWidget->setTabPosition ( QTabWidget::North );
  collapsibleTabWidget->setTabPosition ( QTabWidget::South );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::East );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::West );

  this->setCentralWidget ( collapsibleTabWidget );

  /*QSplitter *splitter = new QSplitter ( this );
  splitter->setOrientation ( Qt::Vertical );
  splitter->addWidget ( collapsibleTabWidget );
  splitter->addWidget ( new QTextEdit ( this ) );

  this->setCentralWidget ( splitter );*/
}
