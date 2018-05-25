#include "CollapsibleTabAct.h"

using namespace Com::Ecosoftware::Window::Components::TabWidget;

CollapsibleTabAct::CollapsibleTabAct ( QString title , QWidget *parent ) : Actions::ActionAbs ( title, parent ) {

  this->setObjectName ( this->metaObject ()->className () );
  //this->setIcon ( QIcon ( ":/images/application-exit.svg" ) );
  //this->setShortcut ( QKeySequence::FullScreen );
}

void CollapsibleTabAct::execAct () {


}
