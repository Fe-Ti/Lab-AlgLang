# ЛР 2

**Задание:**

1. Вывести таблицу ASCII символов (символы и коды).
2. Осуществить проверку введённого пользователем символа: если символ цифра – вывести соответствующее
сообщение; если символ буква – вывести соответствующее сообщение; в иных случаях вывести сообщение о
том, что символ неизвестен.
3. Вывести на экран значение y(x). x ∈ Z, x ≥ 0 вводится пользователем с клавиатуры,
```
              .-
              |  -1, если x mod 4 = 0;
      y(x) = _|   x, если x mod 4 = 1;
              |   1 / x, если x mod 4 = 2;
              |  -x, если x mod 4 = 3.
              '-
```
4. Вычислить, приближённое значение с точностью 10^(-2),..., 10^(-6) . Определить, как меняется число итераций в зависимости от точности.

    sin x = x - (x^3)/(3!) + (x^5)/(5!) - ... + ((-1)^n)*(x^(2n + 1))/((2n + 1)!)