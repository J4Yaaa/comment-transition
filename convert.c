#include <stdio.h>
#include "convert.h"



void Test_NULSTAT(FILE *ipf, FILE *opf)
{
	int c = fgetc(ipf);
	switch ( c )
	{
	case '/':                                   //����ȡΪ / �����п�����   C   C++   A / B    /EOF
	{
		int s = fgetc(ipf);
		switch ( s )
		{
		case '*':                               // C
			fputc('/',opf);
			fputc('/', opf);                    // ���  //
			STATUS = CSTAT;                     // ״̬��λ C
			break;
		case '/':                               // C++
			fputc('/', opf);
			fputc('/', opf);                    // ���  // 
			STATUS = CPPSTAT;                   // ״̬��λ  C++
			break;
		case EOF:                               // ����
			fputc(c, opf);
			STATUS = EOFSTAT;                   // ״̬��λ   EOF
			break;
		default:
			fputc(c, opf);
			break;
		}

	}
		break;
	case EOF:
		fputc(c, opf);
		STATUS = EOFSTAT;
		break;
	default:
		fputc(c, opf);
		STATUS = NULSTAT;
		break;
	}
}

void Test_CSTAT(FILE *ipf, FILE *opf)
{
	int c = fgetc(ipf);
	switch ( c )
	{
	case '\n':
		fputc(c, opf);
		fputc('/', opf);
		fputc('/', opf);
		STATUS = CSTAT;
		break;
	case '*':
	{
		int s = fgetc(ipf);
		switch ( s )
		{
		case '/':
			fputc('\n', opf);
			STATUS = NULSTAT;
			break;
		case EOF:
			fputc('/', opf);
			STATUS = EOFSTAT;
			break;
		default:
			ungetc(c,ipf); //�������� **/ �������Ӧ�˻ظն�ȡ�����ݣ����⽫ **��Ϊһ�� ���ⶪ��ע�ͽ�����
			fputc(c, opf);
			STATUS = CSTAT;
			break;
		}
	}
		break;
	case EOF:
		fputc(c, opf);
		STATUS = EOFSTAT;
		break;
	default:
		fputc(c, opf);
		STATUS = CSTAT;
		break;
	}
}

void Test_CPPSTAT(FILE *ipf, FILE *opf)
{
	int c = getc(ipf);
	switch ( c )
	{
	case EOF:
		fputc(c, opf);
		STATUS = EOFSTAT;
		break;
	case '\n':
		fputc(c, opf);
		STATUS = NULSTAT;
		break;
	default:
		fputc(c, opf);
		STATUS = CPPSTAT;
		break;
	}
}

void Test_EOFSTAT(FILE *ipf, FILE *opf)
{
	int c = getc(ipf);
	fputc(c, opf);
	STATUS = EOFSTAT;
}


void Test_Convert_Main(FILE *ipf, FILE *opf)
{
	while (STATUS != EOFSTAT)     //ֻҪ�ļ�û����һֱ�����жϺ�ת��
	{
		switch (STATUS)
		{
		case NULSTAT:
			Test_NULSTAT(ipf, opf);
			break;
		case CSTAT:
			Test_CSTAT(ipf, opf);
			break;
		case CPPSTAT:
			Test_CPPSTAT(ipf, opf);
			break;
		case EOFSTAT:
			Test_EOFSTAT(ipf, opf);
			break;
		default:
			break;
		}
	}
}
