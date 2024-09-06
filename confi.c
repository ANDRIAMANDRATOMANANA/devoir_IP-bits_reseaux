#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NAME 100
char **create_tab(int un,int deux)  //creation tableau a deux dimension
{
	int i=0;
	char **name=NULL;
	name=(char**)malloc(un*sizeof(char*));
	for(i=0;i<un;i++)
	{
		name[i]=(char*)malloc(deux*sizeof(char));
	}
	if(name == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return name;
}
int *create_tab_int(int dim)  //creation tableau a deux dimension
{
	int  *tab=NULL;
	tab=(int*)malloc(dim*sizeof(int));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return tab;
}		
int generate_IP(char **octet,char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,char *number_bits)
{
	char data[MAX_NAME];
	printf("entrez l'adresse IP et le nombre de sous reseaux:");
	fgets(data,sizeof(data),stdin);
	data[strcspn(data, "\n")] = '\0'; 
    char *ken;
    int b=0;
    ken = strtok(data,"/");
    while (ken != NULL)
    {
       strcpy(octet[b],ken); 
       ken = strtok(NULL,"/");
       b++;
	}
	char ip[MAX_NAME];
	strcpy(ip,octet[0]); 
	strcpy(number_bits,octet[1]); 
	ip[strcspn(ip, "\n")] = '\0';
	char *tok=NULL;
	tok = strtok(ip,".");
	int i=0;
	while (tok != NULL)
	{
		strcpy(token[i],tok);
		tok = strtok(NULL,".");
		i++;
	}
	int ok=0;
	char *endptr=NULL;
	int base=10;
	long opt_enum=0;
	for(int c=0;c<i;c++)
	{
		opt_enum=strtol(token[c], &endptr, base); //strtol detecte les caractere non base 10
		if(opt_enum<0 || opt_enum>255 )
		{
          printf("IP non valide1");
          exit(1);
		}
		if (endptr == token[c] || *endptr != '\0') //egal quand le premier caractere trouver n'est pas un chiffre
		{
          printf("IP non valide2");
                exit(1);
	            
		}
		if(*endptr == '\0' && opt_enum>-1 && opt_enum<256) // Si tout est bon, afficher le nombre converti et sortir de la boucle
        {
			ok++;
	    }
	}
    if(ok==4)
    {
		strcpy(premier_octet,token[0]);
		strcpy(deuxieme_octet,token[1]);
		strcpy(troisieme_octet,token[2]);
		strcpy(quatrieme_octet,token[3]);
	}

	return i;

}
void valid_IP(char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,int *premier,int *deuxieme,int *troisieme,int *quatrieme,int count,char *number_bits,int *nbr_reseau_bits)
{
	
	if(count!=4)
	{
          printf("IP non valide");
          exit(1);
	}
	if(count==4)
	{
		*premier=atoi(premier_octet);
		
		
		
		*deuxieme=atoi(deuxieme_octet);
		
		
		
		*troisieme=atoi(troisieme_octet);
		
		
		
		*quatrieme=atoi(quatrieme_octet);
	}
	*nbr_reseau_bits=atoi(number_bits);
	if(*nbr_reseau_bits>31 || *nbr_reseau_bits<1)
	{
		printf("nombre des bits de reseaux non valide");
		exit(1);
	}
}
void transform_binaire(int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int premier,int deuxieme,int troisieme,int quatrieme,int nbr_reseau_bits)
{
    int tmp1=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(premier==pow(2,d))
					{
						ok++;
						bits1[j]=1;
						premier=0;
						
					}
					if(ok==0 && premier<pow(2,d)+tmp1)
					{
						ok++;
						bits1[j]=0;
						
					}
					if(ok==0 && premier>=pow(2,d)+tmp1)
					{
						ok++;
						bits1[j]=1;
						tmp1=pow(2,d)+tmp1;
					}
	}
    int tmp2=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
			int ok=0;
					if(deuxieme==pow(2,d))
					{
						ok++;
						bits2[j]=1;
						deuxieme=0;
					}
					if(ok==0 && deuxieme<pow(2,d)+tmp2)
					{
						ok++;
						bits2[j]=0;
						
					}
					if(ok==0 && deuxieme>=pow(2,d)+tmp2)
					{
						ok++;
						bits2[j]=1;
						tmp2=pow(2,d)+tmp2;
					}
	}
    int tmp3=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(troisieme==pow(2,d))
					{
						ok++;
						bits3[j]=1;
						troisieme=0;
						
					}
					if(ok==0 && troisieme<pow(2,d)+tmp3)
					{
						ok++;
						bits3[j]=0;
						
					}
					if(ok==0 && troisieme>=pow(2,d)+tmp3)
					{
						ok++;
						bits3[j]=1;
						tmp3=pow(2,d)+tmp3;
					}
					
	}
    int tmp4=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(quatrieme==pow(2,d))
					{
						ok++;
						bits4[j]=1;
						troisieme=0;
						
					}
					if(ok==0 && quatrieme<pow(2,d)+tmp4)
					{
						ok++;
						bits4[j]=0;
						
					}
					if(ok==0 && quatrieme>=pow(2,d)+tmp4)
					{
						ok++;
						bits4[j]=1;
						tmp4=pow(2,d)+tmp4;
					}
	}
	int dim=50;
	int *reste=NULL;
	reste=(int*)malloc(dim*sizeof(int));//stockage de chaque bits d'octet dans un tableau pour gerer le bits de reseaux et hote
	for(int i=0;i<nbr_reseau_bits;i++)//reseaux
	{
		reste[i]=1;
		
	}
	for(int i=nbr_reseau_bits;i<32;i++)//hote
	{
		reste[i]=0;
	}
	printf("\nnetmask en binaire:");
	for(int i=0;i<8;i++)// pour mettre chaque nouveau bits dans chaque tableau de bits i
	{
		bits_msr1[i]=reste[i];
		printf("%d",bits_msr1[i]);
	}
	printf(".");
	for(int i=0,d=8;i<8 && d<16;i++,d++)
	{
		bits_msr2[i]=reste[d];
		printf("%d",bits_msr2[i]);
	}
	printf(".");
	for(int i=0,d=16;i<8 && d<24;i++,d++)
	{
		bits_msr3[i]=reste[d];
		printf("%d",bits_msr3[i]);
	}
	printf(".");
	for(int i=0,d=24;i<8 && d<32;i++,d++)
	{
		bits_msr4[i]=reste[d];
		printf("%d",bits_msr4[i]);
	}
	free(reste);
	
}
void transform_decimal(int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4)
{
	int dim=50;
	int *octet=NULL;
	octet=(int*)malloc(dim*sizeof(int));//pour stocker chaque bits en decimal
	int somme1=0;
	printf("\nnetmask en decimal:");
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet[i]=bits_msr1[i]*pow(2,j);
		somme1=somme1+octet[i];
	}
	printf("%d.",somme1);
	int somme2=0;
	for(int i=8,k=0,j=7;i<16 && k<8 && j>=0;i++,k++,j--)
	{
		octet[i]=bits_msr2[k]*pow(2,j);
		somme2=somme2+octet[i];
	}
	printf("%d.",somme2);
	int somme3=0;
	for(int i=16,k=0,j=7;i<24 && k<8 && j>=0;i++,k++,j--)
	{
		octet[i]=bits_msr3[k]*pow(2,j);
		somme3=somme3+octet[i];
	}
	printf("%d.",somme3);
	int somme4=0;
	for(int i=24,k=0,j=7;i<32 && k<8 && j>=0;i++,k++,j--)
	{
		octet[i]=bits_msr4[k]*pow(2,j);
		somme4=somme4+octet[i];
	}
	printf("%d",somme4);
	free(octet);
}
void adress_reseaux(int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int nbr_reseau_bits)
{
	int dim=50;
	int *adress_r=NULL;
	adress_r=(int*)malloc(dim*sizeof(int));//pour stocker chaque bits de l'adresse reseau
	printf("\nAdresse Reseaux en binaire:");
	for(int i=0;i<8;i++)
	{
		adress_r[i]=bits1[i]*bits_msr1[i];
		if(i==7 || i==15 || i==23 )
		{
			printf("%d.",adress_r[i]);
		}
		else
		{
			printf("%d",adress_r[i]);
		}
	}
	for(int i=0,j=8;i<8 && j<16;i++,j++)
	{
		adress_r[j]=bits2[i]*bits_msr2[i];
		if(j==7 || j==15 || j==23 )
		{
			printf("%d.",adress_r[j]);
		}
		else
		{
			printf("%d",adress_r[j]);
		}
	}
	for(int i=0,j=16;i<8 && j<24;i++,j++)
	{
		adress_r[j]=bits3[i]*bits_msr3[i];
		if(j==7 || j==15 || j==23 )
		{
			printf("%d.",adress_r[j]);
		}
		else
		{
			printf("%d",adress_r[j]);
		}
	}
	for(int i=0,j=24;i<8 && j<32;i++,j++)
	{
		adress_r[j]=bits4[i]*bits_msr4[i];
		if(j==7 || j==15 || j==23 )
		{
			printf("%d.",adress_r[j]);
		}
		else
		{
			printf("%d",adress_r[j]);
		}
	}
	int *octet_r=NULL;
	octet_r=(int*)malloc(dim*sizeof(int));//pour stocker chaque produit des bits par les 2puissance nombre
	int somme1=0;
	printf("\nAdresse Reseaux en decimal:");
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme1=somme1+octet_r[i];
	}
	printf("%d.",somme1);
	int somme2=0;
	for(int i=8,j=7;i<16 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme2=somme2+octet_r[i];
	}
	printf("%d.",somme2);
	int somme3=0;
	for(int i=16,j=7;i<24 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme3=somme3+octet_r[i];
	}
	printf("%d.",somme3);
	int somme4=0;
	for(int i=24,j=7;i<32 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme4=somme4+octet_r[i];
	}
	printf("%d",somme4);
	int nbr_machine=0;
	int nbr_hote_bits=0;
	nbr_hote_bits=32-nbr_reseau_bits;
	nbr_machine=pow(2,nbr_hote_bits);
	printf("\nnombre d'IP possible d'un machine:%d",nbr_machine-2);
	int *octet_bc=NULL;
	octet_bc=(int*)malloc(dim*sizeof(int));//pour stocker chaque bits de diffusion en decimal
	printf("\nadresse de broadcast:");
	int somme1_bc=0;
	for(int i=nbr_reseau_bits;i<32;i++)
	{
		adress_r[i]=1;
	}
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet_bc[i]=adress_r[i]*pow(2,j);
		somme1_bc=somme1_bc+octet_bc[i];
	}
	printf("%d.",somme1_bc);
	int somme2_bc=0;
	for(int i=8,j=7;i<16 && j>=0;i++,j--)
	{
		octet_bc[i]=adress_r[i]*pow(2,j);
		somme2_bc=somme2_bc+octet_bc[i];
	}
	printf("%d.",somme2_bc);
	int somme3_bc=0;
	for(int i=16,j=7;i<24 && j>=0;i++,j--)
	{
		octet_bc[i]=adress_r[i]*pow(2,j);
		somme3_bc=somme3_bc+octet_bc[i];
	}
	printf("%d.",somme3_bc);
	int somme4_bc=0;
	for(int i=24,j=7;i<32 && j>=0;i++,j--)
	{
		octet_bc[i]=adress_r[i]*pow(2,j);
		somme4_bc=somme4_bc+octet_bc[i];
	}
	printf("%d\n",somme4_bc);
	free(adress_r);
	free(octet_bc);
}


