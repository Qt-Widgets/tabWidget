#include "FloatingTab.h"
#include <QDebug>

FloatingTab::FloatingTab ( QIcon icon, QString title, DockDef::DockLocation location, QWidget *parent ) : QWidget ( parent ) {

  this->mainLayout = new QVBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  this->mainLayout->addStretch ( -1 );
  this->setLayout ( this->mainLayout );
  this->setAcceptDrops ( true );
  //this->setMinimumSize ( 200, 200 );
  this->setWindowFlags ( Qt::FramelessWindowHint );
  this->pressing = false;
  this->createTitleBar ( icon, title );
  this->setFloating ( false );
  this->setIcon ( icon );
  this->setTitle ( title );
  this->setLocation ( location );
  //this->addWidget ( new QWidget ( this ) );





  // NUEVO
  this->cursorChanged = false;
  this->leftButtonPressed = false;
  this->borderWidth = 5;
  this->dragPos = QPoint ();
  this->setMouseTracking ( true );
  //this->setWindowFlags ( Qt::FramelessWindowHint );
  this->setAttribute ( Qt::WA_Hover );
  //this->installEventFilter ( this );
  //this->rubberBand = new QRubberBand ( QRubberBand::Rectangle );
}

void FloatingTab::addWidget ( QWidget *widget ) {

  this->mainLayout->addWidget ( widget, 1, Qt::AlignBottom );
}

void FloatingTab::createTitleBar ( QIcon icon, QString title ) {

  this->titleBar = new DockerWindowTitleBar ( icon, title, this );
  connect ( this->titleBar, SIGNAL ( dockWindow () ), this, SLOT ( windowDocker () ) );
  this->mainLayout->addWidget ( this->titleBar, 1, Qt::AlignTop );
}

QIcon FloatingTab::getIcon () const {

  return this->icon;
}

DockDef::DockLocation FloatingTab::getLocation () const {

  return this->location;
}

QString FloatingTab::getTitle () const {

  return this->titleBar->getTitle ();
}

bool FloatingTab::isFloating () const {

  return this->floating;
}

void FloatingTab::setFloating ( bool value, QWidget *parent ) {

  this->floating = value;
  this->titleBar->setVisible ( this->floating );
  this->setParent ( parent );

  if ( this->floating ) {

    this->setWindowFlags ( Qt::Tool | Qt::FramelessWindowHint );
    // NUEVO
    //this->setAttribute ( Qt::WA_TranslucentBackground );
    /*QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect ( this );
    shadowEffect->setBlurRadius ( 4.0 );
    shadowEffect->setColor ( QColor ( 0, 0, 0 ) );
    shadowEffect->setOffset ( 1.0 );
    this->setGraphicsEffect ( shadowEffect );*/
    this->show ();

  } else {

    //this->setAttribute ( Qt::WA_TranslucentBackground, false );
    //this->setGraphicsEffect ( new QGraphicsDropShadowEffect );
  }
}

void FloatingTab::setIcon ( const QIcon &value ) {

  this->icon = value;
}

void FloatingTab::setLocation ( const DockDef::DockLocation &value ) {

  this->location = value;
}

void FloatingTab::setTitle ( const QString &value ) {

  this->titleBar->setTitle ( value );
}

QString FloatingTab::mimeType () {

  return QStringLiteral ( "application/x-DockBar" );
}

void FloatingTab::dragEnterEvent ( QDragEnterEvent *event ) {

  // TODO: ESTO NO VÁ
  qDebug () << "La ventana si está recibiendo el evento DockerWindow::dragEnterEvent ////////////////////////////";
  if ( event->mimeData ()->hasFormat ( FloatingTab::mimeType () ) ) {

    event->acceptProposedAction ();
  }
}

void FloatingTab::dragLeaveEvent ( QDragLeaveEvent *event ) {

  qDebug () << "La ventana si está recibiendo el evento ////////////////////////////";
}

void FloatingTab::dragMoveEvent(QDragMoveEvent *event)
{

  qDebug () << "La ventana si está recibiendo el evento /////////////DockerWindow::dragMoveEvent///////////////";
}

int FloatingTab::getBorderWidth () const {

  return this->borderWidth;
}

void FloatingTab::mouseMoveEvent ( QMouseEvent *event ) {

  // TODO: https://stackoverflow.com/questions/5752408/qt-resize-borderless-widget
  if ( this->floating ) {

    if ( this->pressedEdge.testFlag ( Edge::None ) ) {

      if ( event->localPos ().x () <= 5 ) {

        if ( event->localPos ().y () <= 5 ) {

          QApplication::setOverrideCursor ( Qt::SizeBDiagCursor );
          this->overEdge = Edge::CornerBottomLeft;
          qDebug () << "Estoy en el borde superior izquierdo";

        } else if ( ( this->frameGeometry ().height () - event->localPos ().y () ) <= 5 ) {

          QApplication::setOverrideCursor ( Qt::SizeBDiagCursor );
          this->overEdge = Edge::CornerBottomLeft;

        } else {

          QApplication::setOverrideCursor ( Qt::SizeHorCursor );
          this->overEdge = Edge::Left;
        }
      } else if ( ( this->frameGeometry ().width () - event->localPos ().x () ) <= 5 ) {

        if ( event->windowPos ().y () <= 5 ) {

          QApplication::setOverrideCursor ( Qt::SizeFDiagCursor );
          this->overEdge = Edge::CornerBottomRight;
          qDebug () << "Estoy en el borde superior derecho";

        } else if ( ( this->frameGeometry ().height () - event->localPos ().y () ) <= 5 ) {

          QApplication::setOverrideCursor ( Qt::SizeFDiagCursor );
          this->overEdge = Edge::CornerBottomRight;

        } else {

          QApplication::setOverrideCursor ( Qt::SizeHorCursor );
          this->overEdge = Edge::Right;
        }

      } else if ( ( this->frameGeometry ().height () - event->localPos ().y () ) <= 5 ) {

        if ( ( event->windowPos ().x () <= 5 ) || ( ( this->frameGeometry ().width () - event->localPos ().x () ) <= 5 ) ) {

          QApplication::setOverrideCursor ( Qt::SizeFDiagCursor );
          this->overEdge = Edge::CornerBottomLeft;

        } else {

          QApplication::setOverrideCursor ( Qt::SizeVerCursor );
          this->overEdge = Edge::Bottom;
        }

      } else {

        QApplication::setOverrideCursor ( Qt::ArrowCursor );
        this->overEdge = Edge::None;
      }
    } else {

      if ( this->leftButtonPressed ) {

        int left = this->frameGeometry ().left ();
        int top = this->frameGeometry ().top ();
        int right = this->frameGeometry ().right ();
        int bottom = this->frameGeometry ().bottom ();

        switch ( this->pressedEdge ) {

          case Edge::Top:

            top = event->globalPos ().y ();
            break;

          case Edge::Bottom:

            bottom = event->globalPos ().y ();
            break;

          case Edge::Left:

            left = event->globalPos ().x ();
            break;

          case Edge::Right:

            right = event->globalPos ().x ();
            break;

          case Edge::CornerTopLeft:

            top = event->globalPos ().y ();
            left = event->globalPos ().x ();
            break;

          case Edge::CornerTopRight:

            right = event->globalPos ().x ();
            top = event->globalPos ().y ();
            break;

          case Edge::CornerBottomLeft:

            bottom = event->globalPos ().y ();
            left = event->globalPos ().x ();
            break;

          case Edge::CornerBottomRight:

            bottom = event->globalPos ().y ();
            right = event->globalPos ().x ();
            break;
        }
        QRect auxRect ( QPoint ( left, top ), QPoint ( right, bottom ) );
        if ( auxRect.width () < this->minimumWidth () ) {

          left = this->frameGeometry ().x ();

        } else if ( auxRect.height () < this->minimumHeight () ) {

          top = this->frameGeometry ().y ();
        }
        this->setGeometry ( QRect ( QPoint ( left, top ), QPoint ( right, bottom ) ) );
      }
    }
  } else {

    /*qDebug () << "event->pos (): " << event->pos ();
    qDebug () << "event->localPos (): " << event->localPos ();
    qDebug () << "event->globalPos (): " << event->globalPos ();*/
  }
}

void FloatingTab::mousePressEvent ( QMouseEvent *event ) {

  // TODO: https://stackoverflow.com/questions/5752408/qt-resize-borderless-widget
  if ( this->floating ) {

    this->pressedEdge = this->overEdge;
    this->leftButtonPressed = event->button () == Qt::LeftButton;
  }
}

void FloatingTab::mouseReleaseEvent ( QMouseEvent *event ) {

  if ( this->floating ) {

    this->pressedEdge = Edge::None;
    this->overEdge = Edge::None;
    this->leftButtonPressed = false;
    qDebug () << "Se liberó siendo una ventana flotante: ";
  } else {

    qDebug () << "Se liberó siendo una ventana NO flotante: ";
  }
}

void FloatingTab::setBorderWidth ( int w ) {

  this->borderWidth = w;
}

void FloatingTab::leaveEvent ( QEvent *event ) {

  if ( this->floating ) {

    this->unsetCursor ();
    QApplication::setOverrideCursor ( Qt::ArrowCursor );
  }
}

void FloatingTab::undockedTab ( bool undock ) {

  qDebug () << "Si se activó el slot";
  this->setFloating ( undock );
}

void FloatingTab::windowDocker () {

  this->setFloating ( false );
  emit dockWindow ( this );
}
