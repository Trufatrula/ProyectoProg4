#ifndef JALADCVS
#define JALADCSV

typedef struct {
    char* line;
    unsigned long* fld;
    unsigned long flds;
} CSVRow;

typedef struct {
    CSVRow* row;
    unsigned long rowCount;
} CSV;

int loadCSVEx(CSV* csv, char* path, char delim, char quotes);
int loadCSV(CSV* csv, char* path);
void freeCSV(CSV* csv);
char* getValueCSV(CSV* csv, unsigned long row, unsigned long column);
unsigned long getRowCountCSV(CSV* csv);
unsigned long getColumnCountCSV(CSV* csv, unsigned long row);

#endif