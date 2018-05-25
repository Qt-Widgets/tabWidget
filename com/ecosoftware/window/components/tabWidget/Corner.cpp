#include "Corner.h"
#include <QDebug> // FOR DEBUGGING MESSAGES

using namespace Com::Ecosoftware::Window::Components::TabWidget;

Corner::Corner ( QWidget *parent ) : QWidget ( parent ) {

  this->setContentsMargins ( 0, 0, 0, 0 );
  this->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );

  /*this->showHideTabWidgetBtn = new QToolButton ( this );
  this->showHideTabWidgetBtn->setObjectName ( "showHideTabWidgetBtn" );
  this->showHideTabWidgetBtn->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  this->showHideTabWidgetBtn->setStyleSheet ( "QToolButton {border: none;}" );
  this->showHideTabWidgetBtn->setToolButtonStyle ( Qt::ToolButtonIconOnly );
  //this->showHideTabWidgetBtn->setArrowType ( Qt::ArrowType::DownArrow );
  //this->showHideTabWidgetBtn->setToolTip ( "Collapse" );
  this->showHideTabWidgetBtn->setToolTipDuration ( 5000 );
  this->showHideTabWidgetBtn->setCheckable ( true );
  this->showHideTabWidgetBtn->setChecked ( false );
  this->showHideTabWidgetBtn->setMinimumSize ( 16, 16 );*/

  this->mainLayout = new QHBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  //this->mainLayout->addWidget ( this->showHideTabWidgetBtn );
  this->setLayout ( this->mainLayout );
  //connect ( this->showHideTabWidgetBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
  //this->updateArrowDirection ();
}

void Corner::updateArrowDirection () {

  switch ( ( ( QTabWidget * ) this->parentWidget () )->tabPosition () ) {

    case QTabWidget::North: {

      qDebug () << "Está entrando por el norte";
      QWidget *corner = ( ( QTabWidget * ) this->parentWidget () )->cornerWidget ( Qt::TopRightCorner );
      if ( corner ) {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );

      } else {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::RightArrow : Qt::ArrowType::DownArrow );
      }
      break;
    }
    case QTabWidget::South: {

      qDebug () << "Está entrando por el sur";
      QWidget *corner = ( ( QTabWidget * ) this->parentWidget () )->cornerWidget ( Qt::TopRightCorner );
      if ( corner ) {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::UpArrow );

      } else {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::RightArrow : Qt::ArrowType::UpArrow );
      }
      break;
    }
    case QTabWidget::East:

      qDebug () << "Está entrando por el este";
      this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    case QTabWidget::West:

      qDebug () << "Está entrando por el oeste";
      this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
      break;

    default:

      qDebug () << "Está entrando por el predeterminado";
      QWidget *corner = ( ( QTabWidget * ) this->parentWidget () )->cornerWidget ( Qt::TopRightCorner );
      if ( corner ) {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );

      } else {

        this->showHideTabWidgetBtn->setArrowType ( this->showHideTabWidgetBtn->isChecked () ? Qt::ArrowType::RightArrow : Qt::ArrowType::DownArrow );
      }
      break;
  }
  this->showHideTabWidgetBtn->setToolTip ( this->showHideTabWidgetBtn->isChecked () ? "Uncollapse" : "Collapse" );
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
