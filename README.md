# Instrukcja obsługi sterownika dzwonka szkolnego
![schemat](https://github.com/gcygan2/dzwonek/blob/main/rys.png)
## Zmiana ustawień godziny i innych parametrów
- Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat, np.:
![schemat](https://github.com/gcygan2/dzwonek/blob/main/1.png)
- Kręcąc gałką wybieramy żądaną funkcję.
  
|Fx|Opis                       |Parametr                 |
|--|---------------------------|-------------------------|
|F0|Tryb pracy                 |00 wyłączony             |
|  |                           |01 poniedziałek – piątek |
|  |                           |02 codziennie            |
|F1|Sterowanie ręczne          |                         |
|F2|Czas dzwonienia            |01 – 09 s                |
|F3|Jasność wyświetlacza       |00 – 04                  |
|F4|Ustawianie godziny         |00 – 23                  |
|F5|Ustawianie minuty          |00 – 59                  |
|F6|Ustawianie dnia tygodnia   |01 – 07 (01-poniedziałek)|
|F7|Wyświetlenie listy dzwonków|                         |
|FA|Dodawanie nowego dzwonka   |                         |
|Fb|Bank dzwonków              |Fb:00 normalne (45 min.) |
|  |                           |Fb:01 skrócone (30 min.) |
|  |                           |Fb:02 skrócone (35 min.) |
|FC|Modyfikacja listy dzwonków |                         |
|FE|Usunięcie z listy dzwonków |                         |
- Przykład: po wybraniu funkcji Ustawianie godziny na wyświetlaczu pojawi się komunikat:
![schemat](https://github.com/gcygan2/dzwonek/blob/main/2.png)
- Po ponownym wciśnięciu gałki pojawi się komunikat, np.:
![schemat](https://github.com/gcygan2/dzwonek/blob/main/3.png)
- Kręcąc gałką należy ustawić żądaną godzinę.
- Aby zapisać ustawienie, należy przycisnąć gałkę.
- Jeśli gałka nie zostanie wciśnięta w ciągu 10 sekund, ustawiona wartość nie zostanie zapamiętana.
- W analogiczny sposób należy postępować przy ustawianiu minut oraz pozostałych funkcji.
## Programowanie listy dzwonków przy pomocy komputera
1. Sterownik podłączyć do komputera przy pomocy przewodu USB mini.
2. Proszę sprawdzić w menedżerze urządzeń, na którym porcie COM pojawi się sterownik dzwonka USB-SERIAL CH340. Zapisać numer portu, bo będzie potrzebny w punkcie 3. W razie potrzeby zainstalować sterowniki do układu CH340.
3. Na komputerze uruchomić program putty (może być użyty dowolny tzw. emulator terminala RS232). Ustawić parametry transmisji:
	- Speed 19200,
	- Serial line COM<numer> (ten odczytany w punkcie 2),
	- Connection type: Serial.
4. Po wciśnięciu klawisza Enter sterownik pokaże listę dostępnych poleceń. Należy wiedzieć, że wszystkie podawane wartości są muszą być dwucyfrowe, np godzinę 7 zapisujemy jako 07.
