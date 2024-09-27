import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

// Класс для работы с массивом символов строки
class Array {
    private String arr; // Поле для хранения строки

    // Конструктор класса, инициализирующий строку
    Array(String arr) {
        this.arr = arr;
    }

    // Метод для установки новой строки
    public void setArr(String arr) {
        this.arr = arr;
    }

    // Метод для обновления строки
    public void update() {
        // Преобразуем строку в массив символов (строк длиной 1)
        String[] a = arr.split("");

        // Преобразуем массив в список для удобного удаления элементов
        List<String> list = new ArrayList<>(Arrays.asList(a));
        int j = arr.length(); // Длина оригинальной строки

        // Если длина строки больше 15
        if (arr.length() > 15) {
            for (int i = 0; i < j; i++) {
                // Перезапускаем цикл, если достигли конца списка
                if (i >= list.size()) {
                    j = i; // Обновляем длину строки
                    i = 0; // Сбрасываем индекс
                }
                // Если символ не является заглавной буквой, удаляем его
                if (!Character.isUpperCase(a[i].charAt(0))) {
                    list.remove(i); // Удаляем элемент
                    a = list.toArray(new String[list.size()]); // Обновляем массив
                }
            }
        }
        // Обновляем строку из списка символов
        arr = String.join("", list);
    }

    // Метод для вывода строки
    public void print() {
        System.out.println(arr);
    }
}

// Главный класс для запуска программы
public class Main {
    public static void main(String[] argc) {
        // Создаем объект класса Array с начальной строкой
        Array a = new Array("sdlfjhLJHJKHkhkjhKJHKJHKkjh");
        a.update(); // Обновляем строку
        a.print(); // Выводим обновленную строку

        // Устанавливаем новую строку и обновляем
        a.setArr("wdbf^7gkjHIBHYU7y8hvhfyfT^");
        a.update(); // Обновляем строку
        a.print(); // Выводим обновленную строку

        // Устанавливаем еще одну новую строку и обновляем
        a.setArr("JddddsAdsdsdssdsVsdadA");
        a.update(); // Обновляем строку
        a.print(); // Выводим обновленную строку
    }
}