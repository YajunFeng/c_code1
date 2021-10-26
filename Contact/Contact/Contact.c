#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"

void CheckCapacity(struct Cont* ps);

void LoadContact(struct Cont* ps)
{
	struct Contact tmp = {0};
	FILE* pfRead = fopen("contact.dat","r");
	if(pfRead == NULL)
	{
		printf("����ͨѶ¼��%s\n",strerror(errno));
		return;
	}
	//����ͨѶ¼
	while(fread(&tmp,sizeof(struct Contact),1,pfRead))
	{
		//����ʼ��ͨѶ¼�ռ��Ƿ��㹻
		CheckCapacity(ps);
		//���ļ��е�����д��ͨѶ¼��
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	//�ر��ļ�
	fclose(pfRead);
	pfRead = NULL;
}

void InifContact(struct Cont* ps)
{
	ps->data = (struct Contact*)malloc(NUM*sizeof(struct Contact));
	if(ps->data == NULL)
	{
		printf("���ٿռ䣺%s\n",strerror(errno));
	}
	ps->size = 0;
	ps->Capacity = NUM;
	//�������е�ͨѶ¼ 
	LoadContact(ps);
}


void CheckCapacity(struct Cont* ps)
{
	if(ps->Capacity == ps->size )
	{
		struct Contact* str = (struct Contact*)realloc(ps->data ,(ps->Capacity +2)*sizeof(struct Contact));
		if(str != NULL)
		{
			ps->data = str;
			ps->Capacity +=2;
			printf("���ݳɹ�\n");
		}
		else
		{
			printf("����ʧ��\n");
		}
	}
}

void AddContact(struct Cont* ps)
{
	CheckCapacity(ps);
	printf("����������:>");
	scanf("%s",ps->data[ps->size].name );
	printf("�������Ա�:>");
	scanf("%s",ps->data[ps->size].sex );
	printf("������绰:>");
	scanf("%s",ps->data[ps->size].tel );
	printf("�������ַ:>");
	scanf("%s",ps->data[ps->size].adress );
	printf("����������:>");
	scanf("%d",&(ps->data[ps->size].age ));
	ps->size++ ;
	printf("��ӳɹ�\n");

}

void ShowContact(const struct Cont* ps)
{
	if(ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		printf("%-5s\t%-10s\t%-20s\t%-20s\t%-5s\t\n","����","�Ա�","�绰","��ַ","����");
		for(i = 0;i < ps->size; i++)
		{
			printf("%-5s\t%-10s\t%-20s\t%-20s\t%-5d\t\n",ps->data[i].name,ps->data[i].sex,ps->data[i].tel,ps->data[i].adress,ps->data[i].age);
		}
	}
}

static int FindContact(const struct Cont* ps,char name[MAX_NAME])
{
	int i = 0;
	for(i = 0; i < ps->size ; i++)
	{
		if(0 == strcmp(name,ps->data[i].name))
		{
			return i;
		}
	}
	return -1;
}

void DelContact(struct Cont* ps)
{
	char name[MAX_NAME];
	int ret;
	printf("��������Ҫɾ�����˵�����:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("���޴���\n");
	} 
	else
	{
		int i = 0;
		for(i = ret; i < ps->size-1 ;i++)
		{
			ps->data[i] = ps->data[i+1]; 
		}
		(ps->size)--;
		printf("ɾ���ɹ�\n");
	}
}

void ModContact(struct Cont* ps)
{
	char name[MAX_NAME];
	int ret;
	printf("��������Ҫ�޸ĵ��˵�����:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("���޴���\n");
	} 
	else
	{
	        printf("����������:>");
		    scanf("%s",ps->data[ret].name );
		    printf("�������Ա�:>");
		    scanf("%s",ps->data[ret].sex );
		    printf("������绰:>");
		    scanf("%s",ps->data[ret].tel );
		    printf("�������ַ:>");
		    scanf("%s",ps->data[ret].adress );
		    printf("����������:>");
		    scanf("%d",&(ps->data[ret].age ));
			printf("�޸ĳɹ�\n");
	}
}

void SearchContact(const struct Cont* ps)
{
	char name[MAX_NAME];
	int ret;
	printf("��������Ҫ���ҵ��˵�����:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("���޴���\n");
	}
	else
	{
		printf("����\t�Ա�\t�绰\t��ַ\t����\t\n");
		printf("%-s\t%-s\t%-s\t%-s\t%-d\t\n",ps->data[ret].name,ps->data[ret].sex,ps->data[ret].tel,ps->data[ret].adress,ps->data[ret].age);
	}
}

void DistoryContact(struct Cont* ps)
{
	free(ps->data );
	ps->data = NULL;
}

void SaveContact(struct Cont* ps)
{
	int i = 0;
	FILE* pfWrite = fopen("contact.dat","wb");
	if(pfWrite == NULL)
	{
		printf("����ͨѶ¼��%s\n",strerror(errno));
		return;
	}
	for(i = 0;i < ps->size ;i++)
	{
		fwrite(&(ps->data[i]),sizeof(struct Contact),1,pfWrite);
	}
	fclose(pfWrite);
	pfWrite = NULL;
}