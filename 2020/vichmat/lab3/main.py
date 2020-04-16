#v12

import matplotlib.pyplot as plt
import numpy as np
import lab3_ui
import lab3_math
import sys
from PyQt5 import QtWidgets

class App(QtWidgets.QMainWindow, lab3_ui.Ui_MainWindow, lab3_math.Lab3):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.btnDo.clicked.connect(self.do_lab3)

    def closeEvent(self, event):
        plt.close('all')

    def do_lab3(self):
        if  (self.line_V.text() == '') or (self.line_S.text() == '') or (self.line_l.text() == '') or (self.line_H.text() == '') or (self.line_p1.text() == '') or (self.line_v.text() == ''):
            self.text.clear()
            self.text.setText('Из чего?')
        else:
            self.text.clear()
            self.H = -float(self.line_H.text())
            self.V = float(self.line_V.text())
            self.S = float(self.line_S.text())
            self.l = float(self.line_l.text())
            self.p1 = float(self.line_p1.text())
            self.v = float(self.line_v.text())

            vals = self.rungekutta(self.H, 0, 0)

            matrix = self.polynom(2, vals[2], vals[1])
            coeffs = self.gauss(matrix)

            T = 0.
            vals_pred1 = [[], [], []]
            vals_pred1[0] = np.linspace(min(vals[2]), max(vals[2]), 10*len(vals[0]))
            for t in vals_pred1[0]:
                y_pred = self.predict(t, coeffs)
                vals_pred1[1].append(y_pred)
                if y_pred >= 0:
                    T = t
                    self.text.append('T = ' + str(T) + '\nL = ' + str(self.v*T))
                    break
            vals_pred1[2] = [0]*len(vals_pred1[1])
            vals_pred1[0] = vals_pred1[0][:len(vals_pred1[1])]

            matrix = self.polynom(2, vals[0], vals[1])
            coeffs = self.gauss(matrix)
            
            vals_pred2 = [[], [], []]
            vals_pred2[0] = np.linspace(min(vals[0]), max(vals[0]), 10*len(vals[0]))
            for x in vals_pred2[0]:
                y_pred = self.predict(x, coeffs)
                vals_pred2[1].append(y_pred)
            vals_pred2[2] = [0]*len(vals_pred2[1])

            self.graph(vals, vals_pred1, vals_pred2)

def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()