#include "ShowHideTabAct.h"

using namespace Com::Ecosoftware::Window::Components::TabWidget;

ShowHideTabAct::ShowHideTabAct ( QString title , QWidget *parent ) : Actions::ActionAbs ( title, parent ) {

  this->setObjectName ( this->metaObject ()->className () );
  //this->setIcon ( QIcon ( ":/images/application-exit.svg" ) );
  //this->setShortcut ( QKeySequence::FullScreen );
  this->setCheckable ( true );
  this->setChecked ( false );
}

void ShowHideTabAct::execAct () {

  this->setToolTip ( this->isChecked () ? "Uncollapse" : "Collapse" );
}
