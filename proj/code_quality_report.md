# Kodkvalitetsrapport

Vi har försökt hålla en god kvalité på koden i vårt program. I början av projektet så kom vi överens om en samling formateringsregler och generella riktlinjer för att säkerställa att vårt program skulle vara av så hög kvalité som möjligt. 
Vi bestämde oss för att all kod som ska mergas med vårt masterprogram måste uppfylla vissa krav. Bland annat ska all kod i pull requests var välstrukturerade och innehålla både doxygen kommentarer och vanliga radkommentarer. 
Alla variabler, funktioner och moduler ska vara döpta på ett sätt som beskriver deras mening. Detta är viktigt för läsbarheten, eftersom att man kan få en överblick av vad ett kodblock gör bara genom att läsa den.

Vårt mål har varit att skriva kod som är så robust och flexibel som möjligt. Detta innebär att koden ska vara strukturerad på ett korrekt och läsbart vis och att programmet ska vara som en sammanslagning av självständiga komponenter som tillsammans skapar en helhet. Det gör så att det blir enkelt att utöka programmet med nya delar och lätt att iterera över det vi redan har utan att någonting kraschar i någon annan del av programmet.

## Formatering

Ett mål vi haft är att vi vill att utomstående som läser koden inte ska kunna se skillnad på vem som har skrivit vad i de olika delarna av programmet. Detta har vi försökt uppnå genom att förhålla oss till en kodstandard som vi kommit överens om tidigt i projektet.
Den har vi lagt upp som en .md fil i huvudrepot. 

Kodstandarden fungerar också som en stabil grund för programmets kodstruktur som alla i gruppen kan förhålla sig till. Vi har utgått från GNUs kodstandard, men vi har också tagit inspiration från andra referenser som t.ex. boken The C Programming Language och grafikbiblioteket GTK+.

## Kodgranskning

Vi har tillämpat löpande kodgranskning under projektet som ska göras av någon person i gruppen som inte är med i kodparet som gjorde pull requesten.
Endast den kod som uppfyller kraven vi har för masterbranschen får mergas med den. Resten måste vidare bearbetas innan den kan bli mergad.

Om en pull request inte uppfyller de kraven vi har om kodkvalitet och formatering, så ska kodgranskaren begära förändringar för att den ska integreras med huvudprogrammet. I praktiken så innebär detta att kodgranskaren skriver kommentarer i PR:en där han/hon inte känner sig nöjd, och så måste den ursprungliga utvecklaren ta hänsyn till detta när han/hon uppdaterar sin PR. När utvecklaren har korrigerat alla fel i commiten så kommer kodgranskaren att göra en merge på pullrequesten och huvudprogrammet.

Om man vet att ens kod kan bli avvisad så fokuserar man extra mycket på att skriva korrekt och bra kod. En granskning och uppdatering av en pull request tar tid. Därför fungerar kodgranskningen som ett förebyggande medel mot dåligt skriven kod. Men ibland kan misstag dyka upp som den ursprungliga utvecklaren inte vetat om, då kan det vara bra att ha någon annan utvecklare att läsa igenom ens kod för att hitta eventuella fel man missat.

## Prestanda

Optimering är någonting vi har tänkt på sen början av projektet. Vi har försökt göra så att bokföringsdatan för vår heap använder så lite utrymme som möjligt för att minska antalet skräpsamlingar som måste utföras. Detta leder i sin tur till att vi sparar på prestandan.
Vi har minskat minnesanvändningen genom en rad olika metoder. Bland annat har vi använt oss av bitvektorer för att representera layoutinformationen för objekt, och vi har packat in enskilda konstanter på slutet av alignade variabler för att spara utrymme. Vi har också lagrat adresser med deras relativa offsets istället för deras absoluta pekarpositioner.

Självfallet så ökar det här komplexiteten för vårt program, men vi har försökt kompensera för det genom att skriva väldigt utförliga kommentarer i de delar som det finns optimeringar i. Det är viktigt att alla i gruppen ska förstå hur en optimering fungerar och varför vi har den från första början. Men optimeringar innebär nästan alltid en uppoffring på läsbarhet och simplicitet för att öka effektiviteten i ett program.

## Tester

Vi har skrivit omfattande tester för de olika delarna av vårt bibliotek. Som regel så har vi haft att varje modul man skriver också måste vara försedd med väl genomtänkta enhetstester innan man kan få den mergad till huvudprogrammet. Vi har skrivit både enhetstester som testar individuella funktioner och integrationstester som testar hela moduler. Med tester så kan vi försäkra oss om att tidigare delar av vårt program inte pajar senare i projektet när vi lägger till nya saker.

## Bra kod
Alla medlemmar i gruppen har försökt programmera på ett korrekt sätt.
Vi har försökt göra koden läsbar genom att ha tydliga namntilldelningar på variabler, funktioner och moduler som visar vad de är till för och i vilket sammanhang de kan tänkas användas i.
Det ska gå att läsa ett par rader kod i programmet och kunna få en översiktlig förståelse av vad som händer bara genom att titta på variabelnamnen och funktionsanropningarna. Detta tycker vi är någonting som vi har lyckats bra med.
