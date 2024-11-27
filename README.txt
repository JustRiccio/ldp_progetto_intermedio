# ldp_progetto_intermedio
Progetto intermedio dell'insegnamento "Laboratorio di Programmazione" del CdL Ingegneria Informatica

Riccardo Zamuner:
Ho scritto principalmente il main e le funzioni di test. Ho fatto review del codice degli altri 
con eventuali bug fixing.

Salamone Alessandro:
Ho scritto la struttura base del file .h e dell'implementazione.
In particolare i metodi new_scan(), get_scan() e clear_buffer().

Sperandio Lorenzo:
Ho implementato parte delle funzioni del file LidarDriver.cpp.

Annotazioni aggiuntive:
nella funzione test() del main, la prima parte, quella dove viene chiesta la risoluzione del driver, sarebbe
dovuta essere inserita all'interno dello switch, per permettere di istanziare piu' volte un driver 
nella stessa esecuzione del programma, pero' ci sono state delle complicazioni relative ai costruttori, 
all'operatore di assignment e al fatto che la resolution sia stata definita come const.