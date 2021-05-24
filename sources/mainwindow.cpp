#include "headers/mainwindow.h"
#include "headers/calendar.h"
#include "headers/font.h"
#include <QtWidgets>
#include <fstream>
#include <unistd.h>
#include <git2.h>
#include <mach-o/dyld.h>

QCheckBox *checkM[7][52];

//  get the marked dates from a matrix of dates sorted by weekday
std::vector<std::chrono::system_clock::time_point>
get_active_dates(std::vector<std::vector<std::chrono::system_clock::time_point>> dates)
{
    std::vector<std::chrono::system_clock::time_point> ad;
    for (int i = 0; i < 52; i++)
        for (int j = 0; j < 7; j++)
            if (checkM[j][i]->isChecked())
                ad.push_back(dates[j][i]);
    return ad;
}

//  the qss stylesheet for the app
const QString stylesheet = "\
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
            border-radius: 3px;\
            padding: 1px 18px 1px 3px;\
            background: solid #1c2128;\
        }\
        QLineEdit:focus {\
            border: 1px solid #1f6fcb;\
            border-radius: 3px;\
            padding: 1px 18px 1px 3px;\
            background: solid #1c2128;\
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
            border: 0.5px solid #c9d1d9;\
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
        ";

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Gitfitti!");

    //  create and set properties for the window elements
    y = new QComboBox();
    int yd = std::get<0>(civil_from_days(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) / (24 * 60 * 60)));
    y->addItem("Year (default: last 52 weeks)");
    for (int i = yd + 3; i > yd - 20; i--)
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
    doit->setDefault(true);
    au = new QCheckBox();
    au->setStyleSheet("QCheckBox::indicator {\
                            width: 11px;\
                            height: 11px;\
                            border: 1px solid #30363d;\
                            border-radius: 2px;\
                        }\
                    \
                        QCheckBox::indicator:unchecked {\
                            background-color: #1c2128;\
                            opacity: 0.5;\
                        }\
                    \
                        QCheckBox::indicator:unchecked:hover {\
                            border: 1px solid #c9d1d9;\
                            opacity: 1;\
                        }\
                    \
                        QCheckBox::indicator:checked {\
                            background-color: #f0f6fc;\
                        }\
                    \
                        QCheckBox::indicator:checked:hover {\
                            background-color: #c9d1d9;\
                        }");
    lbl = new QLabel;
    al = new QLabel;
    lbl->setText("Commits/day:");
    al->setText("Auto Update?");
    l = new QGridLayout;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            checkM[i][j] = new QCheckBox();
            l->addWidget(checkM[i][j], i, j);
        }
    }

    //  adding the elements to corresponding layouts
    h = new QHBoxLayout;
    h->addWidget(name);
    h->addWidget(email);
    h->addWidget(pass);
    h3 = new QHBoxLayout;
    h3->addWidget(repo);
    h3->addWidget(y);
    h3->addWidget(lbl);
    h3->addWidget(nc);
    h3->addWidget(al);
    h3->addWidget(au);
    h2 = new QHBoxLayout;
    h2->addWidget(type);
    h2->addWidget(preview);
    h2->addWidget(invert);
    v = new QVBoxLayout;
    v->addLayout(h);
    v->addLayout(h3);
    v->addLayout(l);
    v->addLayout(h2);
    v->addWidget(doit);
    setLayout(v);
    setStyleSheet(stylesheet);

    //  connecting elements to their actions
    connect(doit, SIGNAL(released()), this, SLOT(doIT()));
    connect(invert, SIGNAL(released()), this, SLOT(inv()));
    connect(preview, SIGNAL(released()), this, SLOT(translate()));
    connect(name, &QLineEdit::textChanged, [=] { style()->polish(name); });
    connect(email, &QLineEdit::textChanged, [=] { style()->polish(email); });
    connect(pass, &QLineEdit::textChanged, [=] { style()->polish(pass); });
    connect(repo, &QLineEdit::textChanged, [=] { style()->polish(repo); });
    connect(type, &QLineEdit::textChanged, [=] { style()->polish(type); });
    connect(type, SIGNAL(returnPressed()), preview, SLOT(animateClick()));
    connect(nc, &QSpinBox::valueChanged, [=] { style()->polish(nc); });
}


MainWindow::~MainWindow()
{
    //  delet stuf
    delete y;
    delete fonts;
    delete name;
    delete repo;
    delete type;
    delete preview;
    delete doit;
    delete pass;
    delete nc;
    delete lbl;
    delete al;
    delete au;
    delete h;
    delete h2;
    delete h3;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 52; j++)
            delete checkM[i][j];
    delete l;
    delete v;
}


//  invert current selection
void MainWindow::inv()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            if (checkM[i][j]->isChecked())
                checkM[i][j]->setChecked(false);
            else
                checkM[i][j]->setChecked(true);
        }
    }
}


//  text -> matrix of checkboxes
void MainWindow::translate()
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 52; j++)
            checkM[i][j]->setChecked(false);

    //  load the dict
    std::unordered_map<char, std::vector<std::string>> txt = init();
    std::string str = type->text().toStdString();
    int offset = 1;
    int tw = 0;

    //  find total width of string for centering
    for (char &c : str)
    {
        c = tolower(c);
        if (txt.find(c) != txt.end())
            tw += getwidth(txt[c]) + 1;
    }
    if (--tw > 52)
    {
        QMessageBox Q;
        Q.setWindowTitle("ERROR ");
        Q.setText("You typed too long :(");
        Q.exec();
        return;
    }
    else
        offset = (52 - tw) / 2;

    //  the actual translation
    for (char &c: str)
    {
        if (txt.find(c) != txt.end())
        {
            int cw = getwidth(txt[c]);
            for (int k = 0; k < 7; k++)
                for (int j = offset; j < offset + static_cast<int>(txt[c][j - offset].length()); j++)
                    if (txt[c][k][j - offset] != ' ')
                        checkM[k][j]->setChecked(true);
            offset += cw;
            if (c != ' ')
                offset++;
        }
    }
}


//  get the current state of the matrix for saving to file
Art getcheck()
{
    Art A;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 52; j++)
            if (checkM[i][j]->isChecked())
                A.a[i][j] = 1;
            else
                A.a[i][j] = 0;
    return A;
}


//  yea do it
void MainWindow::doIT()
{
    //  initialize stuf
    Config c;
    std::vector<std::chrono::system_clock::time_point> dates;
    std::string repurl = repo->text().toStdString();
    std::string stdname = name->text().toStdString();
    std::string stdmail = email->text().toStdString();
    std::string repname;
    QMessageBox Q;
    Q.setStyleSheet(stylesheet);

    //  make authenticated url lol
    if (repurl != "" && repurl.find('/') != std::string::npos)
    {
        repname = repurl.substr(repurl.find_last_of('/') + 1, repurl.back());
        repurl.insert(8, stdname + ":" + pass->text().toStdString() + "@");
    }
    else
    {
        Q.setWindowTitle("ERROR ");
        Q.setText("Invalid repo url");
        Q.exec();
        return;
    }
    chdir(getenv("HOME"));
    strncpy(c.url, repurl.c_str(), 100);
    strncpy(c.cname, stdname.c_str(), 50);
    strncpy(c.cmail, stdmail.c_str(), 80);
    strncpy(c.path, "Documents/", 13);
    strncat(c.path, repname.c_str(), 67);
    int cnc = nc->value();
    if (y->currentText().toInt())
        dates = get_active_dates(dates_by_weekday(y->currentText().toInt()));
    else
        dates = get_active_dates(dates_by_weekday());

    //  initialize git stuf
    git_libgit2_init();
    git_repository *rep = NULL;
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

    checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
    clone_opts.checkout_opts = checkout_opts;

    //  git clone
    if (git_clone(&rep, c.url, c.path, &clone_opts) < 0)
    {
        const git_error *err = giterr_last();
        if (err)
        {
            Q.setWindowTitle("ERROR " + QString::number(err->klass));
            Q.setText(err->message);
            Q.exec();
            return;
        }
        if (git_repository_open(&rep, c.path) < 0)
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
    for (auto date : dates)
    {
        for (int j = 0; j < cnc; j++)
        {
            git_signature *me = NULL;
            git_oid commit_oid, tree_oid;
            git_tree *tree;
            git_index *index;
            git_object *parent = NULL;
            git_reference *ref = NULL;

            //  get parent (if it exists)
            git_revparse_ext(&parent, &ref, rep, "HEAD");

            //  create signature
            if (git_signature_new(&me, c.cname, c.cmail, std::chrono::duration_cast<std::chrono::seconds>(date.time_since_epoch()).count() + j * 10, 330) < 0)
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

            //  get index, tree id
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
            git_index_free(index);

            //  get tree from tree id
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

            //  create empty commit
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

            //  free git stuf
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

    //  get remote repo
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

    //  git push
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

    //  free git remote stuf
    git_remote_free(remote);
    git_repository_free(rep);

    //  clean up
    char cmd[80] = "rm -rf ";
    strcat(cmd, c.path);
    system(cmd);

    //  success msg
    Q.setWindowTitle("Success!");
    Q.setText("Created " + QString::number(dates.size() * cnc) + " commits as " + name->text() + " in <a href=\"" + repo->text() + "\" style=\"color:#58a6ff\">" + QString::fromStdString(repname) + "</a>");
    Q.exec();

    //  auto-update extras
    if (au->isChecked())
    {
        Art aout = getcheck();
        if(y->currentText().toInt())
            aout.year = y->currentText().toInt();
        else
            aout.year = -1;
        aout.nc = cnc;
        std::ifstream in("Documents/.config.bin");
        std::fstream out;
        if (!in.good())
        {
            //  if config doesn't exist get token and create file
            in.close();
            QDialog d;
            QVBoxLayout v;
            QHBoxLayout h;
            QLabel l;
            QLineEdit le;
            QPushButton accept, reject;
            accept.setText("OK");
            reject.setText("Heck NO");
            accept.setDefault(true);
            connect(&accept, SIGNAL(released()), &d, SLOT(accept()));
            connect(&reject, SIGNAL(released()), &d, SLOT(reject()));
            l.setText("Please go to <a href=\"https://github.com/settings/tokens\" style=\"color:#58a6ff\">https://github.com/settings/tokens</a> and generate a new token with \n'repo' and 'delete_repo' scopes checked to configure the auto-update script.");
            l.setOpenExternalLinks(true);
            l.setWordWrap(true);
            le.setPlaceholderText("Personal Access Token");
            v.addWidget(&l);
            v.addWidget(&le);
            h.addWidget(&accept);
            h.addWidget(&reject);
            v.addLayout(&h);
            d.setLayout(&v);
            d.setStyleSheet(stylesheet);
            d.resize(420, 125);
            d.exec();

            //  don't write config if Heck NO lol
            if (d.Accepted && !le.text().isEmpty())
            {
                out.open("Documents/.config.bin", std::ios::binary | std::ios::app);
                strncpy(c.auth, le.text().toStdString().c_str(), 50);
                out.write(reinterpret_cast<const char*>(&c), sizeof(c));
                out.write(reinterpret_cast<const char*>(&aout), sizeof(aout));
                out.flush();
                out.close();

                //  get path to auto-update and set a cron job to run it on startup
                char command[] = "( (crontab -l || echo "")  ; echo \"@reboot open /Applications/auto-update.app\") | sort -u - | crontab -";
                system(command);
            }
        }
        else
        {
            if(aout.year != -1)
            {
                Config c2;
                Art a;
                std::vector<Art> A2;
                in.read((char*)&c2, sizeof(c2));

                //  on inserting graffiti with year into an existing file, insert sorted
                bool flag = false;
                while(!in.eof())
                {
                    in.read((char*)&a, sizeof(a));
                    if(!flag && (a.year==-1 || a.year > aout.year))
                    {
                        A2.push_back(aout);
                        flag = true;
                    }
                    A2.push_back(a);
                }
                in.close();
                std::ofstream out("Documents/.config.bin", std::ios::binary);
                out.write(reinterpret_cast<const char*>(&c2), sizeof(c2));
                for(auto it : A2)
                    out.write(reinterpret_cast<const char*>(&it), sizeof(it));
                out.flush();
                out.close();
                return;
            }
            in.close();

            //  default graffiti can be appended
            out.open("Documents/.config.bin", std::ios::binary | std::ios::app);
            out.write(reinterpret_cast<const char*>(&aout), sizeof(aout));
            out.flush();
            out.close();
        }

        //  success msg
        Q.setWindowTitle("Success!");
        Q.setText("Auto-update settings updated!");
        Q.exec();
    }
}
