#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"

void menu()
{
	printf("*********************************************\n");
	printf("******1.Add                      2.Del ******\n");
	printf("******3.Search                   4.Mod ******\n");
	printf("******5.Show                     6.Save*****\n");
	printf("******0.Exiit                          ******\n");
	printf("*********************************************\n");
}

int main()
{
	int input = 0;
	struct Cont con;
	//初始化通讯录
	InifContact(&con);
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d",&input);
		switch(input)
		{   case ADD:
		        AddContact(&con);
				break;
			case DEL:
				DelContact(&con);
				break;
			case SEARCH:
				SearchContact(&con);
				break;
			case MOD:
				ModContact(&con);
				break;
			case SHOW:
				ShowContact(&con);
				break;
			case SAVE:
				SaveContact(&con);
				break;
			case EXIT:
				SaveContact(&con);
				DistoryContact(&con);
				printf("退出成功\n");
				break;
			default:
				printf("请重新输入\n");
				break;
		}
	}
	while(input);
}