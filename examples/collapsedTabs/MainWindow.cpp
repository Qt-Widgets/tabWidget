#include "MainWindow.h"
#include <QDebug>
#include <QIcon>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  this->resize ( 400, 250 );
  Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::North, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::North, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::South, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::South, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::East, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::East, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, true, QTabWidget::West, this );
  //Com::Ecosoftware::Window::Components::TabWidget::TabWidget *collapsibleTabWidget = new Com::Ecosoftware::Window::Components::TabWidget::TabWidget ( true, false, QTabWidget::West, this );

  //collapsibleTabWidget->setTabFlag ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::IconNextText );
  //collapsibleTabWidget->setTabFlag ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::IconOverText );
  collapsibleTabWidget->setTabFlag ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::OnlyIcon );
  //collapsibleTabWidget->setTabFlag ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::OnlyText );

  QWidget *prueba = new QWidget ( this );
  prueba->setStyleSheet ( "background-color: yellow" );
  collapsibleTabWidget->addTab ( prueba, QIcon ( ":/icons/Back.svg" ), QString ( "Tab 1" ) );
  prueba = new QWidget ( this );
  prueba->setStyleSheet ( "background-color: blue" );
  collapsibleTabWidget->addTab ( prueba, QIcon ( ":/icons/Arrow.svg" ), "Tab 2" );
  prueba = new QWidget ( this );
  prueba->setStyleSheet ( "background-color: red" );
  collapsibleTabWidget->addTab ( prueba, QIcon ( ":/icons/arrow-down.svg" ), "Tab 3" );
  prueba = new QWidget ( this );
  prueba->setStyleSheet ( "background-color: brown" );
  collapsibleTabWidget->addTab ( prueba, QIcon ( ":/icons/arrow-right.svg" ), "Tab 4" );


  //collapsibleTabWidget->setTabPosition ( QTabWidget::North );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::South );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::East );
  //collapsibleTabWidget->setTabPosition ( QTabWidget::West );

  //collapsibleTabWidget->setIndicatorPosition ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::Top );
  //collapsibleTabWidget->setIndicatorPosition ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::Bottom );
  //collapsibleTabWidget->setIndicatorPosition ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::Left );
  //collapsibleTabWidget->setIndicatorPosition ( Com::Ecosoftware::Window::Components::TabWidget::TabWidget::Right );

  this->setCentralWidget ( collapsibleTabWidget );

  /*QSplitter *splitter = new QSplitter ( this );
  splitter->setOrientation ( Qt::Vertical );
  splitter->addWidget ( collapsibleTabWidget );
  splitter->addWidget ( new QTextEdit ( this ) );

  this->setCentralWidget ( splitter );*/
}
