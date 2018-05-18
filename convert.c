#include <stdio.h>
#include "convert.h"



void Test_NULSTAT(FILE *ipf, FILE *opf)
{
	int c = fgetc(ipf);
	switch ( c )
	{
	case '/':                                   //若读取为 / ，则有可能是   C   C++   A / B    /EOF
	{
		int s = fgetc(ipf);
		switch ( s )
		{
		case '*':                               // C
			fputc('/',opf);
			fputc('/', opf);                    // 输出  //
			STATUS = CSTAT;                     // 状态置位 C
			break;
		case '/':                               // C++
			fputc('/', opf);
			fputc('/', opf);                    // 输出  // 
			STATUS = CPPSTAT;                   // 状态置位  C++
			break;
		case EOF:                               // 结束
			fputc(c, opf);
			STATUS = EOFSTAT;                   // 状态置位   EOF
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
			ungetc(c,ipf); //例如碰到 **/ 的情况，应退回刚读取的数据，避免将 **看为一组 意外丢掉注释结束符
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
	while (STATUS != EOFSTAT)     //只要文件没结束一直进行判断和转换
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
