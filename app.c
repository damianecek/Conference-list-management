#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WFILE "KonferencnyZoznam.txt"
#define MAXRECORDS 100
#define MAXID 10
#define MAXNAZOV 150
#define MAXAUTOR 300
#define MAXDATUM 12

void vypis(int n, char **id, char **nazov, char **mena, char **datum, int recordcount, FILE **file);
void pridat(char **id, char **nazov, char **mena, char **datum, int recordcount, int alokovane);
void nacitat(char **id, char **nazov, char **mena, char **datum, int *recordcount, int *alokovane, int *n, FILE **file);
void casy(char **id, char **nazov, char **mena, char **datum, int recordcount, int alokovane);
void zmazat(char **id, char **nazov, char **mena, char **datum, int *recordcount, int alokovane);
void dealokovat(char **id, char **nazov, char **mena, char **datum, int alokovane);

int main()
{
    FILE *file = NULL;
    // alokacia pre polia ukazovatelov
    char **prispevokid = (char **)malloc(MAXRECORDS * sizeof(char *));
    char **nazovprispevku = (char **)malloc(MAXRECORDS * sizeof(char *));
    char **menaautorov = (char **)malloc(MAXRECORDS * sizeof(char *));
    char **datumacas = (char **)malloc(MAXRECORDS * sizeof(char *));
    char **MENA = (char **)malloc(MAXRECORDS * sizeof(char *));

    int n = 0, recordcount = 0, alokovane = 0;
    char c;

    do
    {

        printf("\n\n");
        scanf(" %c", &c);
        // switch pre volanie prikazov
        switch (c)
        {
        case 'v':
            vypis(alokovane, prispevokid, nazovprispevku, menaautorov, datumacas, recordcount, &file);
            break;
        case 'p':
            recordcount++;
            pridat(prispevokid, nazovprispevku, menaautorov, datumacas, recordcount, alokovane);
            alokovane++;
            break;
        case 'n':
            nacitat(prispevokid, nazovprispevku, menaautorov, datumacas, &recordcount, &alokovane, &n, &file);
            break;
        case 's':
            casy(prispevokid, nazovprispevku, menaautorov, datumacas, recordcount, alokovane);
            break;
        case 'w':
            printf("MENA (Neimplementovane)");
            break;
        case 'h':
            printf("HISTOGRAM (Neimplementovane)");
            break;
        case 'z':
            zmazat(prispevokid, nazovprispevku, menaautorov, datumacas, &recordcount, alokovane);
            break;
        case 'd':
            dealokovat(prispevokid, nazovprispevku, menaautorov, datumacas, alokovane);
            n = 0;
            alokovane = 0;
            recordcount = 0;
            break;
        case 'k':
            break;
        default:
            printf("Instrukcia nenajdena");
            break;
        }

    } while (c != 'k');

    // prikaz "k", sem sa dostane program po aktivacii k
    printf("\nDealokacia a zatvaranie suboru!");
    // uvolnenie pamate
    for (int i = 0; i < MAXRECORDS; i++)
    {
        free(prispevokid[i]);
        free(nazovprispevku[i]);
        free(menaautorov[i]);
        free(datumacas[i]);
        free(MENA[i]);
    }
    free(prispevokid);
    free(nazovprispevku);
    free(menaautorov);
    free(datumacas);
    free(MENA);
    fclose(file);
    return 0;
}

void vypis(int n, char **id, char **nazov, char **mena, char **datum, int recordcount, FILE **file)
{
    char c;
    if (*file == NULL)
    {
        *file = fopen(WFILE, "r+");
        if (*file == NULL)
        {
            printf("\nNeotvoreny subor.");
        }
    }
    // citanie a vypis dat zo suboru
    if (*file != NULL && n == 0)
    {
        rewind(*file);
        c = fgetc(*file);
        while (c != EOF)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                    printf("\nID prispevku: ");
                if (i == 1)
                    printf("Nazov prispevku: ");
                if (i == 2)
                    printf("Mena autorov: ");
                if (i == 3)
                    printf("Datum prezentovania: ");

                while (c != '\n' && c != EOF)
                {
                    printf("%c", c);
                    c = fgetc(*file);
                }
                printf("%c", c);
                c = fgetc(*file);
            }
        }
    }
    else
    {
        // vypis dat z dynamickych poli
        printf("\n");
        for (int i = 0; i < recordcount; i++)
        {
            printf("ID prispevku: %s\n", id[i]);
            printf("Nazov prispevku: %s\n", nazov[i]);
            printf("Mena autorov: %s\n", mena[i]);
            printf("Datum a cas: %s\n", datum[i]);
            printf("\n");
        }
    }
}

void pridat(char **id, char **nazov, char **mena, char **datum, int recordcount, int alokovane)
{
    // ak polia neboli alokovane tak sa alokuju
    if (alokovane == 0)
    {
        for (int i = 0; i < MAXRECORDS; i++)
        {
            id[i] = (char *)malloc(MAXID * sizeof(char));
            nazov[i] = (char *)malloc(MAXNAZOV * sizeof(char));
            mena[i] = (char *)malloc(MAXAUTOR * sizeof(char));
            datum[i] = (char *)malloc(MAXDATUM * sizeof(char));
        }
    }
    // nacitanie dat do poli s poslednym indexom (rozne vstupy) (fflush pre istotu)
    fflush(stdin);
    printf("\nZadaj ID: ");
    fgets(id[recordcount - 1], MAXID, stdin);
    id[recordcount - 1][strcspn(id[recordcount - 1], "\n")] = '\0';
    fflush(stdin);
    printf("Zadaj nazov prispevku: ");
    fgets(nazov[recordcount - 1], MAXNAZOV, stdin);
    nazov[recordcount - 1][strcspn(nazov[recordcount - 1], "\n")] = '\0';
    fflush(stdin);
    printf("Zadaj mena autorov: ");
    fgets(mena[recordcount - 1], MAXAUTOR, stdin);
    mena[recordcount - 1][strcspn(mena[recordcount - 1], "\n")] = '\0';
    fflush(stdin);
    printf("Zadaj datum a cas ");
    fgets(datum[recordcount - 1], MAXDATUM, stdin);
    datum[recordcount - 1][strcspn(datum[recordcount - 1], "\n")] = '\0';
    fflush(stdin);
    printf("\nZaznam sa podarilo pridat.");
}

void nacitat(char **id, char **nazov, char **mena, char **datum, int *recordcount, int *alokovane, int *n, FILE **file)
{
    int startingIndex = *recordcount;
    // ak polia neboli alokovane tak sa alokuju
    if (*alokovane == 0)
    {
        for (int i = 0; i < MAXRECORDS; i++)
        {
            id[i] = (char *)malloc(MAXID * sizeof(char));
            nazov[i] = (char *)malloc(MAXNAZOV * sizeof(char));
            mena[i] = (char *)malloc(MAXAUTOR * sizeof(char));
            datum[i] = (char *)malloc(MAXDATUM * sizeof(char));
        }
    }
    // ak je subor otvoreny a polia neboli naplnene prikazom n tak sa tak stane
    if (*file != NULL)
    {
        if (*n == 0)
        {
            int recordscount = 0, recordsinfile, line_count = 0, i = 0;
            char prev_char = '\0', ch, line[300];
            // spocitanie zaznamov v subore
            rewind(*file);
            while ((ch = fgetc(*file)) != EOF)
            {
                if (ch == '\n')
                {
                    if (prev_char != '\n')
                    {
                        line_count++;
                    }
                }
                prev_char = ch;
            }
            if (prev_char != '\n')
            {
                line_count++;
            }
            recordsinfile = line_count / 4;
            // prenos zo suboru do poli
            rewind(*file);
            while (fgets(line, 300, *file) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                switch (i % 4)
                {
                case 0: // prenos id zo suboru do poli
                    strcpy(id[startingIndex + recordscount], line);
                    break;
                case 1: // nazov
                    strcpy(nazov[startingIndex + recordscount], line);
                    break;
                case 2: // mena
                    strcpy(mena[startingIndex + recordscount], line);
                    break;
                case 3: // datum
                    strcpy(datum[startingIndex + recordscount], line);
                    break;
                }
                i++;
                if (i % 4 == 0)
                {
                    recordscount++;
                }
            }
            printf("\nNacitane data.");
            // aktualizacia potrebnych premennych v programe
            *recordcount = recordsinfile + *recordcount;
            *n = *n + 1;
            *alokovane = *alokovane + 1;
        }
    }
    else
        printf("\nNeotvoreny subor.");
}

void casy(char **id, char **nazov, char **mena, char **datum, int recordcount, int alokovane)
{
    // inicializacia a naplnenie poli pre porovnavanie
    char date[9], type[3];
    int i, found = 0;
    printf("\n");
    scanf("%8s %2s", date, type);
    printf("\n");
    // vratenie do main ak polia neboli alokovane
    if (alokovane == 0)
    {
        printf("\nPolia niesu vytvorene.");
        return;
    }
    for (i = 0; i < recordcount; i++)
    {
        // ak boli najdene polia so zhodnymi datami tak sa vypisu
        if (strncmp(datum[i], date, 8) == 0 && strncmp(id[i], type, 2) == 0)
        {
            printf("%s  %s      %s\n", datum[i] + 8, strtok(mena[i], "#"), nazov[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nPre dany vstup neexistuju zaznamy.");
    }
}

void zmazat(char **id, char **nazov, char **mena, char **datum, int *recordcount, int alokovane)
{
    // vratenie do main ak polia neboli alokovane
    if (alokovane == 0)
    {
        printf("\nPolia nie su vytvorene.");
        return;
    }
    // string na porovnanie nazvov zaznamov
    char zmazat[MAXNAZOV];
    printf("\n");
    gets(zmazat);
    fgets(zmazat, MAXNAZOV, stdin);
    zmazat[strcspn(zmazat, "\n")] = '\0';

    int deleted_count = 0, write_index = 0;

    // kontrola vsetkych zaznamov pre porovnanie s porovnavacim stringom
    for (int i = 0; i < *recordcount; i++)
    {
        // pre najdeny rovnaky string sa uvolni pamat na danom indexe
        if (nazov[i] != NULL && strcmp(nazov[i], zmazat) == 0)
        {
            free(id[i]);
            free(nazov[i]);
            free(mena[i]);
            free(datum[i]);

            id[i] = NULL;
            nazov[i] = NULL;
            mena[i] = NULL;
            datum[i] = NULL;

            deleted_count++;
        }
        else
        {
            // posun nezhodujucich sa zaznamov s porovnavacim stringom na miesto vymazaneho zaznamu
            if (i != write_index)
            {
                id[write_index] = id[i];
                nazov[write_index] = nazov[i];
                mena[write_index] = mena[i];
                datum[write_index] = datum[i];
            }
            write_index++;
        }
    }
    // uprava alokacie pamate na novu velkost
    *recordcount = write_index;
    id = (char **)realloc(id, write_index * sizeof(char *));
    nazov = (char **)realloc(nazov, write_index * sizeof(char *));
    mena = (char **)realloc(mena, write_index * sizeof(char *));
    datum = (char **)realloc(datum, write_index * sizeof(char *));

    printf("\nVymazalo sa: %d zaznamov!", deleted_count);
}

void dealokovat(char **id, char **nazov, char **mena, char **datum, int alokovane)
{
    // ak boli polia alokovane tak sa dealokuju inak sa program vrati do main
    if (alokovane != 0)
    {
        for (int i = 0; i < MAXRECORDS; i++)
        {
            free(id[i]);
            free(nazov[i]);
            free(mena[i]);
            free(datum[i]);
        }
        free(id);
        free(nazov);
        free(mena);
        free(datum);
    }
    else
        return;
}