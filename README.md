DESCRIZIONE RAPIDA DELLE REGOLE FONDAMENTALI:

    Nel gioco di Cluedo sono presenti 6 Personaggi, 6 armi e 9 luoghi. All'inizio del gioco viene tolta una carta per
    tipo e si distribuiscono le restanti ai giocatori in modo equo. Lo scopo del gioco è indovinare quali sono le tre
    carte nascoste prima di tutti, indagando e scoprendo le carte in possesso degli altri giocatori.
    In ogni turno il giocatore che sta sta giocando, rivolge un quesito (composto da un personaggio, un'arma e un luogo)
    al giocatore successivo, il quale potra fare solo 2 cose:

        1. Negare, passando una sola delle carte della terna, se ne possiede almeno una, al giocatore che ne fa
           richiesta.

        2. Dichiarare "Non posso negare" se non possiede nessuna delle tre.

    Nel secondo caso, la stessa domanda viene posta al giocatore successivo, e cosi via finche qualcuno nega oppure tutti
    i giocatori non possono negare.

----------------------------------------------------------------------------------------------------------------------------------

DESCRIZIONE DEL PROGRAMMA E DELLE SUE FUNZIONI:

   Per il momento il programma è basato per un numero di giocatori fisso a tre (magari una volta tutto funzionante
   potrei pensare di far scegliere il numero di giocatori.
   Ho creato 6 tipi di strutture:

        1. Player: contiene il nome del giocatore e 3 vettori (uno per tipo di carta) che contengono "1, -1, 0" a seconda
           se quella carta "è, non è, non si sa" del giocatore.

        2/3/4. Murder/Weapon/Room: contiene nome della carta e l'indice del suo proprietario (-1 se non si sa).

        5. Solution: Contiene nient'altro che il "riassunto" delle strutture 2/3/4. 3 vettori che rappresentano i 3 tipi
        di carte, contenenti il proprietario (-1 se non si sa).

        6. Nodo *link: se un giocatore nega una terna ad un altro giocatore (nessuno dei 2 sono io) non posso sapere che
        cosa ha negato ma so che almeno una delle 3 carte è in possesso del giocatore che nega. Cosi mi salvo all'interno
        di una lista tutte le terne di un giocatore che ha negato. Così facendo, se andando avanti nel gioco scopro che
        2 di quelle tre carte non sono in possesso di quel giocatore, allora la terza deve essere per forza sua. Questo
        nodo infatti contiene il giocatore che nega, gli indici delle tre carte (con un ulteriore indice 0 posto a -1 se
        scopro che quella carta non può essere sua) e il puntatore al successivo nodo.

   All' inizio del programma la funzione << Body_Init >> prende dal file << Cluedo.txt >> le informazioni su Giocatori
   e Carte.
   Il vero corpo del programma sta nella funzione << RescueRequest >> che legge dal file << Request.txt >> le
   mie 6 carte, quante sono le Richieste e l'elenco delle richieste. Le richieste sono così formattate:

        1. Personaggio che chiede
        2. Le tre carte (Murder, Weapon, Room)
        3. Risposta del giocatore successivo. La risposta può essere:   a. Una carta (se la danno a me e la leggo)
                                                                        b. Yes (negano ma non so cosa)
                                                                        c. Not (non possono negare).
        4. Se la risposta precedente è stata "Not", ne segue anche la risposta del giocatore ancora successivo.

   Per ogni request:

        1. Se so la carta: assegno la carta a quel giocatore, togliendola dagli altri (con << UpdateCard >>) e aggiorno
           i nodi della lista (con << UpdateList >>);
        2. Se non so la carta ma negano: creo il nodo con tutte le info (vedi riga 32 per info) con << NewNode >>.
        3. Se non possono negare: vado a segnarmi in Player che non può avere quella carta e aggiorno anche le request
           in lista con la << UpdateList >>

   Oviamente non faccio nulla quando sono io a rispondere perche non mi darebbe nessuna informazione utile.

   Le funzioni << ListInit >> e << ListFree >> allocano e liberano la lista.
   << IndexByName >> restituisce un array di 2 elementi contenente il tipo e l'indice della carta/giocatore.

   La funzione << PrintAllInfo >> stampa tutte le informazioni riguardante tutto (giocatori, carte, request).
   La funzione << Resolut >> (ancora non testata per via dei problemi precedenti) svolge il ruolo di pulizia della lista:
   cerca i nodi in cui 2 delle 3 proposte non sono fattibili per assegnare la terza a quel giocatore, andando ad
   aggiornare anche gli altri nodi. Il while piu esterno, (all'interno della funzione) fa ricominciare la lettura della 
   lista finchè nessun nodo può essere eliminato oppure tutti i nodi sono stati rimossi. 

   Alla fine di ciò implementerò una funzione ricorsiva che con il brute-force genererà ogni combinazione possibile di 
   assegnazione, considerando tutte le informazioni ottenute. Ovviamente questa funzione sara necessaria con sole poche 
   opzioni rimaste (per magari capire quali domande fare per escludere le ultime opzioni), poiche con non abbastanza 
   informazioni, ne gernererebbe un numero eccessivo, inutile alla finalità del problema.

---------------------------------------------------------------------------------------------------------------------------
