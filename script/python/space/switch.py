class Switch:
    def __init__(self, name, status=False):
        self.name = name
        self.status = status

    def turn(self):
        self.status = not self.status

    def clone(self):
        return Switch(self.name + ".copy", self.status)

    def __str__(self):
        return f"switch({self.name}) is {'on' if self.status else 'off'}"


class Light:
    def __init__(self, name, switch):
        self.name = name
        self.switch = switch

    def turn(self):
        self.switch.turn()

    def get_status(self):
        return self.switch.status

    def set_switch(self, new_switch):
        self.switch = new_switch

    def clone(self):
        return Light(self.name + ".copy", self.switch.clone())

    def __str__(self):
        return f"light({self.name}) with switch({self.switch.name}) is {'on' if self.switch.status else 'off'}"


"""
s1 = Switch("eiei")
s1.turn()
print(Light("uiia", s1))
s2 = s1.clone()
s2.turn()
print(Light("aiiu", s2))
"""
