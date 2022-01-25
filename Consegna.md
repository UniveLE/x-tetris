# x-tetris
[![License](https://img.shields.io/github/license/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)
[![Issues](https://img.shields.io/github/issues/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)
[![Forks](https://img.shields.io/github/forks/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)
[![Stars](https://img.shields.io/github/stars/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)
[![Size](https://img.shields.io/github/languages/code-size/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)
[![Lines](https://img.shields.io/tokei/lines/github/LorenzoVaccher01/x-tetris)](https://github.com/LorenzoVaccher01/x-tetris)

X-tetris è una versione avanzata del gioco originale del Tetris. Per le regole principali, consigliamo di visionare
la seguente pagina [Wikipedia](https://it.wikipedia.org/wiki/Tetris).

## Modalità di gioco
### Single Player
A differenza del Tetris originale, in X-Tetris il giocatore ha inizialmente a disposizione 20 (o più, a voi la
scelta) pezzi per ciascun tipo, detti tetramino, e una mossa consiste nello scegliere quale pezzo giocare, dove
farlo cadere e con quale rotazione.
Il campo di gioco è largo 10 e alto 15 posizioni. Una volta posizionato un tetramino, se una o più righe
orizzontali vengono riempite per intero, queste righe vengono cancellate come nel tetris originale.
La rimozione di una riga vale 1 punto, la rimozione di due righe con un solo pezzo vale 3 punti, tre righe 6
punti, quattro righe 12 punti.
Il gioco termina quando finiscono i pezzi o il giocatore non riesce a posizionare un tetramino nel campo di
gioco rispettando il limite di altezza.

### Multi-player
Il programma supporta una seconda modalità di gioco, selezionabile dal menu iniziale, in cui due giocatori
giocano a turni alterni ciascuno nel proprio campo di gioco ma pescando dallo stesso insieme di tetramini.
In questa modalità si avranno il doppio di pezzi a disposizione. Nel caso in cui un giocatore cancelli una
o due linee simultaneamente, il gioco procede come per il caso single player. Nel caso il giocatore cancelli
3 o più linee con una singola mossa, il campo dell’avversario viene modificato invertendo il corrispondente
numero di linee nella parte più bassa del campo di gioco: una posizione vuota diventa piena e viceversa.
Un giocatore perde la partita se non posiziona correttamente un pezzo nel proprio campo di gioco. Se i pezzi
finiscono vince il giocatore con il punteggio più alto.
La modalità multi-player deve prevedere sia la possibilità di giocare player vs. player, sia player vs. cpu, dove
la cpu può essere implementata con una strategia a vostra scelta.

## Schemi di implementazione
Il programma che implementerete dovrà chiedere al giocatore quale mossa giocare, e dovrà visualizzare il
campo di gioco aggiornato (usando la funzione printf). Dovrà verificare che la mossa scelta non inserisca
un tetramino fuori dal campo di gioco, dovrà aggiornare il punteggio e l lista di pezzi disponibili. Questi
passi si ripetono fino alla fine della partita.
Nel caso multiplayer, il programma dovrà visualizzare entrambi i campi di gioco e chiedere ai due giocatori
a turno le loro mosse.
