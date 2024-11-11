/*
 * testGen.cpp
 * ���� ��������: 26.09.2019
 * �����: ��������� �.�.
 * ��������� ��������� ������������������� ����� �����.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	if(argc == 1) {
		// ������ ��������� ������
		printf("��������� ��������� ������������������� ����� �����\n");
		printf("����������� ��������� �.�.\n");
		printf("��������� ������: <��� ���������> <����� ������>\n");
		printf("���� ������ (d<����� ������>.txt) �������� ����� �����, ����������� �������� ��� Enter\n");
		return 0;
	}

	int nCount = atoi(argv[1]);
	printf("nCount = %d\n", nCount);

	char sPath[12] = {0};
	sprintf(sPath, "d%d.txt", nCount);
	printf("������ ����� ����� ������������ � ���� \"%s\"\n", sPath);

	FILE* fp = fopen(sPath, "w");
	if(fp == NULL) {
		printf("������ �������� ����� ��� ������ \"%s\"\n", sPath);
		return 1; 
	}

	// [100, 1000), [1000, 10000)
	int n0 = (nCount <= 500 ? 100 : 1000);
	int nm = (nCount <= 500 ? 900 : 9000);

	srand(nCount);
	for (int i = 0; i < nCount; ++i) {
		int ir = (int)((double)rand()/RAND_MAX*nm) + n0;
		fprintf(fp, "%d\n", ir);
	}

	fclose(fp);
	return 0;
}

