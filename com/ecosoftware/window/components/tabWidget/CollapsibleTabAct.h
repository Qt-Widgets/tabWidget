#ifndef COLLAPSIBLETABACT_H
#define COLLAPSIBLETABACT_H

// Librerías Internas
#include "TabWidget_global.h"

// Librerías Externas
#include "ActionAbs.h"

namespace Com {

  namespace Ecosoftware {

    namespace Window {

      namespace Components {

        namespace TabWidget {

          class TABWIDGETSHARED_EXPORT CollapsibleTabAct : public Actions::ActionAbs {

              Q_OBJECT

            public:
              Q_INVOKABLE CollapsibleTabAct ( QString title, QWidget *parent );

            public slots:
              void execAct ();
          };
        }
      }
    }
  }
}

#endif // COLLAPSIBLETABACT_H
