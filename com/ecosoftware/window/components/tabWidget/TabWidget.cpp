#include "TabWidget.h"
#include <QDebug>

using namespace Com::Ecosoftware::Window::Components::TabWidget;

TabWidget::TabWidget ( bool collapsible, bool animated, TabPosition tabPosition, QWidget *parent ) : QTabWidget ( parent ) {

  // TODO: En algún punto hay que hacer lo del ejemplo del WidgetResize
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

    this->cornerTopLeft = new Corner ( QTabWidget::North, this );
    this->setCornerWidget ( this->cornerTopLeft, Qt::TopLeftCorner );
    this->cornerBottomRight = new Corner ( QTabWidget::South, this );
    this->setCornerWidget ( this->cornerBottomRight, Qt::TopRightCorner );

  } else if ( ( tabPosition == QTabWidget::East ) || ( tabPosition == QTabWidget::West ) ) {

    this->cornerTopLeft = new Corner ( QTabWidget::West, this );
    this->setCornerWidget ( this->cornerTopLeft, Qt::TopLeftCorner );
    this->cornerBottomRight = new Corner ( QTabWidget::East, this );
    this->setCornerWidget ( this->cornerBottomRight, Qt::TopRightCorner );
  }
  this->setCollapsible ( collapsible );
  this->setAnimated ( animated );
  this->setMinimumHeight ( 0 );

  //this->timerId = 0;
  //this->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding );
  //this->previousIndex = 0;
  //this->openTabWidget = true;
  //this->setCurrentIndex ( 0 );

  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( setCurrentIndex ( int ) ) );
  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( launchAnimation () ) );
  connect ( this, SIGNAL ( toCollapse ( bool ) ), this, SLOT ( onCollapse ( bool ) ) );
}

void TabWidget::addAction ( QAction *action, TabWidget::CornerPosition cornerPosition ) {

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

void TabWidget::leaveEvent ( QEvent *event ) {

  if ( event->type () == QEvent::Leave ) {

    /*if ( this->openTabWidget && this->lockedTabWidget ) {

      this->launchAnimation ();
    }*/
  }
  QWidget::leaveEvent ( event );
}

/*bool TabWidget::getLockedTabWidget () const {

  return this->lockedTabWidget;
}

bool TabWidget::getOpenTabWidget () const {

  return this->openTabWidget;
}

void TabWidget::launchAnimation () {

  if ( this->lockedTabWidget ) {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
      if ( !this->openTabWidget ) {

        this->toggleAnimation->setDirection ( this->openTabWidget ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
        this->setOpenTabWidget ( !this->openTabWidget );
        this->toggleAnimation->start ();
      }
    } else {

      this->toggleAnimation->setDirection ( this->openTabWidget ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
      this->setOpenTabWidget ( !this->openTabWidget );
      this->toggleAnimation->start ();
    }
  } else {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
    }
  }
}

int TabWidget::getPreviousHeight () const {

  return this->previousHeight;
}

void TabWidget::setPreviousHeight ( int value ) {

  this->previousHeight = value;
}*/

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

void TabWidget::setAnimated ( bool value ) {

  this->animated = value;
  // TODO: Aquí activar/desactivar la animación.
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

      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      break;
    }
    case TabWidget::Bottom: {

      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      break;
    }
    case TabWidget::Left:

      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      this->cornerTopLeft->addAction ( this->showHideTabAct );
      break;

    case TabWidget::Right:

      // TODO: Aquí se agrega la acción encontrada a la esquina indicada.
      //this->setCornerWidget ( this->corner, cornerPosition );
      this->cornerBottomRight->addAction ( this->showHideTabAct );
      break;

    default:

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

void TabWidget::launchAnimation () {

  qDebug () << "Se hizo click en el tabbar";
}

void TabWidget::onDobleClick () {

  if ( this->collapsible ) {

    // TODO: cambiar la dirección de la flecha indicadora
    if ( this->lockedTabWidget ) {

      emit toCollapse ( false );

    } else {

      emit toCollapse ( true );
    }
  }
}

void TabWidget::onCollapse ( bool onCollapse ) {

  if ( onCollapse ) {

    this->collapsed ();

  } else {

    this->uncollapsed ();
  }
}

void TabWidget::onStoppedAnimation () {

  if ( ( ( QPropertyAnimation * ) QObject::sender () )->objectName ().compare ( "MaxAnimation" ) == 0 ) {

    //this->setMaximumHeight ( 16777215 );

  } else if ( ( ( QPropertyAnimation * ) QObject::sender () )->objectName ().compare ( "MinAnimation" ) == 0 ) {

    this->setMinimumHeight ( 0 );
    this->setMaximumHeight ( 16777215 );
  }
}

void TabWidget::collapsed () {

  if ( this->isAnimated () ) {

    this->collapsedAnimated ();

  } else {

    this->collapsedUnanimated ();
  }
  this->lockedTabWidget = true;
}

void TabWidget::uncollapsed () {

  if ( this->isAnimated () ) {

    this->uncollapsedAnimated ();

  } else {

    this->uncollapsedUnanimated ();
  }
  this->lockedTabWidget = false;
}

void TabWidget::collapsedAnimated () {

  this->collapsedAnimation->start ();
}

void TabWidget::collapsedUnanimated () {

  this->previousHeight = this->height ();
  this->setMinimumHeight ( 0 );
  this->setMaximumHeight ( this->tabBar ()->height () + 2 );
}

void TabWidget::uncollapsedAnimated () {

  this->uncollapsedAnimation->start ();
}

void TabWidget::uncollapsedUnanimated () {

  this->setMinimumHeight ( this->previousHeight );
  this->setMinimumHeight ( 0 );
  this->setMaximumHeight ( 16777215 );
}

/*
void TabWidget::timerEvent ( QTimerEvent *timerEvent ) {

  qDebug () << "Entró por la línea 107";
  qDebug () << "this->lockedTabWidget ------------------------------------------" << this->lockedTabWidget;
  if ( !this->lockedTabWidget ) {

    switch ( this->tabPosition () ) {

      case QTabWidget::North:

        if ( !this->finishedAnimation ) {

          this->previousHeight = this->geometry ().height ();

        } else {

          this->parentWidget ()->setGeometry ( this->parentWidget ()->geometry ().x (), this->parentWidget ()->geometry ().y (), this->parentWidget ()->geometry ().width (), this->previousHeight );
        }
        qDebug () << "entró por el norte línea 114";
        //this->previousHeight = this->geometry ().height ();
        qDebug () << "this->geometry ().height () línea 117" << this->geometry ().height ();
        qDebug () << "this->previousHeight línea 118" << this->previousHeight;
        QThread::msleep ( 5000 );
        /*if ( ( this->toggleAnimation->state () == QAbstractAnimation::Stopped ) && ( this->toggleAnimation->direction () == QAbstractAnimation::Backward ) ) {

          qDebug () << "La animación está detenida y va en retoceso";
          //this->parentWidget ()->setGeometry ( this->parentWidget ()->x (), this->parentWidget ()->y (), this->parentWidget ()->width (), this->previousHeight );


        } else {

          qDebug () << "La animación no está detenida";
        }*/
        /**
         * entró por el norte línea 114
         * this->previousHeight 149
         * Aquí se detiene y pasa a hacer lo siguiente
         * Entró por la línea 208
         * this->previousHeight 149
         * Entró por la línea 107
         * entró por el norte línea 114
         * this->previousHeight 252
         *
         *
         *
         * entró por el norte línea 114
         * Aquí se detiene y pasa a hacer lo siguiente
         * this->previousHeight 103
         * Entró por la línea 208
         * this->previousHeight 103
         * Entró por la línea 107
         * entró por el norte línea 114
         * this->previousHeight 188
         *
         *
         *
         *
         * Entró por la línea 107
         * this->lockedTabWidget ------------------------------------------ false
         * entró por el norte línea 114
         * Aquí se detiene y pasa a hacer lo siguiente
         * this->previousHeight 89
         * Entró por la línea 208
         * this->previousHeight 89
         * Entró por la línea 107
         * this->lockedTabWidget ------------------------------------------ false
         * entró por el norte línea 114
         * this->previousHeight 157
         *
         *
         *
         *
         * Entró por la línea 107
         * this->lockedTabWidget ------------------------------------------ false
         * entró por el norte línea 114
         * La animación está detenida
         * this->previousHeight 117
         * Entró por la línea 208
         * this->previousHeight 117
         * Entró por la línea 107
         * this->lockedTabWidget ------------------------------------------ false
         * entró por el norte línea 114
         * La animación está detenida
         * this->previousHeight 163
         *//*
        this->setAnimation ();
        this->setMinimumHeight ( 0 );
        this->setMaximumHeight ( 16777215 );
        break;

      case QTabWidget::South:

        qDebug () << "entró por el sur línea 123";
        this->previousHeight = this->geometry ().height ();
        this->setAnimation ();
        this->setMinimumHeight ( 0 );
        this->setMaximumHeight ( 16777215 );
        break;

      case QTabWidget::East:

        qDebug () << "entró por el este línea 132";
        this->previousHeight = this->geometry ().width ();
        this->setAnimation ();
        this->setMinimumWidth ( 0 );
        this->setMaximumWidth ( 16777215 );
        break;

      case QTabWidget::West:

        qDebug () << "entró por el oeste línea 141";
        this->previousHeight = this->geometry ().width ();
        this->setAnimation ();
        this->setMinimumWidth ( 0 );
        this->setMaximumWidth ( 16777215 );
        break;

      default:
        break;
    }
  } else {

    switch ( this->tabPosition () ) {

      case QTabWidget::North:

        qDebug () << "entró por el norte línea 157";
        if ( this->maximumHeight () != this->parentWidget ()->geometry ().height () ) {

          this->setAnimation ();
        }
        break;

      case QTabWidget::South:

        qDebug () << "entró por el sur línea 166";
        if ( this->maximumHeight () != this->parentWidget ()->geometry ().height () ) {

          this->setAnimation ();
        }
        break;

      case QTabWidget::East:

        qDebug () << "entró por el este línea 175";
        if ( this->maximumWidth () != this->parentWidget ()->geometry ().width () ) {

          this->setAnimation ();
        }
        break;

      case QTabWidget::West:

        qDebug () << "entró por el oeste línea 184";
        if ( this->maximumWidth () != this->parentWidget ()->geometry ().width () ) {

          this->setAnimation ();
        }
        break;

      default:

        qDebug () << "entró por la línea 184";
        if ( this->maximumHeight () != this->parentWidget ()->geometry ().height () ) {

          this->setAnimation ();
        }
        break;
    }
  }
  this->killTimer ( timerEvent->timerId () );
  this->timerId = 0;
  qDebug () << "this->previousHeight línea 267" << this->previousHeight;
}*/

void TabWidget::resizeEvent ( QResizeEvent *event ) {

  QTabWidget::resizeEvent ( event );
  this->previousHeight = this->parentWidget ()->height ();
  if ( this->isAnimated () ) {

    if ( ( this->collapsedAnimation == nullptr ) || ( this->uncollapsedAnimation == nullptr ) ) {

      this->setAnimation ();

    } else {

      this->uncollapsedAnimation->setEndValue ( this->previousHeight );
      this->collapsedAnimation->setStartValue ( this->previousHeight );
    }
  }
}

void TabWidget::setAnimation () {

  if ( this->animated ) {

    this->uncollapsedAnimation = new QPropertyAnimation ( this, "minimumHeight" );
    this->uncollapsedAnimation->setObjectName ( "MinAnimation" );
    this->uncollapsedAnimation->setDuration ( 500 );
    this->uncollapsedAnimation->setEasingCurve ( QEasingCurve::OutBounce );
    this->uncollapsedAnimation->setStartValue ( this->tabBar ()->height () + 2 );
    this->uncollapsedAnimation->setEndValue ( this->previousHeight );

    this->collapsedAnimation = new QPropertyAnimation ( this, "maximumHeight" );
    this->collapsedAnimation->setObjectName ( "MaxAnimation" );
    this->collapsedAnimation->setDuration ( 500 );
    this->collapsedAnimation->setEasingCurve ( QEasingCurve::OutBounce );
    this->collapsedAnimation->setStartValue ( this->previousHeight );
    this->collapsedAnimation->setEndValue ( this->tabBar ()->height () + 2 );

    connect ( this->collapsedAnimation, SIGNAL ( finished () ), this, SLOT ( onStoppedAnimation () ) );
    connect ( this->uncollapsedAnimation, SIGNAL ( finished () ), this, SLOT ( onStoppedAnimation () ) );

  } else {


  }
}

/*void TabWidget::setAnimation () {

  /*switch ( this->tabPosition () ) {

    case QTabWidget::North: {

      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "minimumHeight" ) );
      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "maximumHeight" ) );
      QPropertyAnimation *SectionAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 0 ) );
      SectionAnimation->setDuration ( 300 );
      SectionAnimation->setStartValue ( this->previousHeight );
      SectionAnimation->setEndValue ( 0 );
      QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 1 ) );
      contentAnimation->setDuration ( 300 );
      contentAnimation->setStartValue ( 0 );
      contentAnimation->setEndValue ( this->tabBar ()->height () );
      break;
    }
    case QTabWidget::South: {

      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "minimumHeight" ) );
      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "maximumHeight" ) );
      QPropertyAnimation *SectionAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 0 ) );
      SectionAnimation->setDuration ( 300 );
      SectionAnimation->setStartValue ( this->previousHeight );
      SectionAnimation->setEndValue ( 0 );
      QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 1 ) );
      contentAnimation->setDuration ( 300 );
      contentAnimation->setStartValue ( 0 );
      contentAnimation->setEndValue ( this->tabBar ()->height () );
      break;
    }
    case QTabWidget::East: {

      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "minimumWidth" ) );
      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "maximumWidth" ) );
      QPropertyAnimation *SectionAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 0 ) );
      SectionAnimation->setDuration ( 300 );
      SectionAnimation->setStartValue ( this->previousHeight );
      SectionAnimation->setEndValue ( 0 );
      QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 1 ) );
      contentAnimation->setDuration ( 300 );
      contentAnimation->setStartValue ( 0 );
      contentAnimation->setEndValue ( this->tabBar ()->height () );
      break;
    }
    case QTabWidget::West: {

      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "minimumWidth" ) );
      this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "maximumWidth" ) );
      QPropertyAnimation *SectionAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 0 ) );
      SectionAnimation->setDuration ( 300 );
      SectionAnimation->setStartValue ( this->previousHeight );
      SectionAnimation->setEndValue ( 0 );
      QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( 1 ) );
      contentAnimation->setDuration ( 300 );
      contentAnimation->setStartValue ( 0 );
      contentAnimation->setEndValue ( this->tabBar ()->height () );
      break;
    }
    default:
      break;
  }*/
/*
  for ( int i = 0; i < toggleAnimation->animationCount () - 1; ++i ) {

    QPropertyAnimation *SectionAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( i ) );
    SectionAnimation->setDuration ( 300 );
    SectionAnimation->setStartValue ( this->previousHeight );
    SectionAnimation->setEndValue ( 0 );
  }
  QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( this->toggleAnimation->animationAt ( this->toggleAnimation->animationCount () - 1 ) );
  contentAnimation->setDuration ( 300 );
  contentAnimation->setStartValue ( 0 );
  contentAnimation->setEndValue ( this->tabBar ()->height () );
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
