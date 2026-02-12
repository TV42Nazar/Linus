#include <stdio.h>
int main(int c, char *v[]) {
    if(c<3) return 1;
    char b[1024]; int n;
    FILE *r = fopen(v[1], "rb");
    FILE *w = fopen(v[2], "wb");
    while((n = fread(b, 1, 1024, r)) > 0) {
        if(fwrite(b, 1, n, w) < n) {
            perror("Error");
            return 1;
        }
    }
    return 0;
}