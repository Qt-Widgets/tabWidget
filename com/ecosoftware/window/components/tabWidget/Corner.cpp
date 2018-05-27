#include "Corner.h"
#include <QDebug> // FOR DEBUGGING MESSAGES

using namespace Com::Ecosoftware::Window::Components::TabWidget;

Corner::Corner ( QTabWidget::TabPosition cornerPosition, QWidget *parent ) : QWidget ( parent ) {

  this->setContentsMargins ( 0, 0, 0, 0 );
  this->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  this->cornerPosition = cornerPosition;
  if ( ( cornerPosition == QTabWidget::East ) || ( cornerPosition == QTabWidget::West ) ) {

    this->mainLayout = new QHBoxLayout ( this );

  } else if ( ( cornerPosition == QTabWidget::North ) || ( cornerPosition == QTabWidget::South ) ) {

    this->mainLayout = new QVBoxLayout ( this );
  }
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  this->setLayout ( this->mainLayout );
  //this->mainLayout->addWidget ( this->showHideTabWidgetBtn );
  //connect ( this->showHideTabWidgetBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
  //this->updateArrowDirection ();
}

void Corner::updateArrowDirection () {

  QToolButton *toolButton = this->findChild<QToolButton *> ( "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabActBtn" );
  switch ( this->cornerPosition ) {

    case QTabWidget::North:

      toolButton->setArrowType ( toolButton->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    case QTabWidget::South:

      toolButton->setArrowType ( toolButton->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    case QTabWidget::East:

      toolButton->setArrowType ( toolButton->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    case QTabWidget::West:

      toolButton->setArrowType ( toolButton->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    default:

      toolButton->setArrowType ( toolButton->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;
  }
}

void Corner::toggleShowHideTabWidgetBtn ( bool checked ) {

  this->updateArrowDirection ();

  //qDebug () << ( ( CollapsibleTabWidget * ) this->parent () )->getOpenTabWidget ();
  //if ( ( ( ( CollapsibleTabWidget * ) this->parent () )->getOpenTabWidget () ) && !( ( ( CollapsibleTabWidget * ) this->parent () )->getLockedTabWidget () ) ) {

  /*QParallelAnimationGroup *toggleAnimation = ( ( TabWidget * ) this->parent () )->getToggleAnimation ();
  toggleAnimation->setDirection ( checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
  toggleAnimation->start ();
  ( ( TabWidget * ) this->parent () )->setLockedTabWidget ( checked );
  ( ( TabWidget * ) this->parent () )->setOpenTabWidget ( !checked );*/
  //}
}

QTabWidget::TabPosition Corner::getCornerPosition () const {

  return this->cornerPosition;
}

void Corner::setCornerPosition ( const QTabWidget::TabPosition &value ) {

  this->cornerPosition = value;
}

void Corner::Corner::addAction ( QAction *action ) {

  QToolButton *toolBtn = new QToolButton ( this );
  toolBtn->setDefaultAction ( action );
  toolBtn->setObjectName ( action->objectName () + "Btn" );
  toolBtn->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  toolBtn->setStyleSheet ( "QToolButton {border: none;}" );
  toolBtn->setToolButtonStyle ( Qt::ToolButtonIconOnly );
  toolBtn->setToolTip ( action->toolTip () );
  toolBtn->setToolTipDuration ( 5000 );
  toolBtn->setCheckable ( true );
  toolBtn->setChecked ( false );
  toolBtn->setMinimumSize ( 16, 16 );
  if ( action->objectName ().compare ( "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabAct" ) == 0 ) {

    toolBtn->setArrowType ( Qt::ArrowType::DownArrow );
    connect ( toolBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
  }
  this->mainLayout->addWidget ( toolBtn );
}
