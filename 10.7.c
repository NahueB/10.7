#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef struct 
{
    char codAerolinea[11];
    int DIA;
    int nVuelo;
    float costPasaje;
    int cantPasajeros;
}vuelo;

typedef struct
{
    int DNI;
    int nVuelo;
}pasajeros;//vector de 150

int desARCH(vuelo vec[]);//cargar los 150 vuelos de aero1

void carPAS(vuelo vec[],int);//sumas la cantidad de pasajeros de cada vuelo

void carARCH(vuelo vec[],int);//cargar el vector al archivo

int main()
{
    vuelo VUELO[150];
    int MAX;
    MAX=desARCH(VUELO);
    carPAS(VUELO,MAX);
    carARCH(VUELO,MAX);
    return 0;
}

int desARCH(vuelo vec[])
{
    int i=0,aux;
    FILE *Ar;
    Ar=fopen("Vuelos.dat","rb");
    if(Ar==NULL)
    {
        printf("\nERROR ARCHIVO Vuelos.dat NO ENCONTRADO");
        getch();
        exit(1);
    }
    
    fread(&vec[i],sizeof(vuelo),1,Ar);
    
    while(!feof(Ar))
    {
        aux=strcmp(vec[i].codAerolinea,"Aero1");
        if(aux==0)
            i++;
        fread(&vec[i],sizeof(vuelo),1,Ar);
    }

    fclose(Ar);

    return i;
}

void carPAS(vuelo vec[],int MAX)
{
    pasajeros PASAJEROS;
    FILE *Ar;
    int aux,i;
    Ar=fopen("Pasajeros.dat","rb");
    if(Ar==NULL)
    {
        printf("\nERROR ARCHIVO Pasajeros.dat NO ENCONTRADO");
        getch();
        exit(1);
    }

    fread(&PASAJEROS,sizeof(pasajeros),1,Ar);

    while(!feof(Ar))
    {
        i=0;
        aux=0;
        while(aux!=1)
        {
            if(PASAJEROS.nVuelo==vec[i].nVuelo)
            {
                vec[i].cantPasajeros++;
                aux=1;
            }
            i++;
        }
        
        fread(&PASAJEROS,sizeof(pasajeros),1,Ar);
    }

    fclose(Ar);

}

void carARCH(vuelo vec[],int MAX)
{
    FILE *Aw,*Aw2;
    int i;
    char c;
    Aw=fopen("Aero1.dat","wb");
    if(Aw==NULL)
    {
        printf("\nERROR ARCHIVO Aero1.dat NO CREADO");
        getch();
        exit(1);
    }
    
    printf("\nDesea crear el archivo Excel de Aero1? S/N");
    scanf("%c",&c);
    
    if(c=='S')
    {
        Aw2=fopen("Aero1.csv","wb");
        if(Aw2==NULL)
        {
            printf("\nERROR ARCHIVO Aero1.csv NO CREADO");
            getch();
            exit(1);
        }
    }
    
    for(i=0,i<=MAX,i++;)
    {
        fwrite(&vec[i],sizeof(vuelo),1,Aw);
        if(c=='S')
        {
           fwrite(&vec[i],sizeof(vuelo),1,Aw2); 
        }
    }

    fclose(Aw);
    fclose(Aw2);
    
}
