// SPDX-License-Identifier: GPL-3.0

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> //necessário para usar localtime() e struct tm

struct pet {
    char name[20];
    int type;
    int color;
    int food;
    int sleep;
    int play;
};

struct activity {
		char name[200];
        char materials[200];
        char descrip[200];
        char kind[200];
        int hour;
        int minutes;
        int duration;
        int end;
        int done;
		struct activity *next;
};

struct day {
    struct activity *day_routine;
};

struct list_activ {
    struct activity *first;
};

void initial_screen(struct day *aday, struct list_activ* a, struct pet *p);
void readFile(int begin, int end);
void readHeader(int line);
void screen_routine(struct day *aday, struct list_activ *a, struct pet *p);
struct list_activ *initialize(struct list_activ *act);

int calculate_end(struct activity* new)
{
    int x = ((new->hour * 60) + new->minutes + new->duration);
    return x;
}

struct list_activ *create_list(void)
{
    struct list_activ *activities;
    activities = malloc(sizeof(struct list_activ));

    if (activities != NULL)
        activities->first = NULL;

    return activities;
}

void printAct(struct activity *check) 
{
    readFile(46,46);
    printf("%s\n\n", check->name);
    readFile(47,47);
    printf("%s\n\n", check->materials);
    readFile(48,48);
    printf("%s\n\n", check->descrip);
    readFile(49,49);
    printf("%s\n\n", check->kind);
}

struct day *create_day(void)
{
    struct day *aday;
    aday = malloc(sizeof(struct day));

    if (aday != NULL)
        aday->day_routine = NULL;

    return aday;
}

void readRoutine(struct day *aday)
{
	struct activity *check = aday->day_routine;
	while (check != NULL) {
        //print HORARIO
		printf("%dh%d - %s - ", check->hour, check->minutes, check->name);
        printf("%s\n", check->kind);
		check = check->next;
	}
}

void readFile(int begin, int end)
{
    FILE * fPointer;
    fPointer = fopen("texts.txt", "r");

    char singleLine[150];

    for (int x = 0; x <= end; x++) {
        fgets(singleLine, 150, fPointer);
        
        if (x >= begin)
            puts(singleLine);
    }

    fclose(fPointer);
}

void readHeader(int line)
{
    int x = -1;
    FILE * fPointer;
    fPointer = fopen("texts.txt", "r");

    char singleLine[150];
    while (x != line) {
        fgets(singleLine, 150, fPointer);
        x++;

        if (x == line) {
            printf("\n-------------------------------------\n\n");
            printf("           ");
            puts(singleLine);
            printf("-------------------------------------\n\n");
        }

    }

    fclose(fPointer);
}

void writeAct(struct activity* new)
{
    FILE * fInd;
    char final[2] = "\n";
    char nameArch [30];
    FILE * person = fopen("user.txt", "r");
    char end[8] = "Act.txt";
    
    fgets(nameArch, 30, person);
    strtok(nameArch, "\n");
    fclose(person);
    
    strcat(nameArch, end);
    fInd = fopen(nameArch, "a");
    
    fputs(new->name, fInd);
    fputs(final, fInd);
    fputs(new->materials, fInd);
    fputs(final, fInd);
    fputs(new->descrip, fInd);
    fputs(final, fInd);
    fputs(new->kind, fInd);
    fputs(final, fInd);

    fclose(fInd);
}

struct activity *create_act()
{
    struct activity *new_act = malloc(sizeof(struct activity));
    char namen[20];
    char descripn[200];
    char materialn[200];
    int hourn = 60;
    int min = 60;
    char kindn[2];
    char c;
    
    readHeader(14);
    readFile(16,16);

    c = getc(stdin); 
    if (c != '\n')
        ungetc(c, stdin);
    
    scanf("%[^\n]", namen);
    c = getc(stdin); 
    if (c != '\n')
        ungetc(c, stdin);
    
    strcpy(new_act->name, namen);
    
    printf("\n");
    readFile(17,17);

    scanf("%[^\n]", materialn);
    c = getc(stdin); 
    if (c != '\n')
        ungetc(c, stdin);

    strcpy(new_act->materials, materialn);

    printf("\n");

    readFile(18,18);
    scanf("%[^\n]", descripn);
    c = getc(stdin); 
    if (c != '\n')
        ungetc(c, stdin);
    strcpy(new_act->descrip, descripn);
    
    /*while (hourn < 0 || hourn > 23) {
        readFile(56,56);
        scanf("%d", &hourn);
    }
    new_act->hour = hourn;
    
    while (min < 0 || min > 59) {
        readFile(57,57);
        scanf("%d", &min);
    }
    new_act->minutes = min;
    
    readFile(58,58);
    scanf("%d", &new_act->duration);

    new_act->end = calculate_end(new_act);

    printf("\n");*/
    
    int x = 0;
    
    while (x == 0) {
    readFile(19,19);
    scanf("%s", kindn);
    
        if (strcmp (kindn, "P") == 0) {
            strcpy(new_act->kind, "Play");
            break;
        } else if (strcmp (kindn, "S") == 0) {
            strcpy(new_act->kind, "Sleep");
            break;
        } else if (strcmp (kindn, "F") == 0) {
            strcpy(new_act->kind, "Food");
            break;
        } else {
            readFile(0,0);
            printf("\n");
        }
    }
    
    new_act->next = NULL;

    writeAct(new_act);

    return new_act;
}

int askPin(void)
{
    char pin[10];
    char enterPin[10];
    char line[40];
    FILE * person = fopen("user.txt", "r");
    
    fgets(line, 40, person);
    fgets(pin, 10, person);

    fclose(person);
    printf("\n");
    readFile(40, 40);
    strtok(pin, "\n");
    scanf("%s", enterPin);

    if ((strcmp(enterPin, pin)) == 0) {
        return 1;
    }
    return 0;
}

void doXinim(struct day *aday, struct list_activ *a, struct pet *p)
{
    int i = 1, n = 158;
    while (i <= 3) {
        system("clear");
        readHeader(133);
        readFile(157,157);
        readFile(n,n);
        readFile(161,162);
        int op;
        
        scanf("%d", &op);
        
        if (op == 1) {
            n++;

        } else { 
            i--;
            readFile(163,163);
        }
        i++;
    }
}

void doActivity(struct day *aday, struct activity *aux, struct list_activ *a, struct pet *p)
{
    int i = 1;
    struct activity *comp = a->first;

    if (strcmp(aux->materials,comp->materials) == 0)
        doXinim(aday, a, p);
    
    readFile(154,154);
    
    aux->done = 1;
    if (strcmp(aux->kind,"Food") == 0)
        p->food = 1;
    else if (strcmp(aux->kind,"Play") == 0)
        p->play = 1;
    else if (strcmp(aux->kind, "Sleep") == 0)
        p->sleep = 1;
}

int check_time(struct day *aday, struct activity *check)
{
    struct activity * aux = aday->day_routine;
    struct activity * ant = aux;
    int x = 0;

    while (aux != NULL && aux->hour <= check->hour) {
        if (ant->end > ((check->hour*60)+check->minutes)) {
            free(check);
            readFile(60,60);
            return 0;
        }
        ant = aux;
        aux = aux->next;
        x++;
    }

    if (x != 0 && ant->end > ((check->hour*60)+check->minutes)) {
            free(check);
            readFile(60,60);
            return 0;
    }

    if (aux && ((aux->hour*60)+aux->minutes) < check->end) {
        if (aux != ant) {
            ant->next = check;
            check->next = aux;

        } else {
            aday->day_routine = check;
            check->next = aux;
        }
        return 1;

    } else if (aux == NULL) {
        ant->next = check;
        check->next = aux;
        return 1;
    }

    free(check);
    readFile(60,60);
    return 0;
}

struct day *remov(struct day *aday)
{
    int op;
    struct activity *prev;
    struct activity *aux = aday->day_routine;
    
    readHeader(53);
    readRoutine(aday);
    readFile(54,54);
    scanf("%d", &op);

    if (aux != NULL) {

        for (int x = 0; x < op; x++) {
            
            if (x != 0) {
                prev = aux; 
                aux = aux->next;
            }
        }

        if (op == 1) 
            aday->day_routine = aux->next;
        else
            prev->next = aux->next;
        
        free(aux);
    } else {
        readFile(22,22);
    }
    
    return aday;
}

void readActivities(struct list_activ *activities)
{
    struct activity *check = activities->first;
    int x = 0;
    
	while (check != NULL) {
        x++;
		printf("%d. %s\n", x, check->name);
		check = check->next;
	}
    printf("%d. ", x+1);
    readFile(14,14);
    printf("\n");
}

int lenghtList(struct list_activ *activities) 
{
    struct activity* count = activities->first;
    int x = 0;

    while(count != NULL){
        x++;
        count = count->next;
    }
    return x;
}

struct activity *copy(struct activity *one, struct activity *two) 
{
    int x = -1;
    strcpy(one->name, two->name);
    strcpy(one->materials, two->materials);
    strcpy(one->descrip, two->descrip);
    strcpy(one->kind, two->kind);
    one->done = 0;
     
    while (x < 0 || x > 23) {
        readFile(56,56);
        scanf("%d", &x);
    }
    one->hour = x;
    
    x = -1;
    while (x < 0 || x > 59) {
        readFile(57,57);
        scanf("%d", &x);
    }
    one->minutes = x;
    
    readFile(58,58);
    scanf("%d", &x);
    one->duration = x;

    one->end = calculate_end(one);
    one->next = NULL;

    return one;
}

void add_activity(struct day *aday, struct list_activ *activities, struct pet *p)
{
    //escolher o dia da semana
    int op;
    struct activity *new_act = malloc(sizeof(struct activity));
    struct activity *check= activities->first;
    struct activity *aux = aday->day_routine;

    int lenghtL = lenghtList(activities);
    
    readHeader(35);
    readFile(36,36);
    readActivities(activities);

    readFile(12,12);
    scanf("%d", &op);
    printf("\n");

    // printar atividades existentes, escolher uma delas ou criar
    if (op == 0) {
        screen_routine(aday, activities, p);

    } else if (op <= lenghtL && op != 0) {
        readHeader(51);
        for (int x = 0; x < op; x++) {
            if (x != 0)
                check = check->next;
        }
        printAct(check);
        
        int op2;
        
        readFile(42,44);
        scanf("%d", &op2);

        if (op2 == 1) {
            new_act = copy(new_act, check);
        }
        else if (op2 == 0) {
            free(new_act);
            op = 0;
            screen_routine(aday, activities, p);
        } else {
            free(new_act);
            op = 0;
            readFile(0,0);
            screen_routine(aday, activities, p);
        }

    } else if (op > lenghtL) { // if op > lenghtlista    se escolher nova atividade
        
        struct activity *act = create_act();
        
        while (check != NULL) {
            if (check->next == NULL) {
                check->next = act;
                break;
            }
            check = check->next;
        }
        new_act = copy(new_act,act);
    }

    if (op != 0) {
        if (aday->day_routine == NULL) {
            aday->day_routine = new_act;
            readFile(31,31);

        } else {

            if (check_time(aday, new_act) == 1) 
                readFile(31,31);

        }
        screen_routine(aday, activities, p);
    }
}

void screen_routine(struct day *aday, struct list_activ *a, struct pet *p) 
{
    int opcao;

    readHeader(21);

    if (aday->day_routine == NULL)
        readFile(22,22);
    else
        readRoutine(aday);

    readHeader(27);
    readFile(8, 10);
    scanf("%d", &opcao);

    if (opcao == 1) {
        system("clear");
        add_activity(aday, a, p);
    
    } else if (opcao == 2) {
        system("clear");
        aday = remov(aday);
        readFile(29,29);
        initial_screen(aday, a, p);
    
    } else if (opcao == 0) {
        system("clear");
        initial_screen(aday, a, p);
    } else {
        readFile(0,0);
        system("clear");
        screen_routine(aday, a, p);
    }
}

void achiev (struct day *aday, struct list_activ *a, struct pet *p)
{
    readHeader(24);
    // if achiev == NULL
    readFile(25,25);
    initial_screen(aday, a, p);
}

void save_pet(struct pet *p)
{
    FILE *fName = fopen("user.txt", "r");
    char singleLine[100];
    char end[8] = "Pet.txt";
    char final[5] = "\n";

    fgets(singleLine, 100, fName);
    fclose(fName);
    strtok(singleLine, "\n");
    strcat(singleLine,  end);

    char integer[4];

    FILE* fAnimal = fopen(singleLine, "w");
    fputs(p->name, fAnimal);
    fputs(final, fAnimal);

    sprintf(integer, "%d", p->type);
    fputs(integer, fAnimal);
    fputs(final, fAnimal);
    sprintf(integer, "%d", p->color);
    fputs(integer, fAnimal);
    fputs(final, fAnimal);
    sprintf(integer, "%d", p->food);
    fputs(integer, fAnimal);
    fputs(final, fAnimal);
    sprintf(integer, "%d", p->play);
    fputs(integer, fAnimal);
    fputs(final, fAnimal);
    sprintf(integer, "%d", p->sleep);
    fputs(integer, fAnimal);
    fputs(final, fAnimal);
    fclose(fAnimal);
}

void create_pet(struct pet *p)
{
    int tip, ok = 2;
    int voltar = 0;
    system("clear");

    while (voltar == 0) {
        ok = 2;
        
        while (ok == 2 || ok > 2 || ok <= 0) {
            printf("\n");
            readFile(86, 90);
            scanf("%d", &tip);
            printf("\n");
            if (tip == 1)
                readFile(96, 99);

            else if (tip == 2)
                readFile(101, 105);

            else if (tip == 3)
                readFile(107, 110);

            readFile(91, 94);
            scanf("%d", &ok);

            if (tip < 1 || tip > 3 || ok > 2 || ok <= 0) {
                readFile(0,0);
                ok = 2;
            }
        }

        p->type = tip;
        system("clear");
        printf("\n");
        readFile(112, 116);
        scanf("%d", &voltar);
        
        p->color = voltar;
    }
    int n;

    if (p->type == 1)
        n = 100;
    
    else if (p->type == 2)
        n = 106;
    
    else if (p->type == 3)
        n = 111;
    
    int x = 0;
    FILE *name = fopen("texts.txt", "r");
    char singleLine[200];

    while (x <= n) {
        fgets(singleLine, 200, name);
        x++;
    }
    strtok(singleLine, "\n");
    strcpy(p->name, singleLine);
    fclose(name);

    p->food = 1;
    p->play = 1;
    p->sleep = 1;

    save_pet(p);
}

void saveRoutine(struct day *aday)
{
    struct activity* aux = aday->day_routine;
    FILE * fInd;
    char final[2] = "\n";
    char nameArch [30];
    FILE * person = fopen("user.txt", "r");
    char end[8] = "Rot.txt";
    char integer[3];
    fgets(nameArch, 30, person);
    strtok(nameArch, "\n");
    fclose(person);
    
    strcat(nameArch, end);
    fInd = fopen(nameArch, "w");
   
    while (aux != NULL) {
        
        fputs(aux->name, fInd);
        fputs(final, fInd);
        fputs(aux->materials, fInd);
        fputs(final, fInd);
        fputs(aux->descrip, fInd);
        fputs(final, fInd);
        fputs(aux->kind, fInd);
        fputs(final, fInd);

        sprintf(integer, "%d", aux->hour);
        fputs(integer, fInd);
        fputs(final, fInd);
        sprintf(integer, "%d", aux->minutes);
        fputs(integer, fInd);
        fputs(final, fInd);
        sprintf(integer, "%d", aux->duration);
        fputs(integer, fInd);
        fputs(final, fInd);
        aux = aux->next;
    }

    fclose(fInd);
}

void check_pet(struct pet *p, struct day *aday, struct list_activ *a, int def)
{
    time_t currentTime;
    time(&currentTime);
    
    struct tm *temp = localtime(&currentTime);
    struct activity *aux = aday->day_routine;
    int h = temp->tm_hour;
    int min = temp->tm_min;

    int ok = 0;

    while (aux && aux->hour <= h) {
        if ((aux->hour*60 + aux->minutes) <= (h*60 + min)) {
            if ((aux->hour*60 + aux->minutes + aux->duration) >= h*60 + min) {
                ok = 1;
                break;
            }
        }
        aux->done = 0;
        aux = aux->next;
    }

    if (ok == 1 && def == 1 && aux->done == 0) {
        if (strcmp(aux->kind, "Food") == 0) {
            readFile(136,138);
        }
        else if (strcmp(aux->kind, "Sleep") == 0) {
            readFile(136,137);
            readFile(139,139);
        }
        if (strcmp(aux->kind, "Play") == 0) {
            readFile(136,137);
            readFile(140,140);
        }
        if (p->type == 1) {
            readFile(141,141);
            p->food = 0;
        }
        else if (p->type == 2){
            readFile(142,142);
            p->sleep = 0;
        }
        else if (p->type == 3) {
            readFile(143,143);
            p->play = 0;
        }
    }
    // checar se o pet ta ok ou nao ants de fazer
    else if (ok == 1 && def == 2) {
        if (aux->done == 0) {
            readFile(153,153);
            printf("%s\n\n", aux->name);
            int op;

            readFile(149, 151);
            scanf("%d", &op);
            
            if (op == 1)
                doActivity(aday, aux, a, p);

        } else {
            readFile(152,152);
        }
        initial_screen(aday, a, p);
    }

    else if ((ok == 0 && def == 1)|| (aux->done == 1 && def == 1)) {
        if (p->type == 1)
            readFile(145,145);
        else if (p->type == 2)
            readFile(146,146);
        else if (p->type == 3)
            readFile(147,147);
    }

    else if ((ok == 0 && def == 2) || (aux->done == 1 && def == 2)){
        readFile(152,152);
        initial_screen(aday, a, p);
    }
}

void settings(struct pet *p, struct day *aday, struct list_activ *a)
{
    int op, ok = 1;

    while (ok == 1) {
        readHeader(118);
        readFile(119,122);
        scanf("%d", &op);

        if (op == 1) {
            readFile(113,116);
            int op2;
            readFile(124,124);
            scanf("%d", &op2);
        }

        else if (op == 2) {
            int op2;
            readFile(124,124);
            readFile(126,128);
            scanf("%d", &op2);

        } else if (op == 3) {
            readFile(130,130);

        } else if (op == 0) {
            ok = 0;
        }
        system("clear");
        readFile(165,165);
    }

    readFile(165,165);
    initial_screen(aday, a, p);
}

void clothes(struct pet *p, struct day *aday, struct list_activ *a)
{
    readHeader(166);
    readFile(167,167);
    initial_screen(aday, a, p);
}

void initial_screen(struct day *aday, struct list_activ *a, struct pet *p)
{
    int opcao, op2;
    readHeader(1);
    check_pet(p, aday, a, 1);

    readFile(2, 6);
    readFile(8, 8);
    scanf("%d", &opcao);
    
    if (opcao == 1) {
        //VER ROTINA
        if (askPin()) {
            screen_routine(aday, a, p);
        
        } else {
            system("clear");
            readFile(38,38);
            initial_screen(aday, a, p);
        }

    } else if (opcao == 2) {
        system("clear");
        achiev(aday, a, p);

    } else if (opcao == 3) {
        //guarda-roupa
        system("clear");
        clothes(p, aday, a);

    } else if (opcao == 4) {
       //Atividades
        system("clear");
        check_pet(p, aday, a, 2);

    } else if (opcao == 5) {
        system("clear");
        settings(p, aday, a);
  
    } else if (opcao == 0) {
        //SAIR
        saveRoutine(aday);
        FILE * delete = fopen("user.txt", "w");
        fclose(delete);
    
    } else {
        readFile(0, 0);
        initial_screen(aday, a, p);
    }
}

struct list_activ *initialize(struct list_activ *act)
{
    struct activity *check;
    char nameArch [30];
    FILE * person = fopen("user.txt", "r");
    char end[8] = "Act.txt";
    fgets(nameArch, 30, person);
    strtok(nameArch, "\n");
    fclose(person);
    
    strcat(nameArch, end);

    FILE * fAct = fopen("activities.txt", "r");
    FILE * fInd = fopen(nameArch, "r");

    char singleLine[200];
    struct activity *aux;

    if (fInd) {
        while (fgets(singleLine, 200, fInd)) {    

            check = malloc(sizeof(struct activity));
            strcpy(check->name, singleLine);
            strtok(check->name, "\n");
            fgets(check->materials, 200, fInd);
            strtok(check->materials, "\n");
            fgets(check->descrip, 200, fInd);
            strtok(check->descrip, "\n");
            fgets(check->kind, 200, fInd);
            strtok(check->kind, "\n");

            check->next = NULL;

            if (act->first == NULL)
                act->first = check;
            
            else 
                aux->next = check;
        
            aux = check;
            check = check->next;
        }

    } else {
    
        fclose(fInd);
        fInd = fopen(nameArch, "a");

        while (fgets(singleLine, 200, fAct)) {

            check = malloc(sizeof(struct activity));
            strcpy(check->name, singleLine);
            strtok(check->name, "\n");
            fputs(singleLine, fInd);
            fgets(check->materials, 200, fAct);
            fputs(check->materials, fInd);
            strtok(check->materials, "\n");
            fgets(check->descrip, 200, fAct);
            fputs(check->descrip, fInd);
            strtok(check->descrip, "\n");
            fgets(check->kind, 200, fAct);
            fputs(check->kind, fInd);
            strtok(check->kind, "\n");

            check->next = NULL;                   
            
            if (act->first == NULL)
                act->first = check;
            
            else 
                aux->next = check;
        
            aux = check;
            check = check->next;
        }
    } 

    fclose(fAct);
    fclose(fInd);

    return act;
}

struct day *updateRoutine(struct day *aday)
{
    struct activity *check;
    char nameArch [30];
    FILE * person = fopen("user.txt", "r");
    char end[8] = "Rot.txt";
    fgets(nameArch, 30, person);
    strtok(nameArch, "\n");
    fclose(person);
    strcat(nameArch, end);

    FILE *fInd = fopen(nameArch, "a");
    fclose(fInd);

    fInd = fopen(nameArch, "r");

    char singleLine[200];
    char hora[20];
    struct activity* aux;

    while (fgets(singleLine, 200, fInd)) {

        check = malloc(sizeof(struct activity));
        strcpy(check->name, singleLine);
        strtok(check->name, "\n");
        fgets(check->materials, 200, fInd);
        strtok(check->materials, "\n");
        fgets(check->descrip, 200, fInd);
        strtok(check->descrip, "\n");
        fgets(check->kind, 200, fInd);
        strtok(check->kind, "\n");
        fgets(hora, 20, fInd);
        strtok(hora, "\n");
        check->hour = atoi(hora);
        fgets(hora, 20, fInd);
        strtok(hora, "\n");
        check->minutes = atoi(hora);
        fgets(hora, 20, fInd);
        strtok(hora, "\n");
        check->duration = atoi(hora);
        check->done = 0;
        check->end = calculate_end(check);
        check->next = NULL;

        if (aday->day_routine == NULL) {
            aday->day_routine = check;
        
        } else {
            check_time(aday, check);
        }
        
    }
    fclose(fInd);
    //printf("saindo");
    return aday;//
}

void loadPet(struct pet *p)
{   
    //printf("LOAD");
    FILE *fName = fopen("user.txt", "r");
    char singleLine[100];
    char end[10] = "Pet.txt";

    fgets(singleLine, 100, fName);
    fclose(fName);

    strtok(singleLine, "\n");
    strcat(singleLine,  end);
    
    char petline[15];
    int x;
    char *eu;

    FILE* fAnimal = fopen(singleLine, "r");
    fgets(petline, 15, fAnimal);
    strtok(petline, "\n"); 
    strcpy(p->name, petline);
    fgets(petline, 20, fAnimal);
    strtok(petline, "\n");
    p->type = atoi(petline);
    fgets(petline, 20, fAnimal);
    strtok(petline, "\n");
    p->color = atoi(petline);
    fgets(petline, 20, fAnimal);
    strtok(petline, "\n");
    p->food = atoi(petline);
    fgets(petline, 20, fAnimal);
    strtok(petline, "\n");
    p->play = atoi(petline);
    fgets(petline, 20, fAnimal);
    strtok(petline, "\n");
    p->sleep = atoi(petline);

    fclose(fAnimal);
}

int login(struct pet *p)
{
    readHeader(69);
    readFile(70,70);
    readFile(85,85);
    char email[100];
    int log = 2;
    while (log == 2) {
        
        scanf("%s", email);

        if (strcmp(email, "0") == 0){
            log = 3;
        }
        printf("\n");
        FILE * allusers = fopen("allUsers.txt", "r");
        char singleLine[100];
        char em[100];
        int ok = 0;
        int round = 0;

        while (ok == 0 && fgets(singleLine, 100, allusers)) {
            if (round % 4 == 0) {
                strcpy(em, singleLine);
                strtok(em, "\n");
                if (strcmp(em, email) == 0) {
                    ok = 1;
                }
            }
            round++;
        }

        if (ok == 1) {

            fgets(singleLine, 100, allusers);
            
            char passw[20];
            
            readFile(71,71);
            scanf("%s", passw);////
            strtok(singleLine, "\n");

            if ((strcmp(singleLine, passw)) == 0) { //conferencia de senha
        
                char pin[20];
                fgets(pin, 20, allusers);
                fclose(allusers);

                FILE *user = fopen("user.txt", "w");
                fputs(email, user);
                fputs("\n", user);
                fputs(pin, user);
                fclose(user);
                //printf("fechou arquivo chamou load");
                loadPet(p);/////////
                log = 1;
            }
            else  {
                readFile(68,68);
                fclose(allusers);
            }
        
        } else {
            readFile(72,72);
            fclose(allusers);
        }
    }

    if (log == 3)
        return 0;

    return 1;
}

int criarConta(struct pet *p)
{
    readHeader(73);
    char email[100];
    char pass[100];
    char pass2[100];
    char pin[100];
    char pin2[100];
    int ok = 0;
    
    readFile(74,74);
    scanf("%s", email);
    
    readFile(75,75);
    scanf("%s", pass);
    readFile(76,76);
    
    while (ok == 0) {
        scanf("%s", pass2);
        if(strcmp(pass, pass2) == 0)
            ok = 1;
        else
            readFile(77,77);
    }
    ok = 0;
    readHeader(78);
    readFile(79,82);
    scanf("%s", pin);

    readFile(83,83);
    while (ok == 0) {
        scanf("%s", pin2);
        if(strcmp(pin, pin2) == 0)
            ok = 1;
        else
            readFile(82,82);
    }
    
    FILE * allusers = fopen("allUsers.txt", "a");
    char final[2] = "\n";
    fputs(email, allusers);
    fputs(final, allusers);
    fputs(pass, allusers);
    fputs(final, allusers);
    fputs(pin, allusers);
    fputs(final, allusers);
    fputs(final, allusers);
    fclose(allusers);

    FILE * user = fopen("user.txt", "w");
    fputs(email, user);
    fputs(final, user);
    fputs(pin, user);
    fclose(user);

    create_pet(p);
    printf("SALVO");
    return 1;
}

int log_screen(int log, struct pet *p)
{
    int op;

    readHeader(62);
    readFile(63,65);
    scanf("%d", &op);

    if (op == 1) {
        log = login(p);
    }
    else if (op == 2) {
        log = criarConta(p);
    }
    else if (op == 0) {
        log = 0;
    }
    else {
        readFile(0,0);
        log = log_screen(log, p);
    }
    return log;
}

int main(void)
{
    int log = 0;
    struct pet *p = malloc(sizeof(struct pet));

    log = log_screen(log, p);
    if (log != 0) {
    //struct routine *aroutine = create_routine();
        struct day *aday = create_day();
        struct list_activ *activities = create_list();
        
        activities = initialize(activities);
        aday = updateRoutine(aday);

        initial_screen(aday, activities, p);
    }

    readHeader(67);

	return 0;
}
