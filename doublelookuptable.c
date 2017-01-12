#include <stdio.h>

int main(void) {
    
    int lookupTable[4][5] = {
      { -1, 9, 4, -1, 0 },
        {-1, -1, 9, -1, 4},
        {-1, -1, -1, -1, 5},
        {-1, -1, -1, -1, 9}
    };
    int row, columns;
    for(row=0; row < 4; row++) {
        for(columns = 0; columns < 5; columns++){
            printf("Row %d Columns %d Value %d\n", row, columns, lookupTable[row][columns]);
        }
    }
    return 0;
}
