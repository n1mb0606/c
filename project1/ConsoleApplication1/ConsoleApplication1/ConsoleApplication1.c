#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define TRUE 1
#define FALSE 0

#define CROSS -1
#define FILL 1
#define EMPTY 0

int nemo_size;
char** db_ptr_maker(int len)
{
	return (char**)malloc(sizeof(char*) * len);
}
char* arr_maker(int len)
{
	return (char*)malloc(sizeof(char) * len);
}
char** arr_2d_maker(int col, int row)
{
	int i;
	char** arr_2d = (char**)malloc(sizeof(char*)*col);
	for (i = 0; i < col; i++)
		arr_2d[i] = arr_maker(row);
	return arr_2d;
}
void arr_2d_init(char** arr, int col, int row, int init_char)
{
	int i, j;
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
			arr[i][j] = init_char;
	}
}
char* spl_arr(const char* const arr, const int len)
{
	if (len > 100)
	{
		printf("Function:spl_arr Error, Check the parameter, len");
		return NULL;
	}
	int i, buf[100];
	int cnt = 0;
	int num = 0;
	int NE_len = len - 1;//null exterminated len
	for (i = 0; i < NE_len; i++)
	{
		if (arr[i] == ' ')
		{
			if (i == 0)
			{
				fputs("Function spl_arr Error, Invalid Input", stdout);
				return NULL;
			}

			else
			{
				buf[cnt] = num;
				num = 0;
				cnt++;
			}
		}
		else if (i == (NE_len - 1))
		{
			num = (num * 10) + arr[i] - 48;//char to interger
			if ((num > 255) && (num < 0))
			{
				fputs("Function spl_arr Error: overflow occured", stdout);
				return NULL;
			}
			buf[cnt] = num;
			cnt++;
		}
		else
			num = (num * 10) + arr[i] - 48;
	}
	char* sp_arr = (char*)malloc(sizeof(char)*(cnt + 1));//splited arr
	for (i = 0; i < cnt; i++)
		sp_arr[i] = buf[i];
	sp_arr[cnt] = '\0';
	return sp_arr;//please free later
}
void arr_init(int len, char* arr, char init)
{
	int i;
	for (i = 0; i < len; i++) arr[i] = init;
}
//File Functions
void prnt_arr(const int len, const char* const arr)
{
	int i = 0;	//Prints array with numbers
	printf("[");
	for (i = 0; i<len; i++)
	{
		if (arr[i] == FILL) printf("O");
		else if (arr[i] == CROSS) printf("X");
		else printf("_");
	}
	printf("]");
	printf("\n");
}
int iea(char* arr, int len, char emp_char)
{
	/*	DES:	Short of is empty array
	Returns input array is empty or not
	INPUT	(char*)arr:	array to be checked as empty
	(int)len:	length of array
	(char)emp_char:	character recognized as empty
	OUTPUT	(int)TRUE
	(int)FALSE
	Ex) iea(arr, 5, 0); iea(arr, 5, '\0');
	*/
	int i;
	for (i = 0; i < len; i++)
		if (arr[i] != emp_char) return FALSE;
	return TRUE;
}
int issub(char* case_arr, char* comp, int len, char emp_char) //chk case_arr is sub
{
	/*	DES: Returns TRUE if case_arr is subordinated to comp.
	INPUT	(char*)case_arr:	array to be checked as subordinated
	(char*)comp: 		array to be compared
	(int)len:			length of arraies
	(char)emp_char:		character to be recognized as empty
	OUTPUT	(int)TRUE
	(int)FALSE
	Ex)	issub(arr, arr2, 5, 0); issub(arr, arr2, 5, '0');
	*/
	int i;
	for (i = 0; i < len; i++)
		if ((comp[i] != emp_char) & (comp[i] != case_arr[i]))
			return FALSE;
	return TRUE;
}
void dac(char* org, char* res, char* parr, char* nlist, int plen, int* init)//init is initial parr case...
{
	/*	DES:	Short of Difference array check
	Assign res result of differences of arraies
	INPUT	(char*)org:	Orignal array
	(char*)res: array to be saved as result
	(char*)parr:array saves p-parted numbers
	(char*)nlist:array saves number list
	(int)plen: length of parr
	OUTPUT	(void)
	Ex) dac(org, res, parr, nlist, 5);
	*/
	char* arr_case = (char*)malloc(sizeof(char) * nemo_size);//arr_case organizing
	int i, j;
	int cnt = 0;
	int len = 2 * plen - 1; //len for loop
	for (i = 0; i < len; i++)
	{
		if ((i % 2) == 0)
		{
			if (((i / 2) == 0) || ((i / 2) == (len - 1) / 2))
			{
				for (j = 0; j < parr[i / 2]; j++)
					arr_case[cnt++] = CROSS;
			}
			else
			{
				for (j = 0; j < (parr[i / 2] + 1); j++)
					arr_case[cnt++] = CROSS;
			}
		}
		else
		{
			for (j = 0; j < (nlist[i / 2]); j++)
				arr_case[cnt++] = FILL;
		}
	}
	//prnt_arr(nemo_size, arr_case);
	if (iea(org, nemo_size, EMPTY) == TRUE) //short of 'is empty string'
	{
		if ((iea(res, nemo_size, EMPTY) == TRUE) && (*init == TRUE))
		{//if result is empty, fill case in result...
			memcpy(res, arr_case, sizeof(char) * nemo_size);
			*init = FALSE;
		}
		else
		{
			for (i = 0; i < nemo_size; i++)
			{
				if (res[i] != arr_case[i])
					res[i] = EMPTY;
			}
		}
	}
	else
	{
		if (issub(arr_case, org, nemo_size, EMPTY) == TRUE)
		{//issub checks is arr is sub
			if ((iea(res, nemo_size, EMPTY) == TRUE) && (*init == TRUE)) {//errror
				memcpy(res, arr_case, sizeof(char) * nemo_size);
				*init = FALSE;
			}
			else
			{
				for (i = 0; i < nemo_size; i++)
				{
					if (res[i] != arr_case[i])
						res[i] = EMPTY;
				}
			}
		}
	}
	prnt_arr(nemo_size, res);
}
int p_rec(const int p_num, int level, const int num, char* const parr, char* org, char* nlist, char* res, int* init)
{
	/*	INPUT	(int) p_num : Number to part,
	(int) level : interger to count part number and an condition variable to exit,
	(int) num : Number to be parted,
	(int) parr : Pointer of p-partition
	(char*)parr:array saves p-parted numbers
	(char*)nlist:array saves number list
	(char*)res: Result of dac..
	OUTPUT	(void)
	Des: Excute Recursive part of P-Partitioning
	Ex) p_rec(part, 0, num, res);
	*/
	int i, rep; //rep : the number to be repeated
	int sum = 0;
	for (i = 0; i < level; i++) sum += parr[i];	//Calculate sum to caculate remain to be parted
	
	if (level == (p_num - 1))
	{	//if level reach last level
		parr[level] = num - sum;
		dac(org, res, parr, nlist, p_num, init);
		return 0;	//when the last level ends, returns 0
	}
	else if (level == 0)	//if level's status is initial(level == 0)
		rep = num + 1;	//rep is num+1 because first element of p-part can be 0 to num
	else
		rep = num - sum + 1;

	for (i = 0; i < rep; i++)
	{
		parr[level] = i; //Input a number of occasion
		p_rec(p_num, level + 1, num, parr, org, nlist, res, init);
	}
	return 0;	//when a level ends, returns 0
}
char* p_part(const int p_num, const int num, char* org, char* nlist)
{
	/*	INPUT	(int) p_num : Number to part,
	(int) num : Number to be parted
	OUTPUT (char*) res : Pointer of result
	Des : Excute P-Partioning by Number to part and Number to parted.
	Ex) p_part(part, num);
	*/
	int i = 0;
	char* const parr = (char*)malloc(sizeof(char)*p_num);//result of p_part
	char* res = (char*)malloc(sizeof(char) * nemo_size);
	for (i = 0; i < nemo_size; i++) res[i] = 0;

	int* init = (int*)malloc(sizeof(int));//is first case??
	*init = TRUE;//in p_rec, comp for is first case...
	p_rec(p_num, 0, num, parr, org, nlist, res, init);//short of p_recusive:recursive part of p_part
	return res;	//Please free allocated memory
}
//solver Function
int nono_solver(char** nemo_table, char** row_nlist, char** col_nlist, int* p_num, int* num, char* org, char* res)
{
	int i, j;
	for (i = 0; i < nemo_size; i++)
	{
		*num = 0;
		*p_num = strlen(row_nlist[i]) + 1;
		for (j = 0; j < nemo_size; j++) org[j] = nemo_table[i][j];
		for (j = 0; j < strlen(row_nlist[i]); j++) *num += row_nlist[i][j];
		*num = nemo_size - *num - *p_num + 2;
		res = p_part(*p_num, *num, org, row_nlist[i]);
		for (j = 0; j < nemo_size; j++) nemo_table[i][j] = res[j];
		printf("num:%d, p_num:%d\n", *num, *p_num);
	}
	for (i = 0; i < nemo_size; i++)
	{
		*num = 0;
		*p_num = strlen(col_nlist[i]) + 1;
		for (j = 0; j < nemo_size; j++) org[j] = nemo_table[j][i];
		for (j = 0; j < strlen(col_nlist[i]); j++) *num += col_nlist[i][j];
		*num = nemo_size - *num - *p_num + 2;
		res = p_part(*p_num, *num, org, col_nlist[i]);
		for (j = 0; j < nemo_size; j++) nemo_table[j][i] = res[j];
		printf("num:%d, p_num:%d\n", *num, *p_num);
	}

	for (i = 0; i < nemo_size; i++)
	{
		for (j = 0; j < nemo_size; j++)
		{
			if (nemo_table[i][j] == 1)
				printf("■");
			else if (nemo_table[i][j] == -1)
				printf("×");
			else
				printf("　");
		}
		printf("\n");
	}
}
int main(int argc, char *argv[]) {
	FILE* fp;
	errno_t err= fopen_s(&fp, "test.txt", "rt");
	if (err == 1)
		fputs("FILE open error", stdout);
	
	char buf[100];
	fgets(buf, 101, fp);
	nemo_size = atoi(buf); //Input nemo_size
	char** nemo_table = arr_2d_maker(nemo_size, nemo_size);
	arr_2d_init(nemo_table, nemo_size, nemo_size, 0);
	//nemo_table initialized
	char** row_nlist = db_ptr_maker(nemo_size);//horizontal factors
	char** col_nlist = db_ptr_maker(nemo_size);//vertical factors
	//make nlists(numeral hints)

	int i, j;//indexes
	for (i = 0; i < nemo_size; i++)
	{
		fgets(buf, 101, fp);
		row_nlist[i] = spl_arr(buf, strlen(buf));
	}
	fgets(buf, 101, fp);//Enter
	for (i = 0; i < (nemo_size - 1); i++)
	{
		fgets(buf, 101, fp);
		col_nlist[i] = spl_arr(buf, strlen(buf));//Edit
	}
	fgets(buf, 101, fp);
	col_nlist[i] = spl_arr(buf, strlen(buf) + 1);
	if (!feof(fp))
	{
		printf("Input File Error Please check input file");
		return -1;
	}
	printf("File Setting complete");

	int* p_num = (int*)malloc(sizeof(int));
	int* num = (int*)malloc(sizeof(int));
	char* org = (char*)malloc(sizeof(char) * nemo_size);
	char* res = (char*)malloc(sizeof(char) * nemo_size);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);
	nono_solver(nemo_table, row_nlist, col_nlist, p_num, num, org, res);

	system("PAUSE");
	return 0;
}