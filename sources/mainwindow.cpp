#include "headers/mainwindow.h"
#include "headers/calendar.h"
#include "headers/font.h"
#include <QtWidgets>
#include <fstream>
#include <git2.h>

QCheckBox *checkM[7][52];

std::vector<std::chrono::system_clock::time_point>
get_active_dates(std::vector<std::vector<std::chrono::system_clock::time_point>> dates)
{
    std::vector<std::chrono::system_clock::time_point> ad;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 52; j++)
            if (checkM[i][j]->isChecked())
                ad.push_back(dates[i][j]);
    return ad;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("GitHub Abuz!");
    y = new QComboBox();
    int yd = std::get<0>(civil_from_days(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())/(24*60*60)));
    y->addItem("Year (default: last 52 weeks)");
    for (int i = yd+3; i > yd-20; i--)
        y->addItem(QString::number(i));
    nc = new QSpinBox();
    nc->setMinimum(1);
    nc->setValue(1);
    name = new QLineEdit();
    name->setPlaceholderText("Username");
    email = new QLineEdit();
    email->setPlaceholderText("Email");
    repo = new QLineEdit();
    repo->setPlaceholderText("Link to repo");
    type = new QLineEdit();
    type->setPlaceholderText("Translate text to tile art!");
    pass = new QLineEdit();
    pass->setPlaceholderText("Password");
    pass->setEchoMode(QLineEdit::Password);
    preview = new QPushButton(tr("Translate!"));
    invert = new QPushButton(tr("Invert"));
    doit = new QPushButton(tr("Do IT"));
    QLabel *lbl = new QLabel;
    lbl->setText("Commits/day:");
    QGridLayout *l = new QGridLayout;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            checkM[i][j] = new QCheckBox();
            l->addWidget(checkM[i][j], i, j);
        }
    }
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(name);
    h->addWidget(email);
    h->addWidget(pass);
    QHBoxLayout *h3 = new QHBoxLayout;
    h3->addWidget(repo);
    h3->addWidget(y);
    h3->addWidget(lbl);
    h3->addWidget(nc);
    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(type);
    h2->addWidget(preview);
    h2->addWidget(invert);
    QVBoxLayout *v = new QVBoxLayout;
    v->addLayout(h);
    v->addLayout(h3);
    v->addLayout(l);
    v->addLayout(h2);
    v->addWidget(doit);
    setLayout(v);
    connect(doit, SIGNAL(released()), this, SLOT(doIT()));
    connect(invert, SIGNAL(released()), this, SLOT(inv()));
    connect(preview, SIGNAL(released()), this, SLOT(translate()));

    setStyleSheet("\
        QLineEdit{\
            border: 1px solid #30363d;\
            border-radius: 3px;\
            padding: 1px 18px 1px 3px;\
            background: solid #1c2128;\
            color: #f0f6fc;\
        }\
        QLineEdit[text=\"\"]{\
             border: 1px solid #30363d;\
             border-radius: 3px;\
             padding: 1px 18px 1px 3px;\
             background: solid #1c2128;\
             color: #8b949e;\
        }\
        QLineEdit:hover {\
            border: 0.5px solid #c9d1d9;\
        }\
        QLineEdit:focus {\
            border: 1px solid #1f6fcb;\
        }\
        QWidget{\
            background-color: #0d1117;\
        }\
        QCheckBox {\
            spacing: 0px;\
            padding: 0px;\
        }\
\
        QCheckBox::indicator {\
            width: 11px;\
            height: 11px;\
            outline: 1px solid  hsla(0, 0, 100, 0.05);\
            border-radius: 3px;\
        }\
\
        QCheckBox::indicator:unchecked:pressed {\
            outline: 0px;\
        }\
        QCheckBox::indicator:checked:pressed {\
            outline: 0px;\
        }\
\
        QCheckBox::indicator:unchecked {\
            background-color: #161b22;\
            opacity: 0.5;\
        }\
\
        QCheckBox::indicator:unchecked:hover {\
            background-color: #003820;\
            opacity: 1;\
        }\
\
        QCheckBox::indicator:checked {\
            background-color: #10983d;\
        }\
\
        QCheckBox::indicator:checked:hover {\
            background-color: #00602d;\
        }\
\
        QComboBox {\
            border: 1px #30363d;\
            border-radius: 3px;\
            padding: 1px 18px 1px 3px;\
            min-width: 6em;\
            background: #1c2128;\
            color: #f0f6fc;\
        }\
\
        QComboBox:editable {\
            background: #1c2128;\
            color: #f0f6fc;\
        }\
\
        QComboBox:!editable, QComboBox::drop-down:editable {\
            background: #1c2128;\
            color: #f0f6fc;\
        }\
\
        /* QComboBox gets the state when the popup is open */\
        QComboBox:!editable:on, QComboBox::drop-down:editable:on {\
            background: #1c2128;\
            color: #f0f6fc;\
        }\
\
        QComboBox:hover {\
            background: #30363d;\
        }\
\
        QComboBox:on { /* shift the text when the popup opens */\
            padding-top: 3px;\
            padding-left: 4px;\
            color: #f0f6fc;\
        }\
\
        QComboBox::drop-down {\
            border: 1px solid #30363d;\
            subcontrol-origin: padding;\
            subcontrol-position: top right;\
            width: 15px;\
            background-color: #0d1117;\
            color: #f0f6fc;\
        }\
\
\
        QComboBox::down-arrow:on { /* shift the arrow when popup is open */\
            top: 1px;\
            left: 1px;\
            color: #f0f6fc;\
        }\
\
        QComboBox QAbstractItemView {\
            border: 1px solid #30363d;\
            selection-background-color: #0d1117;\
            color: #f0f6fc;\
        }\
        QLabel{\
            color: #f0f6fc;\
        }\
        QPushButton {\
            border: 1px solid #30363d;\
            border-radius: 4px;\
            background-color: #161b22;\
            color: #58a6ff;\
            min-width: 80px;\
        }\
\
        QPushButton:pressed {\
            background-color: #0d1117;\
            border: 0px;\
        }\
\
        QPushButton:hover {\
            background-color: #30363d;\
        }\
\
        QPushButton:flat {\
            border: none; /* no border for a flat push button */\
        }\
\
        QScrollBar:vertical\
        {\
            background-color: #161b22;\
            width: 15px;\
            margin: 15px 3px 15px 3px;\
            border: 1px transparent #2A2929;\
            border-radius: 4px;\
        }\
\
        QScrollBar::handle:vertical\
        {\
            background-color: #58a6ff;\
            min-height: 5px;\
            border-radius: 4px;\
        }\
\
        QScrollBar::sub-line:vertical\
        {\
            margin: 3px 0px 3px 0px;\
            border: 0px;\
            height: 10px;\
            width: 10px;\
            subcontrol-position: top;\
            subcontrol-origin: margin;\
        }\
\
        QScrollBar::add-line:vertical\
        {\
            margin: 3px 0px 3px 0px;\
            border: 0px;\
            height: 10px;\
            width: 10px;\
            subcontrol-position: bottom;\
            subcontrol-origin: margin;\
        }\
\
        QScrollBar::sub-line:vertical:hover,QScrollBar::sub-line:vertical:on\
        {\
\
            border: 0px;\
            height: 10px;\
            width: 10px;\
            subcontrol-position: top;\
            subcontrol-origin: margin;\
        }\
\
        QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on\
        {\
            border: 0px;\
            height: 10px;\
            width: 10px;\
            subcontrol-position: bottom;\
            subcontrol-origin: margin;\
        }\
\
        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\
        {\
            background: none;\
        }\
\
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
        {\
            background: none;\
        }\
        QSpinBox {\
            padding-right: 15px; /* make room for the arrows */\
            border: 1px solid #30363d;\
            border-radius: 3px;\
            color: #f0f6fc;\
            background: solid #1c2128\
        }\
        QSpinBox:focus {\
            border: 1px solid #1f6fcb;\
        }\
        \
        QSpinBox::up-button {\
            subcontrol-origin: border;\
            subcontrol-position: top right; /* position at the top right corner */\
            width: 14px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */\
            border: 1px solid #30363d;\
            border-bottom: 0px;\
            background: solid #30363d;\
        }\
        \
        QSpinBox::up-arrow {\
            width: 7px;\
            height: 7px;\
            background: solid black;\
        }\
        \
        QSpinBox::down-button {\
            subcontrol-origin: border;\
            subcontrol-position: bottom right; /* position at bottom right corner */\
            width: 14px;\
            border: 1px solid #30363d;\
            border-top: 0px;\
            background: solid #30363d;\
        }\
        QSpinBox::down-button:focus {\
            border: 1px solid #1f6fcb;\
            border-top: 0px;\
        }\
        QSpinBox::up-button:focus {\
            border: 1px solid #1f6fcb;\
            border-bottom: 0px;\
        }\
        QSpinBox::down-arrow {\
            width: 7px;\
            height: 7px;\
            background: solid black;\
        }\
        ");
    connect(name, &QLineEdit::textChanged, [=]{ style()->polish(name); });
    connect(email, &QLineEdit::textChanged, [=]{ style()->polish(email); });
    connect(pass, &QLineEdit::textChanged, [=]{ style()->polish(pass); });
    connect(repo, &QLineEdit::textChanged, [=]{ style()->polish(repo); });
    connect(type, &QLineEdit::textChanged, [=]{ style()->polish(type); });
    connect(nc, &QSpinBox::valueChanged, [=]{ style()->polish(nc); });
}

MainWindow::~MainWindow()
{
    delete y;
    delete fonts;
    delete name;
    delete repo;
    delete type;
    delete preview;
    delete doit;
}

void MainWindow::inv()
{
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<52; j++)
        {
            if(checkM[i][j]->isChecked())
                checkM[i][j]->setChecked(false);
            else
                checkM[i][j]->setChecked(true);
        }
    }
}

void MainWindow::translate()
{
    for(int i=0; i<7; i++)
        for(int j=0; j<52; j++)
            checkM[i][j]->setChecked(false);
    std::unordered_map<char, std::vector<std::string>> txt = init();
    std::string str = type->text().toStdString();
    int n = str.length();
    int offset = 1;
    int tw=0;
    for(int i=0; i<n; i++)
    {
        if(txt.find(tolower(str[i]))!=txt.end())
        {
            str[i] = tolower(str[i]);
            tw += getwidth(txt[str[i]])+1;
        }
    }
    if(--tw > 52)
    {
        QMessageBox Q;
        Q.setWindowIcon(QIcon(":/icons/icon.png"));
        Q.setWindowTitle("ERROR ");
        Q.setText("You typed too long :(");
        Q.exec();
        return;
    }
    else
        offset = (52-tw)/2;
    for(int i=0; i<n; i++)
    {
        if(txt.find(str[i])!=txt.end())
        {
            int cw = getwidth(txt[str[i]]);
            for(int k=0; k<7; k++)
                for(int j=offset; j<offset+static_cast<int>(txt[str[i]][j-offset].length()); j++)
                    if(txt[str[i]][k][j-offset]!=' ')
                        checkM[k][j]->setChecked(true);
            offset += cw;
            if(str[i]!=' ')
                offset++;
        }
    }
}

void MainWindow::doIT()
{
    std::vector<std::chrono::system_clock::time_point> dates;
    if(y->currentText().toInt())
        dates = get_active_dates(dates_by_weekday(y->currentText().toInt()));
    else
        dates = get_active_dates(dates_by_weekday());
    QMessageBox Q;
    Q.setWindowIcon(QIcon(":/icons/icon.png"));
    std::string repurl = repo->text().toStdString();
    std::string stdname = name->text().toStdString();
    std::string stdmail = email->text().toStdString();
    std::string repname;
    if(repurl!="" && repurl.find('/')!=std::string::npos)
    {
        repname = repurl.substr(repurl.find_last_of('/')+1, repurl.back());
        repurl.insert(8, stdname+":"+pass->text().toStdString()+"@");
    }
    else
    {
        Q.setWindowTitle("ERROR ");
        Q.setText("Invalid repo url");
        Q.exec();
        return;
    }
    const char *url = &repurl[0];
    const char *cname = &stdname[0];
    const char *cmail = &stdmail[0];
    char *path = &repname[0];
    git_libgit2_init();
    git_repository *rep = NULL;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

    checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    clone_opts.checkout_opts = checkout_opts;
    if (git_clone(&rep, url, path, &clone_opts) < 0)
    {
        if(git_repository_open(&rep, path)<0)
        {
            const git_error *err = giterr_last();
            if (err)
            {
                Q.setWindowTitle("ERROR " + QString::number(err->klass));
                Q.setText(err->message);
                Q.exec();
                return;
            }
        }
    }
    int n = dates.size();
    int m = nc->value();

    for (int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            git_signature *me = NULL;
            git_oid commit_oid, tree_oid;
            git_tree *tree;
            git_index *index;
            git_object *parent = NULL;
            git_reference *ref = NULL;
            git_revparse_ext(&parent, &ref, rep, "HEAD");
            if (git_signature_new(&me, cname, cmail, std::chrono::duration_cast<std::chrono::seconds>(dates[i].time_since_epoch()).count(), 120+j) < 0)
            {
                const git_error *err = giterr_last();
                if (err)
                {
                    Q.setWindowTitle("ERROR " + QString::number(err->klass));
                    Q.setText(err->message);
                    Q.exec();
                    return;
                }
            }
            git_repository_index(&index, rep);
            if (git_index_write_tree(&tree_oid, index) < 0)
            {
                const git_error *err = giterr_last();
                if (err)
                {
                    Q.setWindowTitle("ERROR " + QString::number(err->klass));
                    Q.setText(err->message);
                    Q.exec();
                    return;
                }
            }
            if (git_tree_lookup(&tree, rep, &tree_oid) < 0)
            {
                const git_error *err = giterr_last();
                if (err)
                {
                    Q.setWindowTitle("ERROR " + QString::number(err->klass));
                    Q.setText(err->message);
                    Q.exec();
                    return;
                }
            }
            if (git_commit_create_v(&commit_oid, rep, "HEAD", me, me, NULL, "just aesthetic commits :v:", tree, parent ? 1 : 0, parent) < 0)
            {
                const git_error *err = giterr_last();
                if (err)
                {
                    Q.setWindowTitle("ERROR " + QString::number(err->klass));
                    Q.setText(err->message);
                    Q.exec();
                    return;
                }
            }
            git_index_free(index);
            git_signature_free(me);
            git_tree_free(tree);
            git_object_free(parent);
            git_reference_free(ref);
        }
    }
    git_push_options options;
    git_remote *remote = NULL;
    char *refspec = "refs/heads/master";
    const git_strarray refspecs = {
        &refspec,
        1};
    if (git_remote_lookup(&remote, rep, "origin") < 0)
    {
        const git_error *err = giterr_last();
        if (err)
        {
            Q.setWindowTitle("ERROR " + QString::number(err->klass));
            Q.setText(err->message);
            Q.exec();
            return;
        }
    }
    if (git_push_options_init(&options, GIT_PUSH_OPTIONS_VERSION) < 0)
    {
        const git_error *err = giterr_last();
        if (err)
        {
            Q.setWindowTitle("ERROR " + QString::number(err->klass));
            Q.setText(err->message);
            Q.exec();
            return;
        }
    }
    if (git_remote_push(remote, &refspecs, &options) < 0)
    {
        const git_error *err = giterr_last();
        if (err)
        {
            Q.setWindowTitle("ERROR " + QString::number(err->klass));
            Q.setText(err->message);
            Q.exec();
            return;
        }
    }
    git_remote_free(remote);
    git_repository_free(rep);
    Q.setWindowTitle("Success!");
    Q.setText("Created " + QString::number(n*m) + " commits as " + name->text() + " in " + repo->text());
    Q.exec();
}
