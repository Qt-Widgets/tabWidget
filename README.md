# tabWidget
Sistema de pestañas basado en QTabWidget para extender su funcionalidad ( Tab system based on QTabWidget to extend its functionality ).

TabWidget has the following characteristics:

- Permite expandir/contraer el área de la página de la pestaña a mostrar ( It allows to expand/contract the area of the page of the tab to be displayed ).
- Permite bloquear el área de la página de la pestaña a mostrar, manteniendola contraida ( It allows to block the area of the page of the tab to be displayed, keeping it contracted ).
- Permite expandir/contraer el área de la página de la pestaña a mostrar mediante animación o sin ella ( It allows you to expand/collapse the page area of the tab to be displayed by animation or without it ).
- Permite desacoplar la pestaña, convirtiendola en una ventana flotante en las diferentes modalidades de ventanas permitidas por Qt y una nueva presentación personalizada mediante D&D ( It allows decoupling the tab, converting it into a floating window in the different modalities of windows allowed by Qt and a new personalized presentation through D&D ).
- Permite acoplar la ventana flotante nuevamente a una pestaña ( It allows you to dock the floating window back to a tab ).
- Permite D&D entre otros TabWidget ( Allows D&D among others TabWidget ).
- Permite agregar acciones en las esquinas izquierda/derecha ( It allows adding actions in the left/right corners ).
- Se espera pueda permitir agregar acciones en las esquinas superior/inferior para posiciones verticales ( It is expected that you can allow adding actions in the upper/lower corners for vertical positions ).

Por ahora solo funciona correctamente con TabPosition::North, para TabPosition::South el comportamiento no es el deseable y como la documentación lo dice, "Los widgets de esquina están diseñados para las posiciones de pestañas norte y sur; se sabe que otras orientaciones no funcionan correctamente.", y este intento por extender funcionalidades al QTabWidget no es la excepción, por lo que las posiciones TabPosition::West y TabPosition::East no funcionan.

(For now it only works correctly with TabPosition::North, for TabPosition::South the behavior is not desirable and as the documentation says, "The corner widgets are designed for the north and south tab positions, it is known that other orientations they do not work properly.", and this attempt to extend functionality to the QTabWidget is no exception, so the TabPosition::West and TabPosition::East positions do not work).

### TODO


- [x] Permite expandir/contraer el área de la página de la pestaña a mostrar ( It allows to expand/contract the area of the page of the tab to be displayed ).
- [x] Permite bloquear el área de la página de la pestaña a mostrar, manteniendola contraida ( It allows to block the area of the page of the tab to be displayed, keeping it contracted ).
- [x] Permite expandir/contraer el área de la página de la pestaña a mostrar mediante animación o sin ella ( It allows you to expand/collapse the page area of the tab to be displayed by animation or without it ).
- [ ] Permite desacoplar la pestaña, convirtiendola en una ventana flotante en las diferentes modalidades de ventanas permitidas por Qt y una nueva presentación personalizada mediante D&D ( It allows decoupling the tab, converting it into a floating window in the different modalities of windows allowed by Qt and a new personalized presentation through D&D ).
- [ ] Permite acoplar la ventana flotante nuevamente a una pestaña ( It allows you to dock the floating window back to a tab ).
- [ ] Permite D&D entre otros TabWidget ( Allows D&D among others TabWidget ).
- [ ] Permite agregar acciones en las esquinas izquierda/derecha ( It allows adding actions in the left/right corners ).
- [ ] Se espera pueda permitir agregar acciones en las esquinas superior/inferior para posiciones verticales ( It is expected that you can allow adding actions in the upper/lower corners for vertical positions ).
- [x] La animación necesita ser ajustada después que las dimensiones del QTabWidget han sido modificadas (The animation needs to be adjusted after the dimensions of the QTabWidget have been modified).
- [ ] Adaptar el código para poder ser utilizado desde QtDesigner (Adapt the code to be used from QtDesigner).
- [ ] Adaptar el código a qt-plugin-system (Adapt the code to qt-plugin-system).
- [ ] Hacer de forma transparente, que al colapsar el QTabWidget se redimensione su contenedor padre (Make it transparent, so that when the QTabWidget collapses its parent container is resized). Al colapsar el QTabWidget, permitir se redimensione el contenedor padre no está implementado aun (When the QTabWidget collapses, allowing the parent container to be resized is not implemented yet).
- [ ] Documentar el código (Document the code).
- [x] Ajustar el comportamiento/animación del botón de la esquina de acuerdo a la posición Izquierda/Derecha ( Adjust the behavior/animation of the corner button according to the Left/Right position ).
- [ ] Ajustar el comportamiento/animación del botón de la esquina de acuerdo a la posición de las pestañas Norte/Sur ( Adjust the behavior/animation of the corner button according to the position of the North/South tabs. ).
- [ ] Permitir arrastrar y soltar pestañas y convertirlas en una ventana flotante ( Allow drag and drop tabs and turn them into a floating window ).
- [ ] Permitir convertir pestañas y convertirlas en una ventana flotante la hacer docle click, este punto excluye al punto siguiente ( Allow to convert tabs and turn them into a floating window do click click, this point excludes the next point ).
- [x] Permitir colapsar/descolapsar las pestañas al hacer doble click, este punto excluye al punto anterior ( Allow collapsing/uncollapsing the tabs by double clicking, this point excludes the previous point ).
