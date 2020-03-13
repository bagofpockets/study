#v12

import matplotlib.pyplot as plt
import numpy as np
import lab2_ui
import lab2_math
import sys
from PyQt5 import QtWidgets

class App(QtWidgets.QMainWindow, lab2_ui.Ui_MainWindow, lab2_math.Lab2):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.btnBrowse.clicked.connect(self.browse_files)
        self.btnDo.clicked.connect(self.do_lab2)

    def closeEvent(self, event):
        plt.close('all')

    def browse_files(self):
        options = QtWidgets.QFileDialog.Options()
        options |= QtWidgets.QFileDialog.DontUseNativeDialog
        self.filename = QtWidgets.QFileDialog.getOpenFileName(self,"Выбрать данные", "", options=options)
        self.text.clear()
        plt.close('all')
        filename = str(self.filename[0])
        self.set_data(filename)
        text = ''
        if self.shar == False:
            text += 'x ' + str(self.x)[1:-1] + '\n'
            text += 'y ' + str(self.y)[1:-1] + '\n'
        else:
            text += 'm ' + str(self.m) + '\n'
            text += 'k ' + str(self.k) + '\n'
            text += 'r0 ' + str(self.r0) + '\n'
            text += 'v0 ' + str(self.v0)+ '\n'
        self.text.setText(text)

    def do_lab2(self):
        if self.filename == '':
            self.text.clear()
            self.text.setText('Из чего?')
        else:
            text = ''
            if self.shar == False:
                self.derivatives_polynom()
                self.text.append('Coeffs:\n\ta:\n' + str(self.coeffs[0])[1:-1] + '\n\tb:\n' + str(self.coeffs[1])[1:-1] + '\n\tc:\n' + str(self.coeffs[2])[1:-1] + '\n\td:\n' + str(self.coeffs[3])[1:-1])
                self.graph()
            else:
                text += 'm ' + str(self.m) + '\n'
                text += 'k ' + str(self.k) + '\n'
                text += 'r0 ' + str(self.r0) + '\n'
                text += 'v0 ' + str(self.v0)+ '\n'
                self.text.setText(text)
                self.text.append('Function:\nr = ' + self.moving_shar() + '\n')

def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()