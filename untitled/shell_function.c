#include "Squelette.c"

/* Fonction pour afficher l'aide */
int shell_help(char **args){
    printf("Shell Help\n");
    printf("Type the name of a command to get more information about it.\n");
    printf("List of commands:\n");

    for (int i = 0; i < shell_num_builtins(); i++) {
        printf("  %s: %s\n", builtin_str[i], builtin_desc[i]);
    }

    return EXIT_SUCCESS_SHELL;
}

int shell_cd(char **args) {
    getcwd(HOME_SHELL, 255);
    if (args[1] == NULL) {
        chdir(HOME_HOME);
        return EXIT_SUCCESS_SHELL;
    }
    if (args[1] == TILD) {
        chdir(HOME_HOME);
        return EXIT_SUCCESS_SHELL;
    }
}
int shell_directory (char **args) {
    /* Check if a directory was provided in args[1]*/
    char *dir_to_open = args[1] ? args[1] : ".";

    if(args[1] == NULL){
        printf("No directory specified. Using the current directory.\n");
    }

    DIR *rep = opendir(".");
    if (rep != NULL)
    {
        struct dirent *lecture;
        while ((lecture = readdir (rep)))
        {
            struct stat st;
            char path[255];
            snprintf(path, sizeof(path), "%s/%s",dir_to_open,lecture->d_name);
            stat (lecture->d_name, &st);

            /*verifie si c'est un répertoire*/
            if(S_ISDIR(st.st_mode)){
                printf("\033[1;34m"); // Bleu
            }
                /* verifie si c'est un fichier ou un executable*/
            else if(S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)){
                if(access(path, X_OK) == 0){
                    printf("\033[1;32m"); // Vert
                }else{
                    printf("\033[1;31m"); // Rouge
                }
            }

            time_t t = st.st_mtime;
            struct tm tm = *localtime (&t);
            char s[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
            printf ("%-14s %s\n", lecture->d_name, s);
            printf("\033[0m"); // Reset

        }
        closedir (rep), rep = NULL;
    }
    else {
        /* If the directory could not be opened, print an error message*/
        perror("Error opening directory");
        printf("Failed to open directory: %s\n", dir_to_open);
    }
    return EXIT_SUCCESS_SHELL;
}

/* Fonction pour afficher le répertoire courant*/
int shell_PWD(char **args){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
    return 1;
}
/* Fonction pour afficher l'historique des commandes*/
int shell_history(char **args){
    printf("Historique des commandes\n");
    return 1;
}
/* Fonction pour afficher la date et l'heure courante*/
int shell_date(char **args){
    time_t t;
    struct tm *tm;
    char fech[100];
    t = time(NULL);
    tm = localtime(&t);
    strftime(fech, sizeof(fech), "%c", tm);
    printf("%s\n", fech);
    return 1;
}
/* Fonction pour afficher les arguments de la commande*/
int shell_echo(char **args){
    int i = 1;
    while(args[i] != NULL){
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 1;
}
/* Fonction pour créer un répertoire*/
int shell_mkdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected argument to \"mkdir\"\n");
    } else {
        if(mkdir(args[1], 0777) != 0){
            perror("shell");
        }
    }
    return 1;
}
/* Fonction pour supprimer un répertoire*/
int shell_rmdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected argument to \"rmdir\"\n");
    } else {
        if(rmdir(args[1]) != 0){
            perror("shell");
        }
    }
    return 1;
}
/* Fonction pour exécuter une commande avec les privilèges de l'utilisateur root*/
int shell_sudo(char **args){

}
/* Fonction pour afficher le contenu d'un fichier*/
int shell_dump(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected argument to \"filedump\"\n");
        return EXIT_ERROR_SHELL;
    }

    FILE *infile = fopen(args[1], "r");
    if(infile == NULL){
        perror("shell");
        return EXIT_ERROR_SHELL;
    }

    unsigned long start = strtoul(args[2], NULL, 10);
    unsigned long end = strtoul(args[3], NULL, 10);
    unsigned long nbOctet = strtoul(args[4], NULL, 10);

    printf("Octet debut: %ld\n",start);
    printf("Octet fin: %ld\n",end);
    printf("Nombre d'octet: %ld\n",nbOctet);
    char ch;
    fseek(infile,start,SEEK_SET);
    while(ftell(infile) < end){
        for(int i = 0; i < nbOctet; i++){
            ch = getc(infile);
            printf("%x ",ch);
        }
        printf(" ");
        for(int j=0;j<nbOctet;j++){
            ch = getc(infile);
            printf("%c",ch);
        }
        printf("\n");
    }

    fclose(infile);
    return EXIT_SUCCESS_SHELL;
}

/* Fonction pour créer un fichier vide*/
int shell_touch(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected argument to \"touch\"\n");
    } else {
        FILE *file = fopen(args[1], "w");
        if(file == NULL){
            perror("shell");
        }
        fclose(file);
    }
    return 1;
}
/* Fonction pour effacer l'écran*/
int shell_clear(char **args){
    printf("\033[2J\033[1;1H");
    return 1;
}

/* Fonction pour quitter le shell*/
int shell_exit(char **args){
    return EXIT_FAILURE_SHELL;
}
