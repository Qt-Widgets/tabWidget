#ifndef TITLIEBARFLOATINGTAB_H
#define TITLIEBARFLOATINGTAB_H

#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>
#include <QToolButton>
#include <QWidget>

class TitlieBarFloatingTab : public QFrame {

    Q_OBJECT

  public:
    explicit TitlieBarFloatingTab ( QIcon icon, QString title, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags () );

    QString getTitle () const;
    void setTitle ( const QString &value );

  public slots:
    void btn_close_clicked ();
    void btn_max_clicked ();
    void btn_min_clicked ();
    void windowDocker ( bool checked );

  signals:
    void dockWindow ();

  protected:
    void mouseMoveEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void mousePressEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void mouseReleaseEvent ( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE;

  private:
    QPushButton *btn_close;
    QPushButton *btn_max;
    QPushButton *btn_min;
            int  btn_size;
    QToolButton *couplerBtn;
         QPoint  end;
    QHBoxLayout *mainLayout;
         QPoint  movement;
        QWidget *parent;
           bool  pressing;
         QLabel *title;
         QLabel *titleBarIcon;
         QPoint  start;
};

#endif // TITLIEBARFLOATINGTAB_H
