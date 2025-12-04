# Instrukcja obsługi sterownika dzwonka szkolnego
![schemat](https://github.com/gcygan2/dzwonek/blob/main/rys.png)
## Zmiana ustawień godziny i innych parametrów
1. Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat podobny do tego:<br><div style="text-align: center">F1:</div></li>
2. Kręcąc gałką wybieramy żądaną funkcję.<br>Przykładowo. Po wybraniu funkcji <span style="font-style: italic">Ustawianie godziny</span> na wyświetlaczu pojawi się komunikat:
   F4
3. Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat podobny do tego:
   F4:12
4. Kręcąc gałką należy ustawić żądaną godzinę.
5. Należy przycisnąć gałkę, aby zapisać godzinę w pamięci sterownika. Jeżeli gałka nie zostanie przyciśnięta w ciągu dziesięciu sekund, ustawiona wartość nie zostanie zapamiętana.

W analogiczny sposób należy postępować w przypadku ustawiania minut i pozostałych funkcji.
## Ręczne włączanie dzwonka
1. Aby włączyć dzwonek w dowolnym momencie, należy nacisnąć gałkę.
2. Następnie, obracając gałkę, wybrać funkcję F1 – Sterowanie ręczne i ponownie ją nacisnąć.
3. Dzwonek będzie działał przez czas określony parametrem F2 – Czas dzwonienia.
4. Naciśnięcie gałki w trakcie dzwonienia spowoduje jego natychmiastowe przerwanie.
## Wykaz funkcji
<table width="100%" cellpadding="4" cellspacing="0" border="1">
	<tr>
		<td rowspan="3">
			<p><b>F0</b></p>
		</td>
		<td rowspan="3">
			<p>Tryb pracy</p>
		</td>
		<td>
			<p>F0:00 wyłączony</p>
		</td>
	</tr>
	<tr>
		<td>
			<p>F0:01 poniedziałek &ndash; piątek</p>
		</td>
	</tr>
	<tr>
		<td><p>
			F0:02
			codziennie</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F1</b></p>
		</td>
		<td>
			<p>Sterowanie ręczne</p>
		</td>
		<td>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F2</b></p>
		</td>
		<td>
			<p>Czas dzwonienia</p>
		</td>
		<td>
			<p>F2:01 &ndash; F2:09 (1s &ndash; 9s)</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F3</b></p>
		</td>
		<td>
			<p>Jasność wyświetlacza</p>
		</td>
		<td>
			<p>F3:00 &ndash; F3:04</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F4</b></p>
		</td>
		<td>
			<p>Ustawianie godziny</p>
		</td>
		<td>
			<p>F4:00 &ndash; F4:23</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F5</b></p>
		</td>
		<td>
			<p>Ustawianie minuty</p>
		</td>
		<td>
			<p>F5:00 &ndash; F5:59</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F6</b></p>
		</td>
		<td>
			<p>Ustawianie dnia tygodnia</p>
		</td>
		<td>
			<p>F6:01 &ndash; F6:07 (poniedziałek &ndash; niedziela)</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>F7</b></p>
		</td>
		<td>
			<p>Wyświetlenie listy dzwonków</p>
		</td>
		<td>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>FA</b></p>
		</td>
		<td>
			<p>Dodawanie nowego dzwonka do listy dzwonków</p>
		</td>
		<td>
		</td>
	</tr>
	<tr>
		<td rowspan="3">
			<p><b>Fb</b></p>
		</td>
		<td rowspan="3">
			<p>Bank dzwonków</p>
		</td>
		<td>
			<p>Fb:00 normalne (45 min.)</p>
		</td>
	</tr>
	<tr>
		<td>
			<p>Fb:01 skrócone (30 min.)</p>
		</td>
	</tr>
	<tr>
		<td>
			<p>Fb:02 skrócone (35 min.)</p>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>FC</b></p>
		</td>
		<td>
			<p>Modyfikacja listy dzwonków</p>
		</td>
		<td>
		</td>
	</tr>
	<tr>
		<td>
			<p><b>FE</b></p>
		</td>
		<td>
			<p>Usunięcie z listy dzwonków</p>
		</td>
		<td>
		</td>
	</tr>
</table>

## Programowanie listy dzwonków przy pomocy komputera
1. Sterownik podłączyć do komputera przy pomocy przewodu USB mini.
2. Proszę sprawdzić w menedżerze urządzeń, na którym porcie COM pojawi się sterownik dzwonka USB-SERIAL CH340. Zapisać numer portu, bo będzie potrzebny w punkcie 3. W razie potrzeby zainstalować sterowniki do układu CH340.
3. Na komputerze uruchomić program putty (może być użyty dowolny tzw. emulator terminala RS232). Ustawić parametry transmisji:
	* Speed 19200,
	* Serial line COM<numer> (ten odczytany w punkcie 2),
	* Connection type: Serial.
4. Po wciśnięciu klawisza Enter sterownik pokaże listę dostępnych poleceń. Należy wiedzieć, że wszystkie podawane wartości są muszą być dwucyfrowe, np godzinę 7 zapisujemy jako 07.

