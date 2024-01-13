/*CHEBL YOUSSEF 1 INFO D*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h> // pour appeler la fonction - setlocale -

#include "MyFunctions.cpp"


int main() {
	
	setlocale(LC_CTYPE, "");  //définir les paramètres régionaux
	
    CATEGORY *categories = NULL;
    int categoryCount = 0;

    PRODUCT *products = NULL;
    int productCount = 0;

    CUSTOMER *customers = NULL;
    int customerCount = 0;

    ORDER *orders = NULL;
    int orderCount = 0;
	
	CATEGORY * selectedCat = NULL ;
	
	RESULT ** resultArray = NULL;
	RESULT *res	 = NULL ;
	int prodCount =0 ;
	
	CUSTOMER*  c ;
	 
	 FILE *file;FILE *indexfile;
	 
	 
	int choix ,x, selectedCatID , nid, catID, orderID ,clientID ,categoryID, productID, position;

	while (1)
	{
		printf("\n*************  M E N U    P R I N C I P A L E  *************\n") ;
		printf("0- Quitter le programme \n") ;
		printf("1- Gestion des categories\n");
		printf("2- Gestion des produits \n");
		printf("3- Gestion des clients \n");
		printf("4- Gestion des commandes \n");				
		printf("5- Gestion du tableau RESULTAT \n");
		printf("6- Gestion des fichiers \n");
		printf("\n**********************************************************\n") ;
			
		do
		{
			printf("\n*** Votre choix : ") ;
			scanf("%d", &choix);
		} while ( (choix < 0) || (choix > 6) );
		//system("cls") ;
		 switch (choix) {
        	case 0:
				exit(-1); 
				break;   
            case 1: do
                    {
                    	printf("\n*************  Gestion des categories *************\n") ;
                        printf("1- Pour ajouter une catégorie\n");
                        printf("2- Pour afficher les catégories\n");
                        printf("3- Pour supprimer une catégorie\n");
                        printf("4- Pour afficher le nombres totale des categories \n");
                        printf("5- Retour\n");
                            do
                            {
                            	printf("\n*** Votre choix :");
                        		scanf("%d",&x);
                            }while( x<1 || x>5 );
                        
                        //system("cls");
                        switch(x)
                        {
                            case 1: 
								categories = (CATEGORY*) realloc (categories, (categoryCount + 1) * sizeof(CATEGORY));
						        if(! categories) 
								{ printf("\n!! Erreur d'allocation du mémoire !!\n");
								  break;
								}else
								{
									addCategory(&categories,&categoryCount);
								};
								break;
                            case 2: displayAllCategories(categories, categoryCount);
								break;
                            case 3:  
								printf("\nEntrez l'identifier du categorie a supprimer:");
								scanf("%d",&catID);
								removeCategory(&categories, &categoryCount, catID);
								break;
                            case 4: printf("\nLe nombres totale des categories est %d",categoryCount);
								break;
                            
                        }
					}while (x!=5);
					break;
			case 2: do
                    {
                    	printf("\n*************  Gestion des produits *************\n") ;
                        printf("1- Pour ajouter un produit\n");
                        printf("2- Pour afficher un produit\n");
                        printf("3- Pour supprimer un produit\n");
                        printf("4- Pour afficher le nombres totale des produits \n");
                        printf("5- Retour\n");
                            do
                            {
                            	printf("\n*** Votre choix :");
                        		scanf("%d",&x);
                            }while( x<1 || x>5 );
                        
                        //system("cls");
                        switch(x)
                        {
                            case 1: 
								products = (PRODUCT *) realloc(products, (productCount + 1) * sizeof(PRODUCT));
				                if(! products) 
								{ 
									printf("\n!! Erreur d'allocation du mémoire !!\n");
								  	break;
								}
								else
								{ addProductToCategory(&products, &productCount, categories, categoryCount); 
								prodCount+=1;}
								break;
                            case 2: 
								printf("\nEntrez l'identifier du produit a afficher:");
								scanf("%d",&catID);
								displayProductDetails(categories,  categoryCount, catID);
								break;
                            case 3:  
                            	printf("\nEntrez l'identifier du categorie :");
								scanf("%d",&categoryID);
								printf("\nEntrez l'identifier du produit a supprimer:");
								scanf("%d",&catID);
								removeProductFromCategory(categories, categoryCount, categoryID, catID);
								break;
                            case 4: printf("\nLe nombres totale des produits est %d",prodCount);
								break;
                            }
					}	while (x!=5);
					break;	
			case 3: 
				do
                {
                	printf("\n*************  Gestion des clients *************\n") ;
                    printf("1- Pour ajouter un client\n");
                    printf("2- Pour afficher les clients\n");
                    printf("3- Pour supprimer un client\n");
                    printf("4- Pour afficher le nombres totale des clients \n");
                    printf("5- Retour\n");
                        do
                        {
                        	printf("\n*** Votre choix :");
                    		scanf("%d",&x);
                        }while( x<1 || x>5 );
                    
                    //system("cls");
                    switch(x)
                    {
                        case 1: 
							customers = (CUSTOMER *) realloc(customers, (customerCount + 1) * sizeof(CUSTOMER));
		        			addCustomer(&customers, &customerCount);
							break;
                        case 2: 
                        	printf("\n----------------- Liste des Clients --------------------\n");
							for (int i = 0; i < customerCount; i++) 
							{
						        displayCustomer(*(customers+i));
						    }
							break;
                        case 3:  
							printf("\nEntrez l'identifier du client a supprimer:");
							scanf("%d",&clientID);
							removeCustomer(customers,  customerCount,  clientID);
							break;
                        case 4: printf("\nLe nombres totale des clients est %d",customerCount);
							break;
                       
                    }
				}while (x!=5);
				break;
			case 4: 
				do
                {
                	printf("\n*************  Gestion des commandes *************\n") ;
                    printf("1- Pour ajouter une commande\n");
                    printf("2- Pour afficher les commandes\n");
                    printf("3- Pour supprimer une commande\n");
                    printf("4- Pour afficher le nombres totale des commandes \n");
                    printf("5- Retour\n");
                        do
                        {
                        	printf("\n*** Votre choix :");
                    		scanf("%d",&x);
                        }while( x<1 || x>5 );
                    
                    //system("cls");
                    switch(x)
                    {
                        case 1: 
							orders = (ORDER *) realloc(orders, (orderCount + 1) * sizeof(ORDER));
                			createOrder(customers, categories, &orders, &orderCount, categoryCount, customerCount) ;
							break;
                        case 2: 
							displayOrders(orders, orderCount);
							break;
                        case 3:  
							printf("\nEntrez l'identifier du commande a supprimer:");
							scanf("%d",&orderID);
							removeOrder(orders, orderCount, orderID);
							break;
                        case 4: printf("\nLe nombres totale des commandes est %d",orderCount);
							break;
                        
                       
                    }
				}while (x!=5);
				break;
			case 5:					
                 do
                {
                	printf("\n*************  Gestion du RESULTAT *************\n") ;
                    printf("1- Pour remplir le tableau RESULT\n");
                    printf("2- Pour afficher le tableau RESULT\n");
                    printf("3- Retour\n");
                        do
                        {
                        	printf("\n*** Votre choix :");
                    		scanf("%d",&x);
                        }while( x<1 || x>3 );
                    
                    //system("cls");
                    switch(x)
                    {
                        case 1: 
							fillResults(&resultArray, orders, orderCount);
							break;
                        case 2: 
							displayMostExpensiveOrder(resultArray,orderCount);
							break;
                        
                    }
				}while (x!=3);
				break;  
			case 6:					
                 do
                {
                	printf("\n*************  Gestion des fichiers  *************\n") ;
                    printf("1- Pour remplir les fichiers \n");
                    printf("2- Pour afficher les fichiers \n");
                    printf("3- Pour modifier les fichiers  \n");
                    printf("4- Retour\n");
                        do
                        {
                        	printf("\n*** Votre choix :");
                    		scanf("%d",&x);
                        }while( x<1 || x>4 );
                    
                    //system("cls");
                    switch(x)
                    {
                        case 1: 
							createfile(&file,&indexfile);
							fillfile(file,indexfile);
							break;
                        case 2: 
							displayfile(file,indexfile);
							break;			
						case 3 :	
							printf("\nEntrez la position du modification :");
							scanf("%d",&position);
							modifyCustomer(file, indexfile, position);
							break;		
                        
                    }
				}while (x!=4);
				break;   
			default:
                printf("\n!! Choix invalid !!\n");
        }
		
	}
    
    free(categories) ;
    free(products) ;
    free(customers) ;
    free(orders) ;

	free(resultArray);
	
    return 0;
	 
	 
	 
//	 
//
//	int choix , selectedCatID , nid;
//
//	while (1)
//	{
//		printf("\n***********************************************************\n") ;
//		printf("0- Pour quitter le programme \n") ;
//		printf("1- Pour ajouter une catégorie \n");
//		printf("2- Pour ajouter un produit \n");
//    	printf("3- Pour ajouter un client \n");
//		printf("4- Pour ajouter une commande \n");	
//		printf("5- Pour afficher les catégories \n");
//		printf("6- Pour afficher les clinets \n");
//		printf("7- Pour afficher les commandes \n");
//		printf("8- Pour afficher le nombres totale des clients \n");
//		printf("9- Pour afficher le nombres totale des categories \n");
//		printf("10- Pour afficher le nombres totale des commandes \n");
//		printf("11- Pour remplir le sturcture RESULT \n") ;
//		printf("12- Pour afficher le sturcture RESULT \n") ;
//		printf("13- Pour remplir les fichiers du RESULT \n") ;
//		printf("14- Pour afficher les fichier du RESULT \n") ;
//		printf("\n***********************************************************\n") ;			
//        
//		do
//		{
//			printf("\t* Votre choix : ") ;
//			scanf("%d", &choix);
//		} while ( (choix <= 0) && (choix >= 10) );
//		
//	    system("cls") ; 
//	    
//        switch (choix) {
//        	case 0:
//				exit(-1); 
//				break;   
//            case 1:
//            	categories = (CATEGORY*) realloc (categories, (categoryCount + 1) * sizeof(CATEGORY));
//            	if(! categories) 
//				{ printf("\n!! Erreur d'allocation du mémoire !!\n");
//				  break;
//				}else
//				{
//					addCategory(&categories,&categoryCount);
//				}
//				break;
//            case 2:
//            	    displayAllCategories(categories, categoryCount);
//            		products = (PRODUCT *) realloc(products, (productCount + 1) * sizeof(PRODUCT));
//                if(! products) 
//				{ 
//					printf("\n!! Erreur d'allocation du mémoire !!\n");
//				  	break;
//				}
//				else
//				{ addProductToCategory(&products, &productCount, categories, categoryCount); }
//				
//				
////            	products = (PRODUCT *) realloc(products, (productCount + 1) * sizeof(PRODUCT));
////                if(! products) 
////				{ 
////					printf("\n!! Erreur d'allocation du mémoire !!\n");
////				  	break;
////				}
////				else
////				{
////					do{	
////						printf("\nEntrez l'identifiant de la catégorie à laquelle ajouter le produit : ");
////        				scanf("%d", &selectedCatID);
////        			} while(selectedCatID <= 0);
////        				
////					for (int i=0 ; i < categoryCount ; i++) 
////					{
////        				printf("\nID %d : %d",i,(categories+i)->categoryID);
////			            if ((categories+i)->categoryID == selectedCatID) 
////						{
////			            	printf("\nId exist :)\n");
////			                addProduct(&products, (categories+i));
////			                break;
////			            }else{
////			            	printf("\nId du categories n'esist pas , si tu peut ajouter tapez 1 sinon 0 : ");
////			            	scanf("%d", &nid);	
////					        if (nid == 1 ) 
////							{	categories = (CATEGORY*) realloc (categories, (categoryCount + 1) * sizeof(CATEGORY));
////								addCategory(&categories,&categoryCount);
////							}
////						}
////			        }
////				}
//				break;
//            case 3:
//            	customers = (CUSTOMER *) realloc(customers, (customerCount + 1) * sizeof(CUSTOMER));
//		        addCustomer(&customers, &customerCount);
//                break;
//            case 4:
//                orders = (ORDER *) realloc(orders, (orderCount + 1) * sizeof(ORDER));
//				//createOrder(customers,categories, products, &orders, &orderCount, productCount, categoryCount,customerCount );
//                createOrder(customers, categories, &orders, &orderCount, categoryCount, customerCount) ;
//				break;
//            case 5:/*
//            	for (int i = 0; i < categoryCount; i++) 
//				{
//			        displayCategory(*(categories+i));
//			    }*/
//			    displayAllCategories(categories, categoryCount);
//                break;
//			case 6:
//			    for (int i = 0; i < customerCount; i++) 
//				{
//			        displayCustomer(*(customers+i));
//			    }
//                break;
//            case 7:
////        	    for (int i = 0; i < orderCount; i++) 
////				{
////				    displayOrder(orders[i]);
////				}
////				printf("\n**************************\n");
//				displayOrders(orders, orderCount);
//            	break;
//            case 8:
//        	    printf("Le nombres totale des clients est %d",customerCount);
//            	break;
//			case 9:
//        	    printf("Le nombres totale des categories est %d",categoryCount);
//		       	break;
//			case 10:
//        	    printf("Le nombres totale des commandes est %d",orderCount);
//            	break;
//			case 11:
//			
//				fillResults(&resultArray, orders, orderCount);	
//			   // createresut(resultArray,numres) ;
//				break;
//			case 12 : 
//				
//				displayMostExpensiveOrder(resultArray,orderCount);
//			
//				//displayMostExpensiveOrders(*resultArray, orderCount);
//				/*// Affichage des données du struct RESULT
//			    for (int i = 0; i < numres; i++) 
//				{
//			        printf("Order ID: %d, Total Amount: %.2f\n",  (*(resultArray + i))->orderID,  (*(resultArray + i))->totalAmount);
//			    }*/
//				break;	
//				
//			case 13:
//				    creerfichier(&file,&indexfile);
//					remplirFichier(file,indexfile);
//				//fillFiles(*resultArray, orderCount, file , indexfile);
//				break;	
//			
//			case 14:
//				displayFile(file,indexfile);
//				//displayFiles(file ,indexfile);
//				break;
//			default:
//                printf("\n!! Choix invalid !!\n");
//        }
//	}
//    
//    free(categories) ;
//    free(products) ;
//    free(customers) ;
//    free(orders) ;
//
//	free(resultArray);
//	return 0;
    
}


 



