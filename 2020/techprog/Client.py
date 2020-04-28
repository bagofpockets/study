class Client:

    def __init__(self, id = None, name = None, lastname = None, middlename = None, mobile_number = None, datein = None, dateout = None):
        self.id = id
        self.name = name
        self.lastname = lastname
        self.middlename = middlename
        self.mobile_number = mobile_number
        self.datein = datein
        self.dateout = dateout

    def to_dict(self):
        return {'name':{self.id:self.name},
                'lastname':{self.id:self.lastname},
                'middlename':{self.id:self.middlename},
                'mobile_number':{self.id:self.mobile_number},
                'datein':{self.id:str(self.datein)},
                'dateout':{self.id:str(self.dateout)}}