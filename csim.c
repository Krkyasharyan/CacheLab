#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct cache_line{
    int tag;
    unsigned int valid : 1;
    unsigned long timestamp;
} **cache;

int s, E, b;

// Function to get the current timestamp
unsigned long getTimestamp() {
    static unsigned long timestamp = 0;  // Static variable to store the timestamp
    return ++timestamp;  // Increment and return the timestamp value
}

void tick() {
    for (int i = 0; i < (1 << s); i++)
    {
        for (int j  = 0; j < E; j++)
        {
            if(cache[i][j].valid) cache[i][j].timestamp++;
        }
    }
}

int main(int argc, char **argv)
{
    int opt;
    char *t;
    while((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch(opt) {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                t = optarg;
                break;
            default:
                printf("wrong argument\n");
                exit(1);
        }
    }
// 100000 >> 4 = 10, mask 1111, 0010&1111
    cache = (struct cache_line **)malloc(sizeof(struct cache_line *) * (1 << s));

    for(int i = 0; i < (1 << s); i++) {
        cache[i] = (struct cache_line *)malloc(sizeof(struct cache_line) * E);
        for(int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
        }
    }

    FILE *fp = fopen(t, "r");
    char op;
    unsigned int addr;
    int size;
    int hit_count = 0, miss_count = 0, eviction_count = 0;
    while(fscanf(fp, " %c %x,%d", &op, &addr, &size) != EOF) { // No need for size tho, in our case
        if(op == 'I') continue;
        tick();
        int index = (addr >> b) & ((-1U) >> (64 - s));
        int tag = (addr >> (s + b));
        int hit = 0, hit_index;
        for(int i = 0; i < E; i++) {
            if(cache[index][i].valid && cache[index][i].tag == tag) {
                hit = 1;
                hit_index = i;
                break;
            }
        }
        if(hit) {
            op == 'M' ? hit_count += 2 : hit_count++;
            cache[index][hit_index].timestamp = 0;
            //tick();
        }
        else {
            miss_count++;
            if(op == 'M') hit_count++;
            int empty = -1;
            for (int i = 0; i < E; i++) {
                if(!cache[index][i].valid) {
                    empty = i;
                    break;
                }
            }
            if(empty != -1) {
                cache[index][empty].tag = tag;
                cache[index][empty].valid = 1;
                cache[index][empty].timestamp = 0;
                //tick();
            }
            else {
                eviction_count++;
                long max_timestamp = 0x7fffffff;
                int max_index;
                for(int i = 0; i < E; i++) {
                    if(cache[index][i].timestamp > max_timestamp) {
                        max_timestamp = cache[index][i].timestamp;
                        max_index = i;
                    }
                }
                cache[index][max_index].tag = tag;
                cache[index][max_index].timestamp = 0;
                //tick();
            }
        }

    }
    fclose(fp);
    for(int i = 0; i < (1 << s); i++) {
        free(cache[i]);
    }
    free(cache);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}