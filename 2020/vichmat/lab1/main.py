#v12

import matplotlib.pyplot as plt
import numpy as np
import lab1_ui
import lab1_math
import sys
from PyQt5 import QtWidgets

class App(QtWidgets.QMainWindow, lab1_ui.Ui_MainWindow, lab1_math.Lab1):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.btnBrowse.clicked.connect(self.browse_files)
        self.btnDo.clicked.connect(self.do_lab1)

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
        x_val = 'x ' + str(self.x)[1:-1] + '\n'
        y_val = 'y ' + str(self.y)[1:-1] + '\n'
        text = x_val + y_val
        self.text.setText(text)

    def do_lab1(self, filename):
        matrix = self.polynom(1)
        self.text.append(self.pretty(matrix))

        coeffs = self.gauss(matrix)
        self.text.append('Coeffs, k=1:\n' + str(coeffs[::-1])[1:-1] + '\n')

        y_pred = []
        for i in self.x:
            y_pred.append(self.predict(i))
        self.text.append(self.stats(y_pred))
        
        val_pred1 = [[], []]
        val_pred1[0] = np.linspace(min(self.x) - 0.5, max(self.x) + 0.5, 100)
        for i in val_pred1[0]:
            val_pred1[1].append(self.predict(i))
        #---------------------------------------
        matrix = self.polynom(2)
        self.text.append(self.pretty(matrix))

        coeffs = self.gauss(matrix)
        self.text.append('Coeffs, k=2:\n' + str(coeffs[::-1])[1:-1] + '\n')

        y_pred = []
        for i in self.x:
            y_pred.append(self.predict(i))
        self.text.append(self.stats(y_pred))

        val_pred2 = [[], []]
        val_pred2[0] = np.linspace(min(self.x) - 0.5, max(self.x) + 0.5, 100)
        for i in val_pred2[0]:
            val_pred2[1].append(self.predict(i))

        self.graph(val_pred1, val_pred2)

def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()