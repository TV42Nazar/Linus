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
#include <stdio.h> int main() {
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
#include <stdio.h> int main() {
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
#include <stdio.h> int main() {
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
