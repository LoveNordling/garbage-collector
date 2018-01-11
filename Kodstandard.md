# Kodstandard

Det här är en kodstandard och samling formateringsregler som har utgått från officiella konventioner användna i K&R, GNU C och GTK+.
Om vi alla följer den så kan vi leverera ett bibliotek som är skriven på ett tydligt och sammanhängande vis.

## 1) Konstanter ska vara i caps:

```c
#define MAX_HEAP_SIZE 2^24
const double PI = 3.14159265359f;
```

## 2) Filnamn, variabelnamn och funktionsnamn ska ha understreck mellan orden:

```c
quad_tree.c;
int variable_name;
void function_that_does_something()
{
	
}
```


## 3) Klammerparenteser ska ligga på sina egna rader:

```c
int foo()
{
	while (1)
	{
		
	}
}
```


## 4) Pekare ska se ut på följande sätt:

```c
int* p;
void read_file(char* buf, int size);
```


## 5) Typedefs till struktar och unioner ska separeras med understreck och sluta med 't':

```c
typedef struct
{
	char name[32];
	int age;
} person_t;

typedef union
{
	int i;
	float f;
} decimal_t;
```


## 6) Include guards ska se ut på följande vis:

```c
#ifndef FILE_NAME_H
#define FILE_NAME_H

struct foo 
{
    char c;
};

void bar(void);

#endif /* FILE_NAME_H */
```

## 7) Indentering ska göras med fyra(4) stycken mellanslag
Kan göras genom att lägga till:
(setq-default indent-tabs-mode nil)
(setq c-default-style "linux"
          c-basic-offset 4)
i emacs init-fil. (källa: https://www.emacswiki.org/emacs/IndentingC )

För sublime se https://www.sublimetext.com/docs/2/indentation.html

Använder ni något annat så får ni googla eller skriva 4 mellanslag manuellt
som en pleb.
