# Tree Parser — `trie<T>` Container

> Progetto universitario — Programmazione e Laboratorio A.A. 2023/2024  
> Implementazione di un container `trie<T>` in C++17 con parsing di grammatiche context-free.

---

## Indice

- [Panoramica](#-panoramica)
- [Struttura del progetto](#-struttura-del-progetto)
- [Compilazione](#-compilazione)
- [Formato del file di input](#-formato-del-file-di-input)
- [API del container](#-api-del-container)
- [Iteratori](#-iteratori)
- [Funzionalità opzionali](#-funzionalità-opzionali)
- [Test e debugging](#-test-e-debugging)
- [Consegna](#-consegna)

---

## Panoramica

Il progetto implementa due container C++ templati:

- **`trie<T>`** — container principale, implementato internamente come un albero in cui gli archi sono etichettati con valori di tipo `T` e le foglie con un peso `double`.
- **`bag<T>`** — container di supporto che mantiene i figli ordinati per etichetta crescente.

Il container `trie<T>` rappresenta un **insieme di sequenze pesate**: ogni sequenza è determinata dalle etichette degli archi lungo un cammino dalla radice a una foglia, e il suo peso è il valore `double` memorizzato nella foglia.

**Esempio:** il seguente `trie<char>` rappresenta l'insieme `{(a, 3.1), (bb, 2.9), (bcb, 7.0)}`:

```
children = {
  a 3.1 children = {},
  b children = {
    b 2.9 children = {},
    c children = {
      b 7.0 children = {}
    }
  }
}
```

---

## Struttura del progetto

```
Tree_parser/
├── include/
│   ├── trie.hpp        # Dichiarazioni (non modificare!)
│   └── bag.hpp         # Da implementare (header-only)
├── src/
│   └── trie.cpp        # Da implementare
├── datasets/           # File .tr di esempio per il testing
├── figures/            # Immagini esplicative (README)
├── test/               # File di test
├── Makefile
└── README.md
```

> **Nota:** `trie.hpp` **non va modificato**. I file da consegnare sono esclusivamente `src/trie.cpp` e `include/bag.hpp`.

---

## Compilazione

```bash
make
```

Il progetto usa lo standard **C++17**. Per compilare manualmente con i tool di debug:

```bash
g++ -std=c++17 -Wall -g -fsanitize=address,undefined -o trie_test src/trie.cpp test/test.cpp
```

Per il controllo dei memory leak con Valgrind:

```bash
valgrind --leak-check=full ./trie_test
```

L'output di Valgrind deve sempre terminare con:
```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

## Formato del file di input

Il formato è definito da una **grammatica context-free**. Il parser viene invocato dall'operatore `>>`.

### Foglia

```
<peso> children = {}
```

### Nodo interno

```
children = { <label1> <subtrie1>, <label2> <subtrie2>, ... }
```

Le etichette dei figli devono essere **tutte distinte** (etichette duplicate costituiscono un errore di formato). Spazi, tab e newline sono ammessi ovunque eccetto all'interno della keyword `children` e dei valori numerici.

### Esempi per tipo `T`

**`trie<char>`**
```
children = {
  a 3.1 children = {},
  b children = { b 2.9 children = {}, c children = { b 7.0 children = {} } }
}
```

**`trie<double>`**
```
children = {
  3.14 17.0 children = {},
  2.71 children = { 1.61 children = { 9.8 16.1 children = {} } }
}
```

**`trie<std::string>`**
```
children = {
  languages children = { c++ 1.1 children = {}, java 0.5 children = {} },
  compilers children = { g++ 2.8 children = {}, javac 3.1 children = {} }
}
```

> Su file con formato non valido, il parser deve lanciare `parser_exception`.

---

## API del container

### Costruttori e operatori

| Metodo | Descrizione |
|---|---|
| `trie()` | Costruisce una foglia con peso `0.0` |
| `trie(double w)` | Costruisce una foglia con peso `w` |
| `trie(trie const&)` / `trie(trie&&)` | Copy/move constructor |
| `operator=` | Copy/move assignment |
| `operator==` / `operator!=` | Confronto strutturale |
| `operator>>(istream&, trie&)` | Lettura dal formato testuale |
| `operator<<(ostream&, trie const&)` | Scrittura nel formato testuale |

### Setters / Getters

| Metodo | Descrizione |
|---|---|
| `set_weight(double)` / `get_weight()` | Peso della foglia |
| `set_label(T*)` / `get_label()` | Etichetta dell'arco entrante |
| `set_parent(trie*)` / `get_parent()` | Puntatore al padre |
| `get_children()` | Const reference alla `bag` dei figli |
| `add_child(trie const&)` | Aggiunge un figlio (ordinato per etichetta) |

### Prefix Search

```cpp
trie<T>& operator[](std::vector<T> const& s);
```

Restituisce una reference al sotto-trie raggiunto seguendo il **maggior numero** di elementi di `s` a partire dalla radice.

### Foglia di peso massimo

```cpp
trie<T>& max();
trie<T> const& max() const;
```

Restituisce una reference alla foglia di peso massimo nel (sotto-)trie.

---

## Iteratori

Il container implementa due tipi di **forward iterator**.

### `node_iterator`

Punta a un nodo qualsiasi. `operator++` risale al **padre** del nodo.  
Termina quando l'iteratore è uguale a `trie<T>::root()`.

```cpp
trie<T>::node_iterator root();
```

### `leaf_iterator`

Naviga le foglie da sinistra a destra in **ordine lessicografico** delle sequenze associate.

```cpp
leaf_iterator begin();  // Prima foglia
leaf_iterator end();    // Posizione after-the-last
trie<T> const& get_leaf() const;  // Foglia puntata
operator node_iterator();          // Conversione a node_iterator
```

### Esempio: stampa tutte le sequenze in ordine lessicografico

```cpp
for (auto leaf_it = t.begin(); leaf_it != t.end(); ++leaf_it) {
    trie<T>::node_iterator node_it = leaf_it;
    std::vector<T> s;
    while (node_it != t.root()) {
        s.push_back(*node_it);
        ++node_it;
    }
    std::reverse(s.begin(), s.end());
    for (auto const& x : s) std::cout << x << ' ';
    std::cout << '\n';
}
```

> Gli iteratori devono funzionare correttamente anche su **sotto-tries** ottenuti tramite `operator[]`.

---

## Funzionalità opzionali

### Unione (`operator+` e `operator+=`)

Implementa l'**unione insiemistica** di due `trie<T>`. I pesi delle sequenze in comune vengono sommati. Se una sequenza di un operando è prefisso di una sequenza dell'altro, il peso del prefisso viene sommato a quello della sequenza più lunga nel risultato.

```cpp
trie<T> operator+(trie<T> const&) const;
trie<T>& operator+=(trie<T> const&);
```

### Compattazione (`path_compress`)

Compatta i cammini unari (sequenze di nodi con un solo figlio) in un singolo arco, la cui etichetta è ottenuta combinando le etichette tramite `operator+` del tipo `T`.

```cpp
void path_compress();
```

**Esempio con `T=std::string`:** il cammino `"c" → "dg"` diventa l'arco `"cdg"`.  
**Esempio con `T=int`:** una catena di archi `2 → 3 → 5` diventa un singolo arco `10`.

---

## Note importanti

- `trie.hpp` **non va modificato** in nessuna circostanza.
- `trie.cpp` e `bag.hpp` non possono includere librerie aggiuntive rispetto a quelle già presenti.
- `trie.cpp` **non deve** definire la funzione `main`.
- Il codice viene compilato con `-std=c++17`.
- È attivo un rilevatore automatico di **plagi**: non condividere il codice.

---

## Licenza

Progetto accademico per l'esame di Programmazione e Laboratorio — A.A. 2023/2024. Tutti i diritti riservati.
