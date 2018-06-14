#include "TitlieBarFloatingTab.h"

TitlieBarFloatingTab::TitlieBarFloatingTab ( QIcon icon, QString title, QWidget *parent , Qt::WindowFlags f ) : QFrame ( parent, f ) {

  // TODO: agregar los botones y acciones correspondientes a este tipo de widget
  this->setMinimumWidth ( 128 );
  this->setStyleSheet ( "background: black;" );

  this->parent = parent;
  this->mainLayout = new QHBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );

  this->titleBarIcon = new QLabel ( this );
  this->titleBarIcon->setPixmap ( icon.pixmap ( QSize ( 16, 16 ) ) );

  this->title = new QLabel ( title );
  this->title->setFixedHeight ( 16 );
  this->title->setAlignment ( Qt::AlignCenter );
  this->title->setStyleSheet ( "color: white;" );

  this->btn_size = 16;

  this->btn_close = new QPushButton ( "x" );
  connect ( this->btn_close, SIGNAL ( clicked () ), this , SLOT ( btn_close_clicked () ) );
  this->btn_close->setFixedSize ( this->btn_size, this->btn_size );
  this->btn_close->setStyleSheet ( "background-color: red;" );

  this->btn_min = new QPushButton ( "-" );
  connect ( this->btn_min, SIGNAL ( clicked () ), this , SLOT ( btn_min_clicked () ) );
  this->btn_min->setFixedSize ( this->btn_size, this->btn_size );
  this->btn_min->setStyleSheet ( "background-color: gray;" );

  this->btn_max = new QPushButton ( "+" );
  connect ( this->btn_max, SIGNAL ( clicked () ), this , SLOT ( btn_max_clicked () ) );
  this->btn_max->setFixedSize ( this->btn_size, this->btn_size );
  this->btn_max->setStyleSheet ( "background-color: gray;" );

  this->couplerBtn = new QToolButton ( this );
  this->couplerBtn->setObjectName ( "collapseBtn" );
  this->couplerBtn->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  this->couplerBtn->setStyleSheet ( "QToolButton {border: none;}" );
  this->couplerBtn->setToolButtonStyle ( Qt::ToolButtonIconOnly );
  this->couplerBtn->setArrowType ( Qt::ArrowType::RightArrow );
  this->couplerBtn->setToolTip ( "Collapse" );
  this->couplerBtn->setToolTipDuration ( 5000 );
  this->couplerBtn->setCheckable ( true );
  this->couplerBtn->setChecked ( false );
  this->couplerBtn->setMinimumSize ( 16, 16 );
  this->couplerBtn->setMaximumSize ( 16, 16 );
  connect ( this->couplerBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( windowDocker ( bool ) ) );

  this->mainLayout->addWidget ( this->titleBarIcon );
  this->mainLayout->addWidget ( this->title );
  this->mainLayout->addWidget ( this->couplerBtn );
  //this->mainLayout->addWidget ( this->btn_min );
  //this->mainLayout->addWidget ( this->btn_max );
  this->mainLayout->addWidget ( this->btn_close );

  this->setLayout ( this->mainLayout );

  this->start = QPoint ( 0, 0 );
  this->pressing = false;

  this->setMaximumHeight ( 16 );
}

QString TitlieBarFloatingTab::getTitle () const {

  return this->title->text ();
}

void TitlieBarFloatingTab::mouseMoveEvent ( QMouseEvent *event ) {

  if ( this->pressing ) {

    this->end = this->mapToGlobal ( event->pos () );
    this->movement = this->end - this->start;
    this->parent->setGeometry ( this->mapToGlobal ( this->movement ).x (), this->mapToGlobal ( this->movement ).y (), this->parent->width (), this->parent->height () );
    this->start = this->end;
    QApplication::setOverrideCursor ( Qt::SizeAllCursor );
  }
}

void TitlieBarFloatingTab::mousePressEvent ( QMouseEvent *event ) {

  this->start = this->mapToGlobal ( event->pos () );
  this->pressing = true;
}

void TitlieBarFloatingTab::mouseReleaseEvent ( QMouseEvent *event ) {

  Q_UNUSED ( event )
  this->pressing = false;
  QApplication::setOverrideCursor ( Qt::ArrowCursor );
}

void TitlieBarFloatingTab::resizeEvent ( QResizeEvent *event ) {

  QWidget::resizeEvent ( event );
}

void TitlieBarFloatingTab::btn_close_clicked () {

  this->parent->close ();
}

void TitlieBarFloatingTab::btn_max_clicked () {

  this->parent->showMaximized ();
}

void TitlieBarFloatingTab::btn_min_clicked () {

  this->parent->showMinimized ();
}

void TitlieBarFloatingTab::setTitle ( const QString &value ) {

  this->title->setText ( value );
}

void TitlieBarFloatingTab::windowDocker ( bool checked ) {

  Q_UNUSED ( checked )
  emit dockWindow ();
}
