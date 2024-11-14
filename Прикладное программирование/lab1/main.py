
from interfaces.serializer_interface import ISerializer
from models.pets import Pet
from services.pet_service import PetService
from storage.storage import Storage
from storage.serializers.json_serializer import JsonSerializer
from storage.serializers.xml_serializer import XmlSerializer
from exceptions.exceptions import InvalidPetTypeException, InvalidFileTypeException


def create_serializer(file_type) -> ISerializer:
    file_types = {
        'json': JsonSerializer(),
        'xml': XmlSerializer()
    }

    if file_type not in file_types:
          raise    InvalidFileTypeException(file_type)
    return file_types[file_type]


def input_pet() -> Pet:
    try:
        pet_type = input("Введите тип питомца (Dog, Cat, Parrot, etc.): ")
        name = input("Введите имя питомца: ")
        age = int(input("Введите возраст питомца: "))
        return pet_service.create(pet_type, name, age)
    except ValueError:
        print("Ошибка: возраст должен быть числом.")
    except InvalidPetTypeException as e:
        print(e)


if __name__ == "__main__":
    pet_service = PetService()
    pets = []
    storage = None

    while True:
        print("\n1. Создать нового питомца")
        print("2. Показать всех питомцев")
        print("3. Издать голос питомцу")
        print("4. Сохранить питомцев в файл")
        print("5. Загрузить питомцев из файла")
        print("6. Выйти")

        choice = input("\nВыберите действие: ")

        match choice:
            case "1":
                pet = input_pet()
                if not pet:
                    continue
                pets.append(pet)
                print(f"Питомец {pet.name} добавлен.")

            case "2":
                if not pets:
                    print("\nПитомцы отсутствуют.")
                    continue
                for pet in pets:
                    pet.info()

            case "3":
                if not pets:
                    print("\nСписок питомцев пуст.")
                    continue
                for idx, pet in enumerate(pets, start=1):
                    print(f"{idx}. {pet.name} ({pet.__class__.__name__})")
                selected_idx = int(input("Введите номер питомца: ")) - 1
                pets[selected_idx].make_sound()

            case "4":
                file_format = input("Сохранить как (json/xml)? ").lower()
                try:
                    storage = Storage(create_serializer(file_format))
                    storage.save_to_file(f"db/pets.{file_format}", pets)
                except InvalidFileTypeException as e:
                    print(e)

            case "5":
                file_format = input("Загрузить из (json/xml)? ").lower()
                try:
                    storage = Storage(create_serializer(file_format))
                    pets = storage.load_from_file(f"db/pets.{file_format}")
                except InvalidFileTypeException as e:
                    print(e)

            case "6":
                print("Выход из программы.")
                break