# Instrukcja obsługi sterownika dzwonka
![schemat](https://github.com/gcygan2/dzwonek/blob/main/panel.png)
- Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat, np.:

![schemat](https://github.com/gcygan2/dzwonek/blob/main/1.png)
- Kręcąc gałką wybieramy funkcję zgodnie z poniższą tabelą.
  
|Funkcja|Opis                       |Parametr                 |
|--|---------------------------|-------------------------|
|F0|Tryb pracy                 |00 wyłączony             |
|  |                           |01 poniedziałek – piątek |
|  |                           |02 codziennie            |
|F1|Sterowanie ręczne          |                         |
|F2|Czas dzwonienia            |01 – 09 s                |
|F3|Jasność wyświetlacza       |00 – 03                  |
|F4|Godzina                    |00 – 23                  |
|F5|Minuta                     |00 – 59                  |
|F6|Dzień tygodnia             |01 – 07 (01-poniedziałek)|
|F7|Lista dzwonków             |                         |
|F8|Ustawianie sekundnika 30s  |                         |
|Fb|Bank dzwonków              |Fb:00 normalne (45 min.) |
|  |                           |Fb:01 skrócone (30 min.) |
|  |                           |Fb:02 skrócone (35 min.) |
|FC|Modyfikacja listy dzwonków |                         |
|FE|Usunięcie z listy dzwonków |                         |
- Przykład: po wybraniu funkcji Ustawianie godziny i ponownym wciśnięciu gałki na wyświetlaczu pojawi się komunikat, np.:

![schemat](https://github.com/gcygan2/dzwonek/blob/main/2.png)
1. Kręcąc gałką należy ustawić żądaną godzinę.
1. Aby zapisać ustawienie, należy w ciągu 10 sekund przycisnąć gałkę. Wyjątek stanowią funkcje F5 i F8, gdzie na przyciśnięcie gałki mamy 60s.
1. W analogiczny sposób należy postępować przy ustawianiu parametrów dla pozostałych funkcji.

## Programowanie listy dzwonków przy pomocy komputera
1 Sterownik podłączyć do komputera przy pomocy przewodu USB mini.
1 Proszę sprawdzić w menedżerze urządzeń, na którym porcie COM pojawi się sterownik dzwonka. W razie potrzeby zainstalować sterowniki.
1 Na komputerze uruchomić program putty (może być użyty dowolny tzw. emulator terminala RS232). Ustawić parametry transmisji:
	- 8N1
	- Speed 9600,
	- Serial line COM<numer> (ten odczytany w punkcie 2),
	- Connection type: Serial.
1 Po wciśnięciu klawisza Enter sterownik pokaże listę dostępnych poleceń. Należy wiedzieć, że wszystkie podawane wartości muszą być dwucyfrowe, np godzinę 7 zapisujemy jako 07.

![schemat](https://github.com/gcygan2/dzwonek/blob/main/schemat.png)
