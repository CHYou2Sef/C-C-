#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etud {
	char Nom [30] , Prenom [30] ;
	int Num ;
	float Moy ;
	struct Etud * suiv ;
};
typedef Etud * list ;

void creation (list &t);
void ajoutdebut (list &t);
void parcourir (list t);
void ajoutfin (list & t);
bool rech (list t , int x);
void supp (list &t , int x); 
int compter(list tete );
int compterRec(list tete);
list rech1 (list tete , int x) ;
void triebull (list & tete);
void ajoutlisttrier (list & tete);
void expo (list &t);
void impo (list &t);

main()
{ 
 int x, Rp, N  ; 	
 list t ;
 Etud E ;
//le programme ne marche jamis quand je supprimez (int a=N;) ???!!!!!!!!!!!!! 
 int a=N ;

 
	while (1)
	{
		printf("\n\n**************************************  M E N U  **************************************\n");
		printf("1-Pour ajouter au debut de la list \n");
		printf("2-Pour afficher le contenu du list chainee \n");
    	printf("3-Pour Rechercher un etudiant par son numero \n");
		printf("4-Pour ajouter a la fin de la list  \n");	
		printf("5-Pour supprimer un etudiant de la list \n");
		printf("6-Pour Trie a bull du list chaine par rapport au numero\n");
		printf("7-Pour retourner les info de l etudiant a rechercher \n");
		printf("8-Pour ajouter dans une liste trier\n");
		printf("9-Pour compter la taille du list chaine\n");
		printf("10-Pour compter la taille du list chaine avec la methode Recursive\n");	
        printf("11-Pour sauvegarder les info dans une fichier\n");
        printf("12-Pour importer des info de fichier\n") ;
		printf("13-Pour quitter le programme \n") ;     
	    printf("\n********** VOTRE CHOIX EST :\t");
		scanf("%d",&Rp);
	    system("cls") ; 
	    
   	  switch (Rp)
	  {
	   case 1 : do 
               {printf("Donner le nombre de l etudiant a ajouter : \n");
                scanf("%d",&N);
                } while ( (0>N)&&(N>=50) ) ;
            for (int i=0 ; i<N ; i++)
               { ajoutdebut(t) ; }; break ;
	   case 2 : printf("**** Votre List d etudiants est pret ****\n"); parcourir(t)  ; break ;
	   case 3 :printf("Entrez le numero de l etudiant a recherhcer :\n");
	 		   scanf("%d",&x);
	  			if (rech(t,x)==true)
	            {
	              printf("il exist :) \n");
		        }
	            else
	            {
	              printf("il n exist pas :( \n");	
	            };break;
	   case 4 :ajoutfin(t) ; break;
	   case 5 :printf("Entrez le numero de l etudiant a supprimer :\n");
				int x1 ;  
	           scanf("%d",&x1);	           
               supp(t,x1);
		 	break ;
	   case 6 : triebull(t) ; printf("***La list chaine est trier... \n") ; break;
	   case 7 :printf("Entrez la moyenne de l etudiant a rechercher :\n");
	    		   float m ;
	   			scanf("%f",&m);
				printf("***Les info de l etudiant a rechercher: \n") ;
				rech1(t,m) ;break;
	   case 8 : ajoutlisttrier(t); break;
	   case 9 : printf("La taille de la list chaine est: %d ",compter(t)) ; break;
	   case 10 : printf("La taille de la list chaine (Recursiviter) est: %d",compterRec(t)) ; break; 	
	   case 11 : expo (t);printf("***La list est sauvegarder  :) \n") ;break ;
	   case 12 : impo (t); break ;
	   case 13 : exit(1); break ; 
	   default : printf("\n\n !!!!  Verifier votre choix  !!!! \n\n")	;
	  }
	}	
}

void expo (list &t)
{
	FILE *f=NULL;
	if (f== NULL){
	f=fopen("a.txt","a");
    } 
    else{
    f=fopen("a.txt","w");
	    }
	while (t != NULL)
	{
		fprintf(f,"[ Nom:%s  ;",t->Nom);
		fprintf(f,"Prenom:%s  ;",t->Prenom);
		fprintf(f,"Numero:%d  ;",t->Num);
		fprintf(f,"Moyenne:%f ] \n",t->Moy);
		t = t->suiv ;
	}
	fclose(f);
}
void impo (list &t)
{ 
  
  FILE *f;
    f=fopen("a.txt","r");
    if (f == NULL)
	{
	  printf("Le fichier est vide !!!\n");
	}
	else
	{
	  printf("***Les info du fichier:\n") ;
		list nouv ;
		nouv=new Etud ;
		while(t!=NULL)
		{
		 fscanf(f,"[ Nom:%s  ;",&nouv->Nom);
		 fscanf(f,"Prenom:%s  ;",&nouv->Prenom);
		 fscanf(f,"Numero:%d  ;",&nouv->Num);
		 fscanf(f,"Moyenne:%f ] \n",&nouv->Moy);
		 t=t->suiv ;
    	}
	    nouv->suiv=t ;
		t=nouv ; 
    } 
	fclose(f);	
}

void creation (list &t)
{
	t=NULL;
}
void ajoutdebut (list &t)
{
	list nouv ;
	nouv = new Etud ;
	printf("Entrez le nom de l etudiant : \n");
	scanf("%s",&nouv->Nom);
	printf("Entrez le prenom de l etudiant : \n");
	scanf("%s",&nouv->Prenom);
	printf("Entrez le numero de l etudiant :\n") ;
	scanf("%d",&nouv->Num);
	printf("Entrez le moyenne de l etudiant : \n") ;
	scanf("%f",&nouv->Moy);
	nouv->suiv = t ;
	t = nouv ;
}

void parcourir (list t)
{
	list p ;
	p=t ;
	while (p != NULL)
	{
		printf("[%s ;",p->Nom);
		printf("%s ;",p->Prenom);
		printf("%d ;",p->Num);
		printf("%f ] \n",p->Moy);
		p = p->suiv ;
	}
}
void ajoutfin (list & t)
{
	list p , nouv ;

	if (t == NULL)
	{
		ajoutdebut(t);
	}
	else
	{
	nouv =new Etud ;
	printf("***Donner les infos de l etudiant a ajouter a la fin du list :\n");
	printf("Entrez le nom de l etudiant : \n");
	scanf("%s",&nouv->Nom);
	printf("Entrez le prenom de l etudiant : \n");
	scanf("%s",&nouv->Prenom);
	printf("Entrez le numero de l etudiant :\n") ;
	scanf("%d",&nouv->Num);
	printf("Entrez le moyenne de l etudiant :\n") ;
	scanf("%f",&nouv->Moy);
	nouv->suiv = NULL ;
		p = t ;
		while (p->suiv != NULL)
		{
			p=p->suiv ;
		}
		p->suiv = nouv ;
	}
}
bool rech (list t , int x) 
{
	list cour ;
	cour = t ;
	while ((cour != NULL) && (cour->Num != x))
	{
		cour = cour->suiv ;
	}
	if (cour != NULL)
	{
		return true ;
	}
	else 
	{
		return false ;
	}
}
void supp (list &t , int x)
{
	list pre , cour ;
	cour = t ;
	while ((cour!=NULL)&&(cour->Num!=x))
	{
		pre = cour ;
		cour = cour-> suiv ;
	}
	if (cour != NULL)
	{
		if (cour == t )
		{
			t= cour->suiv ;
		}
		else
		{
			pre->suiv = cour->suiv ; 
		}
		delete (cour);
		printf("L etudiant est supprimer :) \n");
	}
}

int compter(list tete)
{
	list cour;
	int Nbr=0;
	cour=tete;
	while (cour!=NULL)
	{
		Nbr++;
		cour=cour->suiv ;
	}
	return Nbr;
}
int compterRec(list tete)
{
	if (tete==NULL)
	{
		return 0 ;
	}
	else 
	{
		return 1+compterRec(tete->suiv) ;
	}
}
void ajoutlisttrier (list & tete)
{
	list nouv , cour , pre ;
	if (tete == NULL)
	{
		ajoutdebut (tete);
	}
	else 
	{
		nouv= new Etud ;
	printf("Entrez le nom de l etudiant : \n");
	scanf("%s",&nouv->Nom);
	printf("Entrez le prenom de l etudiant : \n");
	scanf("%s",&nouv->Prenom);
	printf("Entrez le numero de l etudiant :\n") ;
	scanf("%d",&nouv->Num);
	printf("Entrez le moyenne de l etudiant :\n") ;
	scanf("%f",&nouv->Moy);
		cour = tete ;
		while ((cour) && (cour->Num) < (nouv->Num) )
		{
			pre = cour ;
			cour = cour->suiv ;
		}
		nouv->suiv = cour ;
		if ( cour == tete)
		{
			tete = nouv ;
		}
		else 
		{
			pre->suiv = nouv ;
		}
	}
}
list rech1 (list tete , int x) 
{
	list cour  ;
	cour = tete ;
	while ((cour != NULL) &&(cour->Moy != x))
	{
		cour = cour->suiv ;
	}
	//return cour ;
	printf("[%s - %s - %d - %f]",cour->Nom,cour->Prenom,cour->Num,cour->Moy) ;
}
// désoler la permutation de nom et prenom ne fonctionne pas
void triebull (list & tete)
{
	list cour ;
	bool trier;
	int aux ;
	float aux1 ;
    char aux2, *aux3 ;
do{
	cour = tete ;
	trier = true ;
	while((cour != NULL)&&(cour->suiv != NULL))
	{
		if ((cour->Num) > ( (cour->suiv)->Num))
		{
			aux = cour->Num ;
			cour->Num = (cour->suiv)->Num ;
			(cour->suiv)->Num = aux ;	
			
		//    strcpy(aux2, cour ->Nom);
        //    strcpy(cour ->Nom , cour ->suiv -> Nom);
        //    strcpy(cour ->suiv -> Nom, aux2);

        //    strcpy(aux3, cour ->Prenom);
        //    strcpy(cour ->Prenom , cour ->suiv -> Prenom);
        //    strcpy(cour ->suiv -> Prenom, aux3);
			
			aux1 = cour->Moy ;
			cour->Moy = (cour->suiv)->Moy ;
			(cour->suiv)->Moy = aux1 ;
			
			trier = false ;
		}
		cour = cour->suiv ;
	}
 } while (trier==false)	;
}
