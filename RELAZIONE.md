# Rubrica Contatti - Progetto C con NCurses
*Classe: 3° Informatica*  
*A.S. 2024-2025*

## Relazione Tecnica

### 1. Obiettivo del Progetto
Il progetto implementa una rubrica con interfaccia testuale utilizzando la libreria NCurses. L'applicazione consente la gestione di contatti con supporto multilingua.

### 2. Struttura del Codice
Il progetto è organizzato secondo il paradigma della programmazione modulare:

- **Modulo Main** (`main.c`)
  - Gestione dell'interfaccia utente
  - Controllo dell'input

- **Modulo CSV** (`csv.c`, `csv.h`)
  - Gestione della persistenza dei dati

- **Modulo UI** (`contatto.c`, `contatto.h`)
  - Rendering dell'interfaccia

- **Modulo Localizzazione** (`lan.c`, `lan.h`)
  - Gestione multilingua
  - Caricamento delle risorse localizzate

### 3. Implementazione
#### 3.1 Strutture Dati
```c
typedef struct Contatto {
    char nome[MAX_STRLEN];
    char cognome[MAX_STRLEN];
    char eta[MAX_STRLEN];
    char numero[MAX_STRLEN];
    char citta[MAX_STRLEN];
} Contatto;
```

#### 3.2 Gestione File
Il programma utilizza:
- File CSV per i dati (`resources/saves.csv`)
- File properties per le traduzioni (`resources/lan/*.properties`)

## Manuale Utente

### 1. Requisiti di Sistema
- Sistema operativo Linux
- Libreria NCurses
- Compilatore GCC

### 2. Compilazione e esecuzione
```bash
./run.sh
```

### 3. Funzionalità
- **Inserimento contatto**
  - Compilare i campi richiesti
  - Selezionare "Aggiungi"

- **Ricerca contatto**
  - Inserire nome e cognome
  - Selezionare "Cerca"

### 4. Comandi
| Tasto | Funzione |
|-------|----------|
| ↑ ↓   | Navigazione |
| ENTER | Conferma |
| BACKSPACE | Cancellazione |

### 5. Note Tecniche
- Lunghezza massima campi: 100 caratteri
- Formato file: CSV con separatore ";"
- Codifica caratteri: UTF-8
- Quando si aggiunge un utente mettere nei campi (se lasciati vuoti) almeno uno spazio

## Conclusioni
Il progetto dimostra l'applicazione pratica dei concetti di:
- Programmazione modulare
- Gestione file
- Interfacce utente
