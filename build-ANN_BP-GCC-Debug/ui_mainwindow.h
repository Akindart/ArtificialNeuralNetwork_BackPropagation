/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir_arquivo_de_treinamento;
    QAction *actionAbrir_arquivo_de_teste;
    QAction *actionCriar_nova_Rede;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuAqruivo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionAbrir_arquivo_de_treinamento = new QAction(MainWindow);
        actionAbrir_arquivo_de_treinamento->setObjectName(QStringLiteral("actionAbrir_arquivo_de_treinamento"));
        actionAbrir_arquivo_de_teste = new QAction(MainWindow);
        actionAbrir_arquivo_de_teste->setObjectName(QStringLiteral("actionAbrir_arquivo_de_teste"));
        actionCriar_nova_Rede = new QAction(MainWindow);
        actionCriar_nova_Rede->setObjectName(QStringLiteral("actionCriar_nova_Rede"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 27));
        menuAqruivo = new QMenu(menuBar);
        menuAqruivo->setObjectName(QStringLiteral("menuAqruivo"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuAqruivo->menuAction());
        menuAqruivo->addAction(actionAbrir_arquivo_de_teste);
        menuAqruivo->addAction(actionAbrir_arquivo_de_treinamento);
        menuAqruivo->addAction(actionCriar_nova_Rede);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAbrir_arquivo_de_treinamento->setText(QApplication::translate("MainWindow", "Abrir arquivo de treinamento", 0));
        actionAbrir_arquivo_de_teste->setText(QApplication::translate("MainWindow", "Abrir arquivo de teste", 0));
        actionCriar_nova_Rede->setText(QApplication::translate("MainWindow", "Criar nova Rede", 0));
        menuAqruivo->setTitle(QApplication::translate("MainWindow", "Aqruivo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
