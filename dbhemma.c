#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/* ATT GÖRA TILL LAB 5
Tillägg i databasen (add_item_to_db())
Borttag ur databasen (remove_item_db())
Integration (verkar färdigt)
Utökad vara
*/

void print_menu()
{
	puts("");
	puts("[L]agga till en vara");
	puts("[T]a bort en vara");
	puts("[R]edigera en vara");
	puts("An[g]ra senaste andringen");
	puts("Lista [h]ela varukatalogen");
	puts("[A]vsluta");
}
bool accepted_menu_input(char c)
{
	c = toupper(c);

	switch (c)
	{
		case 'L': return true;
		case 'T': return true;
		case 'R': return true;
		case 'G': return true;
		case 'H': return true;
		case 'A': return true;
	}

	return false;
}
char ask_question_menu()
{
	print_menu();

	//få input från användaren
	char c;
	char b;
	do
	{
		//print_menu();
		c = getchar();

		//töm input buffern
		while((b = getchar()) != EOF && b != '\n');
	}
	while(!accepted_menu_input(c));

	return toupper(c);
	//printf("%c\n", toupper(c));
}

//TODO:
void add_item_to_db()
{
	puts("add item");
}
//TODO:
void remove_item_from_db()
{
	puts("remove item");

/*
	int nums = {5, 2, -40, 10, 1};

	int remove_index = 3;
	for (int i = remove_index; i > 0; --i)
	{
		db[i - 1] = db[i];
	}
	*/
}
//gjort
void edit_db()
{
	puts("edit item");
}
//gjort
void list_db()
{
	puts("list item");
}
void undo_db()
{
	puts("Not yet implemented!"));
}

void event_loop()
{
	while(true)
	{
		char kommando = ask_question_menu();

		switch(kommando)
		{
			case 'L': add_item_to_db(); break;
			case 'T': remove_item_from_db(); break;
			case 'R': edit_db(); break;
			case 'G': undo_db(); break;
			case 'H': list_db(); break;
			case 'A': return;
		}
	}
}

int main(void)
{
	event_loop();

	return 0;
}