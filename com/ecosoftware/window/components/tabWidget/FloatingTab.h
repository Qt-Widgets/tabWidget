#ifndef FLOATINGTAB_H
#define FLOATINGTAB_H

#include "DockDef.h"
#include "DockerWindowTitleBar.h"

#include <QIcon>
#include <QString>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <QApplication>
#include <QColor>
#include <QDragLeaveEvent>
#include <QGraphicsDropShadowEffect>
#include <QHoverEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QRubberBand>

class FloatingTab : public QWidget {

    Q_OBJECT

  public:

    enum Edge { // NUEVO

      None = 0x0,
      Left = 0x1,
      Top = 0x2,
      Right = 0x4,
      Bottom = 0x8,
      CornerTopLeft = 0x10,
      CornerTopRight = 0x20,
      CornerBottomLeft = 0x40,
      CornerBottomRight = 0x80,
    };
    Q_ENUM ( Edge ) // NUEVO
    Q_DECLARE_FLAGS ( Edges, Edge ) // NUEVO

    explicit FloatingTab ( QIcon icon, QString title, DockDef::DockLocation location, QWidget *parent = 0 );

    void addWidget ( QWidget *widget );
    QIcon getIcon () const;
    DockDef::DockLocation getLocation () const;
    QString getTitle () const;
    bool isFloating () const;
    void setFloating ( bool value, QWidget *parent = 0 );
    void setIcon ( const QIcon &value );
    void setLocation ( const DockDef::DockLocation &value );
    void setTitle ( const QString &value );

    static QString mimeType (); // NUEVO
    int getBorderWidth () const; // NUEVO
    void setBorderWidth ( int w ); // NUEVO
    //void enterEvent ( QEvent *event ) Q_DECL_OVERRIDE; // NUEVO

  signals:
    void dockWindow ( FloatingTab *dockerWindow ); // LISTO

  public slots:
    //void undockedTab ( DockerWindow *dockerWindow );
    void undockedTab ( bool undock );
    void windowDocker (); // LISTO

  protected:
    void dragEnterEvent ( QDragEnterEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void dragLeaveEvent ( QDragLeaveEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void dragMoveEvent ( QDragMoveEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void mouseMoveEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void mousePressEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void mouseReleaseEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE; // NUEVO
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE; // NUEVO

  private:
                     bool  floating;
                    QIcon  icon;
                     bool  leftButtonPressed; // NUEVO
    DockDef::DockLocation  location;
              QVBoxLayout *mainLayout;
                    Edges  overEdge = Edge::None; // NUEVO
                    Edges  pressedEdge = Edge::None; // NUEVO
                     bool  pressing;
     DockerWindowTitleBar *titleBar;

    void createTitleBar ( QIcon icon, QString title );




    //QWidget *_target = nullptr; // NUEVO
    int borderWidth; // NUEVO
    bool cursorChanged; // NUEVO
    QPoint dragPos; // NUEVO
    bool dragStart = false; // NUEVO
};
Q_DECLARE_OPERATORS_FOR_FLAGS ( DockerWindow::Edges )

#endif // FLOATINGTAB_H
