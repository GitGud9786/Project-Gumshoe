#ifndef MAINFORM_H
#define MAINFORM_H
#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();
    void mov_ins(QString &title,QString &genre,QString &year,QString &tyme,QString &stat);
    void book_ins(QString &title,QString &genre,QString &author,QString &year,QString &chapter,QString &page,QString &currpage);
    void tvshow_ins(QString &title, QString &genre, QString &year, QString &runtime, QString &tepisode, QString &currepisode);
    void searcher();

    class nosearch{};
    class emptyinputs
    {
    };

    class numinputs
    {
    };

    class lessthan
    {
    };

    class movstatus
    {
    };

private slots:
    void on_accounbutton_clicked();

    void on_logoutbutton_clicked();

    void on_backbutton_clicked();

    void on_reccbutton_clicked();

    void on_chngpass_clicked();

    void on_changusr_clicked();

    void on_extradd_clicked();

    void on_movinsert_clicked();

    void on_movadd_clicked();

    void on_bacc_clicked();

    void on_movbacc_clicked();

    void on_ebookadd_clicked();

    void on_insertbook_clicked();

    void on_bookbacc_clicked();

    void on_tvshowadd_clicked();

    void on_sinsert_clicked();

    void on_show_gobacc_clicked();
    void on_bookplan_clicked();

    void on_bookdrop_clicked();

    void on_showplan_clicked();

    void on_showdrop_clicked();

    void on_ebookupd_clicked();

    void on_updcoll_clicked();

    void on_updbookbutton_clicked();

    void on_bookupdbacc_clicked();

    void on_upd_bacc_clicked();

    void on_movieupd_clicked();

    void on_movupdbutton_clicked();

    void on_movupdbacc_clicked();

    void on_showupdbacc_clicked();

    void on_showupdbutton_clicked();

    void on_tvshowupd_clicked();

    void on_collbutton_clicked();

    void on_searchbutton_clicked();

    void on_searchreturn_clicked();

    void on_searchadd_clicked();

    void on_FAQsbutton_clicked();

    void on_searchlist_itemSelectionChanged();

    void on_inspectsearch_clicked();

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
