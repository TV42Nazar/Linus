# Підготовка до виконання робіт

### Docker

- Для виконання практичної необхідно встановити docker.
```bash
sudo apt update
sudo apt install docker.io -y
```

- Команда перевірки правильності встановлення 
```bash
sudo docker --version
```

- Команда запуску docker'a
```bash
docker run -it ubuntu bash
```

- Команда запуску docker'a з root правами
```bash
docker run -it ubuntu bash
```

- Встановлення nano на docker
```bash
apt update && apt install nano build-essential -y
```

---

### Perf

- Для завдання 3.2 необхідно встановити додатковий функціонал наступним шляхом:
```bash
apt update && apt install linux-tools-generic linux-tools-common -y
```
- Далі по ходу встановлення слід послідовно вибрати ряд опцій пов'язаних з вибором локації.

- Для перевірки версії введіть
```bash
perf --version
```
*У мене цей спосіб не вийшов, тому я використав запропоновану версію в консолі.*
```bash
apt install linux-tools-6.8.0-94-generic linux-cloud-tools-6.8.0-94-generic -y
```
---

# Завдання 3.1

Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Для цього виконайте команди у вказаному порядку: ...

---

## Виконання

1) Спочатку вводимо `ulimit -n`

<img width="245" height="36" alt="image" src="https://github.com/user-attachments/assets/0869589b-de94-4119-8449-4ad15df5d0e7" />

2)  `ulimit -aS | grep "open files"`

<img width="423" height="33" alt="image" src="https://github.com/user-attachments/assets/c5c628ad-8f25-49e4-ba41-72880a9df083" />


3) `ulimit -aH | grep "open files"`

<img width="423" height="35" alt="image" src="https://github.com/user-attachments/assets/8f964e6e-7c02-460f-8d57-5a107518e2a7" />


4) `ulimit -n 3000`
<img width="420" height="33" alt="image" src="https://github.com/user-attachments/assets/a34e0964-cdb6-4592-9e10-c6d1501134c1" />

5) `ulimit -aS | grep "open files"`

<img width="415" height="34" alt="image" src="https://github.com/user-attachments/assets/608aecd6-998b-42ff-b421-3d5b0d89c23c" />

6) `ulimit -aH | grep "open files"`

<img width="418" height="37" alt="image" src="https://github.com/user-attachments/assets/c62bb22f-57d3-4f32-8937-4c2e16c9ff80" />

7) `ulimit -n 3001`

<img width="571" height="36" alt="image" src="https://github.com/user-attachments/assets/209ac702-0b4b-4ec2-80ff-98f95e71657d" />

8) `ulimit -n 2000`

<img width="290" height="29" alt="image" src="https://github.com/user-attachments/assets/6fcdaf57-0ca3-4252-a443-2691e971a5c5" />

9) `ulimit -n`

<img width="248" height="31" alt="image" src="https://github.com/user-attachments/assets/1114d54d-db2d-4109-90b4-9a8fa746f10b" />

10) `ulimit -aS | grep "open files"`

<img width="420" height="38" alt="image" src="https://github.com/user-attachments/assets/d2ca558e-f800-4d5d-a14c-7be22200df28" />

11) `ulimit -aH | grep "open files"`

<img width="410" height="36" alt="image" src="https://github.com/user-attachments/assets/658e598f-5760-4d7f-9ada-186ed60001ef" />

### Поведінка з root правами

- Можна помітити, що зараз можна збільшити `Hard` ліміт.

<img width="417" height="180" alt="image" src="https://github.com/user-attachments/assets/eb9ab05c-3a6c-46ff-9099-4df607afc065" />

- Також слід зазначити, що з `Soft` ліміт не може бути більшим за `Hard`. При спробі вводу більщої к-сті ресурсів за системні також появиться помилка:

<img width="587" height="82" alt="image" src="https://github.com/user-attachments/assets/5cd38af6-a947-4ed4-b2f9-a8f0470818f9" />

---

# Завдання 3.2
У Docker-контейнері встановіть утиліту perf(1). Поекспериментуйте з досягненням процесом встановленого ліміту.

---
## Виконання

Тут було запущено нескінченний цикл, який нічого не робить, тільки гріє процесор

<img width="667" height="330" alt="image" src="https://github.com/user-attachments/assets/313ec37d-4d3a-42d9-b6d0-6e53ee883157" />

## Рeзультат

- Можемо побачити на скільки швидко програма маштабувалася до та *(не в нашій персективі)* поза наданих заборон. 

---

# Завдання 3.3

Напишіть програму, що імітує кидання шестигранного кубика. Імітуйте кидки, результати записуйте у файл, для якого попередньо встановлено обмеження на його максимальний розмір (max file size). Коректно обробіть ситуацію перевищення ліміту.

---
## Програма
```bash
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fptr = fopen("result.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));

    int count = 0;
    while (1) {
        int roll = (rand() % 6) + 1;
        
        int result = fprintf(fptr, "Rolled: %d\n", roll);
        
        if (result < 0) {
            printf("\nError writing file!\n");
            perror("Cause"); // Виведе системну причину (File too large)
            break;
        }

        count++;
        // Кожні 1000 записів скидаємо буфер на диск
        if (count % 1000 == 0) {
            fflush(fptr);
            printf("n: %d\n", count);
        }
    }

    fclose(fptr);
    return 0;
}
```

## Виконання

**Перед запуском необхідно встановити `ліміт`**
```bash
ulimit -f 20
```

Тут було запущено нескінченний цикл, який записує у файл все більші та більші значення

<img width="304" height="55" alt="image" src="https://github.com/user-attachments/assets/813c6bcc-2dc8-46d9-9617-00b951122dbc" />

# Завдання 3.4
Напишіть програму, що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36. Встановіть обмеження на час ЦП (max CPU time) і генеруйте результати вибору чисел (7 із 49, 6 із 36). Обробіть ситуацію, коли ліміт ресурсу вичерпано.

--

## Програма
```bash
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void cpu_limit_handler(int signum) {
    const char *msg = "\n\n!!! CATCH SIGXCPU !!! Time limit exceeded.\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    
    _exit(0);
}

void shuffle(int *array, int n) {
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main() {
    signal(SIGXCPU, cpu_limit_handler);

    srand(time(NULL));
    int lotto49[49];
    int lotto36[36];
    long count = 0;

    printf("Starting CPU heavy task...\n");

    while (1) {
        for(int i=0; i<49; i++) lotto49[i] = i+1;
        for(int i=0; i<36; i++) lotto36[i] = i+1;

        shuffle(lotto49, 49);
        shuffle(lotto36, 36);

        count++;
        if (count % 100000 == 0) {
            write(STDOUT_FILENO, ".", 1);
        }
    }
    return 0;
}
```

---

## Рeзультат

Система успішно завершила процес примусово, оскільки жорсткий ліміт часу було вичерпано. Обробник сигналу SIGXCPU не встигає відпрацювати через миттєве завершення процесу ядром.

<img width="1081" height="559" alt="image" src="https://github.com/user-attachments/assets/e68489cb-d4ed-4be3-bcc2-805fb9fdb6dd" />



