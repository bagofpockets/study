import datetime

class Room:

    def __init__(self, date_in = datetime.date.today(), date_out = datetime.date.today(), rooms = 0, has_tv = False, has_wifi = False, has_safe = False, has_pets = False, smoker = False, has_breakfast = False):
        self.date_in = date_in
        self.date_out = date_out
        self.rooms = rooms
        self.has_tv = has_tv
        self.has_wifi = has_wifi
        self.has_safe = has_safe
        self.has_pets = has_pets
        self.smoker = smoker
        self.has_breakfast = has_breakfast

if __name__ == '__main__':
    r1 = Room()
    r2 = Room(smoker=True, date_in=datetime.date(2005, 5, 5))
    print(r1.date_in, r2.date_in)