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

  QToolButton *toolButton = this->findChild<QToolButton *> ( "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabActBtn" );
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

void CornerWidget::onToggle ( bool checked ) {

  this->updateArrowDirection ( checked );
}

Qt::Corner CornerWidget::getCornerPosition () const {

  return this->cornerPosition;
}

void CornerWidget::setCornerPosition ( const Qt::Corner &value ) {

  this->cornerPosition = value;
}

void CornerWidget::addAction ( QAction *action ) {

  // TODO: Agregar y reorganizar las acciones de acuerdo a la posición
  // si se agregan acciones del lado derecho, las acciones deben ir antes del indicador de bloqueo de pestañas si este último está activo
  // si se agregan acciones del lado izquierdo, las acciones deben ir después del indicador de bloqueo de pestañas si este último está activo
  // si hay acciones y no está activo el indicador y este se activa después, reordenar en el caso que corresponda
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
    connect ( toolBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( onToggle ( bool ) ) );
  }
  QString objectNameBtn = "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabActBtn";
  QToolButton *showHideToolBtn = this->findChild<QToolButton *> ( objectNameBtn );
  if ( showHideToolBtn != 0 ) { // Si existe el indicador de bloqueo de pestañas

    switch ( this->cornerPosition ) {

      case Qt::Corner::TopLeftCorner:

        this->mainLayout->addWidget ( toolBtn );
        break;

      case Qt::Corner::TopRightCorner: {

        if ( !( this->tabPosition == QTabWidget::East ) || !( this->tabPosition == QTabWidget::West ) ) {

          QList<QToolButton *> allPBtns = this->findChildren<QToolButton *> ();
          if ( allPBtns.count () > 0 ) {

            for ( int i = 0; i < allPBtns.count (); i++ ) {


              this->mainLayout->removeWidget ( allPBtns.at ( i ) );
            }
            for ( int i = 0; i < allPBtns.count () - 1; i++ ) {


              this->mainLayout->addWidget ( allPBtns.at ( i ) );
            }
            this->mainLayout->addWidget ( toolBtn );
            this->mainLayout->addWidget ( allPBtns.at ( allPBtns.count () - 1 ) );

          } else {

            this->mainLayout->addWidget ( toolBtn );
          }
        } else {

          this->mainLayout->addWidget ( toolBtn );
        }
        break;
      }
      case Qt::Corner::BottomLeftCorner:

        // TODO: Falta ajustar esta esquina
        break;

      case Qt::Corner::BottomRightCorner:

        // TODO: Falta ajustar esta esquina
        break;

      default:

        // TODO: Falta ajustar esquina predeterminada
        break;
    }
  } else { // Si no existe el indicador de bloqueo de pestañas

    if ( toolBtn->objectName ().compare ( objectNameBtn ) ) {

      // TODO: Aquí hay que verificar si el boton a insertar es el indicador
      // para reordenar las acciones según corresponda el caso.
      switch ( this->cornerPosition ) {

        case Qt::Corner::TopLeftCorner: {

          QList<QToolButton *> allPBtns = this->findChildren<QToolButton *> ();
          if ( allPBtns.count () > 0 ) {

            for ( int i = 0; i < allPBtns.count (); i++ ) {


              this->mainLayout->removeWidget ( allPBtns.at ( i ) );
            }
            this->mainLayout->addWidget ( toolBtn );
            for ( int i = 0; i < allPBtns.count (); i++ ) {


              this->mainLayout->addWidget ( allPBtns.at ( i ) );
            }

          } else {

            this->mainLayout->addWidget ( toolBtn );
          }
          break;

        case Qt::Corner::TopRightCorner: {

          /*QList<QToolButton *> allPBtns = this->findChildren<QToolButton *> ();
          if ( allPBtns.count () > 0 ) {

            for ( int i = 0; i < allPBtns.count (); i++ ) {


              this->mainLayout->removeWidget ( allPBtns.at ( i ) );
            }
            for ( int i = 0; i < allPBtns.count () - 1; i++ ) {


              this->mainLayout->addWidget ( allPBtns.at ( i ) );
            }
            this->mainLayout->addWidget ( toolBtn );
            this->mainLayout->addWidget ( allPBtns.at ( allPBtns.count () - 1 ) );

          } else {

            this->mainLayout->addWidget ( toolBtn );
          }*/
          break;
        }
        case Qt::Corner::BottomLeftCorner:

          // TODO: Falta ajustar esta esquina
          break;

        case Qt::Corner::BottomRightCorner:

          // TODO: Falta ajustar esta esquina
          break;

        default:

          // TODO: Falta ajustar esquina predeterminada
          break;
      }
    } else {

      this->mainLayout->addWidget ( toolBtn );
    }
  }
}
