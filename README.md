<h1 style="text-align: center">Instrukcja obsługi sterownika dzwonka szkolnego</h1>
<img src="rys.png" alt="dzwonek" style="display: block;margin-left: auto;margin-right: auto">
<h2 style="text-align: center">Zmiana ustawień godziny i innych parametrów</h2>
<ol>
<li>Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat podobny do tego:<br><div style="text-align: center">F1:</div></li>
<li>Kręcąc gałką wybieramy żądaną funkcję.<br>Przykładowo. Po wybraniu funkcji <span style="font-style: italic">Ustawianie godziny</span> na wyświetlaczu pojawi się komunikat:<br><div style="text-align: center">F4:</div></li>
<li>Po wciśnięciu gałki na wyświetlaczu pojawi się komunikat podobny do tego:<br><div style="text-align: center">F4:12</div></li>
<li>Kręcąc gałką należy ustawić żądaną godzinę.</li>
<li>Należy przycisnąć gałkę, aby zapisać godzinę w pamięci sterownika. Jeżeli gałka nie zostanie przyciśnięta w ciągu dziesięciu sekund, ustawiona wartość nie zostanie zapamiętana.</li>
</ol>
<div>W analogiczny sposób należy postępować w przypadku ustawiania minut i pozostałych funkcji.</div>
<h2 style="text-align: center">Ręczne włączanie dzwonka</h2>
<li>Aby włączyć dzwonek w dowolnym momencie, należy nacisnąć gałkę.
<li>Następnie, obracając gałkę, wybrać funkcję F1 – Sterowanie ręczne i ponownie ją nacisnąć.
<li>Dzwonek będzie działał przez czas określony parametrem F2 – Czas dzwonienia.
<li>Naciśnięcie gałki w trakcie dzwonienia spowoduje jego natychmiastowe przerwanie.
<h2 style="text-align: center">Wykaz funkcji</h2>
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

<h2 style="text-align: center">Programowanie listy dzwonków przy pomocy komputera</h2>
<ol>
<li>Sterownik podłączyć do komputera przy pomocy przewodu USB mini.</li>
<li>Proszę sprawdzić w menedżerze urządzeń, na którym porcie COM pojawi się sterownik dzwonka USB-SERIAL CH340. Zapisać numer portu, bo będzie potrzebny w punkcie 3. W razie potrzeby zainstalować sterowniki do układu CH340.</li>
<li>Na komputerze uruchomić program putty (może być użyty dowolny tzw. emulator terminala RS232). Ustawić parametry transmisji:
<ul>
<li>Speed 19200,</li>
<li>Serial line COM<numer> (ten odczytany w punkcie 2),</li>
<li>Connection type: Serial.</li>
</li>
</ul>
<li>Po wciśnięciu klawisza Enter sterownik pokaże listę dostępnych poleceń. Należy wiedzieć, że wszystkie podawane wartości są muszą być dwucyfrowe, np godzinę 7 zapisujemy jako 07.</li>
</ol>

