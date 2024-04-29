# Хэш-таблица: исследование различных хэш-функций и возможностей оптимизации.

# Часть первая: хэш-функции.

## Описание работы

В первой части в учебных целях исследуются различные (в основном простейшие и неприменимые на практике) хэш-функции. 

Элементами хэш-таблицы являются пары "ключ-значение": ключом являются слово, состоящее из букв латинского алфавита или цифр, значением - количество раз, которое данное слово встретилось во входных данных. В качестве входных данных должен быть использован текстовый файл, в котором каждое слово находится на отдельной строке, без пробелов. Программа для каждой хэш-функции по очереди помещает слова из входных данных в хэш-таблицу, а затем создает в указанной папке файл с именем хэш-функции и записывает в него полученное распределение (длина цепочки в каждой ячейке хэш-таблицы).

## Подготовка входного файла

Для того чтобы превратить файл с неким текстом (например, `texts/miserables_vol1.txt`) во входной файл программы нужного формата, можно использовать скрипт на Python, запускаемый следующей командой из основной директории: 
```
python3 py_scripts/parse.py *входной файл* *имя выходного файла*
```

Пример:
```
python3 py_scripts/parse.py texts/miserables_vol1.txt texts/input.txt
```

Чтобы посчитать количество уникальных слов в файле (это может быть нужно для оценки размера хэш-таблицы), можно использовать другой скрипт, входным файлом для которого должен быть уже подготовленный файл (каждое слово на своей строке):
```
python3 py_scripts/uni_words.py *входной файл*
```

Пример:
```
python3 py_scripts/uni_words.py texts/input.txt
```


## Тестирование хэш-функций
1. Используйте команду `make`, чтобы скомпилировать программу.
2. В программе используются следующие аргументы командной строки:
    1. `--input` (`-i`) : входной файл
    2. `--output` (`-o`) : имя директории, в которой будет созданы файлы с результатами тестирования.
    3. `--table-size` (`-s`) : количество ячеек в хэш-таблице.
3. Запустите программу с нужными аргументами или самостоятельно, или с помощью команды `make run`. Пример: 
```
make run ARGS="-i texts/input.txt -o out -s 10271"
```

## Анализ результатов тестирования хэш-функций
Чтобы построить гистограмму распределения одной из хэш-функций, используйте скрипт:
```
python3 py_scripts/draw_hist.py *файл с результатами теста*
```

Пример:
```
python3 py_scripts/draw_hist.py out/hash_checksum
```

При запуске скрипта откроется интерактивное окно matplotlib. В заголовке гистограммы написаны название предоставленного файла и дисперсия (variance) данного распределения. Чем меньше значение дисперсии, тем равномернее распределение и выше скорость поиска в таблице (за счёт уменьшения средней длины цепочки).

### Полученные гистограммы:
- Входной файл для тестирования: `texts/input.txt`, полученный из `texts/miserables_vol1.txt`. 
- Размер хэш-таблицы: 10271 (простое число)

Код хэш-функций можно посмотреть в /src/hashfuncs.cpp.

![](/imgs/hash_funcs_hists/hash_const.png)
Функция возвращает всегда константное значение (19). Результат - единственная цепочка длиной в количество уникальных слов. Польза функции в том, что можно устроить проверку зрения (сможете увидеть столбик на гистограмме?)

![](/imgs/hash_funcs_hists/hash_first_letter_ascii.png)
Функция возвращает ascii-код первой буквы слова. Ожидаемо очень малый диапазон значений.

![](/imgs/hash_funcs_hists/hash_word_len.png)
Функция возвращает длину слова. Ожидаемо очень малый диапазон значений.

![](/imgs/hash_funcs_hists/hash_checksum.png)
Функция считает сумму ascii-кодов всех букв слова. Диапазон значений уже хотя бы достаточно широкий, чтобы он был виден на гистограмме, но все ещё довольно мал. Кроме того, внутри диапазона нет равномерности распределения.

![](/imgs/hash_funcs_hists/hash_rol_xor.png)
Функция итеративно использует ROL (битовый поворот влево) и XOR (исключающее или). Охвачен почти весь диапазон значений, дисперсия приблизилась к единице.

![](/imgs/hash_funcs_hists/hash_ror_xor.png)
Функция итеративно использует ROR (битовый поворот вправо) и XOR (исключающее или). **Результат отличается от предыдущей функции, несмотря на кажущееся малое различие, состоящее только в замене ROL на ROR. Охвачен меньший диапазон значений (больше пробелов), дисперсия около 5.** 

![](/imgs/hash_funcs_hists/hash_murmur3.png)
Используется известная хэш-функция murmur3. Дисперсия практически равна единице, визуально наблюдается равномерное распределение, а максимальный load factor равен 6.

---

# Часть вторая: оптимизации.

## Описание работы

Рассматривается следующая задача, использующая хэш-таблицу из первой части работы:
1. Хэш-таблица **один раз** заполняется известным набором входных данных (пары "слово" : "количество вхождений"). Входные данные состоят из известного заранее, не изменяющегося набора слов, которые могут повторять в каком-то порядке.
2. Производится **большое** количество запросов поиска в хэш-таблицу. Слова для поиска берутся из второго множества, про которое заранее известно, что максимальная длина слова не превышает максимальную длину слова из первого множества.

Требуется оптимизировать функцию поиска хэш-таблицы под данный сценарий работы.

### Компиляция программы для тестирования

Обычная команда `make` собирает в отладочном режиме, что не очень подходит для тестирования. Используется следующая команда:
```
make for_prof
```

Если требуется использовать флаг оптимизации компилятора, отличный от `-O3`, используйте команду вида (пример для `-O0`):
```
make for_prof OPTIMIZE=-O0
```

### Тестирование

Для запуска теста производительности поиска используется флаг `-t` с опциональным аргументом в виде имени файла, задающего множество слов для поиска. Данный файл должен быть подготовлен так же, как файл с входными данными (см. предыдущую часть). ВНИМАНИЕ: между именем файла и опцией НЕ должно быть пробела, например, `-tfile.txt`.

Стандартные настройки:
```
Input file: texts/input.txt
Search file: texts/search.txt
Hashtable's size: 10271 (подходит для texts/input.txt)
```
Команда для запуска тестирования со стандартными настройками:
```
make run ARGS="-t"
```

В конце тестирования выводится значение ("search perforamnce test dummy variable"), являющееся суммой всех результатов запросов и равное `732511132`. Данное число не должно меняться при использовании одной и той же пары множества входных слов и множества слов для поиска. ВАЖНО: это число рассчитывается заново для каждой итерации теста, а потому **не зависит** от количества итераций тестирования.
### Профилирование

Для определения узких мест в программе выбран профилировщик `perf` из `linux-tools`. (До этого были неудачные попытки использовать callgrind+kcachegrind и gprof, отнявшие значительное количество времени). Используются две основные команды:

- Компиляция и сбор данных профилирования при стандартных настройках:
```
make perf_record
```
Результаты записываются в файл `perf.data`.

- Отображение результатов:
- Таблица, позволяющая увидеть функции, имеющие наибольшее "собственное время":
```
make perf_report
```

### Просмотр ассемблерного листинга

В некоторых случаях может быть полезно изучить ассемблерный листинг файла некого исходного кода, полученный при тех же флагах компиляции, что и при компиляции для профилирования. Для этого используется следующая команда (на примере файла hashtable.cpp):

```
make make_asm FILE="src/hashtable.cpp"
```

Данная команда создаст ассемблерный листинг с названием `hashtable.s` в общей папке.

## Протокол профилирования и оптимизаций

### О методике и точности измерений коэффициента улучшение оптимизации

Для вычисления коэффициента, отражающего во сколько раз некоторая оптимизация ускорила работу программы в целом, применяется следующая методика:

1. Для уменьшения влияния сторонних факторов тестирование производится при единственной открытой программе (терминале) и установленной максимальной частоте процессора. (см. ниже про установку частоты). С помощью команды `make show_freq_policy` можно увидеть установленные на данный момент ограничения.

2. Выполняется команда `make for_prof`, чтобы скомпилировать программу для профилирования.

3. Выполняется команда (`time ./bin/prog -t`), которая возвращает оценочное количество секунд, затраченное на исполнение программы (пункт real).

4. Пункт `3.` выполняется ~15 раз подряд, из которых используются последние 10 полученных значений времён.

5. Полученные значения записываются в файл `time_tests/time_test_N`, где `N` - номер оптимизации, каждое на своей строчке.

6. С помощью скрипта вычисляется среднее значение, его абсолютная и относительная ошибка: `python3 py_scripts/abs_error.py time_tests/time_test_N`

7. Данное значение сравнивается с предыдущим и делается вывод об эффективности оптимизации.

**Установка максимальной частоты процессора**: Для этого применяется команда:
```
make set_max_freq MAX_FREQ=**частота в GHz**
```
Стандартное значение устанавливаемой частоты = 1.6GHz (применяется при опускании параметра MAX_FREQ).

---

### Начальное состояние

**Общее время выполнения**: (13.572 ± 0.014) секунд, 0.1%

---

### Первая оптимизация

**До**:

![](/imgs/perf_res_screenshots/0.png)

**Анализ**: Наиболее "тяжелой" является функция `__strcmp_avx2`, выполняющая роль strcmp при -O3. Просмотрев исходник, можно заметить, что отстуствие выравнивания слов приводит к затруднению при использовании SIMD инструкций.

**Гипотеза**: достичь лучшего результата получится, если помещать слова в блоки по 32 байта (слов длиннее 32 символов не встречается в данных), и использовать SIMD инструкции, работающие с выровненными блоками по 32 байта, для реализации strcmp.

**После**:

**Общее время выполнения**: (12.624 ± 0.013) секунд, 0.1%

**Эффективность**: ~7%. Просмотр листинга показывает, что сами инструкции, реализующие интринсики, довольно тяжелые: 

![](/imgs/perf_res_screenshots/1.1.png)

Но будем считать данную оптимизацию всё равно оправданной.

---

### Вторая оптимизация

**До**:

![](/imgs/perf_res_screenshots/1.png)

**Анализ**: Наиболее "тяжёлой" является функция `hashtable_find`. Самым горячим местом являются SIMD-инструкции, упомянутые выше, но так же выделяется инструкция mov: 

![](/imgs/perf_res_screenshots/1.2.png)

Можно предположить, что этот mov подготавливает `search_word_aligned`, зазря повторяя это каждый раз в цикле, из-за чего это место и является таким медленным, но анализ ассемблерного листинга показывает, что компилятор догадывается положить `search_word_aligned` в `ymm1` один раз и до всех циклов, а значит проблема не в этом.

Cледующим по горячести является инструкция divq, использующася для взятия остатка от деления хэша на размер хэш-таблицы. Переходя к другим функциям, следующей по "тяжёлости" является функция хэширования, но единственная возможная её оптимизация - замена на более быстродействующую. Затем идут 4 функции dedlist. Все они - однострочные, но компилятор не имеет права их встроить.

**Гипотеза**: Если захардкодить размер хэш-таблицы (это можно сделать, т.к. сценарий предполагает единственный набор входных данных), компилятор сможет соптимизировать взятие остатка от деления, заменив на набор более простых инструкций. Вынесение в хэдер с модификатором inline упомянутых функций dedlist поможет избежать задержек, вызванных инструкцией ret.

**После**:

**Общее время выполнения**: (9.607 ± 0.008) секунд, 0.08%

**Эффективность**:
- относительно предудыщего:          ~24%
- относительно начального состояния: ~29%

Казалось бы, такое просто изменение, но дало значительный прирост. С другой стороны, это уменьшило общность, но в рассматриваемом сценарии это не играет никакой роли.

---

### Третья оптимизация

**До**:

![](/imgs/perf_res_screenshots/2.png)

**Анализ**: Лидирующую позицию по "тяжёлости" всё так же занимает `hashtable_find`. Вновь посмотрим её аннотацию:

![](/imgs/perf_res_screenshots/2.1.png)

На скриншоте отображены все самые горячие места. На первом месте находится инструкция сравнения, далее - инструкции, загружающую из памяти в регистры какую-либо информацию из dedlist. 

**Гипотеза**: Отказ от dedlist и замена его двумя синхронизированными массивами константной длины (каждый на своё поле структуры WordCount, которая на данный момент хранится в dedlist) улучшит производительность, т.к. не потребуется:
- обращаться в память для получения размера массива, т.к. он будет константой (см. первую по порядку красную инструкцию на скриншоте);
- получать якорь головы списка, получать якорь следующего элемента списка (см. вторую и третью по порядку красную инструкцию);
Кроме того, теоретически улучшится взаимодействие с кэшом, т.к. будет просматриваться последовательно массив только из самих слов (__m256i), а значит в кэш-линии будут оказываться только они, в отличие от случая использования dedlist, когда в кэш попадают структуры WordCount, поле repeats которых засоряет линию.

**После**:

**Общее время выполнения**: (4.925 ± 0.003) секунд, 0.06%

**Эффективность**: 
- относительно предудыщего:          ~49%
- относительно начального состояния: ~64%

Вывод: выбрасывать готовые универсальные библиотеки и вместо них писать частные узкие решения (под конкретный сценарий работы) может дать очень значительный прирост.

---

### Четвёртая оптимизация

**До**:

![](/imgs/perf_res_screenshots/3.png)

**Анализ**: Всё ещё основная нагрузка приходится на `hashtable_find` в силу AVX-инструкции сравнения, что можно увидеть из аннотации, но ничего значительно (и легко) оптимизировать здесь не выйдет. Единственной оставшейся функцией, которую можно оптимизировать, является хэш-функция.

**Гипотеза**: Замена данной хэш-функции на поддерживаему аппаратно (`crc32`) позволит добиться хорошего ускорения производительности.

