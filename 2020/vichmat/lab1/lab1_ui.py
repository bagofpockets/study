# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '\GitHub\study\2020\vichmat\lab1\lab1.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(700, 700)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.btnDo = QtWidgets.QPushButton(self.centralwidget)
        self.btnDo.setObjectName("btnDo")
        self.horizontalLayout.addWidget(self.btnDo)
        self.btnBrowse = QtWidgets.QPushButton(self.centralwidget)
        self.btnBrowse.setObjectName("btnBrowse")
        self.horizontalLayout.addWidget(self.btnBrowse)
        self.gridLayout.addLayout(self.horizontalLayout, 1, 0, 1, 1)
        self.text = QtWidgets.QTextBrowser(self.centralwidget)
        self.text.setObjectName("text")
        self.gridLayout.addWidget(self.text, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.filename = ''

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Lab1"))
        self.btnDo.setText(_translate("MainWindow", "Сделать красиво"))
        self.btnBrowse.setText(_translate("MainWindow", "Выбрать данные"))
