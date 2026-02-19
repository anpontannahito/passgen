#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #pragma comment(lib, "bcrypt.lib")
#else
    #include <unistd.h>
    #include <sys/random.h>
#endif

unsigned int secure_random() {
    unsigned int num;

#ifdef _WIN32
    if (BCryptGenRandom(NULL, (PUCHAR)&num, sizeof(num),
                        BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        fprintf(stderr, "Random generation failed\n");
        exit(1);
    }
#else
    if (getrandom(&num, sizeof(num), 0) != sizeof(num)) {
        perror("getrandom");
        exit(1);
    }
#endif

    return num;
}

typedef struct {
    int use_lower;
    int use_upper;
    int use_number;
    int use_symbol;
} Option;

char *password_gen(int length, Option opt);

int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Usage: %s <password length> <count> [-s,-n,-u,-l]\n", argv[0]);
        return 1;
    }
    int length = atoi(argv[1]);
    int value = atoi(argv[2]);
    Option opt = {1, 1, 1, 0};

    if (length <= 0 || value <= 0){
        printf("[ERROR] Invaid arguments\n");
        return 0;
    }

    for (int i = 3;i < argc; i++){
        if (strcmp(argv[i], "-s") == 0){
            opt.use_symbol = 1;
        }
        else if (strcmp(argv[i], "-n") == 0){
            opt.use_number = 0;
        }
        else if (strcmp(argv[i], "-u") == 0){
            opt.use_upper = 0;
        }
        else if (strcmp(argv[i], "-l") == 0){
            opt.use_lower = 0;
        }
    }

    srand(time(NULL));
    if (!opt.use_lower && !opt.use_upper && !opt.use_number && !opt.use_symbol) {
        printf("[ERROR] All character types disabled\n");
        return 1;
    }
    printf("password:\n");
    for (int i = 0; i < value; i++) {
        char *password = password_gen(length, opt);
        printf("%s\t", password);
        free(password);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}

char *password_gen(int length, Option opt){
    char charset[100] = "";
    if (opt.use_lower)
        strcat(charset, "abcdefghijklmnopqrstuvwxyz");

    if (opt.use_upper)
        strcat(charset, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    if (opt.use_number)
        strcat(charset, "0123456789");

    if (opt.use_symbol)
        strcat(charset, "!@#$%^&*()");
    int charset_size = strlen(charset);

    char *password = malloc(length + 1);
    if (password == NULL) {
        printf("[ERROR] Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        int index = secure_random() % charset_size;
        password[i] = charset[index];
    }
    password[length] = '\0';
    return password;
}