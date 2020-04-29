import Hata_ui
import DataBase
import Client as cl
import pandas as pd
import datetime as dt
from PyQt5.QtWidgets import QMainWindow, QApplication, QMessageBox
from PyQt5.QtCore import QDate
from PyQt5.QtGui import QMovie, QColor, QPalette, QTextCharFormat
import sys
import os

class App(QMainWindow, Hata_ui.Ui_MainWindow):

    def __init__(self):
        super().__init__()
        self.setupUi(self)

        rooms = pd.read_csv(self.rooms_filename, sep = '|')
        for row in rooms.loc[:, 'hasTv':'hasBreakfast']:
            roomprops = []
            for val in rooms[row].tolist():
                roomprops.append(bool(val))
            rooms[row] = roomprops
        self.db = DataBase.DataBase(rooms.to_dict())
        clients = pd.read_csv(self.clients_filename, sep = '|')
        clients['mobile_number'] = clients['mobile_number'].astype(str)
        clients['datein'] = clients['datein'].astype(str)
        clients['dateout'] = clients['dateout'].astype(str)

        self.clientdb = []
        for id in range(len(clients)):
            client = cl.Client(id=id, 
                                name=clients['name'][id],
                                lastname=clients['lastname'][id],
                                middlename=clients['middlename'][id],
                                mobile_number=clients['mobile_number'][id],
                                datein=dt.datetime.strptime(clients['datein'][id], '%Y-%m-%d').date(),
                                dateout=dt.datetime.strptime(clients['dateout'][id], '%Y-%m-%d').date())
            self.clientdb.append(client)
        
        self.ListItems = []
        self.q = len(rooms)
        for i in range(self.q):
            self.ListRooms.addItem('Номер %d' % (i+1))
            self.ListItems.append(self.ListRooms.item(i))
        self.ListItems[0].setSelected(True)

        self.calendar.setSelectedDate(self.in_datein.date())
        self.in_datein.dateChanged.connect(self.highlight)
        self.in_dateout.dateChanged.connect(self.highlight)
        self.BtnSearch.clicked.connect(self.search)
        self.BtnReservate.clicked.connect(self.reservate)
        self.ListRooms.currentItemChanged.connect(self._roomProps)

    def closeEvent(self, event):
        pd.DataFrame(self.db.props).to_csv(self.rooms_filename, index = False, sep = '|')
        tmpclients = self.clientdb[0].to_dict()
        for client in self.clientdb:
            tmp = client.to_dict()
            for key in tmp:
                tmpclients[key].update(tmp[key])
        self.clients = pd.DataFrame(tmpclients)
        self.clients.to_csv(self.clients_filename, index = False, sep = '|')

    def search(self):
        for id in range(self.q):
            self.ListItems[id].setBackground(QColor('#ffffff'))
            if ((self.in_roomsnum.value() == self.db.props['rooms'][id])
            and (self.in_hastv.isChecked() == self.db.props['hasTv'][id])
            and (self.in_haswifi.isChecked() == self.db.props['hasWifi'][id])
            and (self.in_hassafe.isChecked() == self.db.props['hasSafe'][id])
            and (self.in_haspets.isChecked() == self.db.props['hasPets'][id])
            and (self.in_smoker.isChecked() == self.db.props['smoker'][id])
            and (self.in_hasbreakfast.isChecked() == self.db.props['hasBreakfast'][id])):
                self.ListItems[id].setBackground(QColor('#beaed4'))
    
    def reservate(self):
        msg = QMessageBox()
        msg.setWindowTitle('Hata')
        if not ((self.in_name.text() == '') or (self.in_lastname.text() == '') or (self.in_mobilenum.text() == '')) and self.db.props['clientId'][self.ListRooms.currentRow()] != -1:
            current_client = cl.Client(id=len(self.clientdb),
                                        name = self.in_name.text(),
                                        lastname = self.in_lastname.text(),
                                        middlename = self.in_middlename.text(),
                                        mobile_number = self.in_mobilenum.text(),
                                        datein=self.in_datein.date().toPyDate(),
                                        dateout=self.in_dateout.date().toPyDate())
            self.clientdb.append(current_client)
            self.db.props['clientId'][self.ListRooms.currentRow()] = current_client.id
            msg.setText('Забронировано!')
        else: msg.setText("Не забронировано!")
        msg.exec_()                        

    def _roomProps(self):
        id = self.ListRooms.currentRow()
        props = self._makePretty(id)
        self.movie_screen.setToolTip("<html><head/><body>{0}{1}</body></html>".format(props[0], props[1]))
        self._setMovie(id)

    def _setMovie(self, id):
        self.movie = QMovie(self.scriptDir + os.path.sep + 'vids' + os.path.sep + '%d.gif' % id)
        self.movie_screen.setMovie(self.movie)
        self.movie.start()

    def _makePretty(self, id=0):
        pretty = ''
        tmp = ''

        if self.db.props['clientId'][id] != -1:
            pretty += '<p>ЗАБРОНИРОВАНО</p>'

        for key in self.db.props:
            if key != 'vidId' and key != 'clientId':
                if key == 'rooms':
                    pretty += '<p>Комнат: '+str(self.db.props['rooms'][id])+'</p>'
                elif self.db.props[key][id]:
                    tmp += '<p>'+self.db.expl[key]+'</p>'
        return [pretty, tmp]

    def _format_range(self, format):
        d0 = min(self.in_datein.date(), self.in_dateout.date())
        d1 = max(self.in_datein.date(), self.in_dateout.date())
        while d0 <= d1:
            self.calendar.setDateTextFormat(d0, format)
            d0 = d0.addDays(1)

    def highlight(self):
        highlight_format = QTextCharFormat()
        self._format_range(QTextCharFormat())
        self.in_dateout.setMinimumDate(self.in_datein.date())
        self.calendar.setSelectedDate(self.in_dateout.date())
        highlight_format.setBackground(self.calendar.palette().brush(QPalette.Highlight))
        highlight_format.setForeground(self.calendar.palette().color(QPalette.HighlightedText))
        self._format_range(highlight_format)

def main():
    app = QApplication(sys.argv)
    window = App()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()