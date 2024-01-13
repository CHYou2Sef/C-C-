
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <locale.h> // pour appeler la fonction - setlocale -

#include "MyFunctions.h"


//-------------------------------- Fonctions d'ajout --------------------------------------//
// Ajouter une cat�gorie
void addCategory(CATEGORY **categories, int *categoryCount) {
    CATEGORY newCategory;

	do {
    printf("\nEntrez l'id de la cat�gorie ( > 0 ): ");
    scanf("%d", &newCategory.categoryID);
    if (TestIDCat(newCategory.categoryID,categories,categoryCount) == 1 ) printf("\nDeja exist :)");
    
	} while ( (isdigit(newCategory.categoryID)) || (newCategory.categoryID <= 0) || (TestIDCat(newCategory.categoryID,categories,categoryCount) == 1 ) );
	  //test pour id
	
	do{
    printf("\nEntrez le nom de la cat�gorie (le premiere doit etre un caractere): ");
    scanf("%s", newCategory.name);
	} while( !isalpha(newCategory.name[0]) );

    newCategory.products = NULL;
    newCategory.numProducts = 0;

    // Ajouter nouvelle cat�gorie 
    *categories = (CATEGORY *)realloc(*categories, (*categoryCount + 1) * sizeof(CATEGORY));
    (*(*categories+*categoryCount)) = newCategory;
    (*categoryCount)++;
	
    printf("\n-------------------- NB --------------------\n");
	printf("Cat�gorie ajout�e avec succ�s\n");
}

// Ajouter produit � une cat�gorie selectionn�
void addProduct(PRODUCT **products, CATEGORY *category) {
    PRODUCT newProduct;
   
    do{
    printf("Entrez l'identifiant du produit : ");
    scanf("%d", &newProduct.productID);
	} while ( (newProduct.productID <= 0) || (TestIDPro(newProduct.productID,products,category->numProducts) ==1 ) );
	//test pour id
	
	do{
    printf("Entrez le nom du produit : ");
    scanf("%s", newProduct.name);
	} while( !isalpha(newProduct.name[0]) );

	do{
    printf("Entrez la description du produit : ");
    scanf("%s", newProduct.description);
   	} while( !isalpha(newProduct.description[0]) );

	do{
    printf("Entrez la marque du produit : ");
    scanf("%s", newProduct.brand);
   	} while( !isalpha(newProduct.brand[0]) );
     
	do{
    printf("Entrez le prix du produit : ");
    scanf("%f", &newProduct.price);
	} while(isdigit(newProduct.price) );

	do{
    printf("Entrez la quantit� en stock du produit : ");
    scanf("%d", &newProduct.stockQuantity);	
	} while(isdigit(newProduct.stockQuantity) );

    // Ajouter nouvelle produit a la cat�gorie
    category->products = (PRODUCT *)realloc(category->products, (category->numProducts + 1) * sizeof(PRODUCT));
    *(category->products+category->numProducts) = newProduct;
    category->numProducts++;

	printf("\n-------------------- NB --------------------\n");
    printf("Produit ajout� avec succ�s � la cat�gorie\n");
}

// Ajouter produit a une cat�gorie exist
void addProductToCategory(PRODUCT **products, int *productCount, CATEGORY *categories, int categoryCount) {
    int productID, quantity, categoryID;
    CATEGORY *selectedCategory;
    
    if (categories==NULL)
    {
    	printf("Tableau de categories vide , ajouter une categorie avant :)");
    	return ;
	}
	
	do{	 
    printf("Entrez l'identifiant de la cat�gorie � laquelle ajouter le produit : ");
    scanf("%d", &categoryID);
	}while (findCategoryIndex(categoryID, categories, categoryCount)==-1);
	
    // V�rifier si la cat�gorie choisie existe
    int existingCategoryIndex = findCategoryIndex(categoryID, categories, categoryCount);


    if (existingCategoryIndex != -1) {
        selectedCategory = (categories+existingCategoryIndex);
	}
	
    printf("\nEntrez l'identifiant du produit : ");
    scanf("%d", &productID);

    // V�rifier si le produit exist
    int existingProductIndex = findProductIndex(productID, categories->products, categories->numProducts);

    if (existingProductIndex != -1) {
        printf("\nLe produit existe d�j� dans la cat�gorie. \nEntrez la quantit� � ajouter : ");
        scanf("%d", &quantity);

        // Ajout la quantit� au stock 
        selectedCategory->products[existingProductIndex].stockQuantity += quantity;

        printf("\n-------------------- NB --------------------\n");
        printf("Quantit� ajout�e avec succ�s au produit existant dans la cat�gorie\n");
    } else {
        // Le produit n exist pas, ajouter un nouveau produit
        addProduct(products, selectedCategory);

        printf("\n-------------------- NB --------------------\n");
        printf("Nouveau produit ajout� � la cat�gorie\n");
    }
	
}

// Ajouter un client
void addCustomer(CUSTOMER **customers, int *customerCount) {
    CUSTOMER newCustomer;

	do{
    printf("Entrez l'identifiant du client : ");
    scanf("%d", &newCustomer.customerID);
   	} while ((newCustomer.customerID <= 0) || (TestIDCli(newCustomer.customerID,customers,customerCount) == 1 ) );

	do{
    printf("Entrez le nom du client : ");
    scanf("%s", newCustomer.name);
   	} while(isdigit(newCustomer.name[0]) );

    printf("Entrez l'e-mail du client : ");
    scanf("%s", newCustomer.email);

    newCustomer.nbrOrders = 0;

    // Ajouter nouveau client 
    *customers = (CUSTOMER *)realloc(*customers, (*customerCount + 1) * sizeof(CUSTOMER));
    (*(*customers+*customerCount) )= newCustomer;
    (*customerCount)++;

	printf("\n-------------------- NB --------------------\n");
    printf("Client ajout� avec succ�s\n");
}

//---------------------------- Foncions pour trouver les indexs -----------------------------------//
// Trouver l'index du produit
int findProductIndex(int productID, PRODUCT *products, int numProducts) {
    for (int i = 0; i < numProducts; i++) {
        if ((products+i)->productID == productID) {
            return i; // Retourne l'index si trouvr
        }
    }
    return -1; // sinon retourne -1 
}
// Trouver l'index du categorie
int findCategoryIndex(int categoryID, CATEGORY *categories, int categoryCount) {
    for (int i = 0; i < categoryCount; i++) {
        if ((categories+i)->categoryID == categoryID) {
            return i; 
        }
    }
    return -1; 
}
// Trouver l'index du client
int findCustomerIndex(int customerID, CUSTOMER *customers, int numCustomers) {
    for (int i = 0; i < numCustomers; i++) {
        if ((customers+i)->customerID == customerID) {
            return i; 
    }
    return -1;
}
}

// Trouver l'index du commande
int findOrderIndex(int orderID, ORDER *orders, int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        if ((orders+i)->orderID == orderID) {
            return i; 
        }
    }
    return -1;
}


//-------------------------------- Fonctions de suppression -------------------------------------//
// supprimer categorie
void removeCategory(CATEGORY **categories, int *categoryCount, int categoryID) {
    int categoryIndex = findCategoryIndex(categoryID, *categories, *categoryCount);

    if (categoryIndex != -1) {
        // Lib�rer la m�moire pour les produits
        free((*categories)[categoryIndex].products);

        for (int i = categoryIndex; i < *categoryCount - 1; i++) 
		{
		   (*categories)[i] = (*categories)[i + 1];
           // *(categories+i) = *(categories+i + 1);
        }

        (*categoryCount)--;

		printf("\n-------------------- NB --------------------\n");
        printf("Cat�gorie supprim�e avec succ�s\n");
    } else {
    	printf("\n-------------------- NB --------------------\n");
        printf("Cat�gorie introuvable.\n");
    }
}

// supprimer produit
void removeProductFromCategory(CATEGORY *categories, int categoryCount, int categoryID, int productID) {
    for (int i = 0; i < categoryCount; i++) {
        if ((categories + i)->categoryID == categoryID) 
		{
            PRODUCT *products = (categories + i)->products;
            int numProducts = (categories + i)->numProducts;

            int productIndex = findProductIndex(productID, products, numProducts);

            if (productIndex != -1) {
                for (int j = productIndex; j < numProducts - 1; j++) 
				{
//                    *(products+j) = *(products+j + 1);
					products[j] = products[j + 1];
                }
            categories[productIndex].numProducts--;
	
				printf("\n-------------------- NB --------------------\n");
                printf("Produit supprim� avec succ�s de la cat�gorie\n");
            } else 
			{
            	printf("\n-------------------- NB --------------------\n");
                printf("Produit introuvable dans la cat�gorie\n");
            }
            return;
        }
    }
	printf("\n-------------------- NB --------------------\n");
    printf("Cat�gorie introuvable\n");
}

// supprimer client
void removeCustomer(CUSTOMER *customers, int customerCount, int customerID) {
    int customerIndex = findCustomerIndex(customerID, customers, customerCount);

    if (customerIndex != -1) {
        // Supprimer le client en d�calant les �l�ments restants
        for (int i = customerIndex; i < customerCount - 1; i++) {
            customers[i] = customers[i + 1];
        }

        printf("Client supprim� avec succ�s.\n");
    } else {
        printf("Client introuvable.\n");
    }
}

// supprimer commande
void removeOrder(ORDER *orders, int orderCount, int orderID) {
     int orderIndex = findOrderIndex(orderID, orders, orderCount);

    if (orderIndex != -1) {
        // Supprimer la commande en d�calant les �l�ments restants
        for (int i = orderIndex; i < orderCount - 1; i++) {
            orders[i] = orders[i + 1];
        }

        printf("Commande supprim�e avec succ�s.\n");
    } else {
        printf("Commande introuvable.\n");
    }
}

//----------------------------------La creation du commande --------------------------------------//
//creation d une commande 
void createOrder(CUSTOMER *customers, CATEGORY *categories, ORDER **orders, int *orderCount, int categoryCount, int customerCount) {
    ORDER newOrder;
    newOrder.customers = NULL;
    newOrder.categories = NULL;
    newOrder.nbrProducts = 0;
    newOrder.nbrCategories = 0;
    newOrder.totalAmount = 0.0;

    int clientID;
    printf("Entrez l'identifiant du client : ");
    scanf("%d", &clientID);

    for (int i = 0; i < customerCount; i++) {
        if ( (customers+i)->customerID == clientID) {
        	printf("\nID Client trouv� :)\n");
            newOrder.customers = (customers+i);
			//newOrder.customers = &customers[i];
            break;
        }
    }

    if (newOrder.customers == NULL) {
        printf("Client introuvable, ajouter le avant de cr�e une commande :)\n");
        return;
    }

    // Identifier la cat�gorie
    int categoryID;
    printf("Entrez l'identifiant de la cat�gorie : ");
    scanf("%d", &categoryID);

    // Rechercher la cat�gorie 
    CATEGORY *selectedCategory = NULL;
    for (int i = 0; i < categoryCount; i++) {
        if ((categories+i)->categoryID == categoryID) {
            selectedCategory = categories+i;
			//selectedCategory = &categories[i];
            break;
        }
    }

    if (selectedCategory == NULL) {
        printf("Cat�gorie introuvable\n");
        return;
    }

    int productID;
    printf("Entrez l'identifiant du produit dans la cat�gorie : ");
    scanf("%d", &productID);

    // Rechercher le produit dans cat�gorie
    PRODUCT *selectedProduct = NULL;
    for (int i = 0; i < selectedCategory->numProducts; i++) {
        if ((selectedCategory->products+i)->productID == productID) {
        	printf("\nProduit trouv� dans la cat�gorie :)\n");
            //selectedProduct = &selectedCategory->products[i];
            selectedProduct = (selectedCategory->products+i);
            
            newOrder.nbrProducts+=1 ;
            break;
        }
    }

    if (selectedProduct == NULL) {
        printf("Produit introuvable\n");
        return;
    }

    int quantity;
    printf("Entrez la quantit� : ");
    scanf("%d", &quantity);
	
	//diminuer le nbr de produit acheter
	selectedProduct->stockQuantity-=quantity ;
	
    // Allouer la m�moire pour la nouvelle commande
    *orders = (ORDER *)realloc(*orders, (*orderCount + 1) * sizeof(ORDER));

    // Initialiser la nouvelle commande
    newOrder.orderID = *orderCount+1 ;  
    newOrder.categories = (CATEGORY *)malloc(sizeof(CATEGORY));
    newOrder.categories[0] = *selectedCategory;
    newOrder.nbrCategories = 1;

    // Allouer pour les produits du nouvelle commande
    newOrder.categories[0].products = (PRODUCT *)malloc(quantity * sizeof(PRODUCT));
    newOrder.nbrProducts = quantity;

    // Copier le produit dans la commande
    for (int i = 0; i < quantity; i++) {
        *(newOrder.categories[0].products+i) = *selectedProduct;
        newOrder.totalAmount += selectedProduct->price;
    }

    // Incr�menter le nombre de commandes du client
    newOrder.customers->nbrOrders++;

    // Ajouter la commande au tab d'ordre
    (*orders)[*orderCount] = newOrder;
    (*orderCount)++;

    printf("\n-------------------- NB --------------------\n");
    printf("Commande cr�e avec succ�\n");
}

//-------------------------------------  Fonctions pour l'affichage ----------------------------------------//
// Afficher un seul produit
void displayProduct(PRODUCT product) 
{
    printf("ID du produit : %d\n", product.productID);
    printf("Nom du produit : %s\n", product.name);
    printf("Description : %s\n", product.description);
    printf("Prix : %.2f\n", product.price);
    printf("Quantit� en stock : %d\n", product.stockQuantity);
    printf("Marque : %s\n", product.brand);
    printf("\n-------------------------------------\n");
}

// Afficher une seul cat�gorie
void displayCategory(CATEGORY category) 
{	
	
    printf("ID de la cat�gorie : %d\n", category.categoryID);
    printf("Nom de la cat�gorie : %s\n", category.name);
    printf("Nombre de produit : %d\n", category.numProducts);
	
	printf("\n----------------- Liste des produits --------------------\n");
    // Afficher les produits du cat�gorie
    for (int i = 0; i < category.numProducts; i++) 
	{
        displayProduct(*(category.products+i));
    }
    printf("\nLe montant totale du category est : %.2f", calculateCategoryTotal(&category));
    printf("\n-------------------------------------\n");
}

// calculer le montant totale du categorie 
float calculateCategoryTotal(CATEGORY *category) 
{
    float total = 0.0;
    for (int i = 0; i < category->numProducts; i++) 
	{
        total += (category->products+i)->price;
    }
    return total;
}

// Afficher un client
void displayCustomer(CUSTOMER customer) 
{
    printf("ID du client : %d\n" , customer.customerID) ;
    printf("Nom du client : %s\n" , customer.name) ;
    printf("E-mail du client : %s\n" , customer.email) ;
    printf("Nombre des commandes : %d\n" , customer.nbrOrders) ;
    printf("\n-------------------------------------\n") ;
}

// Afficher une commande
void displayOrder(ORDER order) 
{
	 printf("\n-------------------------------------\n");
	 printf("ID de la commande : %d\n", order.orderID) ;
	 printf("Client de la commande :%s\n", order.customers->name);
	 printf("Nombres des categories: %d\n", order.nbrCategories);
	 printf("Montant totale de la commande : %.2f\n" , order.totalAmount);
	 printf("Nombre des produits dans la commande : %d" , order.nbrProducts);
	 printf("\n-------------------------------------\n");
}

// Afficher un produit
void displayProductDetails(CATEGORY *categories, int categoryCount, int productID) {
    for (int i = 0; i < categoryCount; i++) {
        for (int j = 0; j < (*(categories+i)).numProducts; j++) {
            if ( (*((*(categories+i)).products+j)).productID == productID) {
                printf("\nD�tails du Produit :\n");
                printf("ID du Produit: %d\n", (*((*(categories+i)).products+j)).productID);
                printf("Nom du Produit: %s\n", (*((*(categories+i)).products+j)).name);
                printf("Description: %s\n", (*((*(categories+i)).products+j)).description);
                printf("Marque: %s\n", (*((*(categories+i)).products+j)).brand);
                printf("Prix: %.2f\n", (*((*(categories+i)).products+j)).price);
                printf("Quantit� en Stock: %d\n", (*((*(categories+i)).products+j)).stockQuantity);
                return;
            }
        }
    }
	printf("\n-------------------- NB --------------------\n");
    printf("Produit introuvable\n");
}

// Afficher toutes les cat�gories
void displayAllCategories(CATEGORY *categories, int categoryCount) 
{
	printf("\n*-------------------* Toutes les cat�gories *------------------*\n");
    for (int i = 0; i < categoryCount; i++) 
	{
        displayCategory(*(categories+i));
    }
    printf("\n-------------------------------------\n");    
}

// Afficher toutes les orders
void displayOrders(ORDER *orders, int orderCount) 
{
	printf("\n*-------------------* Toutes les orders *------------------*\n");
    for (int i = 0; i < orderCount; i++) 
	{
        displayOrder(*(orders+i));
    }
    printf("\n-------------------------------------\n");    
}

// Afficher une seul structure RESULT
void displayResult(RESULT result) {
    printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);
}

// Affichage du Liste RESULT
void displayResults(RESULT *resultArray, int numResults) {
    printf("\n-------------------- Liste des R�sultats --------------------\n");

    for (int i = 0; i < numResults; i++) {
        displayResult(*(resultArray+i) );
    }
    printf("\n-------------------------------------------------------------\n");
}

//---------------------- Fonctions pour tester l existance des ID --------------------//
int TestIDCat (int ID, CATEGORY **Tab, int * TabSize) 
{
    for (int i = 0; i < *TabSize; i++) {
        if ((*Tab+i)->categoryID == ID) 
		{
            return 1;
        }
    }
    return 0;
}
int TestIDPro (int ID, PRODUCT **Tab, int TabSize) 
{
    for (int i = 0; i < TabSize; i++) {
        if ((*Tab+i)->productID == ID) 
		{
            return 1;
        }
    }
    return 0;
}
int TestIDCli (int ID, CUSTOMER **Tab, int *TabSize) 
{
    for (int i = 0; i < *TabSize; i++) {
        if ((*Tab+i)->customerID == ID) 
		{
            return 1;
        }
    }
    return 0;
}

//------------------------------------ Result ------------------------------------------------------//

void fillResults(RESULT ***resultArray, ORDER *orders, int orderCount) {
    *resultArray = (RESULT **)malloc(orderCount * sizeof(RESULT*));
	if (resultArray==NULL)
	{
		exit(-2);
	}	
	else
	{
	    for (int i = 0; i < orderCount; i++) {
	    	(*resultArray)[i] = (RESULT *)malloc(sizeof(RESULT));
	        (*resultArray)[i]->orderID = orders[i].orderID;
	        (*resultArray)[i]->totalAmount = orders[i].totalAmount;
	    }
    }
    printf("remplissage avec succ�s :)");
    
    printf("\n--- Liste des Commandes  ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("Order ID: %d, \nTotal Amount: %.2f\n",  (*resultArray)[i]->orderID,  (*resultArray)[i]->totalAmount);
    }
}

// Fonction pour trouver l'index de la commande la plus ch�re
int findMostExpensiveOrderIndex(RESULT **resultArray, int orderCount) {
    if (orderCount == 0) {
        return -1; // Pas de commandes
    }

    int maxIndex = 0;
    float maxAmount = resultArray[0]->totalAmount;

    for (int i = 1; i < orderCount; i++) {
        if (resultArray[i]->totalAmount > maxAmount) {
            maxIndex = i;
            maxAmount = resultArray[i]->totalAmount;
        }
    }

    return maxIndex;
}

// Fonction pour afficher la commande la plus ch�re
void displayMostExpensiveOrder(RESULT **resultArray, int orderCount) {
    int mostExpensiveIndex = findMostExpensiveOrderIndex(resultArray, orderCount);

    if (mostExpensiveIndex != -1) {
        printf("\n--- Commande la plus ch�re ---\n");
        printf("Order ID: %d, \nTotal Amount: %.2f\n", resultArray[mostExpensiveIndex]->orderID, resultArray[mostExpensiveIndex]->totalAmount);
    } else {
        printf("\nAucune commande disponible\n");
    }
}


//
//// Fonction pour remplir le tableau dynamique de structures RESULT
//void fillResults(RESULT ***resultArray, ORDER *orders, int orderCount) {
//    *resultArray = (RESULT **)malloc(orderCount * sizeof(RESULT*));
//	if (resultArray==NULL)
//	{
//		exit(-2);
//	}	
//	else
//	{
//	    for (int i = 0; i < orderCount; i++) {
//	    	(*resultArray)[i] = (RESULT *)malloc(sizeof(RESULT));
//	        (*resultArray)[i]->orderID = orders[i].orderID;
//	        (*resultArray)[i]->totalAmount = orders[i].totalAmount;
////	    	*((*resultArray)+i) = (RESULT *)malloc(sizeof(RESULT));
////	        (*((*resultArray)+i))->orderID = (*(orders+i)).orderID;
////	        (*((*resultArray)+i))->totalAmount = (*(orders+i)).totalAmount;
//	    }
//    }
//    printf("\n-------------------- NB --------------------\n");
//    printf("remplissage avec succ�s :)");
//    
//    printf("\n----------------- Liste des Commandes  -----------------\n");
//    for (int i = 0; i < orderCount; i++) {
//        printf("Order ID: %d, \nTotal Amount: %.2f\n",  (*(*resultArray)+i)->orderID,  (*(*resultArray)+i)->totalAmount);
//    }
//}
//
//// Fonction pour trouver l'index de la commande la plus ch�re
//int findMostExpensiveOrderIndex(RESULT **resultArray, int orderCount) {
//    if (orderCount == 0) {
//        return -1; // Pas de commandes
//    }
//
//    int maxIndex = 0;
//    float maxAmount = resultArray[0]->totalAmount;
//
//    for (int i = 1; i < orderCount; i++) {
//        if ((*resultArray+i)->totalAmount > maxAmount) {
//            maxIndex = i;
//            maxAmount = (*resultArray+i)->totalAmount;
//        }
//    }
//
//    return maxIndex;
//}
//
//// Fonction pour afficher la commande la plus ch�re
//void displayMostExpensiveOrder(RESULT **resultArray, int orderCount) 
//{
//    int mostExpensiveIndex = findMostExpensiveOrderIndex(resultArray, orderCount);
//
//    if (mostExpensiveIndex != -1) 
//	{
//        printf("\n--- Commande la plus ch�re ---\n");
//        printf("Order ID: %d, \nTotal Amount: %.2f\n", resultArray[mostExpensiveIndex]->orderID, resultArray[mostExpensiveIndex]->totalAmount);
//    } else 
//	{
//    	printf("\n-------------------- NB --------------------\n");
//        printf("\nAucune commande disponible.\n");
//    }
//}

/*
void openfile(FILE **fs , const char *n)
{
	*fs= fopen(n, "wb+");
    if (*fs == NULL ) {
        printf("Erreur lors de l'ouverture de fichier.\n");
        exit(-1);
    }
}


// Fonction pour remplir les fichiers depuis la structure RESULT
void fillFiles(RESULT *resultArray, int orderCount, const char * fs_filename ,const char * fi_filename) {
    FILE *f,*fi;
    
	openfile( &f, fs_filename);

   	openfile( &fi, fi_filename);

	
	printf ("\nRemplissage de 2 fcihiers :\n");
    for (int i = 0; i < orderCount; i++) {
        fwrite(&resultArray[i].orderID, sizeof(int), 1, f);
        fwrite(&resultArray[i].totalAmount, sizeof(float), 1, f);
        int position = ftell(f);
        fwrite(&position, sizeof(int), 1, fi);
    }

    fclose(f);
    fclose(fi);
}

	// Fonction pour afficher le contenu des fichiers
void displayFiles(const char * fs_filename ,const char * fi_filename) {
    
   FILE *fs,*fi;
    
	openfile( &fs, fs_filename);

   	openfile( &fi, fi_filename);
    
    printf("\n---------------------- Contenu du fichier structure ------------------------\n");
    
    RESULT result;
    while (fread(&result, sizeof(RESULT), 1, fs) == 1) {
        printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);
    }

    printf("\n----------------------- Contenu du fichier index -----------------------\n");
    int position;
    while (fread(&position, sizeof(int), 1, fi) == 1) {
        printf("Position: %ld\n", position);
    }

    fclose(fs);
    fclose(fi);
}

// Fonction pour afficher et modifier une structure � une position donn�e
void displayAndModifyStructureAtPosition(int position,const char * fs_filename ,const char * fi_filename) {
    FILE * f, *indexf ;
    
    openfile(&f,fs_filename);
    openfile(&indexf,fi_filename);
    
    fseek(f, position * sizeof(RESULT), SEEK_SET);
    RESULT result;
    if (fread(&result, sizeof(RESULT), 1, f) == 1) {
        printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);

        // Modifier la structure si n�cessaire
        // ...

        // R��crire la structure � la position donn�e
        fseek(f, position * sizeof(RESULT), SEEK_SET);
        fwrite(&result, sizeof(RESULT), 1, f);
    } else {
        printf("Position invalide.\n");
    }

    fclose(f);
    fclose(indexf);
}
*/
//------------------------------------- Fonctions pour les fichier ----------------------------------------//
void addCustomer(CUSTOMER * c)
{
	printf("Entrez l'identifiant du client : ");
    scanf("%d", &c->customerID);
    printf("Entrez le nom du client : ");
    scanf("%s", c->name);
    printf("Entrez l'e-mail du client : ");
    scanf("%s", c->email);
    printf("Entrez le nombre d'order du client : ");
    scanf("%d", &c->nbrOrders);
}

CUSTOMER readcustomer (FILE *f)
{
    CUSTOMER c;
    fread(&c.customerID,sizeof(int),1,f);
    fread(&c.name,50*sizeof(char),1,f);
    fread(&c.email,50*sizeof(char),1,f);
    fread(&c.nbrOrders,sizeof(int),1,f);
    return c;
}
void createfile(FILE **fp,FILE **fi)
{
    *fp=fopen("Y:\\ENICarthage/cours/1st Sem/C/Projet_E_Commerce/file_res","wb+");
    if(!*fp) exit(-1);
    *fi=fopen("Y:\\ENICarthage/cours/1st Sem/C/Projet_E_Commerce/index_file_res","wb+");
    if(!*fi) exit(-1);
}

void fillfile(FILE *f,FILE *findex)
{	 
	CUSTOMER c;
	int x,stop=1;
    do
    {
	    addCustomer(&c);
	    if (stop == 0) break;
	    x=ftell(f);
	    fwrite(&x,sizeof(int),1,findex);
	    fwrite(&c.customerID,sizeof(int),1,f);
	    fwrite(&c.name,50*sizeof(char),1,f);
	    fwrite(&c.email,50*sizeof(char),1,f);
	    fwrite(&c.nbrOrders,sizeof(int),1,f);
		printf("\nAjouter un client (tapez 0 si vous voulez quitter)\n");
		scanf("%d",&stop);
    }while(stop!=0);
}

void displayfile(FILE *f,FILE *fi)
{
    CUSTOMER c ;
	int x;
    
	rewind(f);
	rewind(fi);
	
	printf("\nAffichage fichier index client\n");
    while(1)
    {
        fread(&x,sizeof(int),1,fi);
        if(feof(fi)) break;
        printf("\n%d",x);
    }
    rewind(fi);
    
    printf("\nAffichage fichier Client\n");
    while(1)
    {
        fread(&x,sizeof(int),1,fi);
        if(feof(fi)) break;
        fseek(f,x,0);
        c=readcustomer(f);
        displayCustomer(c);
        printf("\n");
    }
}

void modifyCustomer(FILE *f, FILE *fi, int position) {
    CUSTOMER c;

    // d�placer � la position dans fichier index
    fseek(fi, position * sizeof(int), SEEK_SET);
    fread(&position, sizeof(int), 1, fi);

    // D�placer � la position dans le fichier struct
    fseek(f, position, SEEK_SET);

    // Lire le client existant
    c = readcustomer(f);

    // Afficher les d�tails du client existant
    printf("\nDetails du client existant :\n");
    displayCustomer(c);

    // Modifier les d�tails du client
    addCustomer(&c);

    // Revenir � la position dans le fichier de donn�es
    fseek(f, position, SEEK_SET);

    // �crire les nouvelles donn�es du client
    fwrite(&c.customerID, sizeof(int), 1, f);
    fwrite(&c.name, 50 * sizeof(char), 1, f);
    fwrite(&c.email, 50 * sizeof(char), 1, f);
    fwrite(&c.nbrOrders, sizeof(int), 1, f);

    printf("\nClient modifi� avec succ�s.\n");
}




/*
// Function to search for a product by ID
PRODUCT* findProductByID(PRODUCT *products, int productCount, int productID) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == productID) {
            return &products[i];
        }
    }
    return NULL; // Product not found
}

// Function to search for a category by ID
CATEGORY* findCategoryByID(CATEGORY *categories, int categoryCount, int categoryID) {
    for (int i = 0; i < categoryCount; i++) {
        if (categories[i].categoryID == categoryID) {
            return &categories[i];
        }
    }
    return NULL; // Category not found
}

// Function to search for a customer by ID
CUSTOMER* findCustomerByID(CUSTOMER *customers, int customerCount, int customerID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == customerID) {
            return &customers[i];
        }
    }
    return NULL; // Customer not found
}

*/




//*****************************************************************************************************************************************************
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <locale.h> // pour appeler la fonction - setlocale -
//
//#include "MyFunctions.h"
//
//
//// Ajouter une cat�gorie
//void addCategory(CATEGORY **categories, int *categoryCount) {
//    CATEGORY newCategory;
//
//	do {
//    printf("\nEntrez l'id de la cat�gorie ( > 0 ): ");
//    scanf("%d", &newCategory.categoryID);
//    if (TestIDCat(newCategory.categoryID,categories,categoryCount) == 1 ) printf("\nDeja exist :)");
//    
//	} while ( (isdigit(newCategory.categoryID)) || (newCategory.categoryID <= 0) || (TestIDCat(newCategory.categoryID,categories,categoryCount) == 1 ) );
//	
//	
//	do{
//    printf("\nEntrez le nom de la cat�gorie (le premiere doit etre un caractere): ");
//    scanf("%s", newCategory.name);
//	} while( !isalpha(newCategory.name[0]) );
//
//    newCategory.products = NULL;
//    newCategory.numProducts = 0;
//
//    // Ajouter nouvelle cat�gorie 
//    *categories = (CATEGORY *)realloc(*categories, (*categoryCount + 1) * sizeof(CATEGORY));
//    (*categories)[*categoryCount] = newCategory;
//    (*categoryCount)++;
//	
//    printf("\n-------------------- NB --------------------\n");
//	printf("Cat�gorie ajout�e avec succ�s\n");
//}
//
//// Ajouter produit � une cat�gorie
//void addProduct(PRODUCT **products, CATEGORY *category) {
//    PRODUCT newProduct;
//   
//    do{
//    printf("Entrez l'identifiant du produit : ");
//    scanf("%d", &newProduct.productID);
//	} while ( (newProduct.productID <= 0) || (TestIDPro(newProduct.productID,products,category->numProducts) ==1 ) );
//	
//	do{
//    printf("Entrez le nom du produit : ");
//    scanf("%s", newProduct.name);
//	} while( !isalpha(newProduct.name[0]) );
//
//	do{
//    printf("Entrez la description du produit : ");
//    scanf("%s", newProduct.description);
//   	} while( !isalpha(newProduct.description[0]) );
//
//	do{
//    printf("Entrez la marque du produit : ");
//    scanf("%s", newProduct.brand);
//   	} while( !isalpha(newProduct.brand[0]) );
//     
//	do{
//    printf("Entrez le prix du produit : ");
//    scanf("%f", &newProduct.price);
//	} while(isdigit(newProduct.price) );
//
//	do{
//    printf("Entrez la quantit� en stock du produit : ");
//    scanf("%d", &newProduct.stockQuantity);	
//	} while(isdigit(newProduct.stockQuantity) );
//
//
//    // Ajouter nouvelle produit � la cat�gorie
//    category->products = (PRODUCT *)realloc(category->products, (category->numProducts + 1) * sizeof(PRODUCT));
//    category->products[category->numProducts] = newProduct;
//    category->numProducts++;
//
//	printf("\n-------------------- NB --------------------\n");
//    printf("Produit ajout� avec succ�s � la cat�gorie\n");
//}
//
//// Ajouter produit � une cat�gorie existante
//void addProductToCategory(PRODUCT **products, int *productCount, CATEGORY *categories, int categoryCount) {
//    int productID, quantity, categoryID;
//    CATEGORY *selectedCategory;
//    
//    
//	do{	 
//	// Demander � l'utilisateur de choisir une cat�gorie
//    printf("Entrez l'identifiant de la cat�gorie � laquelle ajouter le produit : ");
//    scanf("%d", &categoryID);
//	}while (findCategoryIndex(categoryID, categories, categoryCount)==-1);
//	
//    // V�rifier si la cat�gorie choisie existe
//    int existingCategoryIndex = findCategoryIndex(categoryID, categories, categoryCount);
//
//
//    if (existingCategoryIndex != -1) {
//        selectedCategory = &categories[existingCategoryIndex];
//	}
//    printf("\nEntrez l'identifiant du produit : ");
//    scanf("%d", &productID);
//
//    // V�rifier si le produit existe dans la cat�gorie
//    int existingProductIndex = findProductIndex(productID, categories->products, categories->numProducts);
//
//    if (existingProductIndex != -1) {
//        // Le produit existe, demander la quantit� � ajouter
//        printf("\nLe produit existe d�j� dans la cat�gorie. \nEntrez la quantit� � ajouter : ");
//        scanf("%d", &quantity);
//
//        // Ajouter la quantit� au stock existant
//        selectedCategory->products[existingProductIndex].stockQuantity += quantity;
//
//        printf("\n-------------------- NB --------------------\n");
//        printf("Quantit� ajout�e avec succ�s au produit existant dans la cat�gorie\n");
//    } else {
//        // Le produit n'existe pas, ajouter un nouveau produit
//        addProduct(products, selectedCategory);
//
//        printf("\n-------------------- NB --------------------\n");
//        printf("Nouveau produit ajout� � la cat�gorie\n");
//    }
//	
//}
//
//// Fonction utilitaire pour trouver l'index d'un produit dans un tableau
//int findProductIndex(int productID, PRODUCT *products, int numProducts) {
//    for (int i = 0; i < numProducts; i++) {
//        if (products[i].productID == productID) {
//            return i; // Retourne l'index du produit s'il est trouv�
//        }
//    }
//    return -1; // Retourne -1 si le produit n'est pas trouv�
//}
//// Fonction utilitaire pour trouver l'index d'une cat�gorie dans un tableau
//int findCategoryIndex(int categoryID, CATEGORY *categories, int categoryCount) {
//    for (int i = 0; i < categoryCount; i++) {
//        if (categories[i].categoryID == categoryID) {
//            return i; // Retourne l'index de la cat�gorie si elle est trouv�e
//        }
//    }
//    return -1; // Retourne -1 si la cat�gorie n'est pas trouv�e
//}
//
//
//// Ajouter un client
//void addCustomer(CUSTOMER **customers, int *customerCount) {
//    CUSTOMER newCustomer;
//
//	do{
//    printf("Entrez l'identifiant du client : ");
//    scanf("%d", &newCustomer.customerID);
//   	} while ((newCustomer.customerID <= 0) || (TestIDCli(newCustomer.customerID,customers,customerCount) == 1 ) );
//
//
//	do{
//    printf("Entrez le nom du client : ");
//    scanf("%s", newCustomer.name);
//   	} while(isdigit(newCustomer.name[0]) );
//
//
//    printf("Entrez l'e-mail du client : ");
//    scanf("%s", newCustomer.email);
//
//    newCustomer.nbrOrders = 0;
//
//    // Ajouter nouveau client 
//    *customers = (CUSTOMER *)realloc(*customers, (*customerCount + 1) * sizeof(CUSTOMER));
//    (*customers)[*customerCount] = newCustomer;
//    (*customerCount)++;
//
//	printf("\n-------------------- NB --------------------\n");
//    printf("Client ajout� avec succ�s\n");
//}
//
///*
//void removeProductFromCategory(CATEGORY *categories, int categoryCount, int categoryID, int productID) {
//    for (int i = 0; i < categoryCount; i++) {
//        if ((categories + i)->categoryID == categoryID) {
//            PRODUCT *products = (categories + i)->products;
//            int numProducts = (categories + i)->numProducts;
//
//            // Rechercher le produit dans la cat�gorie
//            int productIndex = findProductIndex(productID, products, numProducts);
//
//            if (productIndex != -1) {
//                // Supprimer le produit en d�calant les �l�ments restants
//                for (int j = productIndex; j < numProducts - 1; j++) {
//                    products[j] = products[j + 1];
//                }
//
//                // R�duire le nombre de produits dans la cat�gorie
//                (categories + i)->numProducts--;
//
//                printf("Produit supprim� avec succ�s de la cat�gorie.\n");
//            } else {
//                printf("Produit introuvable dans la cat�gorie.\n");
//            }
//            return;
//        }
//    }
//
//    printf("Cat�gorie introuvable.\n");
//}
//
//void removeCustomer(CUSTOMER *customers, int customerCount, int customerID) {
//    int customerIndex = findCustomerIndex(customerID, customers, customerCount);
//
//    if (customerIndex != -1) {
//        // Supprimer le client en d�calant les �l�ments restants
//        for (int i = customerIndex; i < customerCount - 1; i++) {
//            customers[i] = customers[i + 1];
//        }
//
//        printf("Client supprim� avec succ�s.\n");
//    } else {
//        printf("Client introuvable.\n");
//    }
//}
//
//void removeOrder(ORDER *orders, int orderCount, int orderID) {
//    int orderIndex = findOrderIndex(orderID, orders, orderCount);
//
//    if (orderIndex != -1) {
//        // Supprimer la commande en d�calant les �l�ments restants
//        for (int i = orderIndex; i < orderCount - 1; i++) {
//            orders[i] = orders[i + 1];
//        }
//
//        printf("Commande supprim�e avec succ�s.\n");
//    } else {
//        printf("Commande introuvable.\n");
//    }
//}
//
//*/
//// Function to calculate the total amount for a category
//float calculateCategoryTotal(CATEGORY *category) {
//    float total = 0.0;
//    for (int i = 0; i < category->numProducts; i++) {
//        total += (category->products+i)->price;
//    }
//    return total;
//}
////
////void createOrder(CUSTOMER *customer, CATEGORY *categories, ORDER **orders, int *orderCount, int categoryCount, int customerCount) 
////{
////    ORDER newOrder;
////    RESULT newResult ;
////    
////    int categoryAdded, clientAdded, quantity, productAdded,idc;
////
////    newOrder.categories = NULL;
////    newOrder.nbrCategories = 0;
////
////    printf("Entrez l'identifiant de la commande : ");
////    scanf("%d", &newOrder.orderID);
////    
////	newResult.orderID = newOrder.orderID;
////
////    printf("Entrez l'identifiant du client : ");
////    scanf("%d", &clientAdded);
////	/*
////    for (int i = 0; i < customerCount; i++) {
////        if ( (customer+i)->customerID == clientAdded) {
////            printf("\nID Client trouv� :)\n");
////            newOrder.customers = (customer+i);
////        }
////    }*/
////    
////    if (TestIDCli(clientAdded,&customer,customerCount) == 1 )
////    {
////        printf("\nID Client trouv� :)\n");
////        newOrder.customers = customer;
////    }
////    	
////
////    if (newOrder.customers == NULL) {
////        printf("\nClient introuvable :(, si vous pouvez ajouter un client tapez 1 sinon 0");
////		if (scanf("%d",&idc)==1)
////		    addCustomer(&customer,&customerCount); 
////			// Exit the function if client is not found
////    }
////
////    printf("\nEntrez l'ID de la cat�gorie : ");
////    scanf("%d", &categoryAdded);
////
////    CATEGORY *selectedCategory = NULL;
////
////    for (int i = 0; i < categoryCount; i++) {
////        if ( (categories+i)->categoryID == categoryAdded) {
////            printf("\nID Cat�gorie trouv� :)\n");
////            selectedCategory = categories+i;
////            break;
////        }
////    }
////            printf("\n----------------- Liste des Categories --------------------\n");
////
////	displayCategory(*selectedCategory);
////
////    if (selectedCategory == NULL) {
////        printf("\nCat�gorie introuvable\n");
////        return; // Exit the function if category is not found
////    }
////	
////	printf("\nEntrez l'ID du produit dans la cat�gorie : ");
////    scanf("%d", &productAdded);
////
////    PRODUCT *selectedProduct = NULL;
////
////   for (int i = 0; i < selectedCategory->numProducts; i++) {
////        if( (selectedCategory->products+i)->productID == productAdded) {
////            printf("\nID Produit trouv� dans la cat�gorie :)\n");
////            selectedProduct = (selectedCategory->products+i);
////            newOrder.nbrProducts++ ;
////            break;
////        }
////    }
////	//displayProduct(*selectedProduct);
////    if (selectedProduct == NULL) {
////        printf("\nProduit introuvable\n");
////        return; // Exit the function if the product is not found
////    }
////
////    printf("\nEntrez la quantit� : ");
////    scanf("%d", &quantity);
////
////	// Allocate memory for the categories array in the newOrder
////	newOrder.categories = (CATEGORY *)malloc(sizeof(CATEGORY));
////	newOrder.nbrCategories = 1;
////	
////	// Copy the selected category to the newOrder
////	memcpy(&newOrder.categories[0], selectedCategory, sizeof(CATEGORY));
////	
////	// Allocate memory for the products array in the newOrder
////	newOrder.categories[0].products = (PRODUCT *)malloc(quantity * sizeof(PRODUCT));
////	newOrder.categories[0].numProducts = quantity;
////	
////	// Copy the selected product to the newOrder
////	for (int i = 0; i < quantity; i++) {
////	    memcpy(&newOrder.categories[0].products[i], selectedProduct, sizeof(PRODUCT));
////	}
////	 
////	newOrder.totalAmount = selectedProduct->price * quantity;
////	displayOrder(newOrder) ;
////	//newResult.totalAmount = newOrder.totalAmount ;
////	
////    // R�allouer pour la nouvelle commande
////    *orders = (ORDER *)realloc(*orders, (*orderCount + 1) * sizeof(ORDER));
////    (*orders)[*orderCount] = newOrder;
////    *orderCount++;
////    
////    printf ("\nOrder Count : %d\n", *orderCount);
////    printf ("\n//////////////////////////\n");
////    displayOrder(*orders[0]) ;
////    /*
////    // R�allouer pour le tableau des r�sultats
////    *res = (RESULT *)realloc(*res, (*numres + 1) * sizeof(RESULT));
////    //(*res)[*numres] = newResult;
////    (*res + *numres)->orderID = newResult.orderID;
////	(*res + *numres)->totalAmount = newResult.totalAmount;
////
////	(*numres)++;
////*/
////	if (orders!= NULL){
////		newOrder.customers->nbrOrders++;
////		printf ("\nnbr Order client  : %d\n", newOrder.customers->nbrOrders);
////
////    	printf("\n-------------------- NB --------------------\n");
////    	printf("Commande cr��e avec succ�s\n");
////	}
////}
//
//void createOrder(CUSTOMER *customers, CATEGORY *categories, ORDER **orders, int *orderCount, int categoryCount, int customerCount) {
//    // Cr�er une nouvelle commande
//    ORDER newOrder;
//    newOrder.customers = NULL;
//    newOrder.categories = NULL;
//    newOrder.nbrProducts = 0;
//    newOrder.nbrCategories = 0;
//    newOrder.totalAmount = 0.0;
//
//    // Identifier le client
//    int clientID;
//    printf("Entrez l'identifiant du client : ");
//    scanf("%d", &clientID);
//
//    // Rechercher le client dans le tableau
//    for (int i = 0; i < customerCount; i++) {
//        if ( (customers+i)->customerID == clientID) {
//        	printf("\nID Client trouv� :)\n");
//            newOrder.customers = (customers+i);
//			//newOrder.customers = &customers[i];
//            break;
//        }
//    }
//
//    // V�rifier si le client a �t� trouv�
//    if (newOrder.customers == NULL) {
//        printf("Client introuvable, ajouter le avant de cr�e une commande :)\n");
//        return;
//    }
//
//    // Identifier la cat�gorie
//    int categoryID;
//    printf("Entrez l'identifiant de la cat�gorie : ");
//    scanf("%d", &categoryID);
//
//    // Rechercher la cat�gorie dans le tableau
//    CATEGORY *selectedCategory = NULL;
//    for (int i = 0; i < categoryCount; i++) {
//        if ((categories+i)->categoryID == categoryID) {
//            selectedCategory = categories+i;
//			//selectedCategory = &categories[i];
//            break;
//        }
//    }
//
//    // V�rifier si la cat�gorie a �t� trouv�e
//    if (selectedCategory == NULL) {
//        printf("Cat�gorie introuvable.\n");
//        return;
//    }
//
//    // Identifier le produit
//    int productID;
//    printf("Entrez l'identifiant du produit dans la cat�gorie : ");
//    scanf("%d", &productID);
//
//    // Rechercher le produit dans la cat�gorie
//    PRODUCT *selectedProduct = NULL;
//    for (int i = 0; i < selectedCategory->numProducts; i++) {
//        if ((selectedCategory->products+i)->productID == productID) {
//        	printf("\nProduit trouv� dans la cat�gorie :)\n");
//            //selectedProduct = &selectedCategory->products[i];
//            selectedProduct = (selectedCategory->products+i);
//            newOrder.nbrProducts+=1 ;
//            break;
//        }
//    }
//
//    // V�rifier si le produit trouv�
//    if (selectedProduct == NULL) {
//        printf("Produit introuvable.\n");
//        return;
//    }
//
//    // saisir la quantit�
//    int quantity;
//    printf("Entrez la quantit� : ");
//    scanf("%d", &quantity);
//
//    // Allouer de la m�moire pour la nouvelle commande
//    *orders = (ORDER *)realloc(*orders, (*orderCount + 1) * sizeof(ORDER));
//
//    // Initialiser les champs de la nouvelle commande
//    newOrder.orderID = *orderCount+1 ;  // Utilisation d'un ID simple ici, � adapter selon vos besoins
//    newOrder.categories = (CATEGORY *)malloc(sizeof(CATEGORY));
//    newOrder.categories[0] = *selectedCategory;
//    newOrder.nbrCategories = 1;
//
//    // Allouer de la m�moire pour les produits de la nouvelle commande
//    newOrder.categories[0].products = (PRODUCT *)malloc(quantity * sizeof(PRODUCT));
//    newOrder.nbrProducts = quantity;
//
//    // Copier le produit dans la commande
//    for (int i = 0; i < quantity; i++) {
//        newOrder.categories[0].products[i] = *selectedProduct;
//        newOrder.totalAmount += selectedProduct->price;
//    }
//
//    // Mettre � jour le nombre de commandes du client
//    newOrder.customers->nbrOrders++;
//
//    // Ajouter la nouvelle commande au tableau d'ordres
//    (*orders)[*orderCount] = newOrder;
//    (*orderCount)++;
//
//    printf("\n-------------------- NB --------------------\n");
//    printf("Commande cr��e avec succ�s\n");
//}
//
//
//// Afficher les info d'un produit
//void displayProduct(PRODUCT product) 
//{
//	
//    printf("ID du produit : %d\n", product.productID);
//    printf("Nom du produit : %s\n", product.name);
//    printf("Description : %s\n", product.description);
//    printf("Prix : %.2f\n", product.price);
//    printf("Quantit� en stock : %d\n", product.stockQuantity);
//    printf("Marque : %s\n", product.brand);
//    printf("\n-------------------------------------\n");
//}
//
//
//// Afficher les info d'une cat�gorie
//void displayCategory(CATEGORY category) 
//{	
//	
//    printf("ID de la cat�gorie : %d\n", category.categoryID);
//    printf("Nom de la cat�gorie : %s\n", category.name);
//    printf("Nombre de produit : %d\n", category.numProducts);
//	
//	printf("\n----------------- Liste des produits --------------------\n");
//    // Afficher les produits de la cat�gorie
//    for (int i = 0; i < category.numProducts; i++) 
//	{
//        displayProduct(*(category.products+i));
//    }
//    printf("\nLe montant totale du category est : %.2f", calculateCategoryTotal(&category));
//    printf("\n-------------------------------------\n");
//}
//
//// Afficher les info d un client
//void displayCustomer(CUSTOMER customer) 
//{
//	printf("\n----------------- Liste des Clients --------------------\n");
//    printf("ID du client : %d\n" , customer.customerID) ;
//    printf("Nom du client : %s\n" , customer.name) ;
//    printf("E-mail du client : %s\n" , customer.email) ;
//    printf("Nombre des commandes : %d\n" , customer.nbrOrders) ;
//    printf("\n-------------------------------------\n") ;
//}
//
//void displayOrder(ORDER order) 
//{
//	 printf("\n-------------------------------------\n");
//	 printf("ID de la commande : %d\n", order.orderID) ;
//	 printf("Client de la commande :%s\n", order.customers->name);
//	 printf("Nombres des categories: %d\n", order.nbrCategories);
//	 printf("Montant totale de la commande : %.2f\n" , order.totalAmount);
//	 printf("Nombre des produits dans la commande : %d" , order.nbrProducts);
//	 printf("\n-------------------------------------\n");
//}
//
////
////void displayOrders(ORDER *orders, int orderCount) {
////    printf("\n-------------------- Liste des Commandes --------------------\n");
////
////    for (int i = 0; i < orderCount; i++) {
////        printf("\nCommande ID: %d\n", orders[i].orderID);
////        printf("Client ID: %d\n", orders[i].customers->customerID);
////        printf("Montant total: %.2f\n", orders[i].totalAmount);
////
////        printf("Cat�gories dans la commande:\n");
////        printf("\n----------------- Liste des Categories --------------------\n");
////        for (int j = 0; j < orders[i].nbrCategories; j++) {
////            printf("   Cat�gorie ID: %d\n", orders[i].categories[j].categoryID);
////            printf("   Cat�gorie Nom: %s\n", orders[i].categories[j].name);
////            printf("   Produits dans la cat�gorie:\n");
////
////            for (int k = 0; k < orders[i].categories[j].numProducts; k++) {
////                printf("      Produit ID: %d\n", orders[i].categories[j].products[k].productID);
////                printf("      Produit Nom: %s\n", orders[i].categories[j].products[k].name);
////                // Ajouter d'autres d�tails du produit si n�cessaire
////            }
////        }
////
////        // Ajouter une nouvelle ligne pour une meilleure lisibilit� entre les commandes
////        printf("\n-------------------------------------------------------------\n");
////    }
////}
//
//
////void displayOrders(ORDER *orders, int orderCount) {
////    printf("\n-------------------- Liste des Commandes --------------------\n");
////
////    for (int i = 0; i < orderCount; i++) {
////        printf("\nCommande ID: %d\n", (orders+i)->orderID);
////        printf("Client ID: %d\n", (orders+i)->customers->customerID);
////        printf("Montant total: %.2f\n", (orders+i)->totalAmount);
////        printf("Nombres des categories: %.2d\n", (orders+i)->nbrCategories);
////        (orders+i)->
/////*
////        printf("Cat�gories dans la commande:\n");
////        printf("\n----------------- Liste des Categories --------------------\n");
////        for (int j = 0; j < (orders+i)->nbrCategories; j++) {
////        	displayCategory( ((orders+i)->categories)+j ) ;
////           // printf("   Cat�gorie ID: %d\n", orders[i].categories[j].categoryID);          
////        }
////*/
////    }
////    printf("\n-------------------------------------------------------------\n");
////}
//
//
//// Afficher toutes les cat�gories
//void displayAllCategories(CATEGORY *categories, int categoryCount) 
//{
//	printf("\n*-------------------* Toutes les cat�gories *------------------*\n");
//    for (int i = 0; i < categoryCount; i++) 
//	{
//        displayCategory(*(categories+i));
//    }
//    printf("\n-------------------------------------\n");    
//}
//
//void displayOrders(ORDER *orders, int orderCount) 
//{
//	printf("\n*-------------------* Toutes les orders *------------------*\n");
//    for (int i = 0; i < orderCount; i++) 
//	{
//        displayOrder(*(orders+i));
//    }
//    printf("\n-------------------------------------\n");    
//}
//
//// Afficher le contenu de la structure RESULT
//void displayResult(RESULT result) {
//    printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);
//}
//// Affichage des r�sultats
//void displayResults(RESULT *resultArray, int numResults) {
//    printf("\n-------------------- Liste des R�sultats --------------------\n");
//
//    for (int i = 0; i < numResults; i++) {
//        displayResult(*(resultArray+i) );
//    }
//
//    printf("\n-------------------------------------------------------------\n");
//}
//
//int TestIDCat (int ID, CATEGORY **Tab, int * TabSize) 
//{
//    for (int i = 0; i < *TabSize; i++) {
//        if ((*Tab+i)->categoryID == ID) 
//		{
//            return 1;
//        }
//    }
//    return 0;
//}
//int TestIDPro (int ID, PRODUCT **Tab, int TabSize) 
//{
//    for (int i = 0; i < TabSize; i++) {
//        if ((*Tab+i)->productID == ID) 
//		{
//            return 1;
//        }
//    }
//    return 0;
//}
//
//int TestIDCli (int ID, CUSTOMER **Tab, int *TabSize) 
//{
//    for (int i = 0; i < *TabSize; i++) {
//        if ((*Tab+i)->customerID == ID) 
//		{
//            return 1;
//        }
//    }
//    return 0;
//}
//
//// Fonction pour remplir le tableau dynamique de structures RESULT
//void fillResults(RESULT ***resultArray, ORDER *orders, int orderCount) {
//    *resultArray = (RESULT **)malloc(orderCount * sizeof(RESULT*));
//	if (resultArray==NULL)
//	{
//		exit(-2);
//	}	
//	else
//	{
//	    for (int i = 0; i < orderCount; i++) {
//	    	(*resultArray)[i] = (RESULT *)malloc(sizeof(RESULT));
//	        (*resultArray)[i]->orderID = orders[i].orderID;
//	        (*resultArray)[i]->totalAmount = orders[i].totalAmount;
//	    }
//    }
//    printf("remplissage avec succ�s :)");
//    
//    printf("\n--- Liste des Commandes  ---\n");
//    for (int i = 0; i < orderCount; i++) {
//        printf("Order ID: %d, \nTotal Amount: %.2f\n",  (*resultArray)[i]->orderID,  (*resultArray)[i]->totalAmount);
//    }
//}
//
//// Fonction pour trouver l'index de la commande la plus ch�re
//int findMostExpensiveOrderIndex(RESULT **resultArray, int orderCount) {
//    if (orderCount == 0) {
//        return -1; // Pas de commandes
//    }
//
//    int maxIndex = 0;
//    float maxAmount = resultArray[0]->totalAmount;
//
//    for (int i = 1; i < orderCount; i++) {
//        if (resultArray[i]->totalAmount > maxAmount) {
//            maxIndex = i;
//            maxAmount = resultArray[i]->totalAmount;
//        }
//    }
//
//    return maxIndex;
//}
//
//// Fonction pour afficher la commande la plus ch�re
//void displayMostExpensiveOrder(RESULT **resultArray, int orderCount) {
//    int mostExpensiveIndex = findMostExpensiveOrderIndex(resultArray, orderCount);
//
//    if (mostExpensiveIndex != -1) {
//        printf("\n--- Commande la plus ch�re ---\n");
//        printf("Order ID: %d, \nTotal Amount: %.2f\n", resultArray[mostExpensiveIndex]->orderID, resultArray[mostExpensiveIndex]->totalAmount);
//    } else {
//        printf("\nAucune commande disponible.\n");
//    }
//}
//
//
//// Exemple d'utilisation :
//// RESULT *resultArray;
//// fillResults(&resultArray, orders, orderCount);
//// displayMostExpensiveOrders(resultArray, orderCount);
//
//
////
////void createresut (RESULT **resultArray ,int numres ){
////	// Creation du tableau dynamique des pointeurs du struct RESULT 
////    resultArray = (RESULT **)realloc(resultArray, numres * sizeof(RESULT *));
////    if (resultArray == NULL) 
////	{ 
////		printf("\n!! Erreur d'allocation du m�moire !!\n");
////	}
////
////}
////
////void remplirres (RESULT **resultArray ,RESULT *res,int numres)
////{    // Remplir le tableau dynamique avec les adresses du structure RESULT
////    for (int i = 0; i < numres; i++) 
////	{
////        *(resultArray+i) = (res+i);
////    }
////}
//
//void openfile(FILE **fs , const char *n)
//{
//	*fs= fopen(n, "wb+");
//    if (*fs == NULL ) {
//        printf("Erreur lors de l'ouverture de fichier.\n");
//        exit(-1);
//    }
//}
//
//// Fonction pour remplir les fichiers depuis la structure RESULT
//void fillFiles(RESULT *resultArray, int orderCount, const char * fs_filename ,const char * fi_filename) {
//    FILE *f,*fi;
//    
//	openfile( &f, fs_filename);
//
//   	openfile( &fi, fi_filename);
//
//	
//	printf ("\nRemplissage de 2 fcihiers :\n");
//    for (int i = 0; i < orderCount; i++) {
//        fwrite(&resultArray[i].orderID, sizeof(int), 1, f);
//        fwrite(&resultArray[i].totalAmount, sizeof(float), 1, f);
//        int position = ftell(f);
//        fwrite(&position, sizeof(int), 1, fi);
//    }
//
//    fclose(f);
//    fclose(fi);
//}
//
//	// Fonction pour afficher le contenu des fichiers
//void displayFiles(const char * fs_filename ,const char * fi_filename) {
//    
//   FILE *fs,*fi;
//    
//	openfile( &fs, fs_filename);
//
//   	openfile( &fi, fi_filename);
//    
//    printf("\n---------------------- Contenu du fichier structure ------------------------\n");
//    
//    RESULT result;
//    while (fread(&result, sizeof(RESULT), 1, fs) == 1) {
//        printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);
//    }
//
//    printf("\n----------------------- Contenu du fichier index -----------------------\n");
//    int position;
//    while (fread(&position, sizeof(int), 1, fi) == 1) {
//        printf("Position: %ld\n", position);
//    }
//
//    fclose(fs);
//    fclose(fi);
//}
//
//// Fonction pour afficher et modifier une structure � une position donn�e
//void displayAndModifyStructureAtPosition(int position,const char * fs_filename ,const char * fi_filename) {
//    FILE * f, *indexf ;
//    
//    openfile(&f,fs_filename);
//    openfile(&indexf,fi_filename);
//    
//    fseek(f, position * sizeof(RESULT), SEEK_SET);
//    RESULT result;
//    if (fread(&result, sizeof(RESULT), 1, f) == 1) {
//        printf("Order ID: %d, Total Amount: %.2f\n", result.orderID, result.totalAmount);
//
//        // Modifier la structure si n�cessaire
//        // ...
//
//        // R��crire la structure � la position donn�e
//        fseek(f, position * sizeof(RESULT), SEEK_SET);
//        fwrite(&result, sizeof(RESULT), 1, f);
//    } else {
//        printf("Position invalide.\n");
//    }
//
//    fclose(f);
//    fclose(indexf);
//}
//
//void addCustomer(CUSTOMER * c)
//{
//	printf("Entrez l'identifiant du client : ");
//    scanf("%d", &c->customerID);
//    printf("Entrez le nom du client : ");
//    scanf("%s", c->name);
//    printf("Entrez l'e-mail du client : ");
//    scanf("%s", c->email);
//    printf("Entrez le nombre d'order du client : ");
//    scanf("%d", &c->nbrOrders);
//}
//void creerfichier(FILE **fp,FILE **fi)
//{
//    *fp=fopen("Y:\\ENICarthage/cours/1st Sem/C/Projet_E_Commerce/file_res","wb+");
//    if(!*fp) exit(-1);
//    *fi=fopen("Y:\\ENICarthage/cours/1st Sem/C/Projet_E_Commerce/index_file_res","wb+");
//    if(!*fi) exit(-1);
//}
//
//void remplirFichier(FILE *f,FILE *findex)
//{	 
//	CUSTOMER c;
//	int x,r=0;
//    do
//    {
//    if(r==2) break;
//    r++;
//    addCustomer(&c);
//    x=ftell(f);
//    fwrite(&x,sizeof(int),1,findex);
//    fwrite(&c.customerID,sizeof(int),1,f);
//    fwrite(&c.name,20*sizeof(char),1,f);
//    fwrite(&c.email,20*sizeof(char),1,f);
//    fwrite(&c.nbrOrders,sizeof(int),1,f);
//    }while(c.customerID!=0);
//}
//CUSTOMER readcustomer (FILE *f)
//{
//    CUSTOMER c;
//    fread(&c.customerID,sizeof(int),1,f);
//    fread(&c.name,20*sizeof(char),1,f);
//    fread(&c.email,20*sizeof(char),1,f);
//    fread(&c.nbrOrders,sizeof(int),1,f);
//    return c;
//}
//void displayFile(FILE *f,FILE *fi)
//{
//    CUSTOMER c ;
//	int x;
//    
//	rewind(f);
//	rewind(fi);
//	
//    printf("\nAffichage fichier Client\n");
//    while(1)
//    {
//        fread(&x,sizeof(int),1,fi);
//        if(feof(fi)) break;
//        fseek(f,x,0);
//        c=readcustomer(f);
//        displayCustomer(c);
//        printf("\n");
//    }
//	printf("\nAffichage fichier index client\n");
//    while(1)
//    {
//        fread(&x,sizeof(int),1,fi);
//        if(feof(fi)) break;
//        printf("\n%d",x);
//    }
//    rewind(fi);
//    
//}
//
//
//
///*
//// Function to search for a product by ID
//PRODUCT* findProductByID(PRODUCT *products, int productCount, int productID) {
//    for (int i = 0; i < productCount; i++) {
//        if (products[i].productID == productID) {
//            return &products[i];
//        }
//    }
//    return NULL; // Product not found
//}
//
//// Function to search for a category by ID
//CATEGORY* findCategoryByID(CATEGORY *categories, int categoryCount, int categoryID) {
//    for (int i = 0; i < categoryCount; i++) {
//        if (categories[i].categoryID == categoryID) {
//            return &categories[i];
//        }
//    }
//    return NULL; // Category not found
//}
//
//// Function to search for a customer by ID
//CUSTOMER* findCustomerByID(CUSTOMER *customers, int customerCount, int customerID) {
//    for (int i = 0; i < customerCount; i++) {
//        if (customers[i].customerID == customerID) {
//            return &customers[i];
//        }
//    }
//    return NULL; // Customer not found
//}
//
//*/
//

