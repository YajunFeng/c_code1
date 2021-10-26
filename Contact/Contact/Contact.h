#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_NAME 20
#define MAX_SEX 8
#define MAX_TEL 12
#define MAX_ADRESS 50
//#define MAX 1000
#define NUM 3

enum
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MOD,
	SHOW,
	SAVE
};

struct Contact
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	char tel[MAX_TEL];
	char adress[MAX_ADRESS];
	int age;
};

struct Cont
{
	struct Contact* data;
	int size;
	int Capacity;
};

//º¯ÊýÉùÃ÷
void InifContact(struct Cont* ps);
void AddContact(struct Cont* ps);
void ShowContact(const struct Cont* ps);
void DelContact(struct Cont* ps);
void ModContact(struct Cont* ps);
void SearchContact(const struct Cont* ps);
void DistoryContact(struct Cont* ps);
void SaveContact(struct Cont* ps);