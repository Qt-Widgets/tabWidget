#include "MainWindow.h"
#include <QDebug>
#include <QSplitter>
#include <QTextEdit>

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  this->resize ( 400, 250 );
  Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::North, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::North, this );

  QWidget *prueba = new QWidget ( this );
  prueba->setStyleSheet ( "background-color: yellow" );
  collapsibleTabWidget->addTab ( prueba, "Tab 1" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 2" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 3" );
  collapsibleTabWidget->addTab ( new QWidget ( this ), "Tab 4" );

  //collapsibleTabWidget->setTabPosition ( QTabWidget::North );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::South );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::East );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::West );

  this->setCentralWidget ( collapsibleTabWidget );
  qDebug () << "Está agregando el tabwidget";

  /*QSplitter *splitter = new QSplitter ( this );
  splitter->setOrientation ( Qt::Vertical );
  splitter->addWidget ( collapsibleTabWidget );
  splitter->addWidget ( new QTextEdit ( this ) );

  this->setCentralWidget ( splitter );*/
}
