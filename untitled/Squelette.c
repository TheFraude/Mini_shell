#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_string.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>

/* taille max du buffer d'entrée (stdin) en lecture de la chaine de caractere */
#define shell_BUFSIZE 1024
#define EXIT_FAILURE_SHELL 0

#define EXIT_SUCCESS_SHELL 1
#define EXIT_ERROR_SHELL 2
#define SHELL_TOK_BUFSIZE 64 /* Define the missing constant */
#define SHELL_TOK_DELIM " \t\r\n\a" /*Define the missing constant*/
const char TILD='~';
const char DELIMITED =' ';
const char BACKGROUND ='&';
char HOME_HOME[255];
char HOME_SHELL[255];
/* Prototypes des fonctions REPL*/
int shell_exit(char **args);
int shell_num_builtins();
int shell_launch(char **args);
int shell_execute(char **args);
char *shell_read_line(void);
char **shell_split_line(char *line);
void shell_loop(void);
/*Prototypes des fonctions interne*/
int shell_cd(char **args);
int shell_directory(char **args);
int shell_PWD(char **args);
int shell_history(char **args);
int shell_date(char **args);
int shell_echo(char **args);
int shell_mkdir(char **args);
int shell_rmdir(char **args);
int shell_sudo(char **args);
int shell_dump(char **args);
int shell_touch(char **args);
int shell_help(char **args);
int shell_clear(char **args);
/* Tableau de noms de commandes intégrées*/
char *builtin_str[] = {
        "cd",
        "ls",
        "pwd",
        "history",
        "date",
        "echo",
        "mkdir",
        "rmdir",
        "sudo",
        "dump",
        "touch",
        "clear",
        "help",
        "exit"
};
/* Tableau de pointeurs sur fonctions pour les commandes intégrée*/
int (*builtin_func[]) (char **) = {
        &shell_cd,
        &shell_directory,
        &shell_PWD,
        &shell_history,
        &shell_date,
        &shell_echo,
        &shell_mkdir,
        &shell_rmdir,
        &shell_sudo,
        &shell_dump,
        &shell_touch,
        &shell_clear,
        &shell_help,
        &shell_exit
};

/*tableau de description des commandes intégrées*/
char *builtin_desc[] = {
        "CHANGE DE REPETOIRE <cd [directory]>",
        "LISTE LE CONTENU D'UN REPERTOIRE <ls -[option] [file or not] >",
        "AFFICHE LE REPERTOIRE COURANT <pwd>",
        "AFFICHE L'HISTORIQUE DES COMMANDES <history>",
        "AFFICHE LA DATE ET L'HEURE COURANTE <date>",
        "AFFICHE LES ARGUMENTS DE LA COMMANDE <echo [arguments]>",
        "CREE UN REPERTOIRE <mkdir [name]>",
        "SUPPRIME UN REPERTOIRE <rmdir [name]>",
        "EXECUTE UNE COMMANDE AVEC LES PRIVILEGES DE L'UTILISATEUR ROOT <sudo [command]>",
        "AFFICHE LE CONTENU D'UN FICHIER <dump [file] [start] [end] [nbOctet]>",
        "CREE UN FICHIER VIDE <touch [file]>",
        "EFFACE L'ECRAN <clear>",
        "AFFICHE L'AIDE <help>",
        "QUITTER LE SHELL <exit>"
};
int shell_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}
/* Fonction pour exécuter une commande non intégrée*/
int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0){
        /* Processus fils*/
        if((args[0], args) == -1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if(pid < 0){
        /* Erreur de fork*/
        perror("shell");
    } else {
        /* Processus parent*/
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

/*Fonction pour exécuter une commande interne*/
int shell_execute(char **args){
    int i;

    if (args[0] == NULL) {
        /* An empty command was entered.*/
        return 1;
    }

    for (i = 0; i < shell_num_builtins(); i++) {
        if (my_strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}
/*Fonction pour lire une ligne de commande depuis l'entrée standard*/
char *shell_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}
/*Fonction pour diviser une ligne de commande en arguments*/

char **shell_split_line(char *line){
    int bufsize = SHELL_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = my_strtok(line, SHELL_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += SHELL_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = my_strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
/* Fonction pour exécuter la boucle principale du shell*/
void shell_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = shell_read_line(); /*lecture de la ligne du buffer*/
        printf("Ligne lue : %s\n", line); /*affichage de la ligne lue*/
        args = shell_split_line(line); /*analyse et recheceh commande */
        printf("Arguments : %s\n", args[0]); /*affichage des arguments*/
        printf("\n");
        status = shell_execute(args); /*execution de la commande avec ses pararmetres*/

        free(line);
        free(args);
    } while(status);

}
/* Fonction principale*/

int main(int argc, char **argv){
    printf("Mini SHELL - exit pour Quitter \n");
    shell_loop();
    printf("Fin du Mini SHELL \n");
    return EXIT_SUCCESS;
}