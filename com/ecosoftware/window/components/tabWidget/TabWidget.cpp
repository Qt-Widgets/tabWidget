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
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this->cornerTopLeft, SLOT ( onToggle ( bool ) ) );
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this->cornerBottomRight, SLOT ( onToggle ( bool ) ) );
}

void TabWidget::addActionCorner ( QAction *action, TabWidget::CornerPosition cornerPosition ) {

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

      //this->cornerBottomRight->addAction ( action );
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

bool TabWidget::isTabLocked () const {

  return this->lockedTabWidget;
}

bool TabWidget::isTabOpened () const {

  return this->openTabWidget;
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

void TabWidget::removeShowHideBtn () {

  QToolButton *toolButton;
  QString objectNameBtn = "Com::Ecosoftware::Window::Components::TabWidget::ShowHideTabActBtn";
  switch ( this->indicatorPosition ) {

    case TabWidget::Top:
    case TabWidget::Left:

      toolButton = this->cornerTopLeft->findChild<QToolButton *> ( objectNameBtn );
      if ( toolButton != 0 ) {

        this->cornerTopLeft->layout ()->removeWidget ( toolButton );
      }
      break;

    case TabWidget::Bottom:
    case TabWidget::Right:

      toolButton = this->cornerBottomRight->findChild<QToolButton *> ( objectNameBtn );
      if ( toolButton != 0 ) {

        this->cornerBottomRight->layout ()->removeWidget ( toolButton );
      }
      break;

    default:

      toolButton = this->cornerBottomRight->findChild<QToolButton *> ( objectNameBtn );
      if ( toolButton != 0 ) {

        this->cornerBottomRight->layout ()->removeWidget ( toolButton );
      }
      break;
  }
  if ( toolButton != 0 ) {

    delete toolButton;
    toolButton = nullptr;
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
  if ( this->collapsible ) {

    if ( this->showHideTabAct == nullptr ) {

      this->showHideTabAct = new ShowHideTabAct ( "Collapse", this );
      connect ( this->showHideTabAct, SIGNAL ( triggered ( bool ) ), this, SLOT ( onCollapse ( bool ) ) );

    } else {

      switch ( this->tabPosition () ) {

        case QTabWidget::North:
        case QTabWidget::South:

          this->setIndicatorPosition ( TabWidget::Right );
          break;

        case QTabWidget::East:
        case QTabWidget::West:

          this->setIndicatorPosition ( TabWidget::Top );
          break;

        default:

          this->setIndicatorPosition ( TabWidget::Right );
          break;
      }
    }
  } else {

    if ( this->showHideTabAct != nullptr ) {

      this->removeShowHideBtn ();
      this->setIndicatorPosition ( TabWidget::None );
      this->setAnimated ( false );
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

  if ( this->isCollapsible () ) {

    if ( this->indicatorPosition != CornerPosition::None ) {

      this->removeShowHideBtn ();

    } else {

      this->indicatorPosition = cornerPosition;
    }
    switch ( cornerPosition ) {

      case TabWidget::Top:
      case TabWidget::Left:

        this->cornerTopLeft->addAction ( this->showHideTabAct );
        break;

      case TabWidget::Bottom:
      case TabWidget::Right:

        this->cornerBottomRight->addAction ( this->showHideTabAct );
        break;

      default:

        //this->cornerBottomRight->addAction ( this->showHideTabAct );
        break;
    }
  }
}

void TabWidget::setTabPosition ( QTabWidget::TabPosition tabPosition ) {

  QTabWidget::setTabPosition ( tabPosition );
  //this->corner->updateArrowDirection ();
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
