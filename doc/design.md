

![alt text](https://github.com/IOOPM-UU/sidensvansarna/blob/master/doc/Designmap.png "Logo Title Text 1")


Skräpsamlaren har en interface "gc.h" som ska inkluderas i alla moduler där användaren tänker använda calloc och malloc. 

I programmets mainfunktion ska användaren kalla på h_init och ange hur mycket data man kan behöva för programmets körning.
Funktionen då allokerar ett utrymme på datorns minne och returnerar en pekare till heapen som har allokerats av GC:n.

Skräpsamlarens magi börjar med upprepade anrop till h_alloc_struct, flera steg följer:
1. Först anropas get_available_space som returnerar en pekare till en Cell i det allokerade minnet.
2. Pekaren kan antingen vara valid eller NULL.
3. Ifall pekaren är valid, anropas funktionen new_object som placerar datat på minnet.
3. Om pekaren är NULL startas skräpsamlaren igång med ett anrop till h_gc.
4. h_gc traverserar stacken och letar efter säkra och osäkra pekare. De säkra pekarna leder till data som är allokerat på gc:s heap. 
5.Minnet kompakteras, alltså, datat kopieras i minnet för att minimera fragmentering. Celler vars data är onåelig i gc:s  heap är fria att skrivas över, celler som innehåller data som pekas av en säker eller osäker pekare kan inte skrivas över.
6.När skräpsamlingen är slutförd då returneras en pekare till en ledig plats i gc:s heap till h_alloc_struct.

