Unit testing,

Vi hade som mål från början att det skulle finas tester till alla modulerna. Modulerna cell, memorymap och compact saknar enhetstestning helt. De är dock integrerade i projektet och har inte skapat problem i integrationstesterna. Modulerna gc och root har minimala tester och skulle därför behöva uttökas. gc, root och compact täcks ganska bra dock av integrationstesterna. 


Integrationstestning:
Integrationstestningen började med att allokera stora mängder int:ar och spara endast ett fåtal av dessa. Detta för att trigga skräpsamlaren under testets gång. Många buggar visade sig redan från start och i och med att dessa fixades så framkom många nya. Det står nu klart att allokeringen av data på heapen fungerar som den ska. Problemet ligger någonstans i skräpsamlingsalgoritmen eller i någon av de moduler som den använder. På grund av att detta första test aldrig gick igenom på ett tillfredställande vis så skapades, förutom demo, endast ett till integrationstest för allokering av en lista. 




Regressionstestning:
Lagerhanteraren kördes utan gh interfacet för att se till att allt funkar som det skulle. Andra steget i regressionstestningen var 
att ta bort alla "frees" och funktioner och logik som frigör noder, listor och träd och såg till att lagerhanteraren funkade som 
den skulle utan att krascha. Tredje steget var att byta ut alla callocs i list.c mot h_alloc_struct och sedan testa operationer 
som är beroende på listor som "Add shelf", "remove shelf", "edit shelf" etc. Nästa steg var att byta ut callocs i tree.c och köra
lagerhanteraren. Sista steget var att byta ut calloc funktionerna i goods.c självaste lagerhanteraren. Testerna gick igenom och
lagerhanterrarens funktionalitet inte påverkades. Det finns ett undantag av calloc som inte kunde bytas ut nämligen 
calloc(length,sizeof(node_t)). Vi behöver en funtion som kan ta in ett int och en sträng och upprepa strängen lika många gånger som
int:en anger för att sedan kunna skicka denna formatsträng till h_alloc_struct. Implementationen är enkel med hann inte göra det.

Issues:
Vi har inte varit konsekventa med användingen av issues på github, men såklart hade vi buggar. 
Under testning av object.c uppmärksammades att man hade förstått fel hur man hanterar pekare och hur man kan skapa en pekare i 
minnet som har pre-allokerats. Vid testning av object_copy-funktionen insåg man att man jämförde data som låg på stacken och inte 
på heapen som vi hade allokerat. Det var viktigt att åtgärda detta under testning än att försöka debugga detta sedan.




Code coverage


File 'src/bits.c'
Lines executed:67.00% of 100
Creating 'bits.c.gcov'

File 'src/cell.c'
Lines executed:100.00% of 23
Creating 'cell.c.gcov'

File 'src/compact.c'
Lines executed:79.17% of 24
Creating 'compact.c.gcov'

File 'src/gc.c'
Lines executed:67.11% of 152
Creating 'gc.c.gcov'

File 'src/main.c'
No executable lines
Removing 'main.c.gcov'

File 'src/memorymap.c'
Lines executed:72.09% of 43
Creating 'memorymap.c.gcov'

File 'src/object.c'
Lines executed:89.66% of 58
Creating 'object.c.gcov'

File 'src/root.c'
Lines executed:89.19% of 37
Creating 'root.c.gcov'

File 'test/test.c'
Lines executed:100.00% of 32
Creating 'test.c.gcov'


Den enda modul som vi fick 100% coverage på var cell vilket är rimligt då det är en väldigt enkel modul. För resten av modulerna fick vi mellan 67 och 89%. Även detta finner vi ganska rimligt då vi använt defensiv programmering och därmed har vi flera rader som aldrig körs under normala omständigheter. Dock vore det optimalt om vi hade försökt köra tester som täckte även dessa kodbitar. Det finns även rester av gamla main/test-funktioner i vissa av modulerna vilket påverkar resultatet.
