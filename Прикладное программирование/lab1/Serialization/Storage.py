from serialization.interfaces.ISerializer import ISerializer
from models.Pets import Pet

class Storage:
    def __init__(self, serializer: ISerializer):
        self.serializer = serializer

    def save_to_file(self, filename, pets) -> None:
        try:
            with open(filename, 'w', encoding='utf-8') as file:
                file.write(self.serializer.to_format(pets))
                print(f"Данные сохранены в {filename}")
        except Exception as e:
            print(f"Ошибка при сохранении: {e}")

    def load_from_file(self, filename) -> Pet:
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                data = file.read()
                return self.serializer.from_format(data)
        except FileNotFoundError:
            print(f"Файл {filename} не найден.")
        except Exception as e:
            print(f"Ошибка при загрузке: {e}")
