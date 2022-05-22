#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeCSVRow(CSVRow* row) {
    free(row->fld);
    free(row->line);
}

unsigned long processFileCSV(FILE *f, char delim, char quote, CSVRow** rows) {
    int c;
    char quotes = 0, dquotes = 0, mark = 1, nrow = 0;;
    unsigned long row = 0, crows = 1, slen = 0;
    if(f == NULL)
        return 0;
    if (rows == NULL)
        return 0;
    *rows = (CSVRow*) malloc(sizeof(CSVRow));
    memset(*rows, 0, sizeof(CSVRow));
    while (!feof(f)) {
        if((c = fgetc(f)) == EOF)
            continue;
        if (nrow) {
            nrow = 0;
            *rows = (CSVRow*) realloc(*rows, sizeof(CSVRow) * (crows + 1));
            memset(&(*rows)[crows++], 0, sizeof(CSVRow));
        }
        if (dquotes) {
            dquotes = 0;
            if (c != quote) {
                quotes = 0;
            }
        } else if (c == quote) {
            if (!quotes) {
                quotes = 1;
            } else {
                dquotes = 1;
            }
            continue;
        }
        if (!quotes) {
            if (c == '\n' || c == '\r') {
                if (slen > 0) {
                    row++;
                    nrow = 1;
                    slen = 0;
                    mark = 1;
                }
                continue;
            } else if (c == delim) {
                mark = 2;
                c = 0;
            }
        }
        (*rows)[row].line = (char*) realloc((*rows)[row].line, sizeof(char) * (slen + 2));
        (*rows)[row].line[slen++] = c;
        (*rows)[row].line[slen] = 0;
        if (mark) {
            if (mark-- == 1) {
                (*rows)[row].fld = (unsigned long*) realloc((*rows)[row].fld, sizeof(unsigned long) * ((*rows)[row].flds + 1));
                (*rows)[row].fld[(*rows)[row].flds++] = slen - 1;
            }
        }
    }
    return crows;
}

char* getValueCSV(CSV* csv, unsigned long row, unsigned long column) {
    if (csv->rowCount <= row) return NULL;
    if (csv->row[row].flds <= column) return NULL;
    return &csv->row[row].line[csv->row[row].fld[column]];
}

unsigned long getRowCountCSV(CSV* csv) {
    return csv->rowCount;
}

unsigned long getColumnCountCSV(CSV* csv, unsigned long row) {
    if (csv->rowCount <= row) return 0;
    return csv->row[row].flds;
}

int loadCSV(CSV* csv, char* path, char delim, char quotes) {
    FILE* f = NULL;
    if (!(f = fopen(path, "r"))) {
        return 1;
    }
    csv->rowCount = processFileCSV(f, delim, quotes, &csv->row);
    fclose(f);
    if (csv->rowCount == 0) {
        return 1;
    }
    return 0;
}

void freeCSV(CSV* csv) {
    for (int i = 0; i < csv->rowCount; i++) {
        freeCSVRow(&csv->row[i]);
    }
}