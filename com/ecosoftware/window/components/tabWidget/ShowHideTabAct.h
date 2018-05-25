#ifndef SHOWHIDETABACT_H
#define SHOWHIDETABACT_H

// Librerías Internas
#include "TabWidget_global.h"

// Librerías Externas
#include "ActionAbs.h"

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT ShowHideTabAct : public Actions::ActionAbs {

              Q_OBJECT

            public:
              Q_INVOKABLE ShowHideTabAct ( QString title, QWidget *parent );

            public slots:
              void execAct ();
          };
        }
      }
    }
  }
}

#endif // SHOWHIDETABACT_H
