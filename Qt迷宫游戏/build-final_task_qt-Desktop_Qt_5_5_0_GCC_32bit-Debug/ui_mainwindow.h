/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBack_to_main;
    QAction *actionExit_application;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionAuto_play;
    QAction *actionStop_auto_play;
    QAction *actionPause_Continue;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *welcome;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *playButton;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *mapSelect;
    QSpinBox *nrEnemies;
    QSpinBox *nrHealth;
    QPushButton *quit;
    QWidget *game;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *heroHUDFace;
    QGridLayout *gridLayout_4;
    QLabel *labelspeed;
    QLabel *label_4;
    QSlider *speed;
    QDoubleSpinBox *heuristicWeight;
    QGridLayout *gridLayout_2;
    QLabel *health;
    QProgressBar *energyBar;
    QProgressBar *healthBar;
    QLabel *energy;
    QVBoxLayout *hUD;
    QGraphicsView *mapView;
    QWidget *end;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *resultLabel;
    QLabel *reasonLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *replay;
    QPushButton *main_menu;
    QPushButton *new_map;
    QWidget *page;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuMap;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(880, 770);
        actionBack_to_main = new QAction(MainWindow);
        actionBack_to_main->setObjectName(QStringLiteral("actionBack_to_main"));
        actionExit_application = new QAction(MainWindow);
        actionExit_application->setObjectName(QStringLiteral("actionExit_application"));
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        actionAuto_play = new QAction(MainWindow);
        actionAuto_play->setObjectName(QStringLiteral("actionAuto_play"));
        actionStop_auto_play = new QAction(MainWindow);
        actionStop_auto_play->setObjectName(QStringLiteral("actionStop_auto_play"));
        actionPause_Continue = new QAction(MainWindow);
        actionPause_Continue->setObjectName(QStringLiteral("actionPause_Continue"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        welcome = new QWidget();
        welcome->setObjectName(QStringLiteral("welcome"));
        gridLayout_5 = new QGridLayout(welcome);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label = new QLabel(welcome);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(300, 300));
        label->setMaximumSize(QSize(450, 450));
        label->setPixmap(QPixmap(QString::fromUtf8(":/monkeyHUD.png")));
        label->setScaledContents(true);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        playButton = new QPushButton(welcome);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setMaximumSize(QSize(150, 50));

        verticalLayout->addWidget(playButton, 0, Qt::AlignHCenter);

        label_3 = new QLabel(welcome);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(13);
        label_3->setFont(font);

        verticalLayout->addWidget(label_3, 0, Qt::AlignHCenter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(50, -1, 50, -1);
        mapSelect = new QComboBox(welcome);
        mapSelect->setObjectName(QStringLiteral("mapSelect"));
        mapSelect->setMinimumSize(QSize(400, 0));
        mapSelect->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_3->addWidget(mapSelect);

        nrEnemies = new QSpinBox(welcome);
        nrEnemies->setObjectName(QStringLiteral("nrEnemies"));
        nrEnemies->setMaximumSize(QSize(70, 16777215));
        nrEnemies->setMinimum(1);
        nrEnemies->setMaximum(500);
        nrEnemies->setSingleStep(5);
        nrEnemies->setValue(1);

        horizontalLayout_3->addWidget(nrEnemies);

        nrHealth = new QSpinBox(welcome);
        nrHealth->setObjectName(QStringLiteral("nrHealth"));
        nrHealth->setMaximumSize(QSize(70, 16777215));
        nrHealth->setMinimum(1);
        nrHealth->setMaximum(500);
        nrHealth->setSingleStep(5);
        nrHealth->setValue(1);

        horizontalLayout_3->addWidget(nrHealth);


        verticalLayout->addLayout(horizontalLayout_3);

        quit = new QPushButton(welcome);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setMaximumSize(QSize(150, 50));

        verticalLayout->addWidget(quit, 0, Qt::AlignHCenter);


        gridLayout_5->addLayout(verticalLayout, 0, 0, 1, 1);

        stackedWidget->addWidget(welcome);
        game = new QWidget();
        game->setObjectName(QStringLiteral("game"));
        gridLayout_6 = new QGridLayout(game);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        heroHUDFace = new QLabel(game);
        heroHUDFace->setObjectName(QStringLiteral("heroHUDFace"));
        heroHUDFace->setMaximumSize(QSize(100, 100));
        heroHUDFace->setPixmap(QPixmap(QString::fromUtf8(":/monkeyHUD.png")));
        heroHUDFace->setScaledContents(true);
        heroHUDFace->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(heroHUDFace);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(10, -1, -1, -1);
        labelspeed = new QLabel(game);
        labelspeed->setObjectName(QStringLiteral("labelspeed"));
        labelspeed->setMargin(2);

        gridLayout_4->addWidget(labelspeed, 0, 0, 1, 1);

        label_4 = new QLabel(game);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMargin(2);

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        speed = new QSlider(game);
        speed->setObjectName(QStringLiteral("speed"));
        speed->setMinimum(1);
        speed->setMaximum(10);
        speed->setSingleStep(1);
        speed->setPageStep(1);
        speed->setValue(5);
        speed->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(speed, 0, 1, 1, 1);

        heuristicWeight = new QDoubleSpinBox(game);
        heuristicWeight->setObjectName(QStringLiteral("heuristicWeight"));
        heuristicWeight->setMaximum(19.99);
        heuristicWeight->setSingleStep(0.25);
        heuristicWeight->setValue(1);

        gridLayout_4->addWidget(heuristicWeight, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_4);


        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, -1, 50, -1);
        health = new QLabel(game);
        health->setObjectName(QStringLiteral("health"));
        QFont font1;
        font1.setPointSize(18);
        health->setFont(font1);
        health->setTextFormat(Qt::RichText);

        gridLayout_2->addWidget(health, 0, 0, 1, 1);

        energyBar = new QProgressBar(game);
        energyBar->setObjectName(QStringLiteral("energyBar"));
        energyBar->setMaximumSize(QSize(500, 25));
        energyBar->setMaximum(500);
        energyBar->setValue(500);

        gridLayout_2->addWidget(energyBar, 1, 1, 1, 1);

        healthBar = new QProgressBar(game);
        healthBar->setObjectName(QStringLiteral("healthBar"));
        healthBar->setMaximumSize(QSize(500, 25));
        healthBar->setValue(100);

        gridLayout_2->addWidget(healthBar, 0, 1, 1, 1);

        energy = new QLabel(game);
        energy->setObjectName(QStringLiteral("energy"));
        energy->setFont(font1);
        energy->setTextFormat(Qt::RichText);

        gridLayout_2->addWidget(energy, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 0, 3, 1, 1);

        hUD = new QVBoxLayout();
        hUD->setSpacing(6);
        hUD->setObjectName(QStringLiteral("hUD"));
        mapView = new QGraphicsView(game);
        mapView->setObjectName(QStringLiteral("mapView"));

        hUD->addWidget(mapView);


        gridLayout_6->addLayout(hUD, 2, 0, 1, 4);

        stackedWidget->addWidget(game);
        end = new QWidget();
        end->setObjectName(QStringLiteral("end"));
        gridLayout_3 = new QGridLayout(end);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(end);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setPointSize(48);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        resultLabel = new QLabel(end);
        resultLabel->setObjectName(QStringLiteral("resultLabel"));
        QFont font3;
        font3.setPointSize(72);
        resultLabel->setFont(font3);
        resultLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(resultLabel);

        reasonLabel = new QLabel(end);
        reasonLabel->setObjectName(QStringLiteral("reasonLabel"));
        reasonLabel->setMaximumSize(QSize(16777215, 16777215));
        QFont font4;
        font4.setPointSize(26);
        reasonLabel->setFont(font4);
        reasonLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(reasonLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        replay = new QPushButton(end);
        replay->setObjectName(QStringLiteral("replay"));
        replay->setMinimumSize(QSize(0, 50));

        horizontalLayout->addWidget(replay);

        main_menu = new QPushButton(end);
        main_menu->setObjectName(QStringLiteral("main_menu"));
        main_menu->setMinimumSize(QSize(0, 50));

        horizontalLayout->addWidget(main_menu);

        new_map = new QPushButton(end);
        new_map->setObjectName(QStringLiteral("new_map"));
        new_map->setMinimumSize(QSize(0, 50));

        horizontalLayout->addWidget(new_map);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        stackedWidget->addWidget(end);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 880, 25));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuMap = new QMenu(menuMenu);
        menuMap->setObjectName(QStringLiteral("menuMap"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionBack_to_main);
        menuMenu->addAction(menuMap->menuAction());
        menuMenu->addAction(actionExit_application);
        menuMenu->addAction(actionAuto_play);
        menuMenu->addAction(actionStop_auto_play);
        menuMenu->addAction(actionPause_Continue);
        menuMap->addAction(actionZoom_in);
        menuMap->addAction(actionZoom_out);

        retranslateUi(MainWindow);
        QObject::connect(actionExit_application, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(quit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        stackedWidget->setCurrentIndex(1);
        main_menu->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionBack_to_main->setText(QApplication::translate("MainWindow", "Back to main", 0));
        actionExit_application->setText(QApplication::translate("MainWindow", "Exit application", 0));
        actionZoom_in->setText(QApplication::translate("MainWindow", "Zoom in", 0));
        actionZoom_out->setText(QApplication::translate("MainWindow", "Zoom out", 0));
        actionAuto_play->setText(QApplication::translate("MainWindow", "Auto play", 0));
        actionStop_auto_play->setText(QApplication::translate("MainWindow", "Stop auto play", 0));
        actionPause_Continue->setText(QApplication::translate("MainWindow", "Pause/Continue", 0));
        label->setText(QString());
        playButton->setText(QApplication::translate("MainWindow", "PLAY", 0));
        label_3->setText(QApplication::translate("MainWindow", "Select  map,  number of enemies  and  number of healtpacks:", 0));
#ifndef QT_NO_TOOLTIP
        mapSelect->setToolTip(QApplication::translate("MainWindow", "Select Map", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        nrEnemies->setToolTip(QApplication::translate("MainWindow", "number of Enemies", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        nrHealth->setToolTip(QApplication::translate("MainWindow", "number of healthpacks", 0));
#endif // QT_NO_TOOLTIP
        quit->setText(QApplication::translate("MainWindow", "QUIT", 0));
        heroHUDFace->setText(QString());
        labelspeed->setText(QApplication::translate("MainWindow", "speed", 0));
        label_4->setText(QApplication::translate("MainWindow", "heuristic weight", 0));
        health->setText(QApplication::translate("MainWindow", "Health:", 0));
        energyBar->setFormat(QString());
        healthBar->setFormat(QString());
        energy->setText(QApplication::translate("MainWindow", "Energy:", 0));
        label_2->setText(QApplication::translate("MainWindow", "THE END", 0));
        resultLabel->setText(QApplication::translate("MainWindow", "YOU WIN ", 0));
        reasonLabel->setText(QApplication::translate("MainWindow", "reason", 0));
        replay->setText(QApplication::translate("MainWindow", "Replay Last Map", 0));
        main_menu->setText(QApplication::translate("MainWindow", "Back To Menu", 0));
        new_map->setText(QApplication::translate("MainWindow", "Play New Map", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuMap->setTitle(QApplication::translate("MainWindow", "Map", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
