class DataBase:

    def __init__(self, props=None):
        self.props = props
        self.expl = {'rooms':'Комнат:', 'hasTv':'Tv', 'hasWifi':'Wi-Fi', 'hasSafe':'Сейф', 'hasPets':'Разрешены животные', 'smoker':'Для курящих', 'hasBreakfast':'Завтрак'}