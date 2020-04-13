import Hata_ui
import Room
import sys
import Client as cl
import pandas as pd
from PyQt5 import QtWidgets

class App(QtWidgets.QMainWindow, Hata_ui.Ui_MainWindow):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.roomprops.clear()
        self.rooms = pd.read_csv(self.rooms_filename, sep = '|')
        self.clients = pd.read_csv(self.clients_filename, sep = '|')
        self.calendar.setSelectedDate(self.in_datein.date())
        self.BtnSearch.clicked.connect(self.search)
        self.BtnReservate.clicked.connect(self.reservate)

    def closeEvent(self, event):
        self.rooms.to_csv(self.rooms_filename, index = False, sep = '|')
        self.clients.to_csv(self.clients_filename, index = False, sep = '|')

    def search(self):
        current_client = cl.Client(name = self.in_name.text(), lastname = self.in_lastname.text(), middlename = self.in_middlename.text(), mobile_number = self.in_mobilenum.text())
        if (current_client.name == '') or (current_client.lastname == '') or (current_client.mobile_number == ''):
            self.roomprops.setText('пшёл нах')
        else:
            self.roomprops.setText('хорошо') 
    
    def reservate(self):
        return None

def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()