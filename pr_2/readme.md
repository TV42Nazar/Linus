# Завдання 2.1
Напишіть програму для визначення моменту, коли time_t закінчиться.Дослідіть, які зміни відбуваються в залежності від 32 та 64 бітної архітектури. Дослідіть сегменти виконуваного файлу.

---

Я не знав як 64 бітний `time_t` запустити як 32 бітний і навпаки.
Дізнався про дуже зручний спосіб для windows на stackoverflow,
але він не працює для лінукса. В інтернеті знайшов прапорець `m32`, але він 
в мене не також працює. Дізнавшись більше про сам `time_t`, було обрано
рішення програмно визначити максимум за допомогою побітового зсуву 
та дати можливість вибору ще на етапі запуску програми

---

## Програма
Програма приймає аргумент командного рядка (-t 32 або -t 64), що імітує розрядність системного таймера. Вона обчислює максимальне можливе значення часу (кількість секунд з 1 січня 1970 року), яке може вмістити 32-бітне або 64-бітне ціле число зі знаком

---
## Запуск

- для 32 біт:
```bash
./time_test.exe
```
або

```bash
./time_test.exe -t 32
```

- для 64 біт:
```bash
./time_test.exe -t 64
```

---
---
### Результати

32:

<img width="245" height="34" alt="image" src="https://github.com/user-attachments/assets/acbc1192-3b1c-4aec-a55e-9c657ec843b1" />

64:

<img width="247" height="49" alt="image" src="https://github.com/user-attachments/assets/291946a8-e975-4e3b-984b-19c7a9aac667" />

---
# Завдання 2.2
У цій частині ми використано утиліти size та ls -l , щоб зрозуміти, куди компілятор поміщає різні типи змінних

---
# Компіляція
Для компіляції і подальшого виконання завдання були використані команди, зображені нижче. На місці `name1` , `name2` — **необхідно ввести свої назви**

базова компіляція:
```bash
gcc name1.c -o name2.exe
```
заображення розміру файлу на диску:
```bash
ls -l name2.exe
```
зображення розподілу файлу за сегментами:
```bash
size name2.exe
```

---
## 1. Базова програма
```bash
#include <stdio.h>
int main() {
printf("Hello World\n");
return 0;
}
```
### Результати
Ці дані будуть необхідними для порівняння

розмір:

<img width="602" height="41" alt="image" src="https://github.com/user-attachments/assets/d9951ad8-2095-4d70-b5f5-a086720b1cc6" />

сегменти:

<img width="570" height="70" alt="image" src="https://github.com/user-attachments/assets/0d0f4494-5e8e-49e4-90a3-a528920bf6d6" />

---
## 2. BSS
```bash
#include <stdio.h>
int array[1000];
int main() {
 printf("Hello World\n");
 return 0;
}
```
### Результати
Колонка bss в утиліті size збільшилася. Неініціалізовані глобальні змінні потрапляють у сегмент BSS

розмір:

<img width="420" height="39" alt="image" src="https://github.com/user-attachments/assets/be683123-18ed-4893-a971-25c1e4a5ac58" />


сегменти:

<img width="392" height="47" alt="image" src="https://github.com/user-attachments/assets/47ee70c8-e0eb-4fb5-bc79-3046e1f760a6" />

---
## 3. Data
```bash
#include <stdio.h>
int array[1000] = {1};

int main() {
 printf("Hello World\n");
return 0;
}
```
### Результати
Колонка bss зменшилася, натомість колонка data виросла. Розмір файлу на диску також збільшився

розмір:

<img width="597" height="40" alt="image" src="https://github.com/user-attachments/assets/ca5537da-33de-4e6f-aa0b-a2ac2b02079c" />



сегменти:

<img width="564" height="69" alt="image" src="https://github.com/user-attachments/assets/500cabcb-7e5e-4357-b6cb-4fbb41d14d2b" />

---
## 4. Stack
```bash
#include <stdio.h>
int main() {
int local_empty[10000];
int local_full[10000] = {1};
return 0; }
```
### Результати
Сегменти data та bss залишилися маленькими

розмір:

<img width="601" height="40" alt="image" src="https://github.com/user-attachments/assets/5d4e92ea-f29e-4edf-8197-1b3059801d50" />

сегменти:

<img width="561" height="53" alt="image" src="https://github.com/user-attachments/assets/2ac8e9b2-9157-4aca-865c-92c5cb6af95c" />

---
## 5. Прапорець -g
```bash
#include <stdio.h>
int main() {
int local_empty[10000];
int local_full[10000] = {1};
return 0; }
```
Цього разу до рядку компіляції було додано прапорець `-g`
### Результати
`-g` Додає таблиці символів для дебагера

розмір:

<img width="642" height="45" alt="image" src="https://github.com/user-attachments/assets/3d536994-f2fb-42eb-960e-e149d8b55d8f" />


сегменти:

<img width="612" height="70" alt="image" src="https://github.com/user-attachments/assets/6950f3bd-8feb-4eb5-bfe7-6c9434dfb532" />

---
## 6. Прапорець -Os
```bash
#include <stdio.h>
int main() {
int local_empty[10000];
int local_full[10000] = {1};
return 0; }
```
Цього разу до рядку компіляції було додано прапорець `-Os`
### Результати
`-Os` Заставляє компілятор викидати зайві інструкції.

розмір:

<img width="644" height="44" alt="image" src="https://github.com/user-attachments/assets/7cd381e3-c93f-430c-b42b-727322087f29" />



сегменти:

<img width="624" height="61" alt="image" src="https://github.com/user-attachments/assets/6b3c8803-9775-4cfc-a364-b3a7ec472f65" />

---

# Завдання 2.3
Скомпілюйте й запустіть тестову програму, щоб визначити приблизне розташування стека у вашій системі:

---

## Опис роботи

Функція check_stack порівнює адресу локальної змінної батьківської функції з адресою власної локальної змінної. Оскільки кожен новий виклик створює новий кадр у стеку, різниця в адресах вказує на напрямок його росту.

---

### Результати
**Text** має найменшу адресу з усіх сегментів, оскільки код завантажується на початку віртуальної пам'яті.

**Data** та **BSS** знаходяться одразу за сегментом коду.

**Heap** знаходиться ще вище, адреса виділяється динамічно функцією malloc.

При виклику функції extend_stack був оголошений локальний масив на 10000 елементів.
Адреса нової вершини стека (large_array) виявилася значно МЕНШОЮ за початкову адресу (змінна i). Це повністю підтверджує примітку до завдання: стек дійсно зростає вниз — від пам'яті з більшими значеннями адрес до менших. Великий масив "відкусив" шмат пам'яті, змусивши вказівник стека опуститися вниз.

<img width="478" height="140" alt="image" src="https://github.com/user-attachments/assets/05f3ed0c-4d97-4ed8-ba97-449c81ef799f" />

---

# Завдання 2.4
Ваше завдання – дослідити стек процесу або пригадати, як це робиться

---
## Компіляція та запуск
```bash
gcc -g stacker.c -o stacker.exe
./stacker.exe &
```
## Робота з програмою
<img width="500" height="119" alt="image" src="https://github.com/user-attachments/assets/820f2d2a-406e-434a-8337-e408f059e6f4" />

Маючи `PID` процесу , відбувається підключення до нього за допомогою налагоджувача `GDB` і використовуємо команду `bt`  для перегляду кадрів стека:

```bash
gdb -p 2066
(gdb) bt
```
Команда `backtrace` виводить список викликаних функцій у зворотному порядку

---

# Завдання 2.5 варіант 15
15.	Виміряйте час доступу до різних сегментів пам’яті.
    
---

## Опис роботи

Програма виконує багато операцій інкременту для змінних у різних сегментах: **Data** , **BSS** , **Stack**  та **Heap** . Час виконання вимірюється функцією clock().

## Компіляція та запуск
Якщо увімкнути оптимізатор, він зрозуміє, що цикли просто збільшуються, і замінить весь цикл на одну математичну операцію , що зробить час виконання нульовим.
```bash
gcc pr2.c -o pr2.exe
./pr2.exe
```

---
### Результати
- **stack** — найшвидший
- **data && bss** — середні
- **heap** — найповільніший

<img width="228" height="84" alt="image" src="https://github.com/user-attachments/assets/4b8cdcb4-c036-4048-b5fa-cb51d6ec1605" />

---


