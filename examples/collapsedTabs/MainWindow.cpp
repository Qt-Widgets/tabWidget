#include "MainWindow.h"
#include <QDebug>
#include <QSplitter>
#include <QTextEdit>

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  this->resize ( 400, 250 );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::North, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::North, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::South, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::South, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::East, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::East, this );
  Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::West, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::West, this );

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

  //collapsibleTabWidget->setIndicatorPosition ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::Left );

  this->setCentralWidget ( collapsibleTabWidget );

  /*QSplitter *splitter = new QSplitter ( this );
  splitter->setOrientation ( Qt::Vertical );
  splitter->addWidget ( collapsibleTabWidget );
  splitter->addWidget ( new QTextEdit ( this ) );

  this->setCentralWidget ( splitter );*/
}
