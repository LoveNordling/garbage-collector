# Kodkvalitetsrapport

Vi har försökt hålla en god kvalité på den kod som ligger i huvudbranchen av vår repository. Detta har vi gjort genom att vi endast låter kod mergas till masterbranschen genom pull requests som blir granskade av någon annan medlem i gruppen.

Vårt mål har varit att skriva kod som är så robust och flexibel som möjligt. Detta innebär både att koden ska vara strukturerad på ett korrekt och läsbart vis, och att programmet ska fungera som en sammanslagning av självständiga komponenter som tillsammans skapar en helhet.

## Kodgranskning

Om en pull request inte uppfyller de kraven vi har om kodkvalitet och formatering, så ska kodgranskaren avvisa den och begära förändringar för att den ska integreras med huvudprogrammet. I praktiken så innebär detta att kodgranskaren skriver kommentarer i PR:en där han/hon inte känner sig nöjd, och så måste den ursprungliga utvecklaren ta hänsyn till detta när han uppdaterar sin PR. När utvecklaren har korrigerat alla fel i commiten så kommer kodgranskaren att göra en merge på pullrequesten och huvudprogrammet.

Om man vet att ens kod kan bli avvisad så fokuserar man extra mycket på att skriva korrekt och bra kod. En granskning och uppdatering av en pull request tar tid. Därför fungerar kodgranskningen som ett förebyggande medel mot dåligt skriven kod. Men ibland kan misstag dyka upp som den ursprungliga utvecklaren inte vetat om, då kan det vara bra att ha någon ny att läsa igenom ens kod för att hitta eventuella fel man missat.

## Formatering

Ett mål vi haft är att vi vill att utomstående som läser koden inte ska kunna se skillnad på vem som har skrivit vad i de olika delarna av programmet. Detta har vi försökt uppnå genom att förhålla oss till en kodstandard som vi kommit överens om tidigt i projektet. Den ligger som en .md fil i huvudrepot. Kodstandarden fungerar också som en stabil grund för kodstrukturen i programmet som alla i gruppen kan förhålla sig till.

## Prestanda

Optimering är någonting vi har tänkt på sen tidigt i projektet. Vi har försökt göra så att bokföringsdatan för vår heap använder så lite minne som möjligt för att minska antalet skräpsamlingar som måste utföras och därmed spara på prestandan. Detta har vi åstadkommit genom en rad olika datalogiska metoder.

## Tester

Vi har skrivit omfattande tester för de olika delarna av vårt bibliotek. Som regel så har vi sagt att varje modul man skriver också vara försedd med väl genomtänkta enhetstester innan man kan få den mergad till huvudrepot.


T.ex. när man jobbar med bit flippning så vill man inte veta exakt hur koden fungerar utan man vill kunna lätt överskåda vad som händer i funktionen. Vi har försökt göra detta genom att kommentera vår kod så mycket som möjligt.

Vi har försökt göra koden läsbar genom att ha tydliga namntilldelningar på variabler, funktioner och moduler som visar vad den här saken är till för och i vilket sammanhang den kan tänkas användas i.

All kod som ligger i masterbranchen ska vara formaterade med doxygen kommentarer.
