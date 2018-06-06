#include "TabWidget.h"
#include <QDebug>

using namespace Com::Ecosoftware::Window::Components::TabWidget;

TabWidget::TabWidget ( bool collapsible, bool animated, TabPosition tabPosition, QWidget *parent ) : QTabWidget ( parent ) {

  // TODO: Por si desaparece el cornerWidget
  // https://stackoverflow.com/questions/18144626/qtabwidget-corner-qtoolbutton-widget-disappearing
  // http://www.qtcentre.org/threads/12539-QTabWidget-corner-widget-is-not-shown
  // http://doc.qt.io/qt-5/qstyle.html#subElementRect
  // http://doc.qt.io/qt-5/qstyle.html#SubElement-enum
  // http://doc.qt.io/qt-5/qstyleoption.html
  // http://doc.qt.io/qt-5/style-reference.html
  //
  // https://code.woboq.org/qt5/qtbase/src/widgets/widgets/qtabwidget.cpp.html
  // https://code.woboq.org/qt5/qtbase/src/widgets/widgets/qtabwidget.h.html

  this->customTabBar = new TabBar ( this );
  connect ( this->customTabBar, SIGNAL ( onDobleClick () ), this, SLOT ( onDobleClick () ) );
  this->setTabBar ( this->customTabBar );
  this->setMovable ( true );
  this->setTabPosition ( tabPosition );
  if ( ( tabPosition == QTabWidget::North ) || ( tabPosition == QTabWidget::South ) ) {

    this->cornerTopLeft = new CornerWidget ( Qt::TopLeftCorner, QTabWidget::North, this );
    this->setCornerWidget ( this->cornerTopLeft, Qt::TopLeftCorner );
    this->cornerBottomRight = new CornerWidget ( Qt::TopRightCorner, QTabWidget::South, this );
    this->setCornerWidget ( this->cornerBottomRight, Qt::TopRightCorner );

  } else if ( ( tabPosition == QTabWidget::East ) || ( tabPosition == QTabWidget::West ) ) {

    this->cornerTopLeft = new CornerWidget ( Qt::TopLeftCorner, QTabWidget::West, this );
    this->setCornerWidget ( this->cornerTopLeft, Qt::TopLeftCorner );
    this->cornerBottomRight = new CornerWidget ( Qt::TopRightCorner, QTabWidget::East, this );
    this->setCornerWidget ( this->cornerBottomRight, Qt::TopRightCorner );
  }
  this->setCollapsible ( collapsible );
  this->setAnimated ( animated );
  this->setMinimumHeight ( 0 );
  this->setCurrentIndex ( 0 );
  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( setCurrentIndex ( int ) ) );
  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( launchAnimation () ) );
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this, SLOT ( onCollapse ( bool ) ) );
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this->cornerTopLeft, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this->cornerBottomRight, SLOT ( toggleShowHideTabWidgetBtn ( bool ) ) );
}

void TabWidget::addActionCorner ( QAction *action, TabWidget::CornerPosition cornerPosition ) {

  qDebug () << "Está entrando por el addAction del TabWidget";
  switch ( cornerPosition ) {

    case TabWidget::Top:

      this->cornerTopLeft->addAction ( action );
      break;

    case TabWidget::Bottom:

      this->cornerBottomRight->addAction ( action );
      break;

    case TabWidget::Left:

      this->cornerTopLeft->addAction ( action );
      break;

    case TabWidget::Right:

      this->cornerBottomRight->addAction ( action );
      break;

    default:

      this->cornerBottomRight->addAction ( action );
      break;
  }
}

void TabWidget::collapsed () {

  if ( this->isAnimated () ) {

    this->collapsedAnimated ();

  } else {

    this->collapsedUnanimated ();
  }
  this->lockedTabWidget = true;
  this->openTabWidget = false;
}

void TabWidget::collapsedAnimated () {

  this->collapsedAnimation->start ();
}

void TabWidget::collapsedUnanimated () {

  if ( ( this->tabPosition () == QTabWidget::North ) || ( this->tabPosition () == QTabWidget::South ) ) {

    this->previousHeight = this->height ();
    this->setMinimumHeight ( 0 );
    this->setMaximumHeight ( this->tabBar ()->height () + 2 );

  } else if ( ( this->tabPosition () == QTabWidget::East ) || ( this->tabPosition () == QTabWidget::West ) ) {

    this->previousHeight = this->width ();
    this->setMinimumWidth ( 0 );
    this->setMaximumWidth ( this->tabBar ()->width () + 2 );
  }
}

TabWidget::CornerPosition TabWidget::getIndicatorPosition () const {

  return this->indicatorPosition;
}

bool TabWidget::isAnimated () const {

  return this->animated;
}

bool TabWidget::isCollapsible () const {

  return this->collapsible;
}

bool TabWidget::isFloating () const {

  return this->floating;
}

void TabWidget::launchAnimation () {

  if ( this->lockedTabWidget ) {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
    }
    if ( !this->openTabWidget ) {

      this->uncollapsed ();
      this->lockedTabWidget = true;
    }
  } else {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
    }
  }
}

void TabWidget::leaveEvent ( QEvent *event ) {

  if ( event->type () == QEvent::Leave ) {

    if ( this->openTabWidget && this->lockedTabWidget ) {

      this->collapsed ();
    }
  }
  QWidget::leaveEvent ( event );
}

void TabWidget::onCollapse ( bool onCollapse ) {

  if ( onCollapse ) {

    this->collapsed ();

  } else {

    this->uncollapsed ();
  }
}

void TabWidget::onDobleClick () {

  if ( this->collapsible ) {

    if ( this->lockedTabWidget ) {

      emit toCollapse ( false );

    } else {

      emit toCollapse ( true );
    }
  }
}

void TabWidget::onStoppedAnimation () {

  if ( ( ( QPropertyAnimation * ) QObject::sender () )->objectName ().compare ( "collapsedAnimation" ) == 0 ) {

    //this->setMaximumHeight ( 16777215 );

  } else if ( ( ( QPropertyAnimation * ) QObject::sender () )->objectName ().compare ( "uncollapsedAnimation" ) == 0 ) {

    if ( ( this->tabPosition () == QTabWidget::North ) || ( this->tabPosition () == QTabWidget::South ) ) {

      this->setMinimumHeight ( 0 );
      this->setMaximumHeight ( 16777215 );

    } else if ( ( this->tabPosition () == QTabWidget::East ) || ( this->tabPosition () == QTabWidget::West ) ) {

      this->setMinimumWidth ( 0 );
      this->setMaximumWidth ( 16777215 );
    }
  }
}

void TabWidget::resizeEvent ( QResizeEvent *event ) {

  QTabWidget::resizeEvent ( event );
  if ( ( this->tabPosition () == QTabWidget::North ) || ( this->tabPosition () == QTabWidget::South ) ) {

    this->previousHeight = this->parentWidget ()->height ();

  } else if ( ( this->tabPosition () == QTabWidget::East ) || ( this->tabPosition () == QTabWidget::West ) ) {

    this->previousHeight = this->parentWidget ()->width ();
  }
  if ( this->isAnimated () ) {

    if ( ( this->collapsedAnimation == nullptr ) || ( this->uncollapsedAnimation == nullptr ) ) {

      this->setAnimation ();

    } else {

      this->uncollapsedAnimation->setEndValue ( this->previousHeight );
      this->collapsedAnimation->setStartValue ( this->previousHeight );
    }
  }
}

void TabWidget::showEvent ( QShowEvent *event ) {

  Q_UNUSED ( event )
  if ( ( this->tabPosition () == QTabWidget::North ) || ( this->tabPosition () == QTabWidget::South ) ) {

    this->minimunValue = this->tabBar ()->height () + 2;

  } else if ( ( this->tabPosition () == QTabWidget::East ) || ( this->tabPosition () == QTabWidget::West ) ) {

    this->minimunValue = this->tabBar ()->width () + 2;
  }
  this->collapsedAnimation->setEndValue ( this->minimunValue );
  this->uncollapsedAnimation->setStartValue ( this->minimunValue );
}

void TabWidget::setAnimated ( bool value ) {

  this->animated = value;
  // TODO: Aquí activar/desactivar la animación.
}

void TabWidget::setAnimation () {

  if ( this->animated ) {

    switch ( this->tabPosition () ) {

      case QTabWidget::North:

        this->collapsedAnimation = new QPropertyAnimation ( this, "maximumHeight" );
        this->collapsedAnimation->setStartValue ( this->previousHeight );
        this->collapsedAnimation->setEndValue ( this->minimunValue );
        this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumHeight" );
        this->uncollapsedAnimation->setStartValue ( this->minimunValue );
        this->uncollapsedAnimation->setEndValue ( this->previousHeight );
        break;

      case QTabWidget::South:

        this->collapsedAnimation = new QPropertyAnimation ( this, "maximumHeight" );
        this->collapsedAnimation->setStartValue ( this->previousHeight );
        this->collapsedAnimation->setEndValue ( this->minimunValue );
        this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumHeight" );
        this->uncollapsedAnimation->setStartValue ( this->minimunValue );
        this->uncollapsedAnimation->setEndValue ( this->previousHeight );
        break;

      case QTabWidget::East:

        this->collapsedAnimation = new QPropertyAnimation ( this, "maximumWidth" );
        this->collapsedAnimation->setStartValue ( this->previousHeight );
        this->collapsedAnimation->setEndValue ( this->minimunValue );
        this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumWidth" );
        this->uncollapsedAnimation->setStartValue ( this->minimunValue );
        this->uncollapsedAnimation->setEndValue ( this->previousHeight );
        break;

      case QTabWidget::West:

        this->collapsedAnimation = new QPropertyAnimation ( this, "maximumWidth" );
        this->collapsedAnimation->setStartValue ( this->previousHeight );
        this->collapsedAnimation->setEndValue ( this->minimunValue );
        this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumWidth" );
        this->uncollapsedAnimation->setStartValue ( this->minimunValue );
        this->uncollapsedAnimation->setEndValue ( this->previousHeight );
        break;

      default:

        this->collapsedAnimation = new QPropertyAnimation ( this, "maximumHeight" );
        this->collapsedAnimation->setStartValue ( this->previousHeight );
        this->collapsedAnimation->setEndValue ( this->tabBar ()->height () + 2 );
        this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumHeight" );
        this->uncollapsedAnimation->setStartValue ( this->tabBar ()->height () + 2 );
        this->uncollapsedAnimation->setEndValue ( this->previousHeight );
        break;
    }
    this->uncollapsedAnimation->setObjectName ( "uncollapsedAnimation" );
    this->uncollapsedAnimation->setDuration ( 500 );
    this->uncollapsedAnimation->setEasingCurve ( QEasingCurve::OutBounce );
    this->collapsedAnimation->setObjectName ( "collapsedAnimation" );
    this->collapsedAnimation->setDuration ( 500 );
    this->collapsedAnimation->setEasingCurve ( QEasingCurve::OutBounce );
    connect ( this->collapsedAnimation, SIGNAL ( finished () ), this, SLOT ( onStoppedAnimation () ) );
    connect ( this->uncollapsedAnimation, SIGNAL ( finished () ), this, SLOT ( onStoppedAnimation () ) );

  } else {

    if ( ( this->collapsedAnimation != nullptr ) && ( this->uncollapsedAnimation != nullptr ) ) {

      delete this->collapsedAnimation;
      delete this->uncollapsedAnimation;
      this->collapsedAnimation = nullptr;
      this->uncollapsedAnimation = nullptr;
    }
  }
}

void TabWidget::setCollapsible ( bool value ) {

  this->collapsible = value;
  // TODO: Aquí activar/desactivar la contracción de las pestañas.
  // TODO: Inicialmente se asigna el indicador del lado derecho.
  qDebug () << "Está entrando por el setCollapsible";
  // if ( ( this->collapsible ) && ( this->showHideAct = nullptr ) )
  if ( this->collapsible ) {

    if ( this->showHideTabAct == nullptr ) {

      // TODO: Crear la acción.
      this->showHideTabAct = new ShowHideTabAct ( "Collapse", this );
      connect ( this->showHideTabAct, SIGNAL ( triggered ( bool ) ), this, SLOT ( onCollapse ( bool ) ) );
      qDebug () << "Está creando la acción";

    } else {

      // TODO: Lanzar el setIndicatorPosition
      // Quiere decir que se ha removido de las esquinas y está oculto, validar que sea así.
    }
    //this->setIndicatorPosition ( TabWidget::Left );
    this->setIndicatorPosition ( TabWidget::Right );

  } else {

    if ( this->showHideTabAct != nullptr ) {

      // TODO: Buscarlo y ocultarlo y quitarlo de la esquina donde se encuentre ubicado.
    }
  }
}

void TabWidget::setDuration ( int msecs ) {

  if ( ( this->collapsedAnimation != nullptr ) && ( this->uncollapsedAnimation != nullptr ) ) {

    this->collapsedAnimation->setDuration ( msecs );
    this->uncollapsedAnimation->setDuration ( msecs );
  }
}

void TabWidget::setEasingCurve ( const QEasingCurve &easing ) {

  if ( ( this->collapsedAnimation != nullptr ) && ( this->uncollapsedAnimation != nullptr ) ) {

    this->collapsedAnimation->setEasingCurve ( easing );
    this->uncollapsedAnimation->setEasingCurve ( easing );
  }
}

void TabWidget::setFloating ( bool value ) {

  this->floating = value;
}

void TabWidget::setIndicatorPosition ( CornerPosition cornerPosition ) {

  qDebug () << "Está entrando al setIndicatorPosition";
  if ( this->indicatorPosition != CornerPosition::None ) {

    // TODO: Aquí obtener la acción indicadora expandir/contraer y reasignarla a la nueva posición indicada
    QList<QToolButton *> allPButtons;
    switch ( cornerPosition ) {

      case TabWidget::Top: {

        // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
        //this->setCornerWidget ( this->corner, cornerPosition );
        allPButtons = this->cornerBottomRight->findChildren<QToolButton *> ();
        break;
      }
      case TabWidget::Bottom: {

        // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
        //this->setCornerWidget ( this->corner, cornerPosition );
        allPButtons = this->cornerTopLeft->findChildren<QToolButton *> ();
        break;
      }
      case TabWidget::Left:

        // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
        //this->setCornerWidget ( this->corner, cornerPosition );
        //this->cornerTopLeft->addAction ( this->showHideTabAct );
        allPButtons = this->cornerBottomRight->findChildren<QToolButton *> ();
        if ( allPButtons.count () > 0 ) {

          qDebug () << "Si hay botones";
        }
        break;

      case TabWidget::Right:

        // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
        //this->setCornerWidget ( this->corner, cornerPosition );
        //this->cornerBottomRight->addAction ( this->showHideTabAct );
        allPButtons = this->cornerTopLeft->findChildren<QToolButton *> ();
        break;

      default:

        // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
        //this->setCornerWidget ( this->corner, cornerPosition );
        break;
    }
  }
  this->indicatorPosition = cornerPosition;

  switch ( cornerPosition ) {

    case TabWidget::Top: {

      qDebug () << "Entrando por la línea 424";
      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      break;
    }
    case TabWidget::Bottom: {

      qDebug () << "Entrando por la línea 431";
      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      break;
    }
    case TabWidget::Left:

      qDebug () << "Entrando por la línea 438";
      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      this->cornerTopLeft->addAction ( this->showHideTabAct );
      break;

    case TabWidget::Right:

      qDebug () << "Entrando por la línea 446";
      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      this->cornerBottomRight->addAction ( this->showHideTabAct );
      break;

    default:

      qDebug () << "Entrando por la línea 453";
      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      break;
  }
  //this->setCornerWidget ( this->corner, cornerPosition );
}

void TabWidget::setTabPosition ( QTabWidget::TabPosition tabPosition ) {

  QTabWidget::setTabPosition ( tabPosition );
  //this->corner->updateArrowDirection ();
}

void TabWidget::uncollapsed () {

  if ( this->isAnimated () ) {

    this->uncollapsedAnimated ();

  } else {

    this->uncollapsedUnanimated ();
  }
  this->lockedTabWidget = false;
  this->openTabWidget = true;
}

void TabWidget::uncollapsedAnimated () {

  this->uncollapsedAnimation->start ();
}

void TabWidget::uncollapsedUnanimated () {

  if ( ( this->tabPosition () == QTabWidget::North ) || ( this->tabPosition () == QTabWidget::South ) ) {

    this->setMinimumHeight ( this->previousHeight );
    this->setMinimumHeight ( 0 );
    this->setMaximumHeight ( 16777215 );

  } else if ( ( this->tabPosition () == QTabWidget::East ) || ( this->tabPosition () == QTabWidget::West ) ) {

    this->setMinimumWidth ( this->previousHeight );
    this->setMinimumWidth ( 0 );
    this->setMaximumWidth ( 16777215 );
  }
}

/*bool TabWidget::getLockedTabWidget () const {

  return this->lockedTabWidget;
}

bool TabWidget::getOpenTabWidget () const {

  return this->openTabWidget;
}

int TabWidget::getPreviousHeight () const {

  return this->previousHeight;
}

void TabWidget::setPreviousHeight ( int value ) {

  this->previousHeight = value;
}

void TabWidget::setCornerWidget ( QWidget *widget, Qt::Corner corner ) {

  QTabWidget::setCornerWidget ( widget, corner );
  ( ( TabWidgetCorner * ) widget )->updateArrowType ();
}

void TabWidget::setLockedTabWidget ( bool value ) {

  this->lockedTabWidget = value;
}

void TabWidget::setOpenTabWidget ( bool value ) {

  this->openTabWidget = value;
}*/
