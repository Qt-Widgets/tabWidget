#include "CornerWidget.h"
#include <QDebug> // FOR DEBUGGING MESSAGES

using namespace Com::Ecosoftware::Window::Components::TabWidget;

CornerWidget::CornerWidget ( Qt::Corner cornerPosition, QTabWidget::TabPosition tabPosition, QWidget *parent ) : QWidget ( parent ) {

  this->setContentsMargins ( 0, 0, 0, 0 );
  this->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  this->cornerPosition = cornerPosition;
  this->tabPosition = tabPosition;
  if ( ( tabPosition == QTabWidget::East ) || ( tabPosition == QTabWidget::West ) ) {

    this->mainLayout = new QHBoxLayout ( this );

  } else if ( ( tabPosition == QTabWidget::North ) || ( tabPosition == QTabWidget::South ) ) {

    this->mainLayout = new QVBoxLayout ( this );
  }
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  this->setLayout ( this->mainLayout );
}

void CornerWidget::updateArrowDirection ( bool checked ) {

  qDebug () << "checked" << checked;
  qDebug () << "Si está entrando por el updateArrowDirection";
  QToolButton *toolButton = this->findChild<QToolButton *> ( "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabActBtn" );
  // TODO: aquí identificar primero la posición de las pestañas y luego el cornerPosition

  if ( toolButton ) {

    QAction *defaultAction = toolButton->defaultAction ();
    defaultAction->setChecked ( checked );
    defaultAction->setToolTip ( defaultAction->isChecked () ? "Uncollapse" : "Collapse" );
    toolButton->setChecked ( checked );
    switch ( ( ( QTabWidget * ) this->parentWidget () )->tabPosition () ) {

      case QTabWidget::North:

        switch ( this->cornerPosition ) {

          case Qt::TopLeftCorner:
          case Qt::BottomLeftCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::RightArrow : Qt::ArrowType::DownArrow );
            break;

          case Qt::TopRightCorner:
          case Qt::BottomRightCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
            break;

          default:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
            break;
        }
        break;

      case QTabWidget::South:

        switch ( this->cornerPosition ) {

          case Qt::TopLeftCorner:
          case Qt::BottomLeftCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::RightArrow : Qt::ArrowType::UpArrow );
            break;

          case Qt::TopRightCorner:
          case Qt::BottomRightCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::UpArrow );
            break;

          default:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::UpArrow );
            break;
        }
        break;

      case QTabWidget::East:

        switch ( this->cornerPosition ) {

          case Qt::TopLeftCorner:
          case Qt::BottomLeftCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::LeftArrow );
            break;

          case Qt::TopRightCorner:
          case Qt::BottomRightCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::UpArrow : Qt::ArrowType::LeftArrow );
            break;

          default:

            toolButton->setArrowType ( checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::LeftArrow );
            break;
        }
        break;

      case QTabWidget::West:

        switch ( this->cornerPosition ) {

          case Qt::TopLeftCorner:
          case Qt::BottomLeftCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow );
            break;

          case Qt::TopRightCorner:
          case Qt::BottomRightCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::UpArrow : Qt::ArrowType::RightArrow );
            break;

          default:

            toolButton->setArrowType ( checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow );
            break;
        }
        break;

      default:

        switch ( this->cornerPosition ) {

          case Qt::TopLeftCorner:
          case Qt::BottomLeftCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::RightArrow : Qt::ArrowType::DownArrow );
            break;

          case Qt::TopRightCorner:
          case Qt::BottomRightCorner:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
            break;

          default:

            toolButton->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
            break;
        }
        break;
    }
  }
}

void CornerWidget::toggleShowHideTabWidgetBtn ( bool checked ) {

  this->updateArrowDirection ( checked );

  //qDebug () << ( ( CollapsibleTabWidget * ) this->parent () )->getOpenTabWidget ();
  //if ( ( ( ( CollapsibleTabWidget * ) this->parent () )->getOpenTabWidget () ) && !( ( ( CollapsibleTabWidget * ) this->parent () )->getLockedTabWidget () ) ) {

  /*QParallelAnimationGroup *toggleAnimation = ( ( TabWidget * ) this->parent () )->getToggleAnimation ();
  toggleAnimation->setDirection ( checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
  toggleAnimation->start ();
  ( ( TabWidget * ) this->parent () )->setLockedTabWidget ( checked );
  ( ( TabWidget * ) this->parent () )->setOpenTabWidget ( !checked );*/
  //}
}

Qt::Corner CornerWidget::getCornerPosition () const {

  return this->cornerPosition;
}

void CornerWidget::setCornerPosition ( const Qt::Corner &value ) {

  this->cornerPosition = value;
}

void CornerWidget::addAction ( QAction *action ) {

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

    switch ( ( ( QTabWidget * ) this->parentWidget () )->tabPosition () ) {

      case QTabWidget::North:

        toolBtn->setArrowType ( Qt::ArrowType::DownArrow );
        break;

      case QTabWidget::South:

        toolBtn->setArrowType ( Qt::ArrowType::UpArrow );
        break;

      case QTabWidget::East:

        toolBtn->setArrowType ( Qt::ArrowType::LeftArrow );
        break;

      case QTabWidget::West:

        toolBtn->setArrowType ( Qt::ArrowType::RightArrow );
        break;

      default:

        toolBtn->setArrowType ( Qt::ArrowType::DownArrow );
        break;
    }
    connect ( toolBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
  }
  this->mainLayout->addWidget ( toolBtn );
}
