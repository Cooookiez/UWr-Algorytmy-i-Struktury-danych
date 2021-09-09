
# algorytmy sortujace

| Algorytm  |   | Min          | Avg          | Max          |   | Mem     | stabilny? |
| --------- | - | ------------ | ------------ | ------------ | - | ------- | --------- |
| Insertion |   | `n`          | `n^2`        | `n^2`        |   | `1`     | **Tak**   |
| Merge     |   | `n * log(n)` | `n * log(n)` | `n * log(n)` |   | `n`     | **Tak**   |
| Quick     |   | `n * log(n)` | `n * log(n)` | `n^2`        |   | `impl`  | Nie       |
| Heap      |   | `n * log(n)` | `n * log(n)` | `n * log(n)` |   | `1`     | Nie       |
| Counting  |   | `n + m`      | `n + m`      | `n + m`      |   | `n + m` | **Tak**   |
| Radix     |   | `n * l`      | `n * l`      | `n * l`      |   | `n`     | **Tak**   |
| Bucket    |   | `n + k`      | `n + k`      | `n^2`        |   | `n`     | **Tak**   |
| Bubble    |   | `n^2`        | `n^2`        | `n^2`        |   |         | **Tak**   |

## Bubble
  
znam

## quick

## bucket

**opis:** mam minimalna i maxymalna wartosc, oraz parametr k (liczba bucketów). liczba bucketa dla wartosci: `floor((x-a) / (b-a) * k)`. Połączenie posortowanych bucketów da posortowaną liste. dla kazdek bucketu moge wywołac jakikolwiek inny algorytm sortujący (w tym bucket, ale **default insertion**)

## heap

**opis:** KopiecMAX (na szczycie jest największy element)(trzymane w tablicy). Pierwszy element (wierzchołęk) zamieniamy z ostatnim elementem tablicy, największa wartośc trafia na koniec tablicy. następnie psesiej (HeapDown). **Tablica numerowana od 1**

![Heap sort](https://he-s3.s3.amazonaws.com/media/uploads/e9d6f12.png)

## insert

stabilny

### Z wartownikiem

czas dzialania to liczba inwersji + liczba elementów (+-1)

**opis:** Wartownik jest na pozycji `[-1]` i ma wartosc `-inf`. porównujemy zawszze z lewym elementem czy nie większy i jezeli tak to zamieniamy. tablica ma i posortowane i nie posortowane (trzeba zmienna na liczbe posortowanych)

### Bez wartownikiem

**opis:** Algorytm praktycznie ten sam, tylko za kazdym razem patrzymy czy juz nie jest na poczatku tablicy

## merge

### zwykły

**opis:** dzielimy na równe podciagi az do jedengo elementu. a potem scalamy parami

### Polifazowy

**opis:** tzn nie dzielimy na 2 równe, tylko dzielimy w momenci gdy następna wartoś jest mniejsza (dzielimy na maksymalne rosnące podciagi *(tylko raz)*)

## counting

**opis:**

```md
1 1 2 1 3 1 1

// zliczamy ile razy wystapila kazda wartoscs
1 -> 5
2 -> 1
3 -> 1

// ostatni index gdzie sie znajdzie liczba
1 -> 4
2 -> 5
3 -> 6

1 -> 0
2 -> 4
3 -> 6

// od najmniejszej wartosci wypisujemy kazda wartosc tyle razy co zliczylismy
0 1 2 3 4 5 6
1 1 1 1 1 2 3
```

## radix (+counting) (Sortowanie pozycyjne!)

**opis:** Sortujemy najpierw counting sortem po cyfrze jednosci, dziesiatek, itd. **(sortowane stabilnie)**
