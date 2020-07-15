#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cachelab.h"

#define HIT     0
#define MISS    1
#define EVIT    2

typedef struct {
	int s; /* Number of set index bits. */
	int E; /* Number of lines per set. */
	int b; /* Number of block offset bits. */
} cache_param_t;

typedef struct {
	clock_t timestamp; /* timestamp to record the access time */
	long int tag;      /* tag for the cacheline */
	int valid_bit;     /* valid bit for the cacheline */
} cacheline_t;

/* Global variable for verbose mode */
int verbosity = 0;

void printUsage();
cacheline_t ** initCache(int total_set, int line_number);
void freeCache(cacheline_t **cache, int total_set);
void replayTrace(char *trace_file, cacheline_t **cache,cache_param_t cache_param, int *hit, int 
		*miss, int *eviction);
int checkCacheline(long tag, cacheline_t *cacheline, cache_param_t cache_param, int *hit, int
		*miss, int *eviction);
char *output_verbosity(int type, char *msg);

/* Help function */
void printUsage()
{
	printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	puts("Options:");
	puts("  -h        Print this help message.");
	puts("  -v        Optional verbose flag.");
	puts("  -s <num>  Number of set index bits");
	puts("  -E <num>  Number of lines per set.");
	puts("  -b <num>  Number of block offset bits.");
	puts("  -t <file> Trace file.");
	puts("\nExamples:");
	printf("linux> ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
	printf("linux> ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
	exit(0);
}

/* Initialize the cache */
cacheline_t ** initCache(int total_set, int line_number)
{
	int i, j;
	cacheline_t **cache = (cacheline_t **)malloc(total_set * sizeof(cacheline_t *));
	if (cache == NULL)
		printf("Malloc error(level two)!\n");
	for (i = 0; i < total_set; i++)
	{
		cache[i] = (cacheline_t *)malloc(line_number * sizeof(cacheline_t));
		if (cache[i] == NULL)
			printf("Malloc error(level one)!\n");
	}
	for (i = 0; i < total_set; i++){
		for (j = 0; j < line_number; j++){
			cache[i][j].timestamp = 0;
			cache[i][j].tag = 0;
			cache[i][j].valid_bit = 0;
		}
	}
	return cache;
}

/* Free the cache */
void freeCache(cacheline_t **cache, int total_set)
{
	int i;
	for (i = 0; i < total_set; i++)
		free(cache[i]);
	free(cache);
}

/* Parse each line in traces file and simulate the behavior of cache with defined parameters */
void replayTrace(char *trace_file, cacheline_t **cache, cache_param_t cache_param, int *hit, int *miss, int *eviction)
{
	char line[1024];
	char *result;
	char command;
	long addr;
	int size;
	int ret = 0;

	result = (char *)malloc(64 * sizeof(char));
	FILE * fp = fopen(trace_file, "r");
	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, " %c %lx,%d", &command, &addr, &size);
		if (line[0] == 'I')
			continue;
		else
		{		
			long set_line = (addr >> cache_param.b) & ((0x1 << cache_param.s) - 1);
			long tag = addr >> (cache_param.b + cache_param.s);
			memset(result, 0, 64);

			switch(command)
			{
				case 'L':
					ret = checkCacheline(tag, cache[set_line], cache_param, hit, miss, eviction);
					result = output_verbosity(ret, result);
					break;
				case 'M':
					ret = checkCacheline(tag, cache[set_line], cache_param, hit, miss, eviction);
					result = output_verbosity(ret, result);
					ret = checkCacheline(tag, cache[set_line], cache_param, hit, miss, eviction);
					result = output_verbosity(ret, result);
					break;
				case 'S':
					ret = checkCacheline(tag, cache[set_line], cache_param, hit, miss, eviction);
					result = output_verbosity(ret, result);
					break;
			}
			if (verbosity)
				printf("%c %lx,%d %s\n", command, addr, size, result);
		}
	} 
	fclose(fp);
}

/* Check the cacheline in the cache */
int checkCacheline(long tag, cacheline_t *cacheline, cache_param_t cache_param, int *hit, int *miss, int *eviction)
{
	int i;
	int index = 0;
	clock_t lru = cacheline[0].timestamp;
	for (i = 0; i < cache_param.E; i++)
	{
		if (cacheline[i].valid_bit == 0)
		{
			cacheline[i].valid_bit = 1;
			cacheline[i].tag = tag;
			cacheline[i].timestamp = clock();
			(*miss)++;
			return MISS;
		}
		else if (cacheline[i].tag == tag)
		{
			(*hit)++;
			cacheline[i].timestamp = clock();
			return HIT;
		}
		else
			continue;
	}
	// eviction happens here.
	(*miss)++;
	for (i = 0; i < cache_param.E; i++)
	{
		if (((double) (lru - cacheline[i].timestamp)) > 0)
		{
			lru = cacheline[i].timestamp;
			index = i;
		}
	}
	cacheline[index].tag = tag;
	cacheline[index].timestamp = clock();
	(*eviction)++;
	return EVIT;
}

/* Verbose output */
char *output_verbosity(int type, char *msg)
{
	switch(type)
	{
		case 0:
			strcat(msg, "hit");
			break;
		case 1:
			strcat(msg, "miss");
			break;
		case 2:
			strcat(msg, "miss eviction");
			break;
	}
	return msg;
}

int main(int argc, char **argv)
{
	int ch;
	cache_param_t cache_param;
	memset(&cache_param, 0, sizeof(cache_param));
	char *trace_file = NULL;

	int total_set = 0;

	int hit = 0;
	int miss = 0;
	int eviction = 0;

	/* Parse the argument for the cache parameters */
	while((ch = getopt(argc, argv, "s:E:b:t:vh")) != -1)
	{
		switch(ch) {
			case 's':
				cache_param.s = atoi(optarg);
				break;
			case 'E':
				cache_param.E = atoi(optarg);
				break;
			case 'b':
				cache_param.b = atoi(optarg);
				break;
			case 't':
				trace_file = optarg;
				break;
			case 'v':
				verbosity = 1;
				break;
			case 'h':
				printUsage();
				break;
			default:
				printf("argv %c is not identified\n", ch);
		}
	}
	/* Check if the command parameter is appropriate */
	int flag = (cache_param.s == 0) || (cache_param.E == 0) || (cache_param.b == 0) || (trace_file == NULL);

	if (flag)
	{
		printf("./csim: Missing required command line argument.\n");
		printUsage();
		exit(0);
	}
	total_set = pow(2, cache_param.s);
	cacheline_t **cache = initCache(total_set, cache_param.E);
	replayTrace(trace_file, cache, cache_param, &hit, &miss, &eviction);
	freeCache(cache, total_set);
    printSummary(hit, miss, eviction);
    return 0;
}
