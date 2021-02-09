# ЛР 7

**Задание:**
реализовать 2 структуры данных – **стек и очередь**, для каждой реализовать
следующие функции:

1. Конструктор – функция, которая инициализирует поля структуры при её создании.
Например, void constructor(Stack& stack) или Stack& constructor();
2. Деструктор – функция, которая будет очищать память, которая была задействована для структуры. Например, void destructor(Stack& stack);
3. Подсчёт кол-ва элементов, которые находятся в структуре. Например, unsigned int size(const Stack& stack);
4. Добавление элемента (push). Например, Stack& push(Stack& stack, Node& node) или
void push (Stack& stack, Node& node);
5. Извлечение элемента (pop). Например, Node& pop(Stack& stack);
6. Вывод на экран элементов структуры. Например, void print(const Stack& stack).