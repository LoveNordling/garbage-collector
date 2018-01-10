# Kodkvalitetsrapport

På förekommen anledning -- här är några exempel på bra kod som
löser olika problem i uppgiften. 

Flera tycker att det är krångligt att separera t.ex. listan och
programmet. "Vad skall ligga var?!" Listans uppgift är att hålla i
data, men inte veta vad det är för data. Programmet som använder
listan vet inte hur listan är representerad, men vet hur datat
ser ut.


## Formateringsregler

Med hjälp av denna funktion blir det nu enkelt att utföra många
operationer som kräver att man går igenom listan. Här är ett
exempel på hur man kan skriva en funktion, `total_amount()` som
givet en databas (träd) och namnet på en vara går igenom samtliga
hyllplatser för varan och summerar deras antal:

```c
/// main.c (eller motsvarande) -- hjälpfunktion
/// Hjälpfunktion till total_amount
static
void add_amount(shelf_t *s, int *sum)
{
  *sum += s->amount;
}
```

Vi kan skriva en liknande funktion för att skriva ut alla hyllor, 
och antalet varor på hyllan för något item. Här skickar jag med 
namnet på varan, men kunde lika gärna skriva `NULL` istället för
`i->name` om jag inte behöver den i utskriften. 

Hjälpfunktionerna ovan är deklarerade som `static`. Det betyder
att de är "dolda" och inte syns utanför de `.c`-filer som 
innehåller dem, och det skulle vara fel att lista dem i `.h`-filen. 


## Iterator

En iterator är ett smidigt hjälpmedel för att på ett abstrakt sätt
iterera över elementen i en datasamling, utan att behöva veta hur
elementen är organiserade i datasamlingen. Eftersom koden för
iteratorn ligger i `list.c` kan den enkelt stega framåt med
`next`-pekaren utan att behöva exponera förekomsten av en `node_t`
för användaren. 

