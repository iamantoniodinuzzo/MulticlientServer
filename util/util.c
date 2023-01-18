#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../data_structure/kdtree/kdtree.h"
#include "../data_structure/entity/user.h"

long stringInsideSquareBracket(const char *in, long out_size, char *out)
{
    char *left = strchr(in, '[');
    if (left)
    {
        char *right = strchr(++left, ']');
        if (right)
        {
            long substring_length = right - left;
            if (out_size > substring_length)
            {
                memcpy(out, left, substring_length);
                out[substring_length] = '\0';
                return substring_length;
            }
        }
    }
    if (out_size > 0)
    {
        out[0] = 0;
    }
    return -1;
}

bool writeOnFile(const char *filename, int *pothole)
{
    FILE *file = fopen(filename, "a+");
    assert(file);

    fprintf(file, "[%d]\n", pothole);
    fclose(file);
    return true;
}

double calculateMaxFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    assert(file);
    if (file != NULL)
    {
        double threshold = 0;
        double i;
        int counter = 0;
        char buffer[1000];

        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            counter++;
            char *value = strrchr(buffer, ';');
            if (value != NULL)
            {
                sscanf(value, ";%lf]", &i);
                threshold += i;
            }
        }
        fclose(file);

        if (threshold == 0)
            return 15;
        else
            return threshold / counter;
    }
    else
    {
        return 15;
    }
}

void buildJsonString(const list_node *node, char *json_string)
{
    char tmp[1000];

    if (node != NULL)
    {
        sprintf(tmp, "{\"val\":%d}", node->pothole->user->username, node->pothole->latitude, node->pothole->longitude, node->pothole->variation);

        if (node->next != NULL)
            strcpy(tmp, strcat(tmp, ","));
        else
        {
            strcpy(tmp, strcat(tmp, "]}\n"));
            tmp[strlen(tmp)] = '\0';
        }
        strcpy(json_string, strcat(json_string, tmp));
        buildJsonString(node->next, json_string);
    }
}