Unit testing,

Vi hade som mål från början att det skulle finas tester till alla modulerna. Vi lyckades skriva tester till de flesta modulerna där
de viktigaste funktionerna testades. 








Regressionstestning:
Lagerhanteraren kördes utan gh interfacet för att se till att allt funkar som det skulle. Andra steget i regressionstestningen var 
att ta bort alla "frees" och funktioner och logik som frigör noder, listor och träd och såg till att lagerhanteraren funkade som 
den skulle utan att krascha. Tredje steget var att byta ut alla callocs i list.c mot h_alloc_struct och sedan testa operationer som är beroende på listor som "Add shelf", "remove shelf", "edit shelf" etc. Nästa steg var att byta ut callocs i tree.c och köra lagerhanteraren. Sista steget var att byta ut calloc funktionerna i goods.c självaste lagerhanteraren. 

Issues:
Vi har inte varit konsekventa med användingen av issues på github, men såklart hade vi buggar. 
Under testning av object.c uppmärksammades att man hade förstått fel hur man hanterar pekare och hur man kan skapa en pekare i 
minnet som har pre-allokerats. Vid testning av object_copy-funktionen insåg man att man jämförde data som låg på stacken och inte 
på heapen som vi hade allokerat. Det var viktigt att åtgärda detta under testning än att försöka debugga detta sedan.
