#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"

void CheckCapacity(struct Cont* ps);

void LoadContact(struct Cont* ps)
{
	struct Contact tmp = {0};
	FILE* pfRead = fopen("contact.dat","r");
	if(pfRead == NULL)
	{
		printf("加载通讯录：%s\n",strerror(errno));
		return;
	}
	//加载通讯录
	while(fread(&tmp,sizeof(struct Contact),1,pfRead))
	{
		//检查初始的通讯录空间是否足够
		CheckCapacity(ps);
		//将文件中的数据写入通讯录中
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	//关闭文件
	fclose(pfRead);
	pfRead = NULL;
}

void InifContact(struct Cont* ps)
{
	ps->data = (struct Contact*)malloc(NUM*sizeof(struct Contact));
	if(ps->data == NULL)
	{
		printf("开辟空间：%s\n",strerror(errno));
	}
	ps->size = 0;
	ps->Capacity = NUM;
	//加载已有的通讯录 
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
			printf("扩容成功\n");
		}
		else
		{
			printf("扩容失败\n");
		}
	}
}

void AddContact(struct Cont* ps)
{
	CheckCapacity(ps);
	printf("请输入名字:>");
	scanf("%s",ps->data[ps->size].name );
	printf("请输入性别:>");
	scanf("%s",ps->data[ps->size].sex );
	printf("请输入电话:>");
	scanf("%s",ps->data[ps->size].tel );
	printf("请输入地址:>");
	scanf("%s",ps->data[ps->size].adress );
	printf("请输入年龄:>");
	scanf("%d",&(ps->data[ps->size].age ));
	ps->size++ ;
	printf("添加成功\n");

}

void ShowContact(const struct Cont* ps)
{
	if(ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		printf("%-5s\t%-10s\t%-20s\t%-20s\t%-5s\t\n","姓名","性别","电话","地址","年龄");
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
	printf("请输入需要删除的人的名字:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("查无此人\n");
	} 
	else
	{
		int i = 0;
		for(i = ret; i < ps->size-1 ;i++)
		{
			ps->data[i] = ps->data[i+1]; 
		}
		(ps->size)--;
		printf("删除成功\n");
	}
}

void ModContact(struct Cont* ps)
{
	char name[MAX_NAME];
	int ret;
	printf("请输入需要修改的人的名字:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("查无此人\n");
	} 
	else
	{
	        printf("请输入名字:>");
		    scanf("%s",ps->data[ret].name );
		    printf("请输入性别:>");
		    scanf("%s",ps->data[ret].sex );
		    printf("请输入电话:>");
		    scanf("%s",ps->data[ret].tel );
		    printf("请输入地址:>");
		    scanf("%s",ps->data[ret].adress );
		    printf("请输入年龄:>");
		    scanf("%d",&(ps->data[ret].age ));
			printf("修改成功\n");
	}
}

void SearchContact(const struct Cont* ps)
{
	char name[MAX_NAME];
	int ret;
	printf("请输入需要查找的人的名字:>");
	scanf("%s",&name);
	ret = FindContact(ps,name);
	if(ret == -1)
	{
		printf("查无此人\n");
	}
	else
	{
		printf("姓名\t性别\t电话\t地址\t年龄\t\n");
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
		printf("保存通讯录：%s\n",strerror(errno));
		return;
	}
	for(i = 0;i < ps->size ;i++)
	{
		fwrite(&(ps->data[i]),sizeof(struct Contact),1,pfWrite);
	}
	fclose(pfWrite);
	pfWrite = NULL;
}