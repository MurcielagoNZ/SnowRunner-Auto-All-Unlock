#define _CRT_SECURE_NO_WARNINGS

#include "theTools.h"

const char cmd[] = "dir ";
const char cmd4folder[] = " /a:d /b";
const char cmd4file[] = " /a:-d *.xml /b";

int depth = 0, i;
char name[MaxP] = "";

void searchAndChange(char currPath[])
{
	char data[MaxP * MaxI] = "",
		names[MaxP][MaxI] = { 0 },
		str[MaxP] = "";
	int i, count;

	depth++;

	printf("Now working with path:\n%s\nDepth: %d\n\n", currPath, depth);

	//for all files
	memset(str, 0, sizeof(str));
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4file);
	getCmd(str, data);
	if (notEmpty(data))
	{
		printf("Found files:\n%s\n", data);
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			toChangeFile(str);
		}
	}
	else printf("No files found.\n\n");

	//for all folders
	memset(str, 0, sizeof(str));
	strcpy(str, cmd);
	strcat(str, currPath);
	strcat(str, cmd4folder);
	getCmd(str, data);
	if (notEmpty(data))
	{
		printf("Found folders:\n%s\n", data);
		count = separate(data, names, 10);
		for (i = 0; i < count; i++)
		{
			memset(str, 0, sizeof(str));
			strcpy(str, currPath);
			strcat(str, "\\");
			strcat(str, names[i]);
			if (whiteFolder(names[i]))
				searchAndChange(str);
			else delDir(str);
		}
	}
	else printf("No folders found.\n\n");

	depth--;
}

int main()
{
	printf("�ù��߻���������Ʒ�ĵ������������ƣ�������Ҫ̽�����ܽ�������Ʒֱ�ӿ��á�\n������ȫ�������ͺ������������ܡ�\n");
	printf("This tool will unlock everything.\nAWD-modify and differential-welde feature were added.\n\n");
	printf("������\n");
	printf("����һ��������Ϊ�ٷ������Ұ��¡��س�������������ۣ������븺����\n");
	printf("���磺\n90\n�Ὣ������Ʒ�ļ۸����ۡ�\n");
	printf("ԭ��5000����Ʒ���Ϊ4500��\n");
	printf("0���㣩������Ԫ����\n");
	printf("Would like a discount?\n");
	printf("Input an integer for percent and press ENTER. If don't want discount, input negative number.\n");
	printf("For example:\n90\nmeans the price will be 10%% off.\n");
	printf("An item of price 5000 will be change into 4500.\n");
	printf("0 (zero) will make everything free.\n");
	scanf("%d", &discount);
	printf("\n�����п�������Ϊȫ�������� (1 - ��; 0 - ��)\n");
	printf("Give all trucks AWD? (1 - yes; 0 - no)\n");
	scanf("%d", &AWD);
	printf("\n�����в�֧�ֲ������Ŀ�������Ϊ������������ (1 - ��; 0 - ��)\n");
	printf("Give all trucks differential lock? (1 - yes; 0 - no)\n");
	scanf("%d", &difflock);
	system("cls");

	//debug
	//log = fopen("files_changed.log", "w");

	/*if (argc > 1)
		{
			printf("Working with given file.\n");

			for (i = 1; i < argc; i++)
			{
				memset(name, 0, sizeof(name));
				strcpy(name, argv[i]);
				if (needChange(name))
				{
					printf("Working with:\n%s\n\n", name);
					backupAndPrepareNew(name);
					toChangeFile(name);
				}
			}

			system("pause");
			return 0;
		}
		else*/
	if (checkNotFolder())
	{
		printf("Wrong folder!\n");
		system("pause");
		return -1;
	}
	else
	{
		printf("Searching folders.\n");
		searchAndChange("[media]");
	}

	system("del /s *.bak > nul");
	printf("All done. Changed %d files.\n", count);
	system("pause");

	//debug
	//fprintf(log, "%d\n", count);
	//fclose(log);

	return 0;
}

/*
* need manual change cuz format error:
* dlc6 step_3364_crocodile
* dlc8 step_39331_pike
*
* Offset="(�ӳ�������+ǰ-��; �ӵ���+��-��; �ӳ�������+��-��)"
*/