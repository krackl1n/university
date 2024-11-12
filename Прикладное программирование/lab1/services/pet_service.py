from exceptions.exceptions import InvalidPetTypeException
from models.pets import Cat, Dog, Fish, Hamster, Horse, Parrot, Rabbit, Snake, Turtle


class PetService():
    pet_factory_map = {
        'Dog': lambda name, age: Dog(name, age),
        'Cat': lambda name, age: Cat(name, age),
        'Parrot': lambda name, age: Parrot(name, age),
        'Rabbit': lambda name, age: Rabbit(name, age),
        'Fish': lambda name, age: Fish(name, age),
        'Hamster': lambda name, age: Hamster(name, age),
        'Turtle': lambda name, age: Turtle(name, age),
        'Snake': lambda name, age: Snake(name, age),
        'Horse': lambda name, age: Horse(name, age)
    }

    def create(self, pet_type: str, name: str, age: int):
        if pet_type not in self.pet_factory_map:
            raise InvalidPetTypeException(pet_type)
        return self.pet_factory_map[pet_type](name, age)
    
    def delete(self):
        print(self.pet)
        pass
    

