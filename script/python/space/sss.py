theperson = []


class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

        print(f"Commit at Person:{self.name}, {self.age}")

    def greeting(self):
        print(f"Greeting from {self.name}")


class Job(Person):
    def __init__(self, name, age, job):
        super().__init__(name, age)
        self.job = job

        print(f"commit job: {self.job}")

    def greeting(self):
        super().greeting()

        print(f"I am {self.name}, as {self.job}, and now I am {self.age} years old.\n")


while True:
    n, a, j = None, None, None
    n, a, j = map(str, input("naj with space: ").split())
    if n == "break":
        break
    theperson.append({"name": n, "age": a, "job": j})

for i in theperson:
    daperson = Job(i["name"], i["age"], i["job"]).greeting()
