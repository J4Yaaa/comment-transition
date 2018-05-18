#pragma once
#include <stdio.h>
#include <stdlib.h>

#define INPUT "input.c"
#define OUTPUT "output.c"

enum STA
{
	NULSTAT,
	CSTAT,
	CPPSTAT,
	EOFSTAT,
};

static enum STA STATUS = NULSTAT;    //将代码状态预制为普通状态
