# ЛР 5
Контейнеры и алгоритмы STL.

**Задание:**

1. Создать неупорядоченный ассоциативный массив с повторяющимися значениями ключей (unordered_multimap). Тип ключа – int, тип значения – string.
    1. Удалить значения (erase) с ключами 0 и 3.
    2. Вставить 4 новых значения (insert) c ключом 6.
    3. Cкопировать элементы в упорядоченный ассоциативный массив (map).
2. В полученном массиве (map):
    1. Посчитать число элементов, имеющих отрицательные ключи (count_if).
    2. Все ключи выделить в вектор (transform).
3. В полученном векторе (vector):
    1. Найти элемент, равный 6 (find).
    2. Заменить отрицательные значения на -2 (replace_if).
    3. Отсортировать элементы по убыванию (sort).
    4. Скопировать значения в неупорядоченное множество уникальных элементов (set).

Результат каждого действия выводить на экран. Вывод осуществлять через for_each.